#ifndef GRAPH_H
#define GRAPH_H

#include "LocatorHeap.h"

#include <vector>
using std::vector;


class Edge;

class Vertex
{
public:
    int label;
    vector<Edge*> edges;

    // helpers stored inside a vertex to help with path finding
    // you can use different auxilliary structures if desired
    bool visited;
    float distanceTo;
    vector<Vertex*> pathTo;
    Heap<Vertex*>::Locator locator;
    bool operator < ( const Vertex &v ) const 
    { 
        return this->distanceTo < v.distanceTo;
    }

    Vertex ( int l ) : label (l) { }
};

class Edge
{
public:
    Vertex *v1, *v2;
    float weight;

    Edge ( Vertex *nv1, Vertex *nv2, float newWeight ) : v1 ( nv1 ), v2 ( nv2 ), weight ( newWeight ) { }
};


class Graph
{
protected:
    vector<Vertex*> v;
    vector<Edge*> e;

public:
    Graph () {}

    ~Graph ()
    {
        for(Vertex* vertex : v)
        {
            delete vertex;
        }
        for(Edge* edge : e)
        {
            delete edge;
        }
    }

    // TODO: complete rule of 3
    Graph operator=(Graph &rhs)
    {
        for(Vertex* vertex : this->v)
        {
            delete vertex;
        }
        this->v.clear();

        for(Edge* edge : this->e)
        {
            delete edge;
        }
        this->e.clear();

        for(Vertex* vertex : rhs.v)
        {
            Vertex* newVertex = new Vertex(vertex->label);
            this->v.push_back(newVertex);
        }

        for(Edge* edge : rhs.e)
        {
            Vertex* v1 = this->getVertex(edge->v1->label);
            Vertex* v2 = this->getVertex(edge->v2->label);
            this->insertEdge(v1->label, v2->label, edge->weight);
        }

        return *this;
    }

    Vertex* getVertex(int label) //getVertex helper
    {
        for(Vertex* vertex : v)
        {
            if(vertex->label == label)
            {
                return vertex;
            }
        }
        return nullptr;
    }

    void insertVertex ( int label )
    {
        Vertex* vnew = new Vertex(label);
        v.push_back(vnew);
    }

    void insertEdge ( int l1, int l2, float weight )
    {
        Vertex* v1 = getVertex(l1);
        Vertex* v2 = getVertex(l2);
        //check for if empty
        if(v1 == nullptr || v2 == nullptr)
        {
            throw std::runtime_error("vertex not found");
        }

        Edge* newEdge = new Edge(v1, v2, weight);
        e.push_back(newEdge);
        v1->edges.push_back(newEdge);
        v2->edges.push_back(newEdge);
    }

    vector<Vertex*> shortestPath ( int start, int end )
    {
        Vertex* currentNode = nullptr;
        Vertex* endNode = nullptr;
        for(Vertex* v : v)
        {
            v->visited = false;
            v->pathTo.clear();
            v->distanceTo = INT32_MAX; //get really large number
            if(v->label == start)
            {
                currentNode = v;
            }
            if(v->label == end)
            {
                endNode = v;
            }
        }
        //checks for debugging
        if(currentNode == nullptr)
        {
            throw std::runtime_error("start node not found in graph");
        }
        if(endNode == nullptr)
        {
            throw std::runtime_error("end node not found in graph");
        }
        currentNode->distanceTo = 0.0;
        currentNode->pathTo.push_back(currentNode);

        Heap<Vertex*> queue;
        for(Vertex* vertex : v)
        {
            vertex->locator = queue.insertElement(vertex);
        }

        while(!endNode->visited && !queue.isEmpty())
        {
            currentNode = queue.removeMin();
            currentNode->visited = true;

            vector<Edge*> nextEdges;
            for(Edge* e : currentNode->edges)
            {
                if(e->v1 == currentNode || e->v2 == currentNode)
                {
                    nextEdges.push_back(e);
                }
            }

            for(Edge* e : nextEdges)
            {
                Vertex* nextNode = nullptr;
                if(e->v1 == currentNode)
                {
                    nextNode = e->v2;
                }
                else if(e->v2 == currentNode)
                {
                    nextNode = e->v1;
                }

                if(!nextNode->visited)
                {
                    float candidateDistance = currentNode->distanceTo + e->weight;
                    if(candidateDistance < nextNode->distanceTo)
                    {
                        nextNode->distanceTo = candidateDistance;
                        nextNode->pathTo = currentNode->pathTo;
                        nextNode->pathTo.push_back(nextNode);
                        queue.update(nextNode->locator);
                    }
                }
            }
        }

        return endNode->pathTo;
    }
};

#endif
