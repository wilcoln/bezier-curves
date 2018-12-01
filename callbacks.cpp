#include "utils.h"
#include "callbacks.h"

extern double Scal;

extern double trX,trY,dist;//,trZ=0.0
extern char presse;
extern int anglex,angley,x,y,xold,yold;
extern Fonction f;




void reshape(int x,int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //taille de la scene
    double  Ortho=-150;
    glOrtho(-Ortho,Ortho,-Ortho,Ortho,-Ortho,Ortho);// fenetre
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

void mouse(int button, int state,int x,int y)
{
    /* si on appuie sur le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        presse = 1; /* le booleen presse passe a 1 (vrai) */
        xold = x; /* on sauvegarde la position de la souris */
        yold=y;
    }
    /* si on relache le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
{
    if (presse) /* si le bouton gauche est presse */
    {
        /* on modifie les angles de rotation de l'objet
       en fonction de la position actuelle de la souris et de la derniere
       position sauvegardee */
        anglex=anglex+(x-xold);
        angley=angley+(y-yold);
        glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
}
void clavier(unsigned char touche,int x,int y)
{
    switch (touche)
    {
        case 'q' : /*la touche 'q' permet de quitter le programme */
            exit(0);
        case '+' :
            dist+=0.5;
            Scal=Scal+0.5;
            glutPostRedisplay();
            break;
        case '-' :
            dist-=0.5;
            Scal=Scal-0.5;
            glutPostRedisplay();
            break;
        case '6' : trX-=0.25;  glutPostRedisplay();  break;
        case '4' : trX+=0.25;  glutPostRedisplay();  break;
        case '8' : trY+=0.25;  glutPostRedisplay();  break;
        case '2' : trY-=0.25;  glutPostRedisplay();  break;
            //Nouvelle entrée
        case 'n' :
            f = nouvelle_entree();
            f.affiche();
            glutPostRedisplay();
            break;
    }
}

void affichage()
{
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0,0.0,dist);
    // Pour la 3D
    // glRotatef(-angley,1.0,0.0,0.0);
    //  glRotatef(-anglex,0.0,1.0,0.0);
    // Pour la 2D
    glRotatef(-anglex+angley,0.0,0.0,1.0);
    glScalef(Scal,Scal,Scal); // diminution de la vue de la scene
    glRotatef(180,0.0,1.0,0.0);
    glRotatef(180,1.0,0.0,0.0);
    glTranslatef(-trX,trY,0.);
    glCallList(1); // appel de la liste numero 1
    glCallList(2);   // appel de la liste numero 2
    glCallList(3); // appel de la liste numero 3
    glCallList(4);   // appel de la liste numero 4
    glCallList(5);   // appel de la liste numero 4
    glFlush();
    // On echange les buffers
    glutSwapBuffers();
}

