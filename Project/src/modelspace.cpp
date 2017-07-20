#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include "modelspace.h"
#include "utils.h"

ModelSpace::ModelSpace(){

}

void ModelSpace::setupModelSpace(const char* inputFileName){
    // get size and open input
    int lines = countFileLines(inputFileName);
    energyLevels.resize(lines - 1);
    FILE* spInput;
    spInput = fopen(inputFileName, "r+");

	// get information about the core of the system
    fscanf(spInput, "%i %i %*[^\n]\n", &core.A,  &core.Z);

	// get information about the energy levels
    m_nSpStates = 0;
    for(int i = 0; i < energyLevels.size(); i++){
        fscanf(spInput, "%i %i %i %*[^\n]\n", &energyLevels[i].n,  &energyLevels[i].l, &energyLevels[i].two_j);
        m_nSpStates += energyLevels[i].two_j + 1;
	}
    fclose(spInput);
}

// only gives neutron partitions at this point
void ModelSpace::buildPartitions(int Z, int N, int M){

    // create sps list
    std::vector<int> spStates(m_nSpStates);                  //Initialize array to work on and fill it with possible positions from model space
    for (int i = 0; i < m_nSpStates; i++)                   //working_array=(1,2,3,...,particle_count)
        spStates[i] = i + 1;

    // create the buffer and start creating lists recursively
    std::vector<int> bufferArray(N);
    partitionTable.resize(0);
    findSublists(spStates, bufferArray, partitionTable, N, m_nSpStates, 0, 0, M);

    if(M == 0){
        printf("Number of Orbitals: %i\n", energyLevels.size());
        printf("Number of Single Particle States: %i\n", m_nSpStates);
    }
    m_nPartitions = partitionTable.size();

}

double ModelSpace::SPEnergy(int spState, std::vector<double> spsEnergies){
    // return the single particle energy of the orbital given the SPS
    return spsEnergies[orbital(spState) - 1];
}

int ModelSpace::orbital(int spState){
    // return the number of the orbital given the SPS
    int spStateSum = 1;
    for(int i = 0; i < energyLevels.size(); i++){
        for(int j = 0; j < energyLevels[i].two_j + 1; j++){
            if(spStateSum + j == spState)
                return i + 1;
        }
        spStateSum += energyLevels[i].two_j + 1;
    }
}

void ModelSpace::findSublists(std::vector<int> spStates, std::vector<int> bufferArray, std::vector<std::vector<int>>& configurationArray, int N, int nSpStates, int index, int chosen, int M) {
    // recursively build all possible slater determinants in an odometric order
    if (chosen == N) {
        if(N % 2 == 0 && computeM(bufferArray) == 0.0 + M)
            configurationArray.push_back(bufferArray);        //Append current occupation to configuration_array
        else if(N % 2 == 1 && computeM(bufferArray) == 0.5 + M)
            configurationArray.push_back(bufferArray);        //Append current occupation to configuration_array

        return;
    }
    if (index >= nSpStates) {                          //If end of array is reached, i.e. no more elements to append
        return;
    }

    bufferArray[chosen] = spStates[index];
    // call after having chosen the current indexed particle
    findSublists(spStates, bufferArray, configurationArray, N, nSpStates, index + 1, chosen + 1, M);
    // call after having discarded the current particle
    findSublists(spStates, bufferArray, configurationArray, N, nSpStates, index + 1, chosen, M);
}

bool ModelSpace::brokenPairs(int partition){
    // check if there are any broken pairs in the system
    for(int i = 0; i < partitionTable[partition].size(); i++){
            bool broken = 1;
        for(int j = i + 1; j < partitionTable[partition].size(); j++){
            if(orbital(partitionTable[partition][i]) == orbital(partitionTable[partition][j]) ){
                broken = 0;
                i++;
            }
        }
        // if a pair is broken, return true
        if(broken)
            return 1;
    }
    // return false if no pari is broken
    return 0;
}

double ModelSpace::computeM(std::vector<int> partition){
    double M = 0;
    for (int i = 0; i < partition.size(); i++) {
        int SPScounter = 0;

        for (int k = 0; k < energyLevels.size(); k++) {
            for (int j = 0; j < energyLevels[k].two_j + 1; j++) {
                int pos = SPScounter + j;
                if(partition[i] == pos + 1)
                    M += ( energyLevels[k].two_j / 2.0 ) - (pos - SPScounter);

            }
            SPScounter +=  energyLevels[k].two_j + 1;
        }
    }
    return M;
}
