#include <vector>
#include "utils.h"

class ModelSpace{
    public:
        ModelSpace();
        void setupModelSpace(const char* inputFileName);
        void buildPartitions(int Z, int N);
        int getNumberOfPartitions() { return m_nPartitions; }
        std::vector<EnergyLevel> energyLevels;
        std::vector<std::vector<int>> partitionTable;
        Core core;
        int m_nSpStates;
        int m_nPartitions;
        double SPEnergy(int spState, std::vector<double> spsEnergies);
        int orbital(int spState);
        bool brokenPairs(int partition);
private:
        void findSublists(std::vector<int> spStates, std::vector<int> bufferArray, std::vector<std::vector<int> > &configurationArray, int N, int nSpStates, int index, int chosen);
};
