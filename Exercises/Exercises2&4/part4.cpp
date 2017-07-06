#include <iostream>                         //Lesen und Schreiben der Bildschirmausgabe
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>                          //Lesen und Schreiben von Dateien
#include <sstream>
#include <vector>
#include <iterator>

#include "part2.h"
#include "part4.h"

using namespace std;

//-------------------------------------------------------//
//-------------------------------------------------------//

double calc_r86(double En6, double En8) {
    double r86 = En8 / En6;
    //printf("%f", r86);
    return r86;
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void load_file() {
    ifstream file("/Users/tobiasbeck/Documents/Konferenzen/TALENT/2017/Exercise1/toiee.dat");
    string str;
    
    FILE* output3;
    output3 = fopen("/Users/tobiasbeck/Documents/Konferenzen/TALENT/2017/Exercise1/j68_data.txt", "w+");
    FILE* output4;
    output4 = fopen("/Users/tobiasbeck/Documents/Konferenzen/TALENT/2017/Exercise1/r68.txt", "w+");
    cout << "Result files opened.\n";
    
    string myArray[13];                                         //String definieren
    string buffArray[13];                                       //Buffer-String

    while (getline(file, str)) {                                //Datei zeilenweise einlesen
        
        for(int i = 0; i < 13; ++i) {
            file >> myArray[i];                                 //Zeile in Array schreiben
        }
        
        if (myArray[3] == "6" && myArray[4] == "1" && myArray[5] == "1") {
            for(int i = 0; i < 13; ++i) {                       //Suche J=6 Zustand und schreibe ihn in Buffer
                buffArray[i] = myArray[i];                      //Übertrage aktuellen Array mit J=6 in Buffer
            }
        }
        
        else if (myArray[3] == "8" && myArray[4] == "1" && myArray[5] == "1" && myArray[1] == buffArray[1] && myArray[2] == buffArray[2]) {
            fprintf(output3, "%i\t%i\t%i\t%f\n", stoi(buffArray[1]), stoi(buffArray[2]), stoi(buffArray[3]), stod(buffArray[6]));
            fprintf(output3, "%i\t%i\t%i\t%f\n", stoi(myArray[1]), stoi(myArray[2]), stoi(myArray[3]), stod(myArray[6]));
            
            fprintf(output4, "%i\t%i\t%f\n", stoi(myArray[1]), stoi(myArray[2]), calc_r86(stod(buffArray[6]), stod(myArray[6])));
            //cout << myArray[3];           //Wenn passender J=8 im gleichen Kern gefunden, schreibe beides raus und auch das Verhältnis
        }
    }
    
    fclose(output3);
    fclose(output4);
    cout << "Result files closed.\n\n";
}
