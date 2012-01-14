/* 
 * File:   FloydWarshallShortestpath.h
 * Author: Daniel Princ
 *
 * Created on 14. leden 2012, 3:59
 */

#ifndef FLOYDWARSHALLSHORTESTPATH_H
#define	FLOYDWARSHALLSHORTESTPATH_H

using namespace std;

template<class T> class FloydWarshallShortestPath : public AbstractShortestPath<T> {
public:
    FloydWarshallShortestPath(Graph<T>& graf) {
        this->graf = &graf;
    }
    ~FloydWarshallShortestPath() {}
    
    void find(const int from, const int to) {
        
        typedef typename Vertex<T>::iterator vertexIter; //iterator vertexu
        typedef typename std::multimap<T, Vertex<T>* >::iterator mapIter; //iterator mapy
        typedef std::pair<T, Vertex<T>*> edgePair; //delka hrany a kam vede
        typedef std::vector<edgePair> edges; //vektor hran 
        
        const int size = this->graf->size();
        if(size <= to)
            throw "Cilovy bod je nedosazitelny";
        
        //inicializace matice, vsude krome diagonaly nekonecno, diag na 0
        T ** matrix = new T*[size];
        for(int i = 0; i < size; i++) {
            matrix[i] = new T[size];
            for(int j = 0; j < size; j++) {
                if(i != j)
                    matrix[i][j] = this->INFINITY;
                else
                    matrix[i][j] = 0;
            }
        }
        
        Vertex<T> ** verticies = this->graf->getVerticies();
        
        /**
         * Inicializace vychozich hodnot matice
         */
        for(int i = 0; i < size; i++) {            
            //existujici hodnoty v grafu - hrany
            for(vertexIter it = verticies[i]->begin(); it != verticies[i]->end(); it++) {
                edgePair pair = *it;
		Vertex<T>* vert = pair.second;
                
                T value = pair.first;
                int j = vert->getId();
                
                matrix[i][j] = value;                                
            }
        
        }
        
        /**
         * naplneni matice predku p
         */
        int **P = new int *[size];        
        for(int i = 0; i < size; i++) {
            P[i] = new int[size];
            for(int j =0; j < size; j++) {
                P[i][j] = 0;
            }
        }
        
        
        for(int k = 0; k < size; k++) {
            for(int i = 0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                    if(matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                        P[i][j] = k;
                    }
                }
            }
        }

                    
        
        if(matrix[from][to] == this->INFINITY)
            throw "Cesta do daneho bodu neexistuje";
                
        this->shortestPath = matrix[from][to];

        string res = getPath(P, from, to);
        this->result = int2str(from) + " -> " + res + int2str(to);        
        
        delete [] matrix;
        delete [] P;       
    
    }
    
private:
    string getPath(int** P, int from, int to) {
        string s;
        if(P[from][to] == 0) //mezi vrcholy neni jiny vertex            
            return "";
        int inter = P[from][to];        
        s += getPath(P, from, inter);
        s += int2str(inter) + " -> ";
        s += getPath(P, inter, to);
        return s;
    }
    
    string int2str(int i) {
        stringstream ss;
        ss << i;
        return ss.str();
    }
    

};

#endif	/* FLOYDWARSHALLSHORTESTPATH_H */

