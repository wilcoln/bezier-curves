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
#define Pi 3.141592654

void openGL(double x, double y, double r0,double g0, double b0, double size);
void trace_segment(double x0, double y0,double x1, double y1, double red, double green, double blue, double size);
void tracer_courbe( double (*f)( double ), double a, double b);
void tracer_asymptotes(double a[], double b[]);

#endif //PROJECT_UTILS_H
