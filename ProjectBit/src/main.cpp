#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "system.h"
#include "input.h"

#define UNBROKEN_PAIRS

using namespace std;

int main(){
    // Initialize clock for timing
    std::clock_t start;
    start = std::clock();

    // Read and parse main input file
    Input* input = new Input("../input/O22.input");

    // Create the System class with given input
    // Initialize the hamiltonian matrix
    System* system = new System(input);

    // Run the diagonalization
    system->diagonalize();

    // Compute degeneracy, angular momentum and print results
    system->extractStates();
    system->printOutput();
    //system->saveOutputToFile();

    // Print info about run-time
    printf("\n\nTotal time elapsed: %f\n\n", (std::clock() - start ) / (double) CLOCKS_PER_SEC);

    return 0;
}
