#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int main(int argc, const char * argv[]) {
    cout << "Filename of graph to load: ";

    // TODO: next five code snippets
    // Snippet 1: read filename and open file
    string filename;
    cin >> filename;
    ifstream ifs("Tests/" + filename); //in Tests folder
    if (!ifs.is_open())
    {
        cout << "unable to open input file pls check to see if in correct directory. (needs to be in Tests folder like given code)" << endl;
        return 1;
    }   
    // Snippet 2: get number graph size
    int VerNum, EdgNum;
    ifs >> VerNum >> EdgNum;
    //cout << "VerNum: " << VerNum << "EdgNum: " << EdgNum << endl;
    // Snippet 3: create graph
    Graph graph;
    for(int i = 0; i < VerNum; i++)
    {
        graph.insertVertex(i);
    }

    // Snippet 4: read edges
    for(int i = 0; i < EdgNum; i++)
    {
        int e1, e2; //e1 is origin, e2 is destination
        float weight;
        ifs >> e1 >> e2 >> weight;
        //cout << "e1: " << e1 << "e2: " << e2 << endl;
        graph.insertEdge(e1, e2, weight);
    }

    // Snippet 5: read start and end of path
    int startVertex, endVertex;
    ifs >> startVertex >> endVertex;
    ifs.close();
    //cout << "start: " << startVertex << "EdgNum: " << endVertex << endl;
    cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;

    vector<Vertex*> path;

    // TODO: call shortest path on your graph for the sstart and end verices and save result to path
    path = graph.shortestPath(startVertex, endVertex);
    for (auto i : path) { // this is a for-each loop
        cout << i->label << " ";
    }
    // cout endline at very end
    cout << endl;
    return 0;
}
