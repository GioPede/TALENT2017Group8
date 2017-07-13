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

    // from the input file name, get the name of the system
    int startChar, endChar;
    for(int i = 256; i > 0; i--){
        if(inputFileName[i] == '.')
           endChar = i;
        if(inputFileName[i] == '/'){
           startChar = i + 1;
           break;
        }
    }
    for(int i = startChar; i < endChar; i++){
        m_systemName[i - startChar] = inputFileName[i];
    }
}

