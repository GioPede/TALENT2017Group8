#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include "modelspace.h"
#include "utils.h"
#include "Slater.hpp"

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
void ModelSpace::buildPartitions(int Z, int N, std::vector<manybody::Slater>& slaterDeterm){
    // resize the partition table to the size of the system
    m_nPartitions = binomial(m_nSpStates, N);

    // create sps list
    std::vector<int> spStates(m_nSpStates);                  //Initialize array to work on and fill it with possible positions from model space
    for (int i = 0; i < m_nSpStates; i++)                   //working_array=(1,2,3,...,particle_count)
        spStates[i] = i + 1;

    // create the array containing the partitions
    std::vector<std::vector<int>> partitionTable;

    // create the buffer and start creating lists recursively
    std::vector<int> bufferArray(N);
    findSublists(spStates, bufferArray, partitionTable, N, m_nSpStates, 0, 0);

    // fill the slater determinants array with the corresponding bit represantation
    slaterDeterm.resize(m_nPartitions);
    for(int i = 0; i < m_nPartitions; i++)
        for(int j = 0; j < N; j++)
            slaterDeterm[i].set(partitionTable[i][j] - 1);


    printf("Number of Orbitals: %i\n", energyLevels.size());
    printf("Number of Single Particle States: %i\n", m_nSpStates);
    printf("Number of Partitions: %i\n", partitionTable.size());

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

void ModelSpace::findSublists(std::vector<int> spStates, std::vector<int> bufferArray, std::vector<std::vector<int>>& configurationArray, int N, int nSpStates, int index, int chosen) {
    // recursively build all possible slater determinants in an odometric order
    if (chosen == N) {

        configurationArray.push_back(bufferArray);        //Append current occupation to configuration_array
        return;
    }
    if (index >= nSpStates) {                          //If end of array is reached, i.e. no more elements to append
        return;
    }

    bufferArray[chosen] = spStates[index];
    // call after having chosen the current indexed particle
    findSublists(spStates, bufferArray, configurationArray, N, nSpStates, index + 1, chosen + 1);
    // call after having discarded the current particle
    findSublists(spStates, bufferArray, configurationArray, N, nSpStates, index + 1, chosen);
}

