//
// Created by wilcoln on 26/11/18.
//
#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H
/* inclusion des fichiers d'en-tete Glut */
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Fonction.h"

const double dt = .005;

void openGL(double x, double y, double r0,double g0, double b0, double size);
void trace_segment(double x0, double y0,double x1, double y1, double red, double green, double blue, double size);
void tracer_courbe( const Fonction& fonction, double a, double b);
void tracer_asymptotes(const Fonction& fonction);
Fonction nouvelle_entree();

#endif //PROJECT_UTILS_H
