//
// Created by wilcoln on 26/11/18.
//
#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H
/* inclusion des fichiers d'en-tete Glut */
#include <GL/glut.h>
#include <cmath>
#include <array>
#include <vector>
#include "Fonction.h"
using namespace std;
const double dt = .01;
const double eps = .001;
const vector<vector<double>>  MCB1 = {{1,0},
                                           {1,1}};
const vector<vector<double>>  MCB2 = {{1,0,0},
                                           {1,1./2,0},
                                           {1,1,1}};
const vector<vector<double>>  MCB3 = {{1,0,0,0},
                                           {1,1./3,0,0},
                                           {1, 2./3, 1./3, 0},
                                           {1,1,1,1}};

const vector<vector<vector<double>>>  MCB = {MCB1,MCB2, MCB3};
double delta(vector<double> a);
array<double, 2> solveQ2S(vector<double> a);
double solveQ1S(vector<double> a);
vector<double> canonic2bezier(vector<double> vect, int degre);
vector<double> prodMatVec(const vector<vector<double>>& mat, const vector<double>& vect , int degre);
vector<double> foisT(const vector<double> &vect);
unsigned int combinaison( unsigned int n, unsigned int k );
double B(int i, int n, double x);
void openGL(double x, double y, double r0,double g0, double b0, double size);
void trace_segment(double x0, double y0,double x1, double y1, double red, double green, double blue, double size);
void trace_courbe(const Fonction &fonction, double a, double b);
void trace_bezier(Fonction &fonction, double a, double b);
int degreBezier(const Fonction& fonction);
void trace_asymptotes(Fonction &fonction);
Fonction nouvelle_entree();

#endif //PROJECT_UTILS_H
