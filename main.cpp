#include <iostream>
#include "Grafo.h"
#include "Utils.h"

using namespace std;
int main()
{
    long seed=0;
    srand(seed);

    int ordem = 10;
    int pesoMaximo = 10;

    Utils* u = new Utils(seed);
    Grafo* g = Grafo::gerarGrafoOrdemK(ordem,pesoMaximo, 0.5);

    u->imprimirGrafo(g);

    if(g->ehConexo()) {
        cout<<"EH CONEXO"<<endl;
    }else {
        cout<<"Nao eh conexo"<<endl;
    }




    delete g;
    delete u;
    return 0;
}
