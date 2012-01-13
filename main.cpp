#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>   // file I/O
#include <string>
#include <stdexcept>  //out_of_range exception

#include "Graph.h"
#include "DijsktraShortestPath.h"

using namespace std;

void printUsage(){
	cout << "\nUsage:\n" <<
                "\tgraphFile source dest algorithm\n" <<
                "\tsource, dest = number of the vertex from graphFile\n" <<
                "\talgorithm = [D|FW]";
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

    if(argc == 5){
        fileStream.open(argv[1]);
        if(!fileStream.is_open()){
            printUsage();
            return 1;
        }
    } else {
        printUsage();
        return 1;
    }
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
    
    
    DijsktraShortestPath<int> dijkstra(graf);
    dijkstra.find(0, 33);
    
    return 0;
}
