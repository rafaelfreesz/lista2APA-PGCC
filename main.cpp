#include <iostream>
#include "Grafo.h"
#include "Utils.h"

using namespace std;
int main() {
    long seed=0;
    srand(seed);

    int ordem = 5;
    int pesoMaximo = 10;
    bool orientado = false;

    Utils* u = new Utils(seed);
    Grafo* g = Grafo::gerarGrafo(ordem,pesoMaximo, 0.5, orientado);

    u->imprimirGrafo(g);

    if(g->ehConexo()) {
        cout<<"EH CONEXO"<<endl;
    }else {
        cout<<"Nao eh conexo"<<endl;
    }

    Grafo* g2 = Grafo::gerarGrafoFortementeConexo(5,pesoMaximo);
    u->imprimirGrafo(g);

    int naoConectividade[2]={-1,-1};
    if(g2->orientado &&  g2->ehFortementeConexo(naoConectividade)) {
        cout<<"EH fortemente CONEXO"<<endl;
    }else {
        cout<<"Nao eh fortemente conexo"<<endl;
    }

    double mediaEtapas = g->calculaDistanciaMediaPorEtapas(0);
    cout<< "A media de etapas a partir do indice zero eh "+to_string(mediaEtapas)<<endl;

    g->imprimeCaminho(1,4);

    Grafo::gerarGrafoRestaUm();


    delete g;
    delete g2;
    delete u;
    return 0;
}
