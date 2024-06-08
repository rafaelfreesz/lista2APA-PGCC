#include <iostream>
#include "Grafo.h"
#include "Utils.h"

using namespace std;
int main()
{
    long seed=0;
    srand(0);

    int ordem = 10;
    int pesoMaximo = 10;

    Utils* u = new Utils();
    Grafo* g = Grafo::gerarGrafoOrdemK(ordem,pesoMaximo, 0.5);



    delete g;
    delete u;
    return 0;
}
