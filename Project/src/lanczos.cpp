#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <armadillo>

using namespace std;

//-------------------------------------------------------//
//-------------------------------------------------------//

double norm(vector<double> inVector) {
    double norm = 0;
    for (int i = 0; i < inVector.size(); i++) {
        norm = norm + inVector[i]*inVector[i];
    }
    
    return sqrt (norm);
}

//-------------------------------------------------------//
//-------------------------------------------------------//

/*
void lanczos(double beta_tol, int k_max, vector<double> q1, vector<vector<int>> H, vector<double>& Alpha, vector<double>& Beta) {
    int k = 0;
    double alpha = 0;
    double beta = norm(q1);
    
    vector<double> qm(H.size(), 0);                         //Init qm = 0
    vector<double> r(H.size(), 0);                          //Init r
    vector<double> q(H.size(), 0);                          //Init q
    vector<double> Hq(H.size(), 0);
    
    for (int i = 0; i < H.size(); i++) {                    //Init r0 = q1
        r[i] = q1[i];
    }
    
    while (beta > beta_tol && k < k_max) {                  //Break conditions: beta approx 0 or number of iterations exceeded
        
        for (int i = 0; i < H.size(); i++) {
            qm[i]   = q[i];                                 //qm = q for old value q{k-1}
            q[i]    = r[i]/beta;                            //q = r/beta
        }
        printf("%f %f %f %f %f %f\n", q[0], q[1], q[2], q[3], q[4], q[5]);
        
        for (int i = 0; i < H.size(); i++) {
            for (int j = 0; j < H.size(); j++) {
                Hq[i]   = Hq[i] + H[i][j]*q[j];             //Calculate H*q and store it
            }
        }
        
        alpha = 0;
        for (int i = 0; i < H.size(); i++) {
            alpha   = alpha + q[i]*Hq[i];                   //Calculate alpha from stored H*q
        }
        
        for (int i = 0; i < H.size(); i++) {
            r[i]    = Hq[i] - alpha*q[i] - beta*qm[i];      //
        }
        
        beta = norm(r);
        k = k + 1;                                          //Simple counting for number of maximal iterations
        
        printf("alpha = %f \t beta = %f\n\n", alpha, beta);
        Alpha.push_back(alpha);
        Beta.push_back(beta);
    }
}
*/

//-------------------------------------------------------//
//-------------------------------------------------------//

void lanczos2(double beta_tol, int k_max, vector<double> x, vector<vector<int>> H, vector<double>& Alpha, vector<double>& Beta) {
    double alpha = 0;
    double beta = norm(x);
    
    vector<double> v(H.size(), 0);                          //Init v = 0
    vector<double> r(H.size(), 0);                          //Init r
    vector<double> q(H.size(), 0);                          //Init q
    
    for (int i = 0; i < H.size(); i++) {                    //Init r0 = q1
        q[i] = x[i]/beta;
    }
    
    for (int i = 0; i < H.size(); i++) {
        for (int j = 0; j < H.size(); j++) {
            r[i]   = r[i] + H[i][j]*q[j];                   //Calculate H*q and store it
        }
    }
    
    for (int i = 0; i < H.size(); i++) {
        alpha   = alpha + q[i]*r[i];                        //Calculate alpha from stored H*q
    }
    
    for (int i = 0; i < H.size(); i++) {
        r[i]   = r[i] - alpha*q[i];                         //Calculate alpha from stored H*q
    }
    
    beta = norm(r);
    
    for (int k = 0; k < k_max; k++) {                       //Loop till number of iterations exceeded
        
        for (int i = 0; i < H.size(); i++) {
            v[i]   = q[i];                                  //v = q for old value q{k-1}
            q[i]   = r[i]/beta;                             //q = r/beta
        }
        //printf("%f %f %f %f %f %f\n", q[0], q[1], q[2], q[3], q[4], q[5]);
        
        for (int i = 0; i < H.size(); i++) {
            r[i]   = 0;
            for (int j = 0; j < H.size(); j++) {
                r[i]   = r[i] + H[i][j]*q[j];               //Calculate H*q and store it
            }
            r[i] = r[i] - beta*v[i];
        }
        
        alpha = 0;
        for (int i = 0; i < H.size(); i++) {
            alpha   = alpha + q[i]*r[i];                    //Calculate alpha from stored H*q
        }
        
        for (int i = 0; i < H.size(); i++) {
            r[i]    = r[i] - alpha*q[i];      //
        }
        
        beta = norm(r);
        k = k + 1;                                          //Simple counting for number of maximal iterations
        
        printf("alpha = %f \t beta = %f\n\n", alpha, beta);
        Alpha.push_back(alpha);
        Beta.push_back(beta);
        
        if (beta < beta_tol) {                              //Break condition: beta smaller beta_tol
            break;
        }
    }
}

//-------------------------------------------------------//
//-------------------------------------------------------//

void diagonalize(vector<double> Alpha, vector<double> Beta) {
    arma::vec eigval;
    arma::mat H(Alpha.size(), Alpha.size());
    
    for (int i = 0; i < Alpha.size() - 1; i++) {                //Fill matrix
            H(i,i)      = Alpha[i];
            H(i,i+1)    = Beta[i];
            H(i+1,i)    = Beta[i];
        }
    H(Alpha.size(), Alpha.size()) = Alpha[Alpha.size()];        //Fill last diagonal element
    
    arma::eig_sym(eigval, H);
    eigval.print();
}

//-------------------------------------------------------//
//-------------------------------------------------------//

int run_lanczos() {
    vector<double> Alpha;
    vector<double> Beta;
    
    double beta_tol = 0.0001;
    int k_max       = 100;
    vector<double> qtest = {1, 1, 1, 1, 1, 1};
    
    vector<vector<int>> Matrix;
    vector<int> h1 = {0, 0, 0, 0, 0, 0};
    vector<int> h2 = {0, 1, 0, 0, 0, 0};
    vector<int> h3 = {0, 0, 2, 0, 0, 0};
    vector<int> h4 = {0, 0, 0, 3, 0, 0};
    vector<int> h5 = {0, 0, 0, 0, 4, 0};
    vector<int> h6 = {0, 0, 0, 0, 0, 100000};
    
    Matrix.push_back(h1);
    Matrix.push_back(h2);
    Matrix.push_back(h3);
    Matrix.push_back(h4);
    Matrix.push_back(h5);
    Matrix.push_back(h6);
    
    //norm(qtest);
    //printf("%f", norm(qtest));
    //lanczos(beta_tol, k_max, qtest, Matrix, Alpha, Beta);
    lanczos2(beta_tol, k_max, qtest, Matrix, Alpha, Beta);
    
    return 0;
}
