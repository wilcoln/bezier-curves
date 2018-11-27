#include "utils.h"
void openGL(double x, double y, double r0,double g0, double b0, double size)
{
    glColor3f(r0,g0,b0);	//initialisation de la couleur
    glPointSize(size);	// initialisation de la taille
    glBegin(GL_POINTS);	// on trace un point
    glVertex2f(x,y);	// coordonnees du point
    glEnd();	// fin de glBegin
}

void trace_segment(double x0, double y0,double x1, double y1, double red, double green, double blue, double size)
{
    glColor3f(red,green,blue);//initialisation de la couleur
    glLineWidth(size); // initialisation de la taille
    glBegin(GL_LINES); // on trace un segment
    glVertex2f(x0,y0); // coordonnees du premier point
    glVertex2f(x1,y1); // coordonnees du dernier point
    glEnd(); // fin de glBegin
}
void tracer_courbe( double (* f)( double ), double a, double b){
    for(double t = a; t <= b; t+=.005)
        openGL(t,f(t), 0,0,1,1.);
}
void tracer_courbe( const Fonction& fonction, double a, double b){
    for(double t = a; t <= b; t+=.005)
        openGL(t,fonction.fn(t), 0,0,1,1.);
}
void tracer_asymptotes(const Fonction& fonction){
    std::array<short, 2> degres = fonction.degres;

}
Fonction nouvelle_entree(){
    std::array<double, 4> a{0};
    std::array<double, 3> b{0};
    std::cout << "<========== *************** Saisie d'une fonction ******************** =========>"<<std::endl;
    std::cout << "Entrez a0 a1 a2 et a3 successivement séparés d'un espace"<<std::endl;
    std::cin>> a[0] >> a[1] >> a[2] >> a[3];
    std::cout << "Entrez b0 b1 et b2 successivement séparés d'un espace"<<std::endl;
    std::cin>> b[0] >> b[1] >> b[2];
    return Fonction(a,b);
}