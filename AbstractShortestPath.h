/* 
 * File:   AbstractShortestPath.h
 * Author: Daniel Princ
 */

#ifndef ABSTRACTSHORTESTPATH_H
#define	ABSTRACTSHORTESTPATH_H

template<class T> class AbstractShortestPath {
public:
    virtual void find(const int from, const int to) const=0;
    virtual std::string getPath() const=0;
    
    T getLength() const {
        return shortestPath;
    };
    
protected:
    Graph<T>* graf;
    T shortestPath;
};



#endif	/* ABSTRACTSHORTESTPATH_H */
