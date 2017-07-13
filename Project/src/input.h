#pragma once

class Input{
    public:
        Input(const char* inputFileName);
        int getNuclideA() { return m_inputA; }
        int getNuclideZ() { return m_inputZ; }
        const char* getInteractionFile() { return m_interactionFile; }
        const char* getModelSpaceFile() { return m_modelSpaceFile; }
    private:
        int m_inputA, m_inputZ;
        char m_systemName[256];
        char m_interactionFile[256];
        char m_modelSpaceFile[256];
};
