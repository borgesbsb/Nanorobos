#include <iostream>
using namespace std;

class Grafo;

class Subconjunto {
private:
    int parent;
    int rank;
public:
    Subconjunto(){};
    void setParent(int);
    int getParent();
    void setRank(int);
    int getRank();

};


class Aresta {
private:
    int src,dst,peso;
public:
    Aresta(){};
    void setSrc(int);
    int getSrc();
    void setDst(int);
    int getDst();
    void setPeso(int);
    int getPeso();
};

void Aresta::setSrc(int src) {
    this->src = src;
}

int Aresta::getSrc() {
    return this->src;
}

void Aresta::setDst(int dst) {
    this->dst = dst;
}

int Aresta::getDst() {
    return this->dst;
}


void Aresta::setPeso(int peso) {
    this->peso = peso;
}

int Aresta::getPeso() {
    return this->peso;
}


template<class T>
class Vertice {
private:
    T item;
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
    Aresta *arestas;
    int  ordem;
    int  tamanho;
    int  contadorAresta;
public:
    Grafo(int, int);
    int getOrdem();
    void insertEdge(Vertice<int>*,Vertice<int>*,int);
};


Grafo::Grafo(int ordem, int tamanho) {
    this->tamanho = tamanho;
    this->ordem = ordem;
    this->contadorAresta = 0;

    this->matriz = new int*[this->ordem+1];
    for (int i= 0; i<this->ordem+1;i++) {
        this->matriz[i] = new int[this->ordem+1];
    }

    this->arestas = new Aresta[this->tamanho];

}


void Grafo::insertEdge(Vertice<int> *u, Vertice<int> *v, int peso) {
    this->matriz[u->getItem()][v->getItem()] = peso;
    this->matriz[v->getItem()][u->getItem()] = peso;

    this->arestas[contadorAresta].setSrc(u->getItem());
    this->arestas[contadorAresta].setDst(v->getItem());
    this->arestas[contadorAresta].setPeso(peso);
    this->contadorAresta++;

}

int Grafo::getOrdem() {
    return this->ordem;
}



class Kruskal {
private:
    Grafo *grafo;
    Aresta *resultado;
    Subconjunto *subconjunto;
public:
    Kruskal(Grafo*);
    void makeSet(int);
    int findSet(int);
    void link(int, int);
    void uniondisjunt(int,int);
    int mst();
};

Kruskal::Kruskal(Grafo* grafo) {

    this->grafo = grafo;
    this->subconjunto = new Subconjunto[grafo->getOrdem()];

}

void Kruskal::makeSet(int vertice) {
    this->subconjunto[vertice].setParent(vertice);
    this->subconjunto[vertice].setRank(0);
}

int Kruskal::findSet(int vertice) {
    if (this->subconjunto[vertice].getParent() != vertice ) {

        this->subconjunto->setParent( this->findSet( this->subconjunto[vertice].getParent() )  );
    }
    return this->subconjunto[vertice].getParent();
}



void Kruskal::link(int vertice1, int vertice2 ) {

    if (this->subconjunto[vertice1].getRank() < this->subconjunto[vertice2].getRank()) {
        this->subconjunto[vertice1].setParent(vertice2);
    }else {
        if (this->subconjunto[vertice1].getRank() >  this->subconjunto[vertice2].getRank()) {
            this->subconjunto[vertice2].setParent(vertice1);
        }else {
            this->subconjunto[vertice2].setParent(vertice1);
            this->subconjunto[vertice1].setRank( this->subconjunto[vertice1].getRank()+1);
        }
    }
}

void Kruskal::uniondisjunt(int vertice1 , int vertice2) {
    this->link( this->findSet(vertice1), this->findSet(vertice2));
}

void Kruskal::mst() {
    this->resultado = new Aresta[grafo->getOrdem()];




}





int main() {

    int ordem = 9;
    int tamanho = 15;

    Vertice<int> *vertice1 = new Vertice<int>(1);
    Vertice<int> *vertice2 = new Vertice<int>(2);
    Vertice<int> *vertice3 = new Vertice<int>(3);
    Vertice<int> *vertice4 = new Vertice<int>(4);
    Vertice<int> *vertice5 = new Vertice<int>(5);
    Vertice<int> *vertice6 = new Vertice<int>(6);
    Vertice<int> *vertice7 = new Vertice<int>(7);
    Vertice<int> *vertice8 = new Vertice<int>(8);
    Vertice<int> *vertice9 = new Vertice<int>(9);

    Grafo *grafo = new Grafo(ordem,tamanho);

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



    return 0;
}