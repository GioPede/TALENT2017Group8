#include <cstdio>
#include <cstdlib>
#include "modelSpace.h"

struct nuclide{
    int A;
    int Z;
    int N;
    float rms;
};

void skipLines(FILE* input, int n){
    for(int i = 0; i < n; i++)
        fscanf(input, "%*[^\n]\n");
}

void readNuclides(FILE* input, nuclide nuclides[], int N){
    for(int i = 0; i < N; i++){
        fscanf(input, "%i %i %i %f %*[^\n]\n", &nuclides[i].Z,  &nuclides[i].N, &nuclides[i].A, &nuclides[i].rms);
    }
}

int main(){
    // initialize the file reader
    FILE* input;
    input = fopen("rms13.dat", "r+");
    skipLines(input, 2);

    // initialize output
    FILE* output;
    output = fopen("output.dat", "w+");

    // set up
    int N = 2469;
    nuclide nuclides[N];
    readNuclides(input, nuclides, N);

    // set extremal values
    int minZ = 80;
    int maxZ = 81; //nuclides[N-1].Z;

    // loop over all Z values
    for(int z = minZ; z < maxZ; z++){
        for(int i = 0; i < N; i++){
            if(nuclides[i].Z == z){
                i++;
                fprintf(output, "#%i\n", z);
                while(nuclides[i].Z == z){
                    if(nuclides[i-1].N == nuclides[i].N - 1)
                        fprintf(output, "%i %f\n", nuclides[i].N, nuclides[i].rms - nuclides[i-1].rms );
                    i++;
                }
                fprintf(output, "\n\n\n\n");
                break;
            }
        }
    }

    return 0;
}
