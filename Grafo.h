//
// Created by Rafael on 08/06/2024.
//

#ifndef GRAFO_H
#define GRAFO_H


#include <iostream>

using namespace std;
class Grafo {

public:
    //Funções
    Grafo(int ordem, bool orientado);
    ~Grafo();

    static Grafo * gerarGrafo(int ordem, int pesoMaximo, float densidadeArestas, bool orientado);

    static Grafo * gerarGrafoFortementeConexo(int ordem, int pesoMaximo);

    static Grafo * gerarGrafoRestaUm();

    void incluirAresta(int i, int j, int peso);
    bool ehConexo();
    bool ehFortementeConexo(int *amostragem);
    void buscaProfundidade(int noAtual, int noB, int *verificados);

    string buscaProfundidadeImprime(int noAtual, int noB, int *verificados);

    double calculaDistanciaMediaPorEtapas(int noOrigem);

    int* dijkstra(int noOrigem);

    int* dijkstraParaMedia(int noOrigem, int *etapas);

    void imprimeCaminho(int noA, int noB);



    //Atributos
    int grau; //quantidade de arestas próprias
    int ordem; //quantidade de vertices;
    int** adjacencia; //Matriz de adjacencia binária
    bool orientado;

};



#endif //GRAFO_H
