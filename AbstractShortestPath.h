/* 
 * File:   AbstractShortestPath.h
 * Author: Daniel Princ
 */

#ifndef ABSTRACTSHORTESTPATH_H
#define	ABSTRACTSHORTESTPATH_H

#include <map>
#include <vector>

template<class T> class AbstractShortestPath {
public:
    
    virtual void find(const int from, const int to)=0;
    
    T getLength() const {
        return shortestPath;
    };
    
    std::string getPath() const {
        return this->result;
    }
    
    
protected:
    Graph<T>* graf;
    T shortestPath;
    std::string result;
    
    static const T INFINITY = (T) 99999999;
};



#endif	/* ABSTRACTSHORTESTPATH_H */
