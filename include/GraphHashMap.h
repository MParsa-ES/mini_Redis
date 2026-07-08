#ifndef GRAPH_HASHMAP_H
#define GRAPH_HASHMAP_H

#include "Graph.h"

struct GraphHashNode
{
    std::string graphName;
    Graph graph;

    GraphHashNode *next;

    GraphHashNode(std::string name) : graphName(name), next(nullptr) {};
};

class GraphHashMap
{
private:
    static const int CAPACITY = 10009;

    GraphHashNode *arr[CAPACITY];

    int getHash(std::string name);

public:
    GraphHashMap();
    ~GraphHashMap();

    void GCreate(std::string graphName);
    void GAddNode(std::string graphName, std::string nodeName);
    void GAddEdge(std::string graphName, std::string src, std::string dest, int weight);
    void GConnected(std::string graphName, std::string src, std::string dest);
    void GMST(std::string graphName);
};

#endif