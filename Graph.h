/* 
 * File:   Graph.h
 * Author: Daniel Princ
 */

#ifndef GRAPH_H
#define	GRAPH_H

#include <iostream>
#include <vector>
#include <utility>
#include "Vertex.h"


using namespace std;

template<class T> class Graph {
public:    
    
    Graph() {}
    /**
     * Novy graf
     * @param size pocet vrcholu
     */
    Graph(const int size) {    
        this->num_verticies = size;
        this->verticies = new Vertex<T>*[size];
        for(int i = 0; i < size; i++) {
            this->verticies[i] = new Vertex<T>(i);
        }
    }
    ~Graph() {
        delete [] this->verticies;
    };
    
    /**
     * Vklada do grafu novou hranu
     * @param from Uzel ze ktereho hrana jde
     * @param to Uzel do ktereho hrana jde
     * @param length delka hrany
     */
    void add(const int from, const int to, const T length) {
        Vertex<T> *f = verticies[from];
        Vertex<T> *t = verticies[to]; //todo:tady mozna ukazatel na lokalni promennou??
        f->getEdges()->push_back(pair<T, Vertex<T>*>(length, t));
    }
    
    int size(void) const {
        return this->num_verticies;
    }
    
    Vertex<T>** getVerticies(void) {
        return verticies;
    }
    
private:    
    int num_verticies;
    Vertex<T> **verticies; //ukazatel na pole vrcholu

};

#endif	/* GRAPH_H */
