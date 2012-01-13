/* 
 * File:   Vertex.h
 * Author: jaa
 *
 * Created on 13. leden 2012, 0:33
 */

#ifndef VERTEX_H
#define	VERTEX_H

#include <vector>

using namespace std;


template<class T> class Vertex {
    typedef vector< pair<T, Vertex<T>*> > Edges;
    
private:
    Edges edges;
    T vzdalenost; //vzdalenost od hledaneho bodu
    int id;
    
public:  
    Vertex(int id) {
        this->vzdalenost = 0;
        this->id = id;
    }
    ~Vertex(void) {}

    void setVzdalenost(T v) {
        vzdalenost = v;
    }

    T getVzdalenost(void) const {
        return vzdalenost;
    }
    
    Edges* getEdges(void) {
        return &edges;
    }
    
    const int getId() const {
        return id;
    }
    
    
    class iterator {
    public:
        typedef typename Edges::iterator iter;
        iter it;
        
        iterator() {}
        
        iterator(iter first) {
            this->it = first;
        }

        iterator operator ++(int) {
            this->it++;
            return *this;
        }

        pair<T, Vertex<T>*>& operator *() {
            return *(this->it);
        }

        bool operator !=(const iterator& f) const {
            return this->it != f.it;
        }
    };
    
    iterator begin() {
        return iterator(edges.begin());
    }
    
    iterator end() {
        return iterator(edges.end());
    }
    
    bool operator < (const Vertex<T> & compare) const {
        return this->vzdalenost < compare.vzdalenost;
    }
    
    bool operator > (const Vertex<T> & compare) const {
        return this->vzdalenost > compare.vzdalenost;
    }
    
    bool operator == (const Vertex<T> & compare) const {
        return this->vzdalenost == compare.vzdalenost;
    }
    
    bool operator != (const Vertex<T> & compare) const {
        return this->vzdalenost != compare.vzdalenost;
    }

    
};

#endif	/* VERTEX_H */
