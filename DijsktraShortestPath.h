/* 
 * File:   DijsktraShortestPath.h
 * Author: Daniel Princ
 */

#ifndef DIJSKTRASHORTESTPATH_H
#define	DIJSKTRASHORTESTPATH_H

#include <queue>
#include <map>
#include "Graph.h"
#include "AbstractShortestPath.h"
#include "Vertex.h"

using namespace std;

template<class T> class DijsktraShortestPath : AbstractShortestPath<T> {
public:
    DijsktraShortestPath(Graph<T>& graf) {
        this->graf = &graf;
    }
    ~DijsktraShortestPath() {}
    
    void find(const int from, const int to) const {
        
        typedef typename Vertex<T>::iterator vertexIter; //iterator vertexu
        typedef typename multimap<T, Vertex<T>* >::iterator mapIter; //iterator mapy
        typedef pair<T, Vertex<T>*> edgePair; //delka hrany a kam vede
        typedef vector<edgePair> edges; //vektor hran
        
        multimap<T, Vertex<T>* > data; //na zpusob prioritni fronty
        int size = this->graf->size();
        
        Vertex<T> ** verticies = this->graf->getVerticies();
        unsigned P[size];
        T D[size];
        
        for(int i = 0; i < size; i++) {
	    D[i] = (T) 9999998; //asi to neni uplne optimalni :/
	    P[i] = 0;
	}
        D[from] = 0;
        
        for(int i = 0; i < size; i++) {
            verticies[i]->setVzdalenost(D[i]);
            data.insert(edgePair(D[i] , verticies[i]));
	}
        
        while(data.size() != 0) {
            int i = data.size();
            cout << "size: " << data.size() << endl;
             
            for(mapIter itr = data.begin(); itr != data.end(); itr++) {
                cout << itr->second->getId() << ": " << itr->first << ",  ";
            }
            cout << "\n";
            mapIter head = data.begin();
            T first = head->first;
	    Vertex<T> * vrchol = head->second;
            data.erase(head);
            
            if(vrchol->getId() == 16) {
                cout << "x" <<endl;
            }
            
            cout << "\nV: " << vrchol->getId() << endl;
            cout << "L: " << vrchol->getVzdalenost() << endl;
            
            edges e = *vrchol->getEdges();
            edgePair p = e[0];
            
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
                    while(true) {//it->first == vzd) {
                        Vertex<T> * ve = it->second;
                        if(ve == w)  {
                            data.erase(it);
                            cout << "erase: " << ve->getId() << endl;
                            w->setVzdalenost(D[w->getId()]); //tady se nasetuje ta nova vzdalenost!!
                            data.insert(edgePair(w->getVzdalenost() , w));
                            cout << "insert: " << w->getVzdalenost() <<endl;
                            break;
                        }
                        else
                            it++;
                    }
		}
	    }
	}
        
        cout << "vysledek: " << D[to];
    
    
    }
    
    string getPath() const {
        return string("a");
    }
   
};

#endif	/* DIJSKTRASHORTESTPATH_H */