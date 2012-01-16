#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>   // file I/O
#include <string>
#include <stdexcept>  //out_of_range exception

#include "Graph.h"
#include "DijsktraShortestPath.h"
#include "FloydWarshallShortestpath.h"

using namespace std;

void printUsage(){
	cout << "\nUsage: [graphFile] [source] [dest] [algorithm]\n" <<
                "\tgraphFile = source file with graph data\n" <<
                "\tsource, dest = number of the vertex from graphFile\n" <<
                "\talgorithm = [D|FW] \n" <<
                "\t\tD = Dijkstra's algorithm\n" <<
                "\t\tFW = Floyd–Warshall algorithm\n";
                //"\t\tM = Modified matrix multiplication\n\n";
}

/**
 * rozdeli radek podle daneho znaku a const poctu znaku
 * 
 * @param line vstupni/vystupni parametr, radek bez prvniho slova a deliciho znaku
 * @param param vystupni parametr, prvni slovo
 */
void split(string &line, string &param) {
    //orezeme whitespaces na zacatku
    unsigned j = 0;
    while(isspace(line[j])) j++;
    
    for(unsigned i = j; i < line.length(); i++) {
        if(line[i] == ' ' || line[i] == '-' || line[i] == '=') {
            try {
                param = line.substr(j, i-j);
                line = line.substr(i+1);
            }
            catch(out_of_range &e) {
                return;
            }
            break;
        }
    }
}

/**
 * Prevadi string na int/double...
 * @param line
 * @return 
 */
template <class T>
T str2t(string line) {
  istringstream is(line);
  T num;
  is >> num;
  return num;
}

/**
 * Dela sechno :)
 * @param fileStream vstupni soubor
 * @param verticies pocet vrcholu
 * @param from vychozi vrchol
 * @param to cilovy vrchol
 * @param alg typ algoritmu
 * @return status
 */
template<class T> int  
parse(ifstream& fileStream, int verticies, int from, int to, int alg) {
    string first;
    string line;
    
    int destVertex = -1;
    T length = -1;
    int currentVertex = -1;
    
    Graph<T> graf(verticies);  //instance grafu
    
    //naplneni grafu daty
    while(getline(fileStream, line)) {
        if(line == "END") break;
        
        split(line, first);
        
        if(first == "DEFINE") {
            currentVertex = str2t<int>(line.substr(1,line.length()));
        }
        else {
            destVertex = str2t<int>(first.substr(1,first.length()));
            length = str2t<T>(line);
            
            if(length != -1 && destVertex != -1 && currentVertex != -1) {
                graf.add(currentVertex, destVertex, length);
            }
            else {
                cout << "error parsing file\n";
                return 10;
            }
        }
    }
    
    /**
     * Vytvoreni instace grafu a vyhledani cesty
     */    
    AbstractShortestPath<T>* algorithm;
    switch(alg) {
        case 0:
            cout << "Using Dijkstra's algorithm\n";
            algorithm = new DijsktraShortestPath<T>(graf);
            break;
        case 1:        
            cout << "Using Floyd–Warshall algorithm\n";
            algorithm = new FloydWarshallShortestPath<T>(graf);
            break;
        default:
            return 1;
    }
    
    try {
        algorithm->find(from, to); //tady se provadi vlastni hledani
    }
    catch(char const* string) {
        cout << "ERROR: \n\t" << string << "\n";
        return 1;
    }
    
    //vypiseme nalezenou cestu
    cout << "Shortest path from " << from << " to " << to << ":\n";
    cout << "\tPath:   " << algorithm->getPath() << "\n";
    cout << "\tLength: " << algorithm->getLength() << "\n";
    
    
    delete algorithm;
    
    return 0;
}

/*
 * 
 */
int main(int argc, char **argv) {
    ifstream fileStream;
    string line;
    
    int alg = -1;
    int type = -1;
    int from, to;
    
    /**
     * Zpracovani argumentu
     */
    if(argc == 5){
        fileStream.open(argv[1]);
        if(!fileStream.is_open()){
            printUsage();
            return 1;
        }
        
        from = str2t<int>(argv[2]);
        to = str2t<int>(argv[3]);
        if( from < 0 || to < 0) {
            printUsage();
            return 1;
        }
        
        string arg = argv[4];
        if(arg == "D")
            alg = 0;
        else if(arg == "FW")
            alg = 1;
        //else if(arg == "M")
        //    alg = 2;
        else {
            printUsage();
            return 1;
        }
         
        
    } 
    else {
        printUsage();
        return 1;
    }
    
    /**
     * Parsovani nacteneho souboru
     */
    int verticies = 0;
    string first;
    while(getline(fileStream, line)) {
        split(line, first);
        if(line == "INT")
            type = 0;
        else if(line == "DOUBLE")
            type = 1;
        
        if(first == "START") {
            getline(fileStream, line);
            split(line, first);
            verticies = str2t<int>(line);
            break;
        }
    }
    if(verticies < 3) {
        cout << "error parsing file, graph does not have at least 3 verticies!\n";
        return 10;
    }
    
    //tady je treba rozhodnout, s jakym typem budeme pracovat
    int ret = 0;
    switch(type) {
        case 0:
            ret= parse<int>(fileStream, verticies, from, to, alg);
            break;
        case 1:
            ret= parse<double>(fileStream, verticies, from, to, alg);
            break;
        default:
            ret= 1;   
    }
    
    if(ret== 0)
        return 0;
    
    cout << "\nNastala chyba programu, ukončuji.\n";
    return 1;
    
}
