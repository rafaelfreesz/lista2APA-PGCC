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
    Grafo(int ordem);
    ~Grafo();

    static Grafo * gerarGrafoOrdemK(int ordem, int pesoMaximo, float densidadeArestas);
    void incluirAresta(int i, int j, int peso);
    int dijkstra(int iA, int iB);

    //Atributos
    int grau; //quantidade de arestas próprias
    int ordem; //quantidade de vertices;
    int** adjacencia; //Matriz de adjacencia binária

};


#endif //GRAFO_H
