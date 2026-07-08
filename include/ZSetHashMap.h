#ifndef ZSETHASHMAP_H
#define ZSETHASHMAP_H

#include <string>
#include "ZSet.h"

struct ZNode
{
    std::string key;
    ZSet set;
    ZNode *next;

    ZNode(std::string k) : key(k), next(nullptr) {}
};

class ZSetHashMap
{
private:
    static const int CAPACITY = 10009;
    ZNode *arr[CAPACITY];

    int getHash(std::string key);

public:
    ZSetHashMap();
    ~ZSetHashMap();

    void add(std::string key, int score, std::string member);
    void rem(std::string key, std::string member);
    void score(std::string key, std::string member);
    void rank(std::string key, std::string member);
};

#endif