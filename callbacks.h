//
// Created by wilcoln on 26/11/18.
//

#ifndef PROJECT_CALLBACKS_H
#define PROJECT_CALLBACKS_H

#include "utils.h"
/* Prototype des fonctions */
void affichage();//  procedure a modifier en fonction de la scene
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
#endif //PROJECT_CALLBACKS_H
