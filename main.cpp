#include <iostream>
using namespace std;

class Grafo;

template<class T>
class Vertice {
private:
    T item;
    Vertice *parent;
    int rank;
    Grafo  *grafo;
public:
    Vertice(T);
    T getItem();
    void setItem(T);


};

template<class T>
Vertice<T>::Vertice(T item) {
    this->item = item;
}

template<class T>
T Vertice<T>::getItem() {
    return this->item;
}




class Grafo {
private:
    int **matriz;
    int ordem, tamanho;
public:
    Grafo(int);
    void inicialize();
    void insertEdge(Vertice<int>*,Vertice<int>*,int);
};


Grafo::Grafo(int ordem) {

    this->matriz = new int*[ordem+1];
    for (int i= 0; i<ordem;i++) {
        this->matriz[i] = new int[ordem+1];
    }

}


void Grafo::insertEdge(Vertice<int> *u, Vertice<int> *v, int peso) {
    this->matriz[u->getItem()][v->getItem()] = peso;
    this->matriz[v->getItem()][u->getItem()] = peso;
    this->tamanho++;
}





class Kruskal {
private:
    Grafo *grafo;
public:
    Kruskal(Grafo*);
    void makeSet(Vertice<int>*);
    void uniondisjunt(Vertice<int>*,Vertice<int>*);
    void link(Vertice<int>*,Vertice<int>*);
    void findSet(Vertice<int>*);
};






int main() {


    Vertice<int> *vertice1 = new Vertice<int>(1);
    Vertice<int> *vertice2 = new Vertice<int>(2);
    Vertice<int> *vertice3 = new Vertice<int>(3);
    Vertice<int> *vertice4 = new Vertice<int>(4);
    Vertice<int> *vertice5 = new Vertice<int>(5);
    Vertice<int> *vertice6 = new Vertice<int>(6);
    Vertice<int> *vertice7 = new Vertice<int>(7);
    Vertice<int> *vertice8 = new Vertice<int>(8);
    Vertice<int> *vertice9 = new Vertice<int>(9);

    Grafo *grafo = new Grafo(9);
    /*
    grafo->insertEdge(vertice1,vertice2,4);
    grafo->insertEdge(vertice1,vertice8,8);
    grafo->insertEdge(vertice2,vertice3,8);
    grafo->insertEdge(vertice2,vertice8,11);
    grafo->insertEdge(vertice3,vertice4,7);
    grafo->insertEdge(vertice3,vertice6,4);
    grafo->insertEdge(vertice3,vertice9,2);
    grafo->insertEdge(vertice4,vertice5,9);
    grafo->insertEdge(vertice4,vertice6,14);
    grafo->insertEdge(vertice5,vertice6,10);
    grafo->insertEdge(vertice6,vertice7,2);
    grafo->insertEdge(vertice3,vertice9,2);
    grafo->insertEdge(vertice7,vertice9,6);
    grafo->insertEdge(vertice7,vertice7,8);

*/

















    return 0;
}