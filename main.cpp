/*********************************************************/
/*                    openGL.cc                          */
/*********************************************************/
/*                                                       */
/*********************************************************/

#include <fstream>
#include <iostream>
#include "utils.h"
#include "callbacks.h"
using namespace std;

double Scal=36;

double trX=0.0,trY=0.0,dist=0.;//,trZ=0.0
char presse;
int anglex,angley,x,y,xold,yold;

//-************************************************************
//
//  Procedure avec mise en file des sommets des primitives
//
//-***********************************************************
void init();

Fonction f = Fonction({0,.5,.5,1},{0,1,1}); // fonction d'exemple
int main(int argc,char **argv)
{
    /* initialisation de glut et creation de la fenetre */
//    Fonction f = nouvelle_entree();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Courbes de beziers");
    /* Initialisation d'OpenGL */
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0,0.0,0.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);


    glColor3f(0.0,0.0,0.0);
    //glEdgeFlag(GL_FALSE);
    glEdgeFlag(GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    // glEnable(GL_LIGHTING);
    glDisable(GL_LIGHTING);


    /* enregistrement des fonctions de rappel */
    init();
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);


    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}






/****************************************************************
 **                                                            **
 **                    Affichage de  la scene                  **
 **                                                            **
 ****************************************************************/

void init()
{
    double xO=0.,yO=0.,xI=1.,yI=0.,xJ=0.,yJ=1.;
    glNewList(1,GL_COMPILE_AND_EXECUTE); //Trace le repère
    trace_segment(-GLUT_WINDOW_WIDTH/2,yO,GLUT_WINDOW_WIDTH/2,yO,0,0,0,1.0); // on trace [OI]
    trace_segment(xO,-GLUT_WINDOW_HEIGHT/2,xO,GLUT_WINDOW_HEIGHT/2,0,0,0,1.0);// on trace [OJ]
    glEndList();

    glNewList(2,GL_COMPILE_AND_EXECUTE);  // Place les points du repère
    openGL(xI,yI,0.,0.,0.,5); //I
    openGL(xJ,yJ,0.,0,0.,5); //J
    openGL(xO,yO,1.,0.,0.,7.);//O
    glEndList();

    glNewList(3,GL_COMPILE_AND_EXECUTE);  //Trace la courbe
    tracer_courbe(f, -GLUT_WINDOW_WIDTH/2, GLUT_WINDOW_WIDTH/2);
    glEndList();

    glNewList(4,GL_COMPILE_AND_EXECUTE);  // Trace les asymptotes
    tracer_asymptotes(f);
    glEndList();

    glNewList(5,GL_COMPILE_AND_EXECUTE);  //Placer points de ctrl
    std::array<std::array<double,2>,4> pts = pointsCtrl(f);
    std::array<double, 4> pds = calculPoids(f);
    for(auto pt: pts) {
        openGL(pt[0], pt[1], .5, .5, 0, 10);
        std::cout << pt[0] <<" "<< pt[1] << endl;
    }
    glEndList();
}



