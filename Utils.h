//
// Created by Rafael on 08/06/2024.
//

#ifndef UTILS_H
#define UTILS_H
#include "Grafo.h"
#include <fstream>
#include <string>

using namespace std;
class Utils {
public:
    Utils(long seed);
    ~Utils();

    void imprimirGrafo(Grafo* g);

private:
    ofstream file;
    string fileName;


};



#endif //UTILS_H
