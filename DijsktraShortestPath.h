/* 
 * File:   DijsktraShortestPath.h
 * Author: Daniel Princ
 */

#ifndef DIJSKTRASHORTESTPATH_H
#define	DIJSKTRASHORTESTPATH_H

#include <queue>
#include <map>
#include <sstream>
#include "Graph.h"
#include "AbstractShortestPath.h"
#include "Vertex.h"

using namespace std;

template<class T> class DijsktraShortestPath : public AbstractShortestPath<T> {
public:
    DijsktraShortestPath(Graph<T>& graf) {
        this->graf = &graf;
    }
    ~DijsktraShortestPath() {}
    
    void find(const int from, const int to) {
        
        typedef typename Vertex<T>::iterator vertexIter; //iterator vertexu
        typedef typename std::multimap<T, Vertex<T>* >::iterator mapIter; //iterator mapy
        typedef std::pair<T, Vertex<T>*> edgePair; //delka hrany a kam vede
        typedef std::vector<edgePair> edges; //vektor hran 
        
        multimap<T, Vertex<T>* > data; //na zpusob prioritni fronty
        int size = this->graf->size();
        if(size <= to)
            throw "Cilovy bod je nedosazitelny";
        
        Vertex<T> ** verticies = this->graf->getVerticies();
        unsigned P[size];
        T D[size];
        
        for(int i = 0; i < size; i++) {
	    D[i] =  this->INFINITY; //asi to neni uplne optimalni :/
	    P[i] = 0;
	}
        D[from] = 0;
        
        for(int i = 0; i < size; i++) {
            verticies[i]->setVzdalenost(D[i]);
            data.insert(edgePair(D[i] , verticies[i]));
	}
        
        while(data.size() != 0) {
            mapIter head = data.begin();
	    Vertex<T> * vrchol = head->second;
            data.erase(head);

            
            for(vertexIter it = vrchol->begin(); it != vrchol->end(); it++) {
                
                edgePair pair = *it;
		Vertex<T>* w = pair.second;
                T value = pair.first;
		if(D[w->getId()] > vrchol->getVzdalenost() + value) {
		    D[w->getId()] = vrchol->getVzdalenost() + value; //nova delka
		    P[w->getId()] = vrchol->getId(); //predek

		    //zmenime klic ve fronte - odeberu a pridam s novym klicem
                    T vzd = w->getVzdalenost();
                    mapIter it = data.find(vzd);
                    while(true) {
                        Vertex<T> * ve = it->second;
                        if(ve == w)  {
                            data.erase(it);
                            w->setVzdalenost(D[w->getId()]); //tady se nasetuje ta nova vzdalenost!!
                            data.insert(edgePair(w->getVzdalenost() , w));
                            break;
                        }
                        else
                            it++;
                    }
		}
	    }
	}
        
        
        size--;
        this->shortestPath = D[to];   
        
        if(this->shortestPath == this->INFINITY)
            throw "Cesta do daneho bodu neexistuje";
        
        //ted uz jen zpetne najdu kudy jsem vlastne sel       
	int tempPredek = to;
	int tempPocatek = size;
	vector<int> cesta;
	while(tempPocatek != 0) {
	    for(int i = size; i >= 0; i--) {
		if(i == tempPredek) {
		    cesta.push_back(tempPredek);
		    tempPredek = P[i];
		    tempPocatek = tempPredek;
		    break;
		}
	    }
	}
        
        
        stringstream c;
        c << from << " -> ";
	for(int i = cesta.size()-1; i>0; i--) {
            if(cesta[i] != from)
                c << cesta[i] << " -> " ;
	}        
	c << to;
        
        this->result = c.str();
    }
   
   
};

#endif	/* DIJSKTRASHORTESTPATH_H */