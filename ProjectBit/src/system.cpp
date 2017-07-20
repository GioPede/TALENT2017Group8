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

    // create all possible slater determinants
    m_modelSpace->buildPartitions(m_Z, m_N, m_slaterDeterm);



    // initialize the interaction matrix elements
    m_matrixElements = readMatrixElements(input->getInteractionFile());

    // get the size of the system
    m_hamiltonianSize = m_modelSpace->getNumberOfPartitions();
}

void System::diagonalize(){
    printf("\nReturning the vector H|0>\n");
    arma::mat H(m_hamiltonianSize, m_hamiltonianSize);

    for(int i = 0; i < m_hamiltonianSize; i++){
        std::vector<double> result(m_hamiltonianSize, 0);
        // one-body component
        result[i] += computeSPEnergy(i);
/*
        // two-body components
        for(int j = 0; j < m_hamiltonianSize; j++){
            size_t ketDiff[2];
            size_t braDiff[2];
            size_t ketPhase[2];
            size_t braPhase[2];
            int n = 2;
            int nDiff = m_slaterDeterm[i].analyze_difference(m_slaterDeterm[j], ketDiff, braDiff, ketPhase, braPhase, n);


            // if the slated determinants differ by just 2 particles
            if(nDiff == 2){
                // loop over the matrix elements
                for(int k = 0; k < m_matrixElements.size(); k++){

                    if(ketDiff[0] + 1 == m_matrixElements[k].index[0]){
                        if(ketDiff[1] + 1 == m_matrixElements[k].index[1]){
                            if(braDiff[0] + 1 == m_matrixElements[k].index[2]){
                                if(braDiff[1] + 1 == m_matrixElements[k].index[3]){
                                    double phase = 1.0;
                                    if((ketPhase[0] + ketPhase[1] + braPhase[0] + braPhase[1]) % 2 == 1)
                                        phase *= -1;
                                    result[j] += m_matrixElements[k].val * phase;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            // if the determinants differ by just 1 particle
            else if(nDiff == 1){
                for(int k = 0; k < m_matrixElements.size(); k++){

                    for(int l = 0; l < ketDiff[0]; l++){
                        if(m_slaterDeterm[i].get(l) && l + 1 == m_matrixElements[k].index[0]){
                            if(ketDiff[0] + 1 == m_matrixElements[k].index[1]){


                                if(braDiff[0] + 1 == m_matrixElements[k].index[2]){

                                    if(m_slaterDeterm[j].get(l) && l + 1 == m_matrixElements[k].index[3]){
                                        double phase = 1.0;
                                        if((ketPhase[0] + braPhase[0]) % 2 == 1)
                                            phase *= -1;
                                        result[j] += m_matrixElements[k].val * phase;
                                    }
                                }



                                if(m_slaterDeterm[j].get(l) && l + 1 == m_matrixElements[k].index[2]){
                                    if(braDiff[0] + 1 == m_matrixElements[k].index[3]){
                                        double phase = 1.0;
                                        if((ketPhase[0] + braPhase[0]) % 2 == 1)
                                            phase *= -1;
                                        result[j] += m_matrixElements[k].val * phase;
                                    }
                                }
                            }
                        }
                    }

                    for(int l = ketDiff[0] + 1; l < 12; l++){
                        if(ketDiff[0] + 1 == m_matrixElements[k].index[0]){
                            if(m_slaterDeterm[i].get(l) && l + 1 == m_matrixElements[k].index[1]){
                                if(braDiff[0] + 1 == m_matrixElements[k].index[2]){
                                    if(m_slaterDeterm[j].get(l) && l + 1 == m_matrixElements[k].index[3]){
                                        double phase = 1.0;
                                        if((ketPhase[0] + braPhase[0]) % 2 == 1)
                                            phase *= -1;
                                        result[j] += m_matrixElements[k].val * phase;
                                    }
                                }
                                if(m_slaterDeterm[j].get(l) && l + 1 == m_matrixElements[k].index[2]){
                                    if(braDiff[0] + 1 == m_matrixElements[k].index[3]){
                                        double phase = 1.0;
                                        if((ketPhase[0] + braPhase[0]) % 2 == 0)
                                            phase *= -1;
                                        result[j] += m_matrixElements[k].val * phase;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // diagonal elements
            else if(nDiff == 0){
                for(int k = 0; k < m_matrixElements.size(); k++){
                    if(m_matrixElements[k].index[0] == m_matrixElements[k].index[2] &&
                       m_matrixElements[k].index[1] == m_matrixElements[k].index[3] ){
                        if(m_slaterDeterm[j].get(m_matrixElements[k].index[0] - 1) &&
                           m_slaterDeterm[j].get(m_matrixElements[k].index[1] - 1) ){
                            result[j] += m_matrixElements[k].val;
                        }
                    }
                }
            }
        }
*/
//        for(int j = 0; j < m_hamiltonianSize; j++){
//            printf("%f\n", result[j]);
//        }


        for(int j = 0; j < m_matrixElements.size(); j++){
            manybody::Slater ket = m_slaterDeterm[i];
            double me = m_matrixElements[j].val *
                        ket.annihilate(m_matrixElements[j].index[1] - 1) *
                        ket.annihilate(m_matrixElements[j].index[0] - 1) *
                        ket.create(m_matrixElements[j].index[2] - 1) *
                        ket.create(m_matrixElements[j].index[3] - 1);

            if( ket.count_between(0,12) != m_slaterDeterm[i].count_between(0,12) )
                continue;

            for(int k = 0; k < m_hamiltonianSize; k++){
                manybody::Slater bra = m_slaterDeterm[k];
                if(bra == ket)
                    result[k] += me;
            }
        }


        for(int j = 0; j < result.size(); j++)
            H(i,j) = result[j];

    }

    m_slaterDeterm[23].print();
    printf("\nDiagonalizing...\n");

    arma::vec eigval;
    arma::eig_sym(eigval, H);

    for(int i = 0; i < eigval.size(); i++){
        m_eigenvalues.push_back(eigval(i));
    }
    printf("Diagonalization Should Be Completed\n");
}


void System::extractStates(){
    // compute the multiplicity of the states and assign J value
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
    for(unsigned int i = 0; i < m_states.size(); i++){
        fprintf(outputFile, "%i\t%f\t%f\t %s \n", i, m_states[i].E, m_states[i].E - m_states[0].E, Jpi(m_states[i].J,m_states[i].pi));
    }
}


std::vector<MatrixElement> System::readMatrixElements(const char* inputFileName){
    double scalingFactor = pow( 18.0 / double(16 + m_N), 0.3);

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

double System::computeSPEnergy(int index){
    // sum the single particle energies of all particles in the partition
    double sum = 0;
    for(int i = 0; i < m_modelSpace->m_nSpStates; i++){
        if(m_slaterDeterm[index].get(i) == 1)
        sum += m_modelSpace->SPEnergy(i + 1, m_spe);
    }

    // return the total sum
    return sum;
}
