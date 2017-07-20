#include <cstdio>
#include <vector>
#include <cmath>
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

    for(int i = 0; i < m_modelSpace->partitionTable.size(); i++)
        m_modelSpace->computeM(m_modelSpace->partitionTable[i]);
    // initialize the interaction matrix elements
    m_matrixElements = readMatrixElements(input->getInteractionFile());


}

void System::runShell(){
    int i = 0;
    while("Still Working"){
        // create all possible slater determinants
        m_modelSpace->buildPartitions(m_Z, m_N, i);
        if(m_modelSpace->partitionTable.size() == 0)
            break;

        // create the Hamiltionian matrix
        m_hamiltonianSize = m_modelSpace->getNumberOfPartitions();
        m_hamiltonian = buildHamiltionian();

        // diagonalize
        diagonalize();

        // update energy levels list
        extractStates(i);
        i++;
    }

    // correct odd states
    if(m_N % 2 == 1)
        correctOddJ();
}

void System::diagonalize(){

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
    //H.save("O20.mat", arma::raw_ascii);
    arma::eig_sym(eigval, H);



    // copy the results in a std::vector
    m_eigenvalues.resize(eigval.size());
    for(int i = 0; i < eigval.size(); i++){
        m_eigenvalues[i] = eigval(i);
    }
}


void System::extractStates(int M){
    // compute the multiplicity of the states and assign J value

    // initial array
    if(M == 0){
        for(unsigned int i = 0; i < m_eigenvalues.size(); i++){
            State state;
            state.E = m_eigenvalues[i];
            state.J = 0;
            state.pi = 1;
            m_states.push_back(state);
        }
    }

    else{
        for(unsigned int i = 0; i < m_eigenvalues.size(); i++){
            for(unsigned int j = 0; j < m_states.size(); j++){
                if(fabs(m_eigenvalues[i] - m_states[j].E) < 0.0001){
                    m_states[j].J++;
                    break;
                }
            }
        }
    }

    /*
    double previous = m_eigenvalues[0];
    int count = 0;
    for(unsigned int i = 0; i < m_eigenvalues.size(); i++){
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
    m_states.push_back(state);*/
}

void System::correctOddJ(){
    for(int i = 0; i < m_states.size(); i++){
        m_states[i].J = (2 *
                         m_states[i].J + 1) / 2.0;
    }
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
    for(unsigned int i = 0; i < m_states.size(); i++){
        fprintf(outputFile, "%i\t%f\t%f\t %s \n", i, m_states[i].E, m_states[i].E - m_states[0].E, Jpi(m_states[i].J,m_states[i].pi));
    }
}


std::vector<MatrixElement> System::readMatrixElements(const char* inputFileName){
    // if used for sd shell calculation scale the matrix elements by
    // (18/A)^0.3, otherwise do not scale
    double scalingFactor = 1;
    if(m_hamiltonianSize != 70)
        scalingFactor = pow( 18.0 / double(16 + m_N), 0.3);

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

        // SO BAD!!!!
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
            me.val *= scalingFactor;
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

    for(int ket = 0; ket < m_hamiltonianSize; ket++){

//#define UNBROKEN_PAIRS
#ifdef UNBROKEN_PAIRS
        // OPTIONAL: if working with the pair model, these two lines will set matrix
        // elements of states with broken pairs to 0
        if(m_hamiltonianSize == 70 && m_modelSpace->brokenPairs(ket))
            continue;
#endif


        for(int bra = 0; bra < m_hamiltonianSize; bra++){
            hamiltonian[bra][ket] = 0;
            if(bra == ket)
                hamiltonian[bra][ket] += computeSPEnergy(m_modelSpace->partitionTable[ket]);
        }
    }


    for(int ket = 0; ket < m_hamiltonianSize; ket++){

#ifdef UNBROKEN_PAIRS
        // OPTIONAL: if working with the pair model, these two lines will set matrix
        // elements of states with broken pairs to 0
        if(m_hamiltonianSize == 70 && m_modelSpace->brokenPairs(ket))
            continue;
#endif

        for(unsigned int me = 0; me < m_matrixElements.size(); me++){

            // create a copy of the base vector
            std::vector<int> ketVector(m_modelSpace->partitionTable[ket]);
            double phase = 1.0;

            // a_1 operator
            for(int i = 0; i < m_N; i++){
                if(ketVector[i] == m_matrixElements[me].index[0]){
                    ketVector.erase(ketVector.begin() + i);
                    if(i % 2 == 1)
                        phase *= -1.0;
                }
            }

            if(ketVector.size() == m_N)
                continue;

            // a_2 operator
            for(int i = 0; i < m_N - 1; i++){
                if(ketVector[i] == m_matrixElements[me].index[1]){
                    ketVector.erase(ketVector.begin() + i);
                    if(i % 2 == 1)
                        phase *= -1.0;
                }
            }

            if(ketVector.size() == m_N - 1)
                continue;

            // a+_3 operator
            if(ketVector.size() == 0){
                ketVector.push_back(m_matrixElements[me].index[3]);
                phase *= -1.0;
            }
            else{

                for(int i = 0; i < m_N - 2; i++){
                    if(ketVector[i] == m_matrixElements[me].index[3]){
                        phase = 0.0;
                        break;
                    }
                    if(ketVector[i] > m_matrixElements[me].index[3]){
                        ketVector.insert(ketVector.begin() + i,  m_matrixElements[me].index[3]);
                        if(i % 2 == 0)
                            phase *= -1.0;
                        break;
                    }
                    if(i == m_N - 3){
                        ketVector.push_back(m_matrixElements[me].index[3]);
                        if(i % 2 == 1)
                            phase *= -1.0;
                    }
                }

            }

            if(ketVector.size() == m_N - 2)
                continue;

            // a+_4 operator
            for(int i = 0; i < m_N - 1; i++){
                if(ketVector[i] == m_matrixElements[me].index[2]){
                    phase = 0.0;
                    break;
                }
                if(ketVector[i] > m_matrixElements[me].index[2]){
                    ketVector.insert(ketVector.begin() + i, m_matrixElements[me].index[2]);
                    if(i % 2 == 0)
                        phase *= -1.0;
                    break;
                }
                if(i == m_N - 2){
                    ketVector.push_back(m_matrixElements[me].index[2]);
                    if(i % 2 == 1)
                        phase *= -1.0;
                }
            }
            if(ketVector.size() == m_N - 1)
                continue;

            // loop over possible bra slater determinants
            for(int bra = 0; bra < m_hamiltonianSize; bra++){
                if(ketVector == m_modelSpace->partitionTable[bra]){
                    hamiltonian[bra][ket] += phase  *  m_matrixElements[me].val;
                    if(bra != ket)
                        hamiltonian[ket][bra] += phase *  m_matrixElements[me].val;
                    break;
                }
            }
        }
    }
    return hamiltonian;
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
