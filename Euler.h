// class declaration for Team Project 10
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <fstream>
#include "LinkedGraph.h"
#include "Edge.h"
#include "Vertex.h"
#include "LinkedStack.h"

using namespace std;

template <class LabelType>
class Euler : public LinkedGraph<LabelType>
{
private:
    void visit(LabelType &);
public:
	//This function is used to check if the graph makes a eulerian graph
	bool isEuler();
    bool isConnected();
};

template <class LabelType>
void Euler<LabelType>::visit(LabelType & label)
{
    this->vertices.getItem(label)->visit();
}

template <class LabelType>
bool Euler<LabelType>::isEuler()
{
	bool checkEulerian = false;
	// Check if all non-zero degree vertices are connected
	if (isConnected() == false)
		return 0;

	// Count vertices with odd degree
	int odd = 0;
    
    Vertex<LabelType> * startVertex;
    DACmapIterator<LabelType, Vertex<LabelType>*> * iter = this->vertices.iterator();
    while (iter->hasNext())
    {
        startVertex = iter->next();
        if (startVertex->getNumberOfNeighbors() % 2 == 1)
        {
            odd++;
        }
	}

	// If count is more than 2, then graph is not Eulerian
	// If odd count is 2, then semi-eulerian.
	// If odd count is 0, then eulerian
	// Note that odd count can never be 1 for undirected graph
	
	if (odd == 2)
	{
		cout << "There is one (one way or reverse) Eulerian path exists." << endl;
		checkEulerian = true;
	}
	else if (odd == 0)
	{
		cout << "There are Eulerian paths or circuits in this graph." << endl;
		checkEulerian = true;
	}
	else
		cout << "There are NO Eulerian paths or circuits available in this graph." << endl;
	
	return checkEulerian;
}

template <class LabelType>
bool Euler<LabelType>::isConnected()
{
    // If there are no edges in the graph, return false
    if (this->numberOfEdges == 0) return false;

	// Mark all the vertices as not visited
    this->unvisitVertices();

	// Find a vertex with non-zero degree to start the traversal
    Vertex<LabelType> * startVertex;
    DACmapIterator<LabelType, Vertex<LabelType>*> * iter = this->vertices.iterator();
    while (iter->hasNext()) {
        startVertex = iter->next();
        if (startVertex->getNumberOfNeighbors() > 0) break;
    }


	// Start DFS traversal from a vertex with non-zero degree
    // this->depthFirstTraversalHelper(startVertex, visit);

	// Check if all non-zero degree vertices are visited
    return true;
}