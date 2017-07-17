#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "lanczos.h"

using namespace std;


//-------------------------------------------------------//
//-------------------------------------------------------//

int particle_number;        //Number of particles
int particle_count;         //Counts the number of particles which fit into the given orbitals
int number_of_orbitals;     //Solely the number of orbitals given in the input file
int dim = 1;                //Init of dimension variable

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
    //printf("%i %i %i %i \n", particle_number, number_of_orbitals, orbitals[0].j, orbitals[1].j);
    printf("Number of particles: %i\nNumber of positions: %i \n\n", particle_number, particle_count);
    
    if (particle_count < particle_number) {
        printf("ERROR: Model space too small, add more orbitals!\n");
        abort();
    }
    
}

//-------------------------------------------------------//
//-------------------------------------------------------//
/*
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
*/
//-------------------------------------------------------//
//-------------------------------------------------------//


void current_step(vector<int> working_array, vector<int> buffer_array, vector<vector<int>>& configuration_array, int particle_number, int particle_count, int index, int chosen);

void print_subsets(vector<int> working_array, vector<vector<int>>& configuration_array, int particle_number, int particle_count) {
    vector<int> buffer_array(particle_number);                   //Create buffer array
    current_step(working_array, buffer_array, configuration_array, particle_number, particle_count, 0, 0);
}

void current_step(vector<int> working_array, vector<int> buffer_array, vector<vector<int>>& configuration_array, int particle_number, int particle_count, int index, int chosen) {
    if (chosen == particle_number) {
    //for (int i = 0; i < particle_number; i++) {
    //    printf("%i\n", buffer_array[i]);
    //}
        configuration_array.push_back(buffer_array);        //Append current occupation to configuration_array
        //printf("\n");
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

void map_m(int particle_number, int number_of_orbitals, vector<vector<int>>& particles_in_orbital, vector<vector<int>> configuration_array, orbital orbitals[]) {
    for (int i = 0; i < configuration_array.size(); i++) {
        int counter = 0;                                        //Counts number of particles fitting in the individual orbitals
        vector<int> buffer(number_of_orbitals, 0);
        for (int k = 0; k < number_of_orbitals; k++) {
            for (int j = 0; j < particle_number; j++) {
                if (configuration_array[i][j] > counter && configuration_array[i][j] <= counter + orbitals[k].j + 1) {
                    buffer[k] = buffer[k] + 1;                  //Calculates how many particles occupy a given orbital
                }
            }
            counter = counter + orbitals[k].j + 1;
        }
        particles_in_orbital.push_back(buffer);
        //printf("%i %i %i\n", configuration_array[i][0], configuration_array[i][1], configuration_array[i][2]);
        //printf("%i %i \n", buffer[0], buffer[1]);
        //printf("%i %i \n", particles_in_orbital[i][0], particles_in_orbital[i][1]);
        //printf("\n");
    }
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void construct_mscheme(int number_of_orbitals, vector<vector<int>> particles_in_orbital, vector<vector<int>>& M_values, vector<vector<int>> configuration_array, orbital orbitals[]) {
    for (int i = 0; i < configuration_array.size(); i++) {
        
        int counter = 0;
        int counter2 = 0;
        vector<int> M_buffer(number_of_orbitals + 1, 0);
        
        for (int k = 0; k < number_of_orbitals; k++) {
            for (int j = 0; j < particles_in_orbital[i][k]; j++) {
                
                int pos = configuration_array[i][counter + j] - counter2;
                M_buffer[k] = M_buffer[k] - 2*(pos - 1) + orbitals[k].j;
            
            }
            counter = counter + particles_in_orbital[i][k];
            counter2 = counter2 + orbitals[k].j + 1;
            M_buffer[number_of_orbitals] = M_buffer[number_of_orbitals] + M_buffer[k];
        }
        M_values.push_back(M_buffer);
        printf("----------------------\n");
        printf("Configuration: %i %i \n", configuration_array[i][0], configuration_array[i][1]);
        printf("Part. in orb.: %i \n", particles_in_orbital[i][0]);
        printf("2M of orbital: %i \n", M_values[i][0]);
        printf("2M total:      %i\n", M_values[i][number_of_orbitals]);
        printf("\n");
    }
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void calc_J(int number_of_orbitals, vector<vector<int>> M_values, vector<vector<double>>& J_values) {
    double counter = 0;
    
    vector<double> J_buffer(M_values.size(), 0);
    for (int i = 0; i < M_values.size(); i++) {                 //M_values contains values of 2M, need to divide by 2
        J_buffer[i] = M_values[i][number_of_orbitals]/2.;       //Write total M of each configuration in separate vector, divide by 2 to get M
        if (J_buffer[i] > counter) {                            //Find largest M value and set it to int counter
            counter = J_buffer[i];
        }
        //printf("%.1f\n", J_buffer[i]);
    }
    printf("\nMaximum M: %.1f\n", counter);
    
    vector<double> J_buffer2(M_values.size()/2, 0);
    vector<double> J_buffer3(M_values.size()/2, 0);
    for (int i = 0; i < counter + 1; i++) {
        J_buffer2[i] = counter - i;                                                     //Fill in possible J values
        J_buffer3[i] = int(count(J_buffer.begin(), J_buffer.end(), counter - i));       //Determine how often an M value occurs
    }
    J_values.push_back(J_buffer2);
    
    vector<double> J_buffer4(M_values.size()/2, 0);
    for (int i = 0; i < counter + 1; i++) {
        J_buffer4[i] = J_buffer3[i] - J_buffer3[i - 1];         //Determine which J values exist, e.g. (31.3) in Alex' notes
    }
    J_values.push_back(J_buffer4);
    
    printf("%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n", J_values[0][0], J_values[0][1], J_values[0][2], J_values[0][3], J_values[0][4]);
    printf("%.0f\t%.0f\t%.0f\t%.0f\t%.0f\n", J_values[1][0], J_values[1][1], J_values[1][2], J_values[1][3], J_values[1][4]);
}

//-------------------------------------------------------//
//-------------------------------------------------------//

int main() {
    FILE* input;
    input = fopen("/Users/tobiasbeck/Documents/Konferenzen/TALENT/2017/Project/input.dat","r+");

    //Get input
    
    orbital orbitals[100];
    load_file(input, orbitals);
    //get_dimension(particle_number, particle_count);           //Not necessary anymore as configuration_array is enlarged on the fly
    
    //Init vectors

    vector<int> working_array(particle_count);                  //Initialize array to work on and fill it with possible positions from model space
    for (int i = 0; i < particle_count; i++) {                  //working_array=(1,2,3,...,particle_count)
        working_array[i] = i + 1;
        //printf("%i ", working_array[i]);
    }
    //printf("\n");
    vector<vector<int>> configuration_array;                    //Initialize array to be filled with solutions
    /* for (int i = 0; i < particle_count; i++) {
     configuration_array[i].resize(particle_count);
    }*/
    
    //Determine occupations
    
    printf("Determine occupations...\n\n");
    print_subsets(working_array, configuration_array, particle_number, particle_count);
    //printf("%i", configuration_array.size());
    
    //Build m-scheme
    
    printf("Build m-scheme...\n\n");
    vector<vector<int>> particles_in_orbital;
    
    map_m(particle_number, number_of_orbitals, particles_in_orbital, configuration_array, orbitals);
    //printf("%i %i %i\n", configuration_array[0][0], configuration_array[0][1], configuration_array[0][2]);
    //printf("%i %i %i\n", particles_in_orbital[0][0], particles_in_orbital[0][1], particles_in_orbital[4][1]);
    //printf("%i", particles_in_orbital[1][0]);
    vector<vector<int>> M_values;
    construct_mscheme(number_of_orbitals, particles_in_orbital, M_values, configuration_array, orbitals);
    
    //Determine possible J values
    
    vector<vector<double>> J_values;
    calc_J(number_of_orbitals, M_values, J_values);

    
    return 0;
}
