//
// Created by wilcoln on 27/11/18.
//
#include "Fonction.h"

using namespace std;

Fonction::Fonction(){};
Fonction::Fonction(vector<double> a, vector<double> b) {
    // initialise degres
    this->a = a;
    this->b = b;

    degres[0] = degres[1] = 0;
    if(a[1] != 0)
        degres[0] = 1;
    if(a[2] != 0)
        degres[0] = 2;
    if(a[3] != 0)
        degres[0] = 3;
    if(b[1] != 0)
        degres[1] = 1;
    if(b[2] != 0)
        degres[1] = 2;

    // Initialise record
    ostringstream oss, oss1, oss2;
    oss1 << abs(a[3]);
    oss << "==================================================================\nNous considérons la fonction suivante:\n"<<endl;
    oss << "       " <<(a[3] >= 0? "" : "-") << (abs(a[3]) != 1 ? oss1.str():"")  << "x³"  << (a[2] > 0? " + " : " - ") << abs(a[2]) <<"x²" << (a[1] > 0? " + " : " - ") << abs(a[1]) <<"x" << (a[0] > 0? " + " : " - ") << abs(a[0])<<endl;
    oss << "f(x) = ------------------------ "<<endl;
    oss2 << abs(b[2]);
    oss << "       " << (b[2] >= 0? "" : "-") << (abs(b[2]) != 1 ? oss1.str():"") <<"x²" << (b[1] > 0? " + " : " - ") << abs(b[1]) <<"x" << (b[0] > 0? " + " : " - ") << abs(b[0])<<endl;
    oss << endl;

    record = oss.str();

    affiche();

}
double Fonction::val(double x) const{
    double x2(x*x),x3(x*x*x);
    return (a[3]*x3 + a[2]*x2 + a[1]*x + a[0])/(b[2]*x2 + b[1]*x + b[0]);

}
Fonction::~Fonction() {
}

void Fonction::affiche() const {
    cout << record;

}

int Fonction::degreBezier() const {
    return max(degres[0], 1 + degres[1]);
}
Degres Fonction::getDegres() const { ;
    return (Degres)(3*degres[0] + degres[1]);
}

void Fonction::addInfos(string infos) {
    record += infos;
    record +="\n";
}
