#pragma once
#include <vector>

int countFileLines(const char* fileName);
int binomial(int n, int k);
const char* Jpi(double J, int pi);


struct EnergyLevel{
    int n;
    int l;
    int two_j;
};

struct Core{
    int A;
    int Z;
};

struct State{
    double J;
    int pi;
    double E;
};
