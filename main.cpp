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

double Scal=10;

double trX=0.0,trY=0.0,dist=0.;//,trZ=0.0
char presse;
int anglex,angley,x,y,xold,yold;

//-************************************************************
//
//  Procedure avec mise en file des sommets des primitives
//
//-***********************************************************
void init();

Fonction f;
string nom_file;
//Fonction f = Fonction({-1,1,2,0},{-3,2,1});
//Fonction f = Fonction({-1,0,2,0},{-3,2,1});
//Fonction f = Fonction({1,0,0,0},{0,1,0});
//Fonction f = Fonction({1,1,0,0},{0,1,0});
//Fonction f = Fonction({1,0,0,0},{0,1,0});
//Fonction f = Fonction({1, -5, 3, 2}, {-1, 1, 0});
//Fonction f = Fonction({-6,1,2,1},{1,0,1});
//
int main(int argc,char **argv)
{
    /* initialisation de glut et creation de la fenetre */
//    f = nouvelle_entree();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Courbes de beziers");
    /* Initialisation d'OpenGL */
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0,0.0,0.0);
    glEnable( GL_POINT_SMOOTH );
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);


    glColor3f(0.0,0.0,0.0);
    //glEdgeFlag(GL_FALSE);
    glEdgeFlag(GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    // glEnable(GL_LIGHTING);
    glDisable(GL_LIGHTING);

    // menu du programe
    int choix; 
    cout << "Projet de mathématiques"<< endl;
    cout << "======================="<< endl;
    cout << "Choisir une fonction à traiter : " << endl;
    cout << "1 - f(x) = (2x² - 1)/(x² + 2x - 3)"<<endl;
    cout << "2 - f(x) = (x³ - 4x² - 11x + 16)/(x² + 2x - 3)"<<endl;
    cout << "3 - f(x) = (x² - x - 1)/(2x - 3)"<<endl;
    cout << "4 - f(x) = x²"<<endl;
    cout << "5 - Entrée manuelle"<<endl;
    cout << "# Votre choix => ";
    cin >> choix;

    switch(choix){
        case 1:
        f = Fonction({-1,0,2,0},{-3,2,1});
        break;
        case 2:
        f = Fonction({16,-11,-4,1},{-3,2,1});
        break;
        case 3:
        f = Fonction({-1,-1,1,0},{-3,2,0});
        break;
        case 4:
        f = Fonction({0,0,1,0},{1,0,0});
        break;
        case 5:
        f = nouvelle_entree();
        break;
    }
    cout << "Entrez maintenant le nom du fichier d'enregistrement : "; cin>> nom_file;

    /* enregistrement des fonctions de rappel */
    init();
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
   // glutIdleFunc(idle);

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

    glNewList(3,GL_COMPILE_AND_EXECUTE);  // Trace les asymptotes
    trace_asymptotes(f);
    glEndList();

    glNewList(4,GL_COMPILE_AND_EXECUTE);  //Trace la courbe de bézier
    if(f.degres[1] == 1){
        double x0 = -f.b[0] / f.b[1];
        trace_bezier(f, -HUGE_VAL, x0);
        trace_bezier(f, x0, HUGE_VAL);
    }else if (f.degres[1] == 2){
        if (delta(f.b) > 0) {
            array<double, 2> x = solveQ2S(f.b);
            trace_bezier(f, -HUGE_VAL, x[0]);
            trace_bezier(f, x[0], x[1]);
            trace_bezier(f, x[1], HUGE_VAL);
        } else if (delta(f.b) == 0) {
            double x0 = solveQ1S(f.b);
            trace_bezier(f, -HUGE_VAL, x0);
            trace_bezier(f, x0, HUGE_VAL);
        }else{
            trace_bezier(f, -HUGE_VAL, 0);
            trace_bezier(f, 0, HUGE_VAL);
        }
    } else{
        trace_bezier(f, -HUGE_VAL, 0);
        trace_bezier(f, 0, HUGE_VAL);
    }
    // trace_bezier(f, 0, 1);
    ofstream myfile;
    myfile.open (nom_file,myfile.app);
    myfile << f.record << "================= Fin traitement de la fonction ===================\n\n" << endl;
    myfile.close();

    glEndList();

    glNewList(5,GL_COMPILE_AND_EXECUTE);  //Tracer la courbe
    if(f.degres[1] == 1){
        double x0 = -f.b[0] / f.b[1];
        trace_courbe(f, -HUGE_VAL, x0 - eps);
        trace_courbe(f, x0 + eps, HUGE_VAL);
    }else if (f.degres[1] == 2){
        if (delta(f.b) > 0) {
            array<double, 2> x = solveQ2S(f.b);
            trace_courbe(f, -HUGE_VAL, x[0] - eps);
            trace_courbe(f, x[0], x[1] - eps);
            trace_courbe(f, x[1] + eps, HUGE_VAL);
        } else if (delta(f.b) == 0) {
            double x0 = solveQ1S(f.b);
            trace_courbe(f, -HUGE_VAL, x0 - eps);
            trace_courbe(f, x0 + eps, HUGE_VAL);
        }else{
            trace_courbe(f, -HUGE_VAL, 0);
            trace_courbe(f, 0, HUGE_VAL);
        }
    } else{
        trace_courbe(f, -HUGE_VAL, 0);
        trace_courbe(f, 0, HUGE_VAL);
    }

    glEndList();
}



