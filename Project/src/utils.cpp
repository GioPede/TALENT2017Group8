#include <cstdio>
#include <cstdlib>
#include <vector>

// simple funcition that return the total lines in a file
int countFileLines(const char* fileName){
    FILE* file;
    file = fopen(fileName, "r+");

    int lines = 0;
    char ch;
    while(!feof(file)){
        ch = fgetc(file);
        if(ch == '\n')
            lines++;
    }
    fclose(file);
    return lines;
}

// return binomial coefficient given n,k
int binomial(int n, int k){
    int res = 1;

    if(k > n - k)
        k = n - k;

    // Calculate value of [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]
    for(int i = 0; i < k; ++i){
       res *= (n - i);
       res /= (i + 1);
    }
    return res;
}

// nice style of J^pi for output formatting
const char* Jpi(double J, int pi){
    const char* string;
    switch (int(2*J)) {
    case 0:
        string = "0+";
        break;
    case 1:
        string = "1/2+";
        break;
    case 2:
        string = "1+";
        break;
    case 3:
        string = "3/2+";
        break;
    case 4:
        string = "2+";
        break;
    case 5:
        string = "5/2+";
        break;
    case 6:
        string = "3+";
        break;
    case 7:
        string = "7/2+";
        break;
    case 8:
        string = "4+";
        break;
    case 9:
        string = "9/2+";
        break;
    case 10:
        string = "5+";
        break;
    case 11:
        string = "11/2+";
        break;
    case 12:
        string = "6+";
        break;
    case 13:
        string = "13/2+";
        break;
    case 14:
        string = "7+";
        break;
    default:
        string = "undefined";
        break;
    }
    return string;
}
