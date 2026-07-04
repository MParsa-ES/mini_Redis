#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <chrono>

struct HashNode
{
    std::string key, value;
    int ttl;
    std::chrono::steady_clock::time_point editTime;

    HashNode *next;

    HashNode(std::string k, std::string v) : key(k), value(v), next(nullptr), ttl(-1) {}
};

class HashMap
{
private:
    static const int CAPACITY = 100009;
    HashNode *arr[CAPACITY] = {nullptr};

    int checkTTL(HashNode *node);
    int getHash(std::string key);
    void deleteExpiredNodes(int hash);

public:
    HashMap();
    ~HashMap();

    void set(std::string key, std::string value);
    void get(std::string key);
    void del(std::string key);
    void exists(std::string key);
    void expire(std::string key, int sec);
    void TTL(std::string key);
};

#endif