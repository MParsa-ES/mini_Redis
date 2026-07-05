#ifndef LISTHASHMAP_H
#define LISTHASHMAP_H

#include <string>
#include "LinkedList.h"

struct ListHashNode
{
    std::string key;
    LinkedList values; 
    ListHashNode *next;

    ListHashNode(std::string k) : key(k), next(nullptr) {}
};

class ListHashMap
{
private:
    static const int CAPACITY = 100009;
    ListHashNode *arr[CAPACITY] = {nullptr};

    int getHash(std::string key);

public:
    ListHashMap();
    ~ListHashMap();

    void lpush(std::string key, std::string value);
    void rpush(std::string key, std::string value);
    void lpop(std::string key);
    void rpop(std::string key);
    void lrange(std::string key, int start, int end);
};

#endif