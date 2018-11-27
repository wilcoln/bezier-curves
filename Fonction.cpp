//
// Created by wilcoln on 27/11/18.
//
#include "Fonction.h"
Fonction::Fonction(){};
Fonction::Fonction(std::array<double, 4> a, std::array<double, 3> b) {
    this->a = a;
    this->b = b;

    if(a[1] != 0)
        degres[0]++;
    if(a[2] != 0)
        degres[0]++;
    if(a[3] != 0)
        degres[0]++;
    if(b[1] != 0)
        degres[1]++;
    if(b[2] != 0)
        degres[1]++;
}
double Fonction::fn(double x) const{
    double x2(x*x),x3(x*x*x);
    return (a[3]*x3 + a[2]*x2 + a[1]*x + a[0])/(b[2]*x2 + b[1]*x + b[0]);
}
Fonction::~Fonction() {
}

void Fonction::affiche() const {
    std::cout << "       " << a[3] << "*x^3 + " << a[2] <<"*x^2 + " << a[1] <<"*x + " << a[0]<<std::endl;
    std::cout << "f(x) = ----------------------- "<<std::endl;
    std::cout << "       " << b[2] <<"*x^2 + " << b[1] <<"*x + " << b[0]<<std::endl;

}

Degres Fonction::getDegres() const { ;
    return (Degres)(3*degres[0] + degres[1]);
}
