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
            matrix[i] = new int[size];
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
                P[i][j] = -1;
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
        for(int i = 0; i < size; i++) 
                for(int j = 0; j < size; j++) 
                        cout << i << ":" << j << " " << matrix[i][j] <<endl;
                
        //this->shortestPath = getPath(matrix, P, from, to);
        
        
        delete [] matrix;
        delete [] P;       
    
    }
    
private:
    int getPath(T** matrix, int** P, int from, int to) {
        if(matrix[from][to] == this->INFINITY)
            throw "Cesta do daneho bodu neexistuje";
        int i = P[from][to];
        if(from == to) 
            return 0;
        cout << matrix[from][to] << endl;
        return getPath(matrix, P, from, i) +  i + getPath(matrix, P, i, to);
    }
    
    

};

#endif	/* FLOYDWARSHALLSHORTESTPATH_H */

