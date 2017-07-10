#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//-------------------------------------------------------//
//-------------------------------------------------------//

int particle_number;        //Number of particles
int particle_count;         //Counts the number of particles which fit into the given orbitals
int number_of_orbitals;     //Solely the number of orbitals given in the input file
int dim = 1;

struct orbital {
    int n;
    int l;
    int j;
};

//-------------------------------------------------------//
//-------------------------------------------------------//

void load_file(FILE* input, orbital orbitals[]) {
    fscanf(input, "%i %i%*[^\n]\n", &particle_number, &number_of_orbitals);
    for (int i = 0; i < number_of_orbitals; i++) {
        fscanf(input, "%i %i %i%*[^\n]\n", &orbitals[i].n, &orbitals[i].l, &orbitals[i].j);
        particle_count = particle_count + orbitals[i].j + 1;
    }
    //printf("%i %i %i %i %i \n", particle_number, number_of_orbitals, orbitals[2].n, orbitals[2].l, orbitals[2].j);
    printf("Number of particles: %i\nNumber of positions: %i \n\n", particle_number, particle_count);
    
    if (particle_count < particle_number) {
        printf("ERROR: Model space too small, add more orbitals!\n");
        abort();
    }
    
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void get_dimension(int particle_number, int particle_count) {       //Not necessary anymore as configuration_array is enlarged on the fly
    int buf = particle_number;
    
    if (particle_number < particle_count - particle_number) {
        buf = particle_count - particle_number;
    }
    
    for (int i = 0; i < buf; i++) {
        dim = dim * (particle_count - i) / (i + 1);
    }
    printf("Resulting dimension: %i\n", dim);
}

//-------------------------------------------------------//
//-------------------------------------------------------//


void current_step(vector<int> working_array, vector<int> buffer_array, vector<vector<int>>& configuration_array, int particle_number, int particle_count, int index, int chosen);

void print_subsets(vector<int> working_array, vector<vector<int>>& configuration_array, int particle_number, int particle_count) {
    vector<int> buffer_array(particle_number);                   //Create buffer array
    current_step(working_array, buffer_array, configuration_array, particle_number, particle_count, 0, 0);
}

void current_step(vector<int> working_array, vector<int> buffer_array, vector<vector<int>>& configuration_array, int particle_number, int particle_count, int index, int chosen) {
    if (chosen == particle_number) {
        /*for (int i = 0; i < particle_number; i++) {
            printf("%i", buffer_array[i]);
        }
        printf("  %i\n", buffer_array.size());
        return;*/
        configuration_array.push_back(buffer_array);        //Append current occupation to configuration_array
        return;
    }
    if (index >= particle_count) {                          //If end of array is reached, i.e. no more elements to append
        return;
    }
    
    buffer_array[chosen] = working_array[index];
    current_step(working_array, buffer_array, configuration_array, particle_number, particle_count, index + 1, chosen + 1);
    current_step(working_array, buffer_array, configuration_array, particle_number, particle_count, index + 1, chosen);
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void construct_mscheme() {
    
}

//-------------------------------------------------------//
//-------------------------------------------------------//

int main() {
    FILE* input;
    input = fopen("/Users/tobiasbeck/Documents/Konferenzen/TALENT/2017/Project/input.dat","r+");

    //Get input
    
    orbital orbitals[number_of_orbitals];
    load_file(input, orbitals);
    //get_dimension(particle_number, particle_count);           //Not necessary anymore as configuration_array is enlarged on the fly
    
    //Init vectors

    vector<int> working_array(particle_count);                  //Initialize array to work on and fill it with possible positions from model space
    for (int i = 0; i < particle_count; i++) {                  //working_array=(1,2,3,...,particle_count)
        working_array[i] = i + 1;
        //printf("%i ", working_array[i]);
    }
    printf("\n");
    vector<vector<int>> configuration_array;                    //Initialize array to be filled with solutions
    /* for (int i = 0; i < particle_count; i++) {
     configuration_array[i].resize(particle_count);
    }*/
    
    //Determine occupations
    
    print_subsets(working_array, configuration_array, particle_number, particle_count);
    
    return 0;
}
