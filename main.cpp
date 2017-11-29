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

void Subconjunto::setParent(int parent) {
    this->parent = parent;
}

int Subconjunto::getParent() {
    return this->parent;
}

void Subconjunto::setRank(int rank) {
    this->rank = rank;
}

int Subconjunto::getRank() {
    return this->rank;
}




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
    Aresta* getAresta();
    int getOrdem();
    int getTamanho();
    void insertEdge(Vertice<int>*,Vertice<int>*,int);
};


Grafo::Grafo(int ordem,int tamanho) {
    this->tamanho = tamanho;
    this->ordem = ordem;
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

int Grafo::getTamanho() {
    return this->tamanho;
}


Aresta* Grafo::getAresta() {
    return this->arestas;
}


class Heap {
private:
    Aresta *arestas;
    int tamanho;
    int tamanhoHeap;
public:
    Heap(Aresta*, int);
    int pai(int);
    int esq(int);
    int dir(int);
    void heapfica(int);
    void constroiHeap();
    Aresta* heapSort();

};

Heap::Heap(Aresta *arestas, int tamanho ) {
    this->arestas =  new Aresta[tamanho];
    this->arestas = arestas;
    this->tamanho = tamanho;
}

int Heap::pai(int i) {
    return i/2;
}

int Heap::esq(int i ) {
    return 2*i;
}

int Heap::dir(int i) {
    return (2*i)+1;
}

void Heap::heapfica(int i ) {
    int l = this->esq(i);
    int r = this->dir(i);
    int menor = i;
    Aresta *aux = new Aresta() ;


    if (l < this->tamanhoHeap && this->arestas[l].getPeso() > this->arestas[menor].getPeso()) {
        menor = l;
    }

    if (r < this->tamanhoHeap  && this->arestas[r].getPeso() > this->arestas[menor].getPeso()  ) {
        menor = r;
    }

    if (menor != i ) {
        *aux = this->arestas[i];
        this->arestas[i] = this->arestas[menor];
        this->arestas[menor] = *aux;
        heapfica(menor);
    }
}

void Heap::constroiHeap() {
    this->tamanhoHeap = this->tamanho;
    for (int i = (this->tamanho)/2 - 1; i >= 0  ; i--) {
        this->heapfica(i);
    }
}

Aresta* Heap::heapSort() {
    this->constroiHeap();
    for (int i = this->tamanho-1; i >= 0; i--) {
        Aresta *aux  =  new Aresta();
        *aux = this->arestas[0];
        this->arestas[0] = this->arestas[i];
        this->arestas[i] = *aux;
        this->tamanhoHeap--;
        this->heapfica(0);
    }
    return this->arestas;
}


class Kruskal {
private:
    Grafo *grafo;
    Aresta *resultado;
    Subconjunto *subconjunto;
    int inc;
public:
    Kruskal(Grafo*);
    void makeSet(int);
    int findSet(int);
    void link(int, int);
    void uniondisjunt(int,int);
    Aresta* mst();
};

Kruskal::Kruskal(Grafo* grafo) {

    this->grafo = grafo;
    this->subconjunto = new Subconjunto[grafo->getOrdem()];
    this->inc =  0;

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

Aresta* Kruskal::mst() {

    this->resultado = new Aresta[grafo->getOrdem()];

    for (int i = 0; i < grafo->getOrdem();i++) {
        this->subconjunto[i].setParent(i);
        this->subconjunto[i].setRank(0);
    }

    Heap heap(this->grafo->getAresta(),this->grafo->getTamanho());
    heap.heapSort();

    for (int i = 0; i < grafo->getOrdem(); i++) {

        int u = findSet(grafo->getAresta()[i].getSrc());
        int v = findSet(grafo->getAresta()[i].getDst());

        if ( u != v) {
            this->resultado[inc] = grafo->getAresta()[i];
            this->inc++;
            this->uniondisjunt(u, v);
        }

    }

    for (int i = 0; i<inc-1;i++) {
        cout << resultado[i].getSrc() <<" ---- "<<resultado[i].getDst() << " = "  << resultado[i].getPeso() << endl ;
    }

    return resultado;

}



int main() {

    int ordem = 9;
    int tamanho = 14;

    Vertice<int> *vertice1 = new Vertice<int>(0);
    Vertice<int> *vertice2 = new Vertice<int>(1);
    Vertice<int> *vertice3 = new Vertice<int>(2);
    Vertice<int> *vertice4 = new Vertice<int>(3);
    Vertice<int> *vertice5 = new Vertice<int>(4);
    Vertice<int> *vertice6 = new Vertice<int>(5);
    Vertice<int> *vertice7 = new Vertice<int>(6);
    Vertice<int> *vertice8 = new Vertice<int>(7);
    Vertice<int> *vertice9 = new Vertice<int>(8);

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
    grafo->insertEdge(vertice7,vertice9,6);
    grafo->insertEdge(vertice7,vertice8,1);
    grafo->insertEdge(vertice8,vertice9,7);

    Kruskal kruscal(grafo);

    kruscal.mst();



    return 0;
}