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

int main(int argc,char **argv)
{
    /* initialisation de glut et creation de la fenetre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Courbes de béziers");
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

//fonction ou les objets sont a definir
double f(double x){
    return x*x;
}
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
    tracer_courbe(f, -10, 10);
    glEndList();

    glNewList(4,GL_COMPILE_AND_EXECUTE);  // Trace les asymptotes
    double a[] = {0,0,0, 1};
    double b[] = {0,1,2};
    tracer_asymptotes(a, b);
    glEndList();

    glNewList(5,GL_COMPILE_AND_EXECUTE);  //Trace la courbe de bézier

    glEndList();
    glNewList(6,GL_COMPILE_AND_EXECUTE); //liste numero 6

    glEndList();


    cout<<"\n Voila, c'est fini"<<endl;

}


