#include "utils.h"
using namespace std;

double delta(vector<double> a) {
    return a[1] * a[1] - 4 * a[2] * a[0];
}

array<double, 2> solveQ2S(vector<double> a) {
    double D = delta(a);
    array<double, 2> result = {(-a[1] - sqrt(D)) / (2 * a[2]), (-a[1] + sqrt(D)) / (2 * a[2])};
    return result;
}

double solveQ1S(vector<double> a) {
    return -a[1] / (2 * a[3]);
}


vector<double> prodMatVec(const vector<vector<double>> &mat, const vector<double> &vect, int degre) {
    int n = degre;
    vector<double> result(n+1, 0);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++)
            result[i] += mat[i][j] * vect[j];
    }
    return result;

}

vector<double> canonic2bezier(vector<double> vect, int degre) {
    while (vect.size() <= degre)
        vect.push_back(0);
    return prodMatVec(MCB[degre - 1], vect, degre);
}

vector<double> foisT(const vector<double> &vect) {
    vector<double> v(1, 0);
    for (auto val: vect)
        v.push_back(val);
    return v;
}

vector<array<double, 2>> pointsCtrl(vector<double> QB, vector<double> tQB, vector<double> PB) {
    vector<array<double, 2>> pts;
    double t;
    for (int i = 0; i < QB.size(); i++) {
        pts.push_back({tQB[i] / QB[i], PB[i] / QB[i]});
    }
    return pts;
}

void openGL(double x, double y, double r0, double g0, double b0, double size) {
    glColor3f(r0, g0, b0);    //initialisation de la couleur
    glPointSize(size);    // initialisation de la taille
    glBegin(GL_POINTS);    // on trace un point
    glVertex2f(x, y);    // coordonnees du point
    glEnd();    // fin de glBegin
}

void trace_segment(double x0, double y0, double x1, double y1, double red, double green, double blue, double size) {
    glColor3f(red, green, blue);//initialisation de la couleur
    glLineWidth(size); // initialisation de la taille
    glBegin(GL_LINES); // on trace un segment
    glVertex2f(x0, y0); // coordonnees du premier point
    glVertex2f(x1, y1); // coordonnees du dernier point
    glEnd(); // fin de glBegin
}

void trace_courbe(const Fonction &fonction, double a, double b) {
    double x;
    double x2;
    double t;
    if (b == HUGE_VAL) {
        t=0;
        while(t <=1) {
            x = a - 1 + 1 / t;
            x2 = a - 1 + 1 / (t + dt);
            trace_segment(x, fonction.val(x), x2, fonction.val(x2), 0, 0, 0, 1.5);
            t+=dt;
        }
    } else if (a == -HUGE_VAL) {
        t=0;
        while(t <=1) {
            x = -1 / t + b + 1;
            x2 = -1 / (t + dt) + b + 1;
            trace_segment(x, fonction.val(x), x2, fonction.val(x2), 0, 0, 0, 1.5);
            t+=dt;
        }
    } else {
        t=0;
        while(t <=1) {
            x = a + t * (b - a);
            x2 = a + (t + dt) * (b - a);
            trace_segment(x, fonction.val(x), x2, fonction.val(x2), 0, 0, 0, 1.5);
            t+=dt;
        }
    }
}

unsigned int combinaison(unsigned int n, unsigned int k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    unsigned int result = n;
    for (int i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

double B(int i, int n, double x) {
    return combinaison(n, i) * pow(x, i) * pow((1 - x), (n - i));
}

void trace_bezier(Fonction &f, double a, double b) {
    ostringstream oss;
    ostringstream oss1;
    ostringstream oss2;
    if(a == -HUGE_VAL)
        oss1 << "]-inf";
    else
        oss1 << "[" << a;
    if(b == HUGE_VAL)
        oss2 << " +inf[";
    else
        oss2 << b << "]";
    oss << "Courbe de Bezier de f dans l'interval "<< oss1.str() << ", " << oss2.str() <<  "\n--------------------------------------------" << endl;
    double x, prev_x;
    double y, prev_y;
    double deno;
    int n = f.degreBezier();
    vector<double> beta = canonic2bezier(f.b, n);
    vector<double> gamma = canonic2bezier(foisT(f.b), n);
    vector<double> alpha = canonic2bezier(f.a, n);
    vector<double> P(n + 1, 0);
    vector<double> Q(n + 1, 0);
    vector<double> tQ(n + 1, 0);
    vector<double> params;
    vector<array<double, 2>> pts;
    double cr, cg, cb;
    if (b == HUGE_VAL){
        params = {a - 1, 1, 1, 0};
        cr=170.0/255;
        cg=110.0/255;
        cb=70.0/255;
    }

    else if (a == -HUGE_VAL){
        params = {b + 1, -1, 1, 0};
        cr=72.0/255;
        cg=109.0/255;
        cb=168.0/255;
    }

    else{
        params = {b - a, a, 0, 1};
        cr=72.0/255;
        cg=168.0/255;
        cb=109./255;
    }

    double tmp = 0;
    for (int i = 0; i <= n; i++) {
        for (int p = 0; p <= n - i; p++) {
            for (int m = p; m <= i + p; m++) {
                tmp = combinaison(n, i) * combinaison(i, m-p) * combinaison(n - i, p) * pow(params[0], m-p) *
                      pow((params[2] - params[0]), p) * pow(params[1], i - m + p) *
                      pow((params[3] - params[1]), n - i - p);
                P[m] += gamma[i] * tmp;
                Q[m] += beta[i] * tmp;
                tQ[m] += alpha[i] * tmp;
            }
        }
    }

    beta = canonic2bezier(Q, n);
    gamma = canonic2bezier(P, n);
    alpha = canonic2bezier(tQ, n);
    pts = pointsCtrl(beta, gamma, alpha);

    // Trace courbe
    double t = 0;
    while(t <= 1) {
        deno = 0;
        x = 0;
        y = 0;
        for (int i = 0; i < n + 1; i++) {
            deno += beta[i] * B(i, n, t);
            x += (beta[i] != 0 ? beta[i] * pts[i][0] : gamma[i]) * B(i, n, t);
            y += (beta[i] != 0 ? beta[i] * pts[i][1] : alpha[i]) * B(i, n, t);
        }
        x /= deno;
        y /= deno;
        if(t > 0)
            trace_segment(prev_x, prev_y, x, y, cr,cg,cb, 3);
        prev_x = x;
        prev_y = y;
        t+=dt;
    }
    // Place et enregistre les points
    for (int i = 0; i < pts.size(); i++) {
        if (beta[i] != 0) {
            openGL(pts[i][0], pts[i][1], .1+ cr, .1 + cg,.1 + cb, 10);
            oss << " -> Point " << i + 1 << " : (" << pts[i][0] << ", " << pts[i][1] << ") de poids " << beta[i] << endl;
        } else {
            if(i == 0){
               trace_segment(pts[i + 1][0], pts[i + 1][1], pts[i + 1][0] + gamma[i], pts[i + 1][1] + alpha[i], .2 + cr, .2 + cg, .2 + cb, 5);
            }else{
                trace_segment(pts[i - 1][0], pts[i - 1][1], pts[i - 1][0] - gamma[i], pts[i - 1][1] - alpha[i],  .2  + cr, .2 + cg, .2 + cb, 5);
            }
            oss << " -> Vecteur " << i + 1 << " : (" << gamma[i] << ", " << alpha[i] << ")"<< endl;
        }
    }
    f.addInfos(oss.str());
}

void trace_asymptotes(Fonction &f) {
    ostringstream oss;
    oss << "Etude des asymptotes\n--------------------" << endl;
    double x0, y0, l, r;
    double alpha, beta;
    array<double, 2> x;
    switch (f.getDegres()) {
        case _0_0:
            oss << " -> f ne possède pas d'asymptote" << endl;
            break;
        case _0_1:
            x0 = -f.b[0] / f.b[1];
            trace_segment(x0, -GLUT_WINDOW_HEIGHT / 2, x0, GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
            oss << " -> f possède une asymptote verticale d'équation  (D) : x = " << x0 << endl;
            break;
        case _0_2:
            if (delta(f.b) > 0) {
                x = solveQ2S(f.b);
                trace_segment(x[0], -GLUT_WINDOW_HEIGHT / 2, x[0], GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                trace_segment(x[1], -GLUT_WINDOW_HEIGHT / 2, x[1], GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                oss << " -> f possède deux asymptotes verticales d'équation : " << endl;
                oss << " (D1) : x = " << x[0] << endl;
                oss << " (D2) : x = " << x[1] << endl;
            } else if (delta(f.b) == 0) {
                x0 = solveQ1S(f.b);
                trace_segment(x0, -GLUT_WINDOW_HEIGHT / 2, x0, GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                oss << " -> f possède une asymptote verticale d'équation  (D) : x = " << x0 << endl;
            }
            break;
        case _1_0:
            oss << " -> f ne possède pas d'asymptote" << endl;
            break;
        case _1_1:
            x0 = -f.b[0] / f.b[1];
            trace_segment(x0, -GLUT_WINDOW_HEIGHT / 2, x0, GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
            oss << " -> f possède une asymptote verticale d'équation  (D) : x = " << x0 << endl;

            y0 = f.a[1] / f.b[1];
            trace_segment(-GLUT_WINDOW_WIDTH / 2, y0, GLUT_WINDOW_WIDTH / 2, y0, .6,.6,.6, 2);
            oss << " -> f possède une asymptote horizontale d'équation : \n (D') : y = " << y0 << endl;
            break;
        case _1_2:
            if (delta(f.b) > 0) {
                x = solveQ2S(f.b);
                trace_segment(x[0], -GLUT_WINDOW_HEIGHT / 2, x[0], GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                trace_segment(x[1], -GLUT_WINDOW_HEIGHT / 2, x[1], GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                oss << " -> f possède deux asymptotes verticales d'équation : " << endl;
                oss << " (D1) : x = " << x[0] << endl;
                oss << " (D2) : x = " << x[1] << endl;
            } else if (delta(f.b) == 0) {
                x0 = solveQ1S(f.b);
                trace_segment(x0, -GLUT_WINDOW_HEIGHT / 2, x0, GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                oss << " -> f possède une asymptote verticale d'équation  (D) : x = " << x0 << endl;
            }
            break;
        case _2_0:
            oss << " -> f ne possède pas d'asymptote" << endl;
            break;
        case _2_1:
            x0 = -f.b[0] / f.b[1];
            trace_segment(x0, -GLUT_WINDOW_HEIGHT / 2, x0, GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
            oss << " -> f possède une asymptote verticale d'équation  (D) : x = " << x0 << endl;

            alpha = f.a[2] / f.b[1];
            beta = (f.b[1] * f.a[1] - f.a[2] * f.b[0]) / (f.b[1] * f.b[1]);
            l = -GLUT_WINDOW_WIDTH / 2;
            r = GLUT_WINDOW_WIDTH / 2;
            trace_segment(l, alpha * l + beta, r, alpha * r + beta, .6,.6,.6, 2);
            oss << " -> f possède une asymptote oblique d'équation : \n (D'') : y = " << alpha<<"x + " << beta  << endl;
            break;
        case _2_2:
            if (delta(f.b) > 0) {
                x = solveQ2S(f.b);
                trace_segment(x[0], -GLUT_WINDOW_HEIGHT / 2, x[0], GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                trace_segment(x[1], -GLUT_WINDOW_HEIGHT / 2, x[1], GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                oss << " -> f possède deux asymptotes verticales d'équation : " << endl;
                oss << " (D1) : x = " << x[0] << endl;
                oss << " (D2) : x = " << x[1] << endl;
            } else if (delta(f.b) == 0) {
                x0 = solveQ1S(f.b);
                trace_segment(x0, -GLUT_WINDOW_HEIGHT / 2, x0, GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                oss << " -> f possède une asymptote verticale d'équation  (D) : x = " << x0 << endl;
            }
            y0 = f.a[2] / f.b[2];
            trace_segment(-GLUT_WINDOW_WIDTH / 2, y0, GLUT_WINDOW_WIDTH / 2, y0, .6,.6,.6, 2);
            oss << " -> f possède une asymptote horizontale d'équation : \n (D') : y = " << y0 << endl;

            break;
        case _3_0:
            oss << " -> f ne possède pas d'asymptote" << endl;
            break;
        case _3_1:
            x0 = -f.b[0] / f.b[1];
            trace_segment(x0, -GLUT_WINDOW_HEIGHT / 2, x0, GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
            oss << " -> f possède une asymptote verticale d'équation  (D) : x = " << x0 << endl;
            break;
        case _3_2:
            if (delta(f.b) > 0) {
                x = solveQ2S(f.b);
                trace_segment(x[0], -GLUT_WINDOW_HEIGHT / 2, x[0], GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                trace_segment(x[1], -GLUT_WINDOW_HEIGHT / 2, x[1], GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);

                oss << " -> f possède deux asymptotes verticales d'équation : " << endl;
                oss << " (D1) : x = " << x[0] << endl;
                oss << " (D2) : x = " << x[1] << endl;
            } else if (delta(f.b) == 0) {
                x0 = solveQ1S(f.b);
                trace_segment(x0, -GLUT_WINDOW_HEIGHT / 2, x0, GLUT_WINDOW_HEIGHT / 2, .6,.6,.6, 2);
                oss << " -> f possède une asymptote verticale d'équation  (D) : x = " << x0 << endl;
            }
            alpha = f.a[3] / f.b[2];
            beta = (f.b[2] * f.a[2] - f.a[3] * f.b[1]) / (f.b[2] * f.b[2]);
            l = -GLUT_WINDOW_WIDTH / 2;
            r = GLUT_WINDOW_WIDTH / 2;
            trace_segment(l, alpha * l + beta, r, alpha * r + beta, .6,.6,.6, 2);
            oss << " -> f possède une asymptote oblique d'équation : \n (D'') : y = " << alpha<<"*x + " << beta  << endl;
            break;
    }
    f.addInfos(oss.str());

}

Fonction nouvelle_entree() {
    vector<double> a(4, 0);
    vector<double> b(3, 0);
    cout << "\n\n";
    cout << "       " << "a[3]" << "*x^3 + " << "a[2]" << "*x^2 + " << "a[1]" << "*x + " << "a[0]" << endl;
    cout << " -> f(x) = ----------------------- " << endl;
    cout << "       " << "b[2]" << "*x^2 + " << "b[1]" << "*x + " << "b[0]" << endl;
    cout << "<======================== Saisie d'une fonction ========================>" << endl;
    cout << "Entrez a0 a1 a2 et a3 successivement séparés d'un espace" << endl;
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    cout << "Entrez b0 b1 et b2 successivement séparés d'un espace" << endl;
    cin >> b[0] >> b[1] >> b[2];
    return Fonction(a, b);
}