#include <cstdio>
#include <vector>
#include <armadillo>
#include "system.h"
#include "input.h"
#include "modelspace.h"
#include "utils.h"

System::System(Input* input){
    // assign the system name
    m_systemName = input->getSystemName();

    // create the model space container
    m_modelSpace = new ModelSpace();

    // get basic info about nuclide
    m_nuclideA = input->getNuclideA();
    m_nuclideZ = input->getNuclideZ();

    // initialize the model space from file
    m_modelSpace->setupModelSpace(input->getModelSpaceFile());

    // compute number of valence nucleons
    m_Z = m_nuclideZ - m_modelSpace->core.Z;
    m_N = m_nuclideA - m_modelSpace->core.A - m_Z;
    printf("Number of valence protons:  %i\n", m_Z);
    printf("Number of valence neutrons: %i\n", m_N);

    // create all possible slater determinants
    m_modelSpace->buildPartitions(m_Z, m_N);

    // initialize the interaction matrix elements
    m_matrixElements = readMatrixElements(input->getInteractionFile());

    // create the Hamiltionian matrix
    printf("\nBuilding Hamiltonian Matrix...\n");
    m_hamiltonianSize = m_modelSpace->getNumberOfPartitions();
    m_hamiltonian = buildHamiltionian();
    printf("Hamiltonian Built Succesfully\n");
}

void System::diagonalize(){
    printf("\nDiagonalizing...\n");

    // create armadillo containers
    arma::vec eigval;
    arma::mat eigvec;

    // create the hamiltonian armadillo copy
    arma::mat H(m_hamiltonian.size(), m_hamiltonian.size());
    for(int i = 0; i < m_hamiltonian.size(); i++)
        for(int j = i; j < m_hamiltonian.size(); j++){
            H(i,j) = m_hamiltonian[i][j];
            H(j,i) = m_hamiltonian[i][j];
        }
    arma::eig_sym(eigval, eigvec, H);

    // copy the results in a std::vector
    for(int i = 0; i < eigval.size(); i++)
        m_eigenvalues.push_back(eigval(i));
    printf("Diagonalization Completed\n");
}


void System::extractStates(){
    // compute the multiplicity of the states and assign J value
    double previous = m_eigenvalues[0];
    int count = 0;
    for(int i = 0; i < m_eigenvalues.size(); i++){
        if(m_eigenvalues[i] - previous <= 0.0001){
            // if the state is the same as the previous one increase the count
            count++;
            previous = m_eigenvalues[i];
        }
        else{
            // create the information about the state and its J value
            State state;
            state.E = previous;
            state.J = (count - 1.0) / 2.0;
            state.pi = 1;

            // add the state to the list
            m_states.push_back(state);

            // reset the counter
            count = 1;
            previous = m_eigenvalues[i];
        }
    }

    // add the last state info
    State state;
    state.E = previous;
    state.J = (count - 1.0) / 2.0;
    state.pi = 1;
    m_states.push_back(state);
}

void System::printOutput(){
    // some nicely formatted terminal output
    // basic info
    printf("\n--------------------------------------------------------------------------------\n");
    printf("A = %i     Z = %i\n", m_nuclideA, m_nuclideZ);
    printf("Ground State = %f\n\n", m_states[0].E);

    // list of levels and properties
    printf("  N\tEnergy (MeV)\t Ex (MeV)\tJ pi\n");
    for(int i = 0; i < m_states.size(); i++){
        printf("%i\t%f\t%f\t %s \n", i, m_states[i].E, m_states[i].E - m_states[0].E, Jpi(m_states[i].J,m_states[i].pi));
    }
}

void System::saveOutputToFile(){
    // open the output file
    char outputFileName[256];
    sprintf(outputFileName, "../output/%s.output", m_systemName);
    FILE* outputFile;
    outputFile = fopen(outputFileName, "w+");

    // some nicely formatted output
    // basic info
    fprintf(outputFile, "\n--------------------------------------------------------------------------------\n");
    fprintf(outputFile, "A = %i     Z = %i\n", m_nuclideA, m_nuclideZ);
    fprintf(outputFile, "Ground State = %f\n\n", m_states[0].E);
    fprintf(outputFile, "\n--------------------------------------------------------------------------------\n");

    // list of levels and properties
    fprintf(outputFile, "  N\tEnergy (MeV)\t Ex (MeV)\tJ pi\n");
    for(int i = 0; i < m_states.size(); i++){
        fprintf(outputFile, "%i\t%f\t%f\t %s \n", i, m_states[i].E, m_states[i].E - m_states[0].E, Jpi(m_states[i].J,m_states[i].pi));
    }
}



std::vector<MatrixElement> System::readMatrixElements(const char* inputFileName){
    std::vector<MatrixElement> meVector;
    // open the interaction file
    int nLines = countFileLines(inputFileName);
    FILE* interactionFile;
    interactionFile = fopen(inputFileName ,"r+");

    // bool for first line to be read
    bool spe = 0;

    // loop over the lines of the file
    for(int i = 0; i < nLines; i++){
        char line[1000];
        fgets(line, sizeof line, interactionFile);

        // ignore comment lines
        if(*line == '!') continue;

        // read first line into SPE vector (should be changed, no more than 4 orbitals are allowed)
        if(spe == 0){
            // create the vector for single particle energies
            m_spe.resize(m_modelSpace->energyLevels.size());

            // read the single particle energies of the orbitals
            int dumb;
            switch (m_spe.size()) {
                case 1:
                    sscanf(line, "%i %lf", &dumb, &m_spe[0]);
                    break;

                case 2:
                    sscanf(line, "%i %lf %lf", &dumb, &m_spe[0], &m_spe[1]);
                    break;

                case 3:
                    sscanf(line, "%i %lf %lf %lf", &dumb, &m_spe[0], &m_spe[1], &m_spe[2]);
                    break;

                case 4:
                    sscanf(line, "%i %lf %lf %lf %lf", &dumb, &m_spe[0], &m_spe[1], &m_spe[2], &m_spe[3]);
                    break;
            }
            spe = 1;
        }

        // fill the matrix element table from file
        else if(spe == 1){
            MatrixElement me;
            me.index.resize(4);
            sscanf(line, "%i %i %i %i %lf", &me.index[0], &me.index[1],
                                            &me.index[2], &me.index[3],
                                            &me.val);
            meVector.push_back(me);
        }
    }
    return meVector;
}


std::vector<std::vector<double>> System::buildHamiltionian(){
    // create the empty hamiltonian matrix
    std::vector<std::vector<double>> hamiltonian;

    // resize the hamiltonian matrix
    hamiltonian.resize(m_hamiltonianSize);
    for(int i = 0; i < m_hamiltonianSize; i++)
        hamiltonian[i].resize(m_hamiltonianSize);

    // if used for sd shell calculation scale the matrix elements by
    // (18/A)^0.3, otherwise do not scale
    double scalingFactor = 1;
    if(m_hamiltonianSize != 70)
        scalingFactor = pow( 18.0 / double(16 + m_N), 0.3);

    // loop over the elements of the matrix and compute the potential
    // if on the diagonal the h_0 term is also added
    for(int i = 0; i < m_hamiltonianSize; i++){
        for(int j = i; j < m_hamiltonianSize; j++){

#define UNBROKEN_PAIRS
#ifdef UNBROKEN_PAIRS
            // OPTIONAL: if working with the pair model, these two lines will set matrix
            // elements of states with broken pairs to 0
            if(m_hamiltonianSize == 70 && m_modelSpace->brokenPairs(i) && m_modelSpace->brokenPairs(j) )
                continue;
#endif

            // diagonal elements
            if(i == j){
                hamiltonian[i][j] = scalingFactor * computePotential(m_modelSpace->partitionTable[i], m_modelSpace->partitionTable[j]);
                hamiltonian[i][j] += computeSPEnergy(m_modelSpace->partitionTable[i]);
            }

            // off-diagonal elements
            else{
                hamiltonian[i][j] = scalingFactor * computePotential(m_modelSpace->partitionTable[i], m_modelSpace->partitionTable[j]);
                hamiltonian[j][i] = hamiltonian[i][j]; // the malitonian is symmetric!
            }
        }
    }
    return hamiltonian;
}

double System::computePotential(std::vector<int>& partA, std::vector<int>& partB){
    // count how many elements are common to the 2 partitions
    int sameCount = 0;
    for(int i = 0; i < m_N; i++){
        for(int j = 0; j < m_N; j++){
            if(partA[i] == partB[j]){
                sameCount++;
                break;
            }
        }
    }

    // exit if the two partitions differ by more than 2 elements
    if(m_N - sameCount > 2)
        return 0;

    // running value of the potential energy
    double pot = 0;

    // loop through the V_ijkl matrix elements
    for(int me = 0; me < m_matrixElements.size(); me++){
        // loop through partition A with two ordered indexes (i,j) i < j
        for(int i = 0; i < m_N; i++){
            if(partA[i] > m_matrixElements[me].index[0])
                break;
        for(int j = i + 1; j < m_N; j++){
            if(partA[j] > m_matrixElements[me].index[1])
                break;
        // loop through partition B with two ordered indexes (k,l) k < l
        for(int k = 0; k < m_N; k++){
            if(partB[k] > m_matrixElements[me].index[2])
                break;
        for(int l = k + 1; l < m_N; l++){
            if(partB[l] > m_matrixElements[me].index[3])
                break;
            // check if there exists a matrix element that connects the two partitions
            if( (partA[i] == m_matrixElements[me].index[0] &&
                 partA[j] == m_matrixElements[me].index[1])     ){

                if( (partB[k] == m_matrixElements[me].index[2] &&
                     partB[l] == m_matrixElements[me].index[3])   ){

                    // create the vectors for storing the reduced slater determinant
                    std::vector<int> reducedPartA;
                    std::vector<int> reducedPartB;

                    // compute the phase and populate the reduced vectors
                    double phase = 1.0;
                    for(int t = 0; t < m_N; t++){
                        // if there exists an element with the index from the matrix element,
                        // don't copy it and compute the phase
                        if(t == i){
                            if(t % 2 == 1)
                                phase *= -1;
                        }
                        else if(t == j){
                            if(t % 2 == 0)
                                phase *= -1;
                        }
                        // if it is different, than add it to the reduced vector
                        else
                            reducedPartA.push_back(partA[t]);

                        // if there exists an element with the index from the matrix element,
                        // don't copy it and compute the phase
                        if(t == k){
                            if(t % 2 == 1)
                                phase *= -1;
                        }
                        else if(t == l){
                            if(t % 2 == 0)
                                phase *= -1;
                        }
                        // if it is different, than add it to the reduced vector
                        else
                            reducedPartB.push_back(partB[t]);

                    }

                    // check if remaining vectors are the same
                    if(reducedPartA == reducedPartB)
                        // add the matrix element value to the potential
                        pot += phase * m_matrixElements[me].val;
                }
            }
        }}}}
    }

    // return the total potential
    return pot;
}

double System::computeSPEnergy(std::vector<int> part){
    // sum the single particle energies of all particles in the partition
    double sum = 0;
    for(int i = 0; i < m_N; i++){
        sum += m_modelSpace->SPEnergy(part[i], m_spe);
    }

    // return the total sum
    return sum;
}
