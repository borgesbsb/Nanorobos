#include <iostream>
#include <vector>

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
    int src,dst;
    float peso;
public:
    Aresta(){};
    void setSrc(int);
    int getSrc();
    void setDst(int);
    int getDst();
    void setPeso(float);
    float getPeso();
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


void Aresta::setPeso(float peso) {
    this->peso = peso;
}

float Aresta::getPeso() {
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
    float **matriz;
    Aresta **arestas;
    int  ordem;
    int  tamanho;
    int  contadorAresta;
public:
    Grafo(int, int);
    Aresta** getAresta();
    int getOrdem();
    int getTamanho();
    void insertEdge(int,int,float);
    float **getMatriz();

};


Grafo::Grafo(int ordem,int tamanho) {
    this->tamanho = tamanho;
    this->ordem = ordem;
    this->matriz = new float*[this->ordem];
    for (int i= 0; i<this->ordem;i++) {
        this->matriz[i] = new float[this->ordem];
    }

    for (int i =0; i<this->ordem ;  i++) {
        for (int j = 0;j<this->ordem;j++) {
            this->matriz[i][j] = 0;
        }
    }

    this->arestas = new Aresta*[this->tamanho];

    for (int i=0; i<tamanho;i++) {
        this->arestas[i] = new Aresta();
    }

    this->contadorAresta = 0;

}


void Grafo::insertEdge(int u , int v, float peso) {
    this->matriz[u][v] = peso;
    this->matriz[v][u] = peso;
    this->arestas[contadorAresta]->setSrc(u);
    this->arestas[contadorAresta]->setDst(v);
    this->arestas[contadorAresta]->setPeso(peso);
    this->contadorAresta++;

}

int Grafo::getOrdem() {
    return this->ordem;
}

int Grafo::getTamanho() {
    return this->tamanho;
}

float **Grafo::getMatriz() {
    return matriz;
}


Aresta** Grafo::getAresta() {
    return this->arestas;
}


class Heap {
private:
    Aresta **arestas;
    int tamanho;
    int heapsize;


public:
    int tamanhoHeap;
    Heap(Aresta**, int);
    Heap(int);
    int pai(int);
    int esq(int);
    int dir(int);
    void maxheapify(int);
    void minheapify(int);
    void constroiMaxHeap();
    void constroiMinHeap();
    Aresta** heapSort();
    Aresta* extraimin();
    void decreasekey(int,Aresta*);
    void insert(Aresta*);
    Aresta **getAresta();




};

Heap::Heap(int tamanho) {
    this->tamanho = tamanho;
    this->tamanhoHeap = 0;

    this->arestas = new Aresta*[tamanho];
    for (int i=0; i< tamanho;i++) {
        this->arestas[i] = new Aresta();
    }


}

Heap::Heap(Aresta **arestas, int tamanho ) {
    this->arestas =  arestas;
    this->tamanho = tamanho;
}

int Heap::pai(int i) {
    return  (i-1)/2;
}

int Heap::esq(int i ) {
    return 2*i + 1;
}

int Heap::dir(int i) {
    return (2*i)+2;
}

void Heap::minheapify(int i ) {
    int l = this->esq(i);
    int r = this->dir(i);
    int menor = i;
    Aresta *aux = new Aresta() ;


    if (l < this->tamanhoHeap && this->arestas[l]->getPeso() <   this->arestas[menor]->getPeso()) {
        menor = l;
    }

    if (r < this->tamanhoHeap  && this->arestas[r]->getPeso() < this->arestas[menor]->getPeso()  ) {
        menor = r;
    }

    if (menor != i ) {
        aux = this->arestas[i];
        this->arestas[i] = this->arestas[menor];
        this->arestas[menor] = aux;
        minheapify(menor);
    }
}


void Heap::maxheapify(int i ) {
    int l = this->esq(i);
    int r = this->dir(i);
    int maior = i;
    Aresta *aux = new Aresta() ;


    if (l < this->tamanhoHeap && this->arestas[l]->getPeso() >   this->arestas[maior]->getPeso()) {
        maior = l;
    }

    if (r < this->tamanhoHeap  && this->arestas[r]->getPeso() > this->arestas[maior]->getPeso()  ) {
        maior = r;
    }

    if (maior != i ) {
        aux = this->arestas[i];
        this->arestas[i] = this->arestas[maior];
        this->arestas[maior] = aux;
        maxheapify(maior);
    }
}

void Heap::constroiMaxHeap() {
    this->tamanhoHeap = this->tamanho;
    for (int i = (this->tamanho)/2 - 1; i >= 0  ; i--) {
        this->maxheapify(i);
    }
}

void Heap::constroiMinHeap() {
    this->tamanhoHeap = this->tamanho;
    for (int i = (this->tamanho)/2 - 1; i >= 0  ; i--) {
        this->minheapify(i);
    }
}


Aresta** Heap::heapSort() {
    this->constroiMaxHeap();
    for (int i = this->tamanho-1; i >= 0; i--) {
        Aresta *aux  =  this->arestas[0];
        this->arestas[0] = this->arestas[i];
        this->arestas[i] = aux;
        this->tamanhoHeap--;
        this->maxheapify(0);
    }
    return this->arestas;
}

Aresta* Heap::extraimin() {
    Aresta *min;
    if (this->tamanhoHeap < 0) {
        cout <<  "underflow";
    }

    min = this->arestas[0];
    this->arestas[0] = this->arestas[this->tamanhoHeap-1];
    this->tamanhoHeap--;
    this->tamanho--;
    this->minheapify(0);
    return min;
}

void Heap::decreasekey(int i , Aresta *key) {

    if (key->getPeso() < this->arestas[i]->getPeso()) {
        this->arestas[i] = key;
        while ((i > 0 && this->arestas[this->pai(i)]->getPeso() > this->arestas[i]->getPeso())) {
            Aresta *aux = this->arestas[i];
            this->arestas[i] = this->arestas[this->pai(i)];
            this->arestas[this->pai(i)] = aux;
            i = this->pai(i);
        }
    }
}


void Heap::insert(Aresta *key) {

    this->tamanhoHeap++;
    int i = tamanhoHeap -1;
    this->arestas[i] = key;

    while (i != 0 && this->arestas[this->pai(i)]->getPeso() > this->arestas[i]->getPeso())
    {
        Aresta *aux = this->arestas[i];
        this->arestas[i] = this->arestas[this->pai(i)];
        this->arestas[this->pai(i)] = aux;
        i = this->pai(i);
    }


}

Aresta **Heap::getAresta() {
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
    float mst();
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

        this->subconjunto[vertice].setParent( this->findSet( this->subconjunto[vertice].getParent() )  );
    }
    return this->subconjunto[vertice].getParent();
}



void Kruskal::link(int vertice1, int vertice2 ) {

    if (this->subconjunto[vertice1].getRank() < this->subconjunto[vertice2].getRank()) {
        this->subconjunto[vertice1].setParent(vertice2);
    }else if (this->subconjunto[vertice1].getRank() >  this->subconjunto[vertice2].getRank())
            this->subconjunto[vertice2].setParent(vertice1);
     else {
        this->subconjunto[vertice2].setParent(vertice1);
        this->subconjunto[vertice1].setRank( this->subconjunto[vertice1].getRank() + 1 );
     }
}


void Kruskal::uniondisjunt(int vertice1 , int vertice2) {
    this->link( this->findSet(vertice1), this->findSet(vertice2));
}

float Kruskal::mst() {
    this->inc = 0;
    this->resultado = new Aresta[grafo->getOrdem()];
    float soma = 0;

    for (int i = 0; i < grafo->getOrdem();i++) {
        this->subconjunto[i].setParent(i);
        this->subconjunto[i].setRank(0);
    }

    Heap heap(this->grafo->getAresta(),this->grafo->getTamanho());
    heap.heapSort();

    for (int i = 0; i < grafo->getTamanho(); i++) {

        int u = findSet(grafo->getAresta()[i]->getSrc());
        int v = findSet(grafo->getAresta()[i]->getDst());

        if ( u != v) {
            this->resultado[inc] = *grafo->getAresta()[i];
            this->inc++;
            this->uniondisjunt(u, v);
        }

    }

    for (int i = 0; i<inc;i++) {
        soma = resultado[i].getPeso() + soma ;
    }

    return soma;

}

class Dijkstra {
private:

    Heap *filaPrioridade;
    vector<Aresta*> *vertices;
    Grafo *grafo;
    float **matriz;

public:
    Dijkstra(Grafo*);
    void inicializa(int);
    void relaxa(int,int,float);
    Aresta* CaminhoMinimo(int);
    vector<Aresta*> *getVertices();


};

Dijkstra::Dijkstra(Grafo *grafo) {

    this->grafo = grafo;
    this->filaPrioridade = new Heap(grafo->getOrdem());
    this->vertices = new vector<Aresta*>();

    this->matriz = new float*[this->grafo->getOrdem()];
    for (int i= 0; i < this->grafo->getOrdem();i++) {
        this->matriz[i] = new float[this->grafo->getOrdem()];
    }
    this->matriz = this->grafo->getMatriz();

}

void  Dijkstra::inicializa(int inicio) {

    for (int i = 0; i < this->grafo->getOrdem();i++)   {
        Aresta *vertice = new Aresta();
        vertice->setDst(i);
        vertice->setSrc(-1);
        vertice->setPeso(9998);
        this->vertices->push_back(vertice);
        this->filaPrioridade->insert(vertice);

    }

    this->vertices->at(inicio)->setPeso(0);
    this->filaPrioridade->constroiMinHeap();




}

void Dijkstra::relaxa(int u , int v , float w ) {

    if (this->vertices->at(v)->getPeso() > this->vertices->at(u)->getPeso() + w  ) {
        this->vertices->at(v)->setPeso( this->vertices->at(u)->getPeso() + w );
        this->vertices->at(v)->setSrc(u);
        this->filaPrioridade->constroiMinHeap();


    }


}


Aresta* Dijkstra::CaminhoMinimo(int inicio) {

    this->inicializa(inicio);

    for (int i = 0; i < this->grafo->getOrdem(); i++) {

        Aresta *u  = this->filaPrioridade->extraimin();


        for (int j = 0 ; j < grafo->getOrdem();j++) {

            if  (this->matriz[u->getDst()][j] != 0) {
                this->relaxa(u->getDst(), j , matriz[u->getDst()][j]);

            }

        }

    }

}

vector<Aresta*> *Dijkstra::getVertices() {
    return this->vertices;
}




int main() {

    int ordem;
    int tamanho;
    int src;
    int dst;
    float peso;
    int entrada;
    int saida;
    int qtdNeurDoentes;
    int neuronioDoente;
    bool *blocodoente;
    float soma = 0;

    cin >> ordem;
    cin >> tamanho;



    Grafo *cerebro = new Grafo(ordem,tamanho);
    Grafo **bloco = new Grafo*[ordem];
    blocodoente = new bool[ordem];


    //pegando as arestas
    for (int i = 0; i < cerebro->getTamanho(); i++) {
        cin >> src;
        cin >> dst;
        cin >> peso;
        cerebro->insertEdge(src-1,dst-1,peso);
    }

        cin >> entrada;
        cin >> saida;


        //loop para pegar os blocos
        for (int i = 0; i < cerebro->getOrdem(); i++) {
            cin >> ordem;
            cin >> tamanho;
            cin >> qtdNeurDoentes;

            for (int j = 0; j < qtdNeurDoentes;j++) {
                cin >> neuronioDoente;
            }

            if (qtdNeurDoentes != 0) {
                blocodoente[i] = true;
            }else {
                blocodoente[i] = false;
            }

            bloco[i] = new Grafo(ordem,tamanho);

            //loop para pegar source e destino de cada bloco
            for (int j = 0;j < tamanho; j++ ) {
                cin >> src;
                cin >> dst;
                cin >> peso;
                bloco[i]->insertEdge(src-1,dst-1,peso);
            }
        }

    Dijkstra dijkstra(cerebro);
    dijkstra.CaminhoMinimo(entrada-1);
    vector<Aresta*> *navegar = dijkstra.getVertices();
    int numeroBloco = navegar->at(saida-1)->getSrc();

    if (blocodoente[saida-1]) {
        Kruskal caminhoMinimoEntrada(bloco[saida - 1]);
        soma = caminhoMinimoEntrada.mst() + soma;
    }
    while (numeroBloco != -1) {
        if (blocodoente[numeroBloco]) {
            Kruskal caminhoMinimo(bloco[numeroBloco]);
            soma = caminhoMinimo.mst() + soma;
        }
            numeroBloco = navegar->at(numeroBloco)->getSrc();

    }

    cout << soma;


    return 0;
}