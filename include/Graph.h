#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>

struct EdgeNode
{
    int neighborID;
    int weight;
    EdgeNode *next;

    EdgeNode(int neighbID, int w) : neighborID(neighbID), weight(w), next(nullptr) {};
};

struct VertexHashNode
{
    std::string name;
    int vertexID;
    EdgeNode *edges;
    VertexHashNode *next;

    VertexHashNode(std::string n, int id) : name(n), vertexID(id), edges(nullptr), next(nullptr) {};
};

class Graph
{
private:
    const static int CAPACITY = 10009;
    int numberOfVertices;

    int *parent;
    int dsuCapacity;

    VertexHashNode *vertices[CAPACITY];

    int getHash(std::string name);
    void resizeDSU();
    int dsuFind(int i);
    void dsuUnion(int i, int j);

public:
    Graph();
    ~Graph();

    void GAddNode(std::string nodeName);
    void GAddEdge(std::string src, std::string dest, int weight);
    void GIsConnected(std::string src, std::string dest);
};

#endif