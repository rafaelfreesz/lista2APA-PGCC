//
// Created by Rafael on 08/06/2024.
//

#include "Grafo.h"

//Construtores e Destrutores
Grafo::Grafo(int ordem) {
    this->grau = 0;
    this->ordem = ordem;

    this->adjacencia = new int* [ordem];

    for(int i = 0; i<this->ordem; i++) {
        this->adjacencia[i] = new int[ordem];
        for(int j=0; j<this->ordem; j++) {
            this->adjacencia[i][j] = false;
        }
    }


}

Grafo::~Grafo() {

    for(int i = 0; i<this->ordem; i++) {
        delete this->adjacencia[i];
    }
    delete this->adjacencia;
}

Grafo * Grafo::gerarGrafoOrdemK(int ordem, int pesoMaximo, float densidadeArestas) {

    Grafo* grafo = new Grafo(ordem);

    int grau =(int)(densidadeArestas*(ordem*(ordem-1)/2));

    for(int i=0;i<grau || !grafo->ehConexo();i++) {
        int a = rand()%grafo->ordem;
        int b = rand()%grafo->ordem;

        while(a==b || grafo->adjacencia[a][b]) {
            a = rand()%grafo->ordem; b = rand()%grafo->ordem;
        }

        grafo->incluirAresta(a,b, rand()%(pesoMaximo+1));

    }

    return grafo;
}

void Grafo::incluirAresta(int i, int j, int peso) {
    if(i==j){ cout<<"Laço não permitido"<<endl; return; }

    if(this->adjacencia[i][j]>0) { cout<<"Multiaresta não permitido"<<endl; return; }

    this->adjacencia[i][j] = peso;
    this->adjacencia[j][i] = peso;
    this->grau++;
}

bool Grafo::ehConexo() {

    int* verificados = new int[this->ordem];
    for(int i=0;i<this->ordem;i++) {
        verificados[i]=0;
    }

    for(int i=1;i<this->ordem;i++) {
        if(verificados[i]==0) {
            buscaProfundidade(0,i,verificados);
        }
    }

    for(int i=0;i<this->ordem;i++) {
        if(!verificados[i]) {
            delete [] verificados;
            return nullptr;
        }
    }

    delete []verificados;
    return true;
}

void Grafo::buscaProfundidade(int noAtual, int noB, int *verificados) {

    verificados[noAtual]=2;

    for(int prox=0;prox<this->ordem;prox++) {

            if(this->adjacencia[noAtual][prox]>0) {
                if(noB==prox) {
                    verificados[prox] = 1;
                    return;
                }

                if(verificados[prox]!=2) {
                    buscaProfundidade(prox, noB,verificados);
                }
            }

    }

}
