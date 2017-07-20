#pragma once
#include <vector>
#include "Slater.hpp"

class System{
    public:
        System(class Input* input);
        void diagonalize();
        void extractStates();
        void printOutput();
        void saveOutputToFile();

private:
        int m_nuclideA;
        int m_nuclideZ;
        int m_N;
        int m_Z;
        int m_hamiltonianSize;

        const char* m_systemName;

        class ModelSpace* m_modelSpace;
        std::vector<double> m_spe;
        std::vector<struct MatrixElement> m_matrixElements;

        std::vector<manybody::Slater> m_slaterDeterm;

        std::vector<std::vector<double>> m_eigenvectors;
        std::vector<double> m_eigenvalues;
        std::vector<struct State> m_states;

        std::vector<struct MatrixElement> readMatrixElements(const char *inputFileName);
        double computeSPEnergy(int index);
};

