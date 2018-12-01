#include "utils.h"

double delta(std::array<double,3> a){
    return a[1]*a[1] - 4*a[2]*a[0];
}
std::array<double, 2> solveQ2S(std::array<double,3> a){
    double D = delta(a);
    std::array<double, 2> result = { (-a[1] + D)/(2*a[2]), (-a[1] - D)/(2*a[2])  };
    return result;
}
double solveQ1S(std::array<double, 3> a){
    return -a[1]/(2*a[3]);
}
std::array<double, 2> multiplie(const std::array<double, 2>& vect, const std::array<std::array<double, 2>, 2>& mat){
    return {(vect[0]*mat[0][0] + vect[1]*mat[0][1]), (vect[0]*mat[1][0] + vect[1]*mat[1][1]) };
}
std::array<double, 3> multiplie(const std::array<double, 3>& vect, const std::array<std::array<double, 3>, 3>& mat){
    return {(vect[0]*mat[0][0] + vect[1]*mat[0][1] + vect[2]*mat[0][2]), (vect[0]*mat[1][0] + vect[1]*mat[1][1] + vect[2]*mat[1][2]), (vect[0]*mat[2][0] + vect[1]*mat[2][1] + vect[2]*mat[2][2])};
}

std::array<double, 4> multiplie(const std::array<double, 4>& vect, const std::array<std::array<double, 4>, 4>& mat) {
    std::array<double, 4> result{0};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            result[i] += vect[j] * mat[i][j];
        }
    }

    return result;

}

std::array<double, 3> multiplieParT(const std::array<double, 2>& vect){
    return {0,vect[0],vect[1]};
}
std::array<double, 4> multiplieParT(const std::array<double, 3>& vect){
    return {0,vect[0],vect[1],vect[2]};
}
std::array<double, 4> calculPoids(Fonction const& f){
    return multiplie({f.b[0],f.b[1],f.b[2], 0}, MCB3);
}
std::array<std::array<double,2>,4> pointsCtrl(Fonction const& f){
    std::array<double, 4> tQB = multiplieParT(f.b);
    std::array<double, 4> PB = multiplie(f.a,MCB3);
    std::array<double, 4> pds = calculPoids(f);
    return {tQB[0]/pds[0], PB[0]/pds[0],
            tQB[1]/pds[1], PB[1]/pds[1],
            tQB[2]/pds[2], PB[2]/pds[2],
            tQB[3]/pds[3], PB[3]/pds[3]};


}
/*std::array<double, 4> poids(Fonction const& f){
    std::array<double, 4> b{f.b[0],f.b[1],f.b[2],0};
    return multiplie(b, MCB3);
}*/
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
void tracer_courbe(const Fonction& fonction, double a, double b){
    double x;
    if(b == HUGE_VAL){
        for(double t = 0; t <= 1; t+=dt){
            x = a - 1 + 1/t;
            openGL(x,fonction.fn(x), 0,0,1,1);
        }
    }else if(a == -HUGE_VAL){
        for(double t = 0; t <= 1; t+=dt){
            x = -1/t + b + 1;
            openGL(x,fonction.fn(x), 0,0,1,1);
        }
    }else{
        for(double t = 0; t <= 1; t+=dt){
            x = a + t*(b-a);
            openGL(x,fonction.fn(x), 0,0,1,1);
        }
    }

        //trace_segment(t, fonction.fn(t), t + dt, fonction.fn(t + dt), 0,0,1,1);
}
void tracer_asymptotes(const Fonction& f){
    double x0,y0,l,r;
    double alpha, beta;
    std::array<double, 2> x;
    switch(f.getDegres()){
        case _0_0:
            std::cout << "Pas d'asymptotes"<<std::endl;
            break;
        case _0_1:
            x0 = -f.b[0]/f.b[1];
            trace_segment(x0, -GLUT_WINDOW_HEIGHT/2,x0, GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            break;
        case _0_2:
            if(delta(f.b) > 0){
                x = solveQ2S(f.b);
                trace_segment(x[0], -GLUT_WINDOW_HEIGHT/2,x[0], GLUT_WINDOW_HEIGHT/2,1,0,0,1);
                trace_segment(x[1], -GLUT_WINDOW_HEIGHT/2,x[1], GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            }else if (delta(f.b) == 0){
                x0 = solveQ1S(f.b);
                trace_segment(x0, -GLUT_WINDOW_HEIGHT/2,x0, GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            }
            break;
        case _1_0:
            std::cout << "Pas d'asymptotes"<<std::endl;
            break;
        case _1_1:
            x0 = -f.b[0]/f.b[1];
            trace_segment(x0, -GLUT_WINDOW_HEIGHT/2,x0, GLUT_WINDOW_HEIGHT/2,1,0,0,1);

            y0 = f.a[1]/f.b[1];
            trace_segment(-GLUT_WINDOW_WIDTH/2, y0, GLUT_WINDOW_WIDTH/2, y0, 1,0,0,1);
            break;
        case _1_2:
            if(delta(f.b) > 0){
                x = solveQ2S(f.b);
                trace_segment(x[0], -GLUT_WINDOW_HEIGHT/2,x[0], GLUT_WINDOW_HEIGHT/2,1,0,0,1);
                trace_segment(x[1], -GLUT_WINDOW_HEIGHT/2,x[1], GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            }else if (delta(f.b) == 0){
                x0 = solveQ1S(f.b);
                trace_segment(x0, -GLUT_WINDOW_HEIGHT/2,x0, GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            }
            break;
        case _2_0:
            std::cout << "Pas d'asymptotes"<<std::endl;
            break;
        case _2_1:
            x0 = -f.b[0]/f.b[1];
            trace_segment(x0, -GLUT_WINDOW_HEIGHT/2,x0, GLUT_WINDOW_HEIGHT/2,1,0,0,1);

            alpha = f.a[2]/f.b[1];
            beta = (f.b[1]*f.a[1] - f.a[2]*f.b[0])/(f.b[1]*f.b[1]);
            l = -GLUT_WINDOW_WIDTH/2;
            r = GLUT_WINDOW_WIDTH/2;
            trace_segment(l,alpha*l + beta, r, alpha*r + beta, 1, 0, 0, 1);
            break;
        case _2_2:
            if(delta(f.b) > 0){
                x = solveQ2S(f.b);
                trace_segment(x[0], -GLUT_WINDOW_HEIGHT/2,x[0], GLUT_WINDOW_HEIGHT/2,1,0,0,1);
                trace_segment(x[1], -GLUT_WINDOW_HEIGHT/2,x[1], GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            }else if (delta(f.b) == 0){
                x0 = solveQ1S(f.b);
                trace_segment(x0, -GLUT_WINDOW_HEIGHT/2,x0, GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            }
            y0 = f.a[2]/f.b[2];
            trace_segment(-GLUT_WINDOW_WIDTH/2, y0, GLUT_WINDOW_WIDTH/2, y0, 1,0,0,1);
            break;
        case _3_0:
            std::cout << "Pas d'asymptotes"<<std::endl;
            break;
        case _3_1:
            x0 = -f.b[0]/f.b[1];
            trace_segment(x0, -GLUT_WINDOW_HEIGHT/2,x0, GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            break;
        case _3_2:
            if(delta(f.b) > 0){
                x = solveQ2S(f.b);
                trace_segment(x[0], -GLUT_WINDOW_HEIGHT/2,x[0], GLUT_WINDOW_HEIGHT/2,1,0,0,1);
                trace_segment(x[1], -GLUT_WINDOW_HEIGHT/2,x[1], GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            }else if (delta(f.b) == 0){
                x0 = solveQ1S(f.b);
                trace_segment(x0, -GLUT_WINDOW_HEIGHT/2,x0, GLUT_WINDOW_HEIGHT/2,1,0,0,1);
            }
            alpha = f.a[3]/f.b[2];
            beta = (f.b[2]*f.a[2] - f.a[3]*f.b[1])/(f.b[2]*f.b[2]);
            l = -GLUT_WINDOW_WIDTH/2;
            r = GLUT_WINDOW_WIDTH/2;
            trace_segment(l,alpha*l + beta, r, alpha*r + beta, 1, 0, 0, 1);
            break;
    }

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