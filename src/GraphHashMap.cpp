#include "GraphHashMap.h"

GraphHashMap::GraphHashMap()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        arr[i] = nullptr;
    }
}

GraphHashMap::~GraphHashMap()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        GraphHashNode *current = arr[i];
        while (current != nullptr)
        {
            GraphHashNode *temp = current;
            current = current->next;
            delete temp;
        }
        arr[i] = nullptr;
    }
}

int GraphHashMap::getHash(std::string name)
{
    long long hash = 5381;
    for (auto &&c : name)
    {
        hash = hash * 33 + c;
    }
    return hash % CAPACITY;
}

void GraphHashMap::GCreate(std::string graphName)
{
    int hash = getHash(graphName);

    GraphHashNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->graphName == graphName)
        {
            std::cout << "A Graph With This Name Already Exists" << '\n';
            return;
        }
        tmp = tmp->next;
    }
    GraphHashNode *node = new GraphHashNode(graphName);
    node->next = arr[hash];
    arr[hash] = node;
}

void GraphHashMap::GAddNode(std::string graphName, std::string nodeName)
{
    int hash = getHash(graphName);

    GraphHashNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->graphName == graphName)
        {
            tmp->graph.GAddNode(nodeName);
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Graph With This Name Not Found" << '\n';
}

void GraphHashMap::GAddEdge(std::string graphName, std::string src, std::string dest, int weight)
{
    int hash = getHash(graphName);

    GraphHashNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->graphName == graphName)
        {
            tmp->graph.GAddEdge(src, dest, weight);
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Graph With This Name Not Found" << '\n';
}

void GraphHashMap::GConnected(std::string graphName, std::string src, std::string dest)
{
    int hash = getHash(graphName);

    GraphHashNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->graphName == graphName)
        {
            tmp->graph.GIsConnected(src, dest);
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Graph With This Name Not Found" << '\n';
}

void GraphHashMap::GMST(std::string graphName)
{
    int hash = getHash(graphName);
    GraphHashNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->graphName == graphName)
        {
            tmp->graph.GMST();
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Graph With This Name Not Found" << '\n';
}
