#include <cstdlib>
#include <cstdio>
#include "input.h"

// read the main input file and assign the data
Input::Input(const char* inputFileName){
    // open *.input file and read the main data
    FILE* inputFile;
    inputFile = fopen(inputFileName, "r+");
    fscanf(inputFile, "%i %i %*[^\n]\n", &m_inputA, &m_inputZ);
    fscanf(inputFile, "%s %*[^\n]\n", &m_modelSpaceFile);
    fscanf(inputFile, "%s %*[^\n]\n", &m_interactionFile);
}

