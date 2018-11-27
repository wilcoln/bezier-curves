//
// Created by wilcoln on 27/11/18.
//

#ifndef PROJECT_FONCTION_H
#define PROJECT_FONCTION_H
#include <array>
#include <iostream>
typedef enum Degres {_0_0, _0_1, _0_2,_1_0,_1_1,_1_2,_2_0,_2_1,_2_2, _3_0, _3_1, _3_2} Degres;
class Fonction {
private:
    std::array<short, 2> degres;
public:
    std::array<double, 4> a;
    std::array<double, 3> b;
    Degres getDegres() const;
    Fonction();
    Fonction(std::array<double, 4> a, std::array<double, 3> b);
    double fn(double x) const;
    void affiche() const;
    ~Fonction();
};


#endif //PROJECT_FONCTION_H
