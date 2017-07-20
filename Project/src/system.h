#pragma once
#include <vector>

class System{
    public:
        System(class Input* input);
        void diagonalize();
        void extractStates(int M);
        void printOutput();
        void saveOutputToFile();
        void runShell();
        void correctOddJ();
private:
        int m_nuclideA;
        int m_nuclideZ;
        int m_N;
        int m_Z;
        int m_hamiltonianSize;

        const char* m_systemName;

        class ModelSpace* m_modelSpace;
        std::vector<std::vector<double>> m_hamiltonian;
        std::vector<double> m_spe;
        std::vector<struct MatrixElement> m_matrixElements;


        std::vector<std::vector<double>> m_eigenvectors;
        std::vector<double> m_eigenvalues;
        std::vector<struct State> m_states;

        std::vector<std::vector<double>> buildHamiltionian();
        std::vector<struct MatrixElement> readMatrixElements(const char *inputFileName);
        double computePotential(std::vector<int>& partA, std::vector<int>& partB);
        double computeSPEnergy(std::vector<int> part);
};

