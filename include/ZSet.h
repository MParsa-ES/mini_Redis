#ifndef ZSET_H
#define ZSET_H

#include <string>
#include <iostream>
#include "ZTree.h"

struct ZHashNode
{
    std::string member;
    int score;
    ZHashNode *next;
    ZHashNode(std::string mem, int sc) : member(mem), score(sc), next(nullptr) {};
};

class ZSet
{
private:
    static const int CAPACITY = 10009;

    ZTree tree;
    ZHashNode *arr[CAPACITY] = {nullptr};

    int getHash(std::string member);

public:
    ZSet();
    ~ZSet();

    void ZAdd(int score, std::string member);
    void ZRem(std::string member);
    void ZScore(std::string memeber);
    void ZRank(std::string memeber);
};

#endif