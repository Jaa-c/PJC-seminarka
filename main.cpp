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
                "\talgorithm = [D|FW|M] \n" <<
                "\t\tD = Dijkstra's algorithm\n" <<
                "\t\tFW = Floyd–Warshall algorithm\n" <<
                "\t\tM = Modified matrix multiplication\n\n";
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

int str2int(string line) {
  istringstream is(line);
  int num;
  is >> num;
  return num;
}

/*
 * 
 */
int main(int argc, char **argv) {
    ifstream fileStream;
    string line;
    
    int alg = -1;
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
        
        from = str2int(argv[2]);
        to = str2int(argv[3]);
        if( from < 0 || to < 0) {
            printUsage();
            return 1;
        }
        
        string arg = argv[4];
        if(arg == "D")
            alg = 0;
        else if(arg == "FW")
            alg = 1;
        else if(arg == "M")
            alg = 2;
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
        if(line == "START") {
            getline(fileStream, line);
            split(line, first);
            verticies = str2int(line);
            break;
        }
    }
    if(verticies < 3) {
        cout << "error parsing file, graph does not have at least 3 verticies!\n";
        return 10;
    }
    
    int destVertex = -1;
    int length = -1;
    int currentVertex = -1;
    Graph<int> graf(verticies);
    
    //naplneni grafu daty
    while(getline(fileStream, line)) {
        if(line == "END") break;
        
        split(line, first);
        
        if(first == "DEFINE") {
            currentVertex = str2int(line.substr(1,line.length()));
        }
        else {
            destVertex = str2int(first.substr(1,first.length()));
            length = str2int(line);
            
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
    AbstractShortestPath<int>* algorithm;
    switch(alg) {
        case 0:
            algorithm = new DijsktraShortestPath<int>(graf);
            break;
        case 1:            
            algorithm = new FloydWarshallShortestPath<int>(graf);
            break;
    }
    
    try {
        algorithm->find(2, 6);
    }
    catch(char const* string) {
        cout << "CHYBA: \n\t" << string << "\n";
        return 1;
    }
    
    //vypiseme nalezenou cestu
    cout << algorithm->getPath();
    cout << algorithm->getLength();
    
    
    delete algorithm;
    
    return 0;
}
