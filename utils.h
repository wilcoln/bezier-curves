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

const double dt = .00002;
const std::array<std::array<double, 2>, 2>  MCB1 = {1,0,
                                                    1,1};
const std::array<std::array<double, 3>, 3>  MCB2 = {1,0,0,
                                                    1,1./2,0,
                                                    1,1,1};
const std::array<std::array<double, 4>, 4>  MCB3 = {1,0,0,0,
                                                    1,1./3,0,0,
                                                    1, 2./3, 1./3, 0,
                                                     1,1,1,1};

std::array<double, 2> multiplie(const std::array<double, 2>& vect, const std::array<std::array<double, 2>, 2>& mat);
std::array<double, 3> multiplie(const std::array<double, 3>& vect, const std::array<std::array<double, 3>, 3>& mat);
std::array<double, 4> multiplie(const std::array<double, 4>& vect, const std::array<std::array<double, 4>, 4>& mat);

std::array<double, 3> multiplieParT(const std::array<double, 2>& vect);
std::array<double, 4> multiplieParT(const std::array<double, 3>& vect);
std::array<double, 4> calculPoids(Fonction const& f);
std::array<std::array<double,2>,4> pointsCtrl(Fonction const& f);
void openGL(double x, double y, double r0,double g0, double b0, double size);
void trace_segment(double x0, double y0,double x1, double y1, double red, double green, double blue, double size);
void tracer_courbe( const Fonction& fonction, double a, double b);
void tracer_asymptotes(const Fonction& fonction);
Fonction nouvelle_entree();

#endif //PROJECT_UTILS_H
