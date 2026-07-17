#include "Graph.h"

Graph::Graph()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        vertices[i] = nullptr;
    }
    numberOfVertices = 0;

    dsuCapacity = 4;
    parent = new int[dsuCapacity];

    mst_weight = 0;
    lctNodes = new LCTNode *[dsuCapacity];
}

Graph::~Graph()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        VertexHashNode *currVertex = vertices[i];
        while (currVertex != nullptr)
        {
            EdgeNode *currEdge = currVertex->edges;
            while (currEdge != nullptr)
            {
                EdgeNode *tempEdge = currEdge;
                currEdge = currEdge->next;
                delete tempEdge;
            }

            VertexHashNode *tempVertex = currVertex;
            currVertex = currVertex->next;
            delete tempVertex;
        }
        vertices[i] = nullptr;
    }
    for (int i = 0; i < numberOfVertices; i++)
    {
        delete lctNodes[i];
    }
    delete[] lctNodes;
    delete[] parent;
}

int Graph::getHash(std::string name)
{
    long long hash = 5381;
    for (auto &&c : name)
    {
        hash = hash * 33 + c;
    }
    return hash % CAPACITY;
}

void Graph::resizeDSU()
{
    int oldCapacity = dsuCapacity;
    dsuCapacity *= 2;

    int *newParent = new int[dsuCapacity];

    for (int i = 0; i < oldCapacity; i++)
    {
        newParent[i] = parent[i];
    }

    delete[] parent;

    parent = newParent;

    LCTNode **newLCTNodes = new LCTNode *[dsuCapacity];
    for (int i = 0; i < oldCapacity; i++)
    {
        newLCTNodes[i] = lctNodes[i];
    }
    delete[] lctNodes;
    lctNodes = newLCTNodes;
}

int Graph::dsuFind(int i)
{
    if (parent[i] == i)
    {
        return i;
    }
    parent[i] = dsuFind(parent[i]);
    return parent[i];
}

void Graph::dsuUnion(int i, int j)
{
    int rootI = dsuFind(i);
    int rootJ = dsuFind(j);

    if (rootI != rootJ)
    {
        parent[rootJ] = rootI;
    }
}

void Graph::GAddNode(std::string nodeName)
{
    int hash = getHash(nodeName);

    VertexHashNode *tmp = vertices[hash];

    while (tmp != nullptr)
    {
        if (tmp->name == nodeName)
        {
            std::cout << "This Node Already Exists" << '\n';
            return;
        }
        tmp = tmp->next;
    }

    if (numberOfVertices >= dsuCapacity)
    {
        resizeDSU();
    }

    parent[numberOfVertices] = numberOfVertices;
    lctNodes[numberOfVertices] = new LCTNode(-1000000000, false);

    VertexHashNode *node = new VertexHashNode(nodeName, numberOfVertices);
    node->next = vertices[hash];
    vertices[hash] = node;

    numberOfVertices++;
}

void Graph::GAddEdge(std::string src, std::string dest, int weight)
{
    int srcHash = getHash(src);
    VertexHashNode *srcNode = vertices[srcHash];
    while (srcNode != nullptr && srcNode->name != src)
    {
        srcNode = srcNode->next;
    }

    int destHash = getHash(dest);
    VertexHashNode *destNode = vertices[destHash];
    while (destNode != nullptr && destNode->name != dest)
    {
        destNode = destNode->next;
    }

    if (srcNode == nullptr || destNode == nullptr)
    {
        std::cout << "Either the Source or Destination Node Doesn't Exiest" << '\n';
        return;
    }

    EdgeNode *srcToDest = new EdgeNode(destNode->vertexID, weight);
    EdgeNode *destToSrc = new EdgeNode(srcNode->vertexID, weight);

    srcToDest->next = srcNode->edges;
    srcNode->edges = srcToDest;

    destToSrc->next = destNode->edges;
    destNode->edges = destToSrc;

    dsuUnion(srcNode->vertexID, destNode->vertexID);

    LCTNode *u = lctNodes[srcNode->vertexID];
    LCTNode *v = lctNodes[destNode->vertexID];
    lct.addEdge(u, v, weight, mst_weight);
}
void Graph::GIsConnected(std::string src, std::string dest)
{
    int srcHash = getHash(src);
    VertexHashNode *srcNode = vertices[srcHash];
    while (srcNode != nullptr && srcNode->name != src)
    {
        srcNode = srcNode->next;
    }

    int destHash = getHash(dest);
    VertexHashNode *destNode = vertices[destHash];
    while (destNode != nullptr && destNode->name != dest)
    {
        destNode = destNode->next;
    }

    if (srcNode == nullptr || destNode == nullptr)
    {
        std::cout << "0" << '\n';
        return;
    }

    if (dsuFind(srcNode->vertexID) == dsuFind(destNode->vertexID))
    {
        std::cout << "1" << '\n';
    }
    else
    {
        std::cout << "0" << '\n';
    }
}

void Graph::GMST()
{
    std::cout << mst_weight << '\n';
    return;
}
