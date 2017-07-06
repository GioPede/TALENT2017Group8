#include <iostream>                         //Lesen und Schreiben der Bildschirmausgabe
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>                          //Lesen und Schreiben von Dateien

#include "part2.h"
#include "part4.h"

using namespace std;

//-------------------------------------------------------//
//-------------------------------------------------------//

double binding_energy (int Z, int N) {
    double be = (15.49*(Z + N) - 17.23*pow(Z + N, 2./3.) - 0.697*(pow(Z, 2)/pow(Z + N, 1./3.)) - 22.6*(pow(N - Z, 2)/(N + Z)))/(N + Z);
    return be;
}
int ceiling_binding_energy (double be) {
    int ceiling_be = ceil(be);
    return ceiling_be;
}

int ceiling_binding_energy (int Z, int N) {
    int ceiling_be = ceil(binding_energy(Z, N));
    return ceiling_be;
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void get_limits (int &Z_low, int &Z_high, int &N_low, int &N_high) {
    
    
    printf("Z_low \t Z_high ");
    scanf("%i %i",&Z_low, &Z_high);
    printf("N_low \t N_high ");
    scanf("%i %i",&N_low, &N_high);
    printf("\n");
    
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void plot (int Z_low, int Z_high, int N_low, int N_high) {
    
    int table [Z_high - Z_low + 1][N_high - N_low + 1];             //Table definition
    
    
    for (int i = 0; i <= Z_high - Z_low; i++) {
        for (int j = 0; j <= N_high - N_low; j++) {
            
            double be = binding_energy(Z_low + i, N_low + j);
            table[i][j] = ceiling_binding_energy(be);
            
        }
    }
    
    //In File schreiben
    
    FILE* output;
    output = fopen("/Users/tobiasbeck/Documents/Konferenzen/TALENT/2017/Exercise1/avg_be.txt", "w+");
    cout << "Result file opened.\n";
    
    for (int i = Z_high - Z_low; i >= 0; i--) {
        for (int j = 0; j <= N_high - N_low; j++) {
            if (table[i][j] > 0) {
                fprintf(output, "%i ", table[i][j]);
            } else {
                fprintf(output, "%i ", 0);
            }
        }
        fprintf(output, "\n");
    }
    
    fclose(output);
    cout << "Result file closed.\n\n";
    
    //In Konsole ausgeben
    
    for (int i = Z_high - Z_low; i >= 0; i--) {
        printf("Z=%i \t | ", Z_low+i);
        for (int j = 0; j <= N_high - N_low; j++) {
            if (table[i][j] > 0) {
                printf("%i ", table[i][j]);
            } else {
                printf("%i ", 0);                                      //Bindungsenergie kleiner 0 durch 0 ersetzen
            }
        }
        printf("\n");
    }
 /*   printf("\nN=\t\t | ");
    if (N_high - N_low >= 10) {                                         //Korrektes Spacing Neutronenzahl
        for (int j = 1; j < 10; j++) {
            printf("%i  ",j);
        }
        for (int j = 10; j <= N_high - N_low + 1; j++) {
            printf("%i ",j);
        }
    } else {
        for (int j = 1; j <= N_high - N_low; j++) {
            printf("%i  ",j);
        }
    
    }
    printf("\n\n");
  */
    //Ende Konsolenausgabe
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void find_dripline(int Z_low, int Z_high, int N_low, int N_high) {
    
    FILE* output2;
    output2 = fopen("/Users/tobiasbeck/Documents/Konferenzen/TALENT/2017/Exercise1/dripline.txt", "w+");
    cout << "Result file opened.\n";
    
    for (int i = Z_low; i <= Z_high; i++) {                         //Suche, wann ein Wechsel von 0 nach !=0 oder andersrum stattfindet
        for (int j = N_low; j <= N_high; j++) {
            
            if (ceiling_binding_energy(i, j-1) < 0.001 && ceiling_binding_energy(i, j) > 0) {
                fprintf(output2, "(%i , %i) \t", i, j);
            }
            else if (ceiling_binding_energy(i, j) > 0 && ceiling_binding_energy(i, j+1) < 0.001) {
                fprintf(output2, "(%i , %i) \t", i, j);
            }
        }
        fprintf(output2, "\n");
    }
    
    fclose(output2);
    cout << "Result file closed.\n\n";
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void calc_single() {                                                //Bindungsenergie für einen Kern (Z,N) berechnen
    int Z_value, N_value;
    
    printf("Z, N = ");
    scanf("%i %i",&Z_value, &N_value);
    //printf("A = ");
    //scanf("%i",&A_value);
    
    double be = binding_energy(Z_value, N_value);
    //int ceiling_be = ceiling_binding_energy(be);
    printf("Using Z=%i and N=%i, the binding energy is %.2f MeV per nucleon.\n", Z_value, N_value, be);
}