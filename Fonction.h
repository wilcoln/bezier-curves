//
// Created by wilcoln on 27/11/18.
//

#ifndef PROJECT_FONCTION_H
#define PROJECT_FONCTION_H
#include <array>
#include <iostream>
class Fonction {
public:
    std::array<double, 4> a;
    std::array<double, 3> b;
    std::array<short, 2> degres;
    Fonction();
    Fonction(std::array<double, 4> a, std::array<double, 3> b);
    double fn(double x) const;
    void affiche() const;
    ~Fonction();
};


#endif //PROJECT_FONCTION_H
