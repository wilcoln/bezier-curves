//
// Created by wilcoln on 27/11/18.
//

#ifndef PROJECT_FONCTION_H
#define PROJECT_FONCTION_H
#include <array>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
typedef enum Degres {_0_0, _0_1, _0_2, _1_0, _1_1, _1_2, _2_0, _2_1, _2_2, _3_0, _3_1, _3_2} Degres;
class Fonction {
public:
    array<int, 2> degres;
    vector<double> a; // à 4 éléments
    vector<double> b; // À 3 éléments
    string record;
    Degres getDegres() const;

    Fonction();
    Fonction(vector<double> a, vector<double> b);
    
    int degreBezier() const;
    double val(double x) const;
    void addInfos(string infos);
    void affiche() const;
    ~Fonction();
};


#endif //PROJECT_FONCTION_H
