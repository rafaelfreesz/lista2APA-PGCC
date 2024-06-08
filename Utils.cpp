//
// Created by Rafael on 08/06/2024.
//

#include "Utils.h"
Utils::Utils(long seed) {
    int k=0;
    this->file.open("OUTPUT_"+to_string(k)+".TXT", ios_base::in);
    while(this->file.is_open()) {
        this->file.close();
        k++;
        this->file.open("OUTPUT_"+to_string(k)+".TXT", ios_base::in);
    }
    this->fileName="OUTPUT_"+to_string(k)+".TXT";
    this->file.open("OUTPUT_"+to_string(k)+".TXT", ios_base::out);
    this->file<<"----------RELATORIO DE RESULTADOS (SEED "+to_string(seed)+")----------"<<endl<<endl;
}

Utils::~Utils() {
    this->file.close();
    cout<<endl<<"----------RELATORIO EMITIDO NO ARQUIVO "+this->fileName+"----------"<<endl;
}
void Utils::imprimirGrafo(Grafo *g) {
    this->file<<"--------GRAFO GERADO--------"<<endl;

    this->file<<"ORDEM: "<<g->ordem<<endl;
    this->file<<"GRAU: "<<g->grau<<endl;
    this->file<<"MATRIZ DE ADJACENCIA: "<<endl;

    for(int i=0;i<g->ordem;i++) {
        for (int j=0;j<g->ordem-1;j++) {
            this->file<<g->adjacencia[i][j]<<",";
        }
        this->file<<g->adjacencia[i][g->ordem-1]<<endl;
    }

    this->file<<"--------------------"<<endl<<endl;
}