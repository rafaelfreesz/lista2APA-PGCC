//
// Created by Rafael on 08/06/2024.
//

#include "Grafo.h"

#include <list>
#include <string>
#include <vector>

//Construtores e Destrutores
Grafo::Grafo(int ordem, bool orientado) {
    this->grau = 0;
    this->ordem = ordem;
    this->orientado = orientado;

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

Grafo * Grafo::gerarGrafo(int ordem, int pesoMaximo, float densidadeArestas, bool orientado) {

    Grafo* grafo = new Grafo(ordem, orientado);

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

Grafo * Grafo::gerarGrafoFortementeConexo(int ordem, int pesoMaximo) {
    Grafo* grafo = new Grafo(ordem, true);

    while(!grafo->ehConexo()) {
        int a = rand()%grafo->ordem;
        int b = rand()%grafo->ordem;

        while(a==b || grafo->adjacencia[a][b]) {
            a = rand()%grafo->ordem; b = rand()%grafo->ordem;
        }

        grafo->incluirAresta(a,b, rand()%(pesoMaximo+1));

    }

    int naoConectividade[2];
    while(!grafo->ehFortementeConexo(naoConectividade)) {
        int a = rand()%grafo->ordem;
        int b = rand()%grafo->ordem;

        while(a==b || grafo->adjacencia[a][b]) {
            a = rand()%grafo->ordem; b = rand()%grafo->ordem;
        }

        grafo->incluirAresta(a,b, rand()%(pesoMaximo+1));

    }

    return grafo;
}

Grafo * Grafo::gerarGrafoRestaUm() {

    //Contabilizando Estados
    vector<int> totalAntes;
    vector<string> jogador;
    vector<int> totalDepois;

    for(int i=1;i<=3;i++) {
        totalAntes.push_back(10);
        jogador.push_back("A");
        totalDepois.push_back(10-i);
    }

    for(int i=1;i<=3;i++) {
        totalAntes.push_back(9);
        jogador.push_back("B");
        totalDepois.push_back(9-i);
    }

    for(int i=8;i>0;i--) {
        for(int j=1;j<=3;j++) {
            if(i-j>=0) {
                totalAntes.push_back(i);
                jogador.push_back("A");
                totalDepois.push_back(i-j);
            }
        }
        for(int j=1;j<=3;j++) {
            if(i-j>=0) {
                totalAntes.push_back(i);
                jogador.push_back("B");
                totalDepois.push_back(i-j);
            }
        }
    }

    for(int i=0;i<totalAntes.size();i++) {
        cout<<totalAntes.at(i)<<" - "<<jogador.at(i)<<" - "<<totalDepois.at(i)<<endl;
    }

    int qtdEstados = totalAntes.size();


    vector<string> rotulos;

    //Gerando o grafo
    Grafo* g = new Grafo(qtdEstados, true);



    return nullptr;
}

void Grafo::incluirAresta(int i, int j, int peso) {
    if(i==j){ cout<<"Laço não permitido"<<endl; return; }

    if(this->adjacencia[i][j]>0) { cout<<"Multiaresta não permitido"<<endl; return; }

    this->adjacencia[i][j] = peso;
    if(!this->orientado) {
        this->adjacencia[j][i] = peso;
    }
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
        if(verificados[i]==0) {
            delete [] verificados;
            return nullptr;
        }
    }

    delete []verificados;
    return true;
}

bool Grafo::ehFortementeConexo(int *amostragem) {
    int* verificados = new int[this->ordem];


    for(int i=0;i<this->ordem;i++) {

        for(int k=0;k<this->ordem;k++) {
            verificados[k]=0;
        }

        for(int j=0;j<this->ordem;j++) {
            if(verificados[j]==0) {
                buscaProfundidade(i,j,verificados);
            }
        }

        for(int l=0;l<this->ordem;l++) {
            if(verificados[l]==0 ) {
                amostragem[0]=l;
                amostragem[2]=i;
                delete [] verificados;
                return false;
            }
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

string Grafo::buscaProfundidadeImprime(int noAtual, int noB, int *verificados) {

    verificados[noAtual]=2;
    for(int prox=0;prox<this->ordem;prox++) {

        if(this->adjacencia[noAtual][prox]>0) {
            if(noB==prox) {
                verificados[prox] = 1;
                return "-"+to_string(noAtual)+"-"+to_string(prox);
            }

            if(verificados[prox]!=2) {
                string s = buscaProfundidadeImprime(prox, noB,verificados);
                if(s!="") {
                    return "-"+to_string(noAtual)+s;
                }
            }
        }

    }

    return "";

}

double Grafo::calculaDistanciaMediaPorEtapas(int noOrigem) {

    int* etapas = new int[this->ordem];

    for(int i=0;i<this->ordem;i++) { etapas[i]=0; }

    int* distancias = dijkstraParaMedia(0, etapas);

    int somaDistancias=0;
    int somaEtapas=0;
    for(int i=0;i<this->ordem;i++) {
        somaDistancias+=distancias[i];
        somaEtapas+=etapas[i];
    }

    delete[] distancias;
    delete[] etapas;

    return (double)somaDistancias/(double)somaEtapas;
}

int* Grafo::dijkstraParaMedia(int noOrigem, int *etapas) {
    int* visitados = new int[this->ordem];
    int* distancias = new int[this->ordem];
    int* predecessor = new int[this->ordem];


    for(int i=0;i<this->ordem;i++) {
        visitados[i]=-1;
        distancias[i]=-1;
        predecessor[i] = -1;
    }

    int qtdNosVisitados=0;
    int indiceMenor=noOrigem;
    distancias[noOrigem]=0;
    predecessor[noOrigem]=noOrigem;

    while (qtdNosVisitados++<this->ordem) {
        visitados[indiceMenor]=2;

        for(int j=0;j<this->ordem;j++) {

            if(this->adjacencia[indiceMenor][j]>0 && visitados[j]!=2) {
                if(distancias[j]==-1 || (distancias[indiceMenor]+this->adjacencia[indiceMenor][j])<distancias[j]) {
                    distancias[j]=distancias[indiceMenor]+ this->adjacencia[indiceMenor][j];
                    predecessor[j]=indiceMenor;
                    etapas[j] = etapas[indiceMenor]+1;
                }
            }

        }


        indiceMenor=-1;
        for(int k=0;k<this->ordem;k++) {
            if(visitados[k]==-1 && distancias[k]!=-1) {
                if(indiceMenor==-1 || distancias[k]<distancias[indiceMenor]) {
                    indiceMenor=k;
                }
            }
        }



    }

    return distancias;
}

int* Grafo::dijkstra(int noOrigem) {
    int* visitados = new int[this->ordem];
    int* distancias = new int[this->ordem];
    int* predecessor = new int[this->ordem];


    for(int i=0;i<this->ordem;i++) {
        visitados[i]=-1;
        distancias[i]=-1;
        predecessor[i] = -1;
    }

    int qtdNosVisitados=0;
    int indiceMenor=noOrigem;
    distancias[noOrigem]=0;
    predecessor[noOrigem]=noOrigem;

    while (qtdNosVisitados++<this->ordem) {
        visitados[indiceMenor]=2;

            for(int j=0;j<this->ordem;j++) {

                if(this->adjacencia[indiceMenor][j]>0 && visitados[j]!=2) {
                    if(distancias[j]==-1 || (distancias[indiceMenor]+this->adjacencia[indiceMenor][j])<distancias[j]) {
                        distancias[j]=distancias[indiceMenor]+ this->adjacencia[indiceMenor][j];
                        predecessor[j]=indiceMenor;
                    }
                }

            }


            indiceMenor=-1;
            for(int k=0;k<this->ordem;k++) {
                if(visitados[k]==-1 && distancias[k]!=-1) {
                    if(indiceMenor==-1 || distancias[k]<distancias[indiceMenor]) {
                        indiceMenor=k;
                    }
                }
            }



    }

    return distancias;
}

void Grafo::imprimeCaminho(int noA, int noB) {
    int* verificados = new int[this->ordem];
    for(int i=0;i<this->ordem;i++) {
        verificados[i] = 0;
    }

    cout<<"Caminho minimo impresso:"<<endl;
    cout<<buscaProfundidadeImprime(noA, noB,verificados)<<endl;

    delete[] verificados;
}

/*int * Grafo::calculaDistanciaMediaPorEtapas(int noOrigem) {

    //Armazenando
    float* distanciaMedia = new float[this->ordem];
    int* verificados = new int[]
    for(int i=0;i<this->ordem;i++) {
        distanciaMedia[i]=0.0;
    }

}*/
