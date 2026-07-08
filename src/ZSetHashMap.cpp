#include <string>
#include "ZSet.h"

struct ZNode
{
    std::string key;
    ZSet set;

    ZNode *next;

    ZNode(std::string k) : key(k), next(nullptr) {};
};

class ZSetHashMap
{
private:
    static const int CAPACITY = 10009;

    ZNode *arr[CAPACITY] = {nullptr};

    int getHash(std::string key);

public:
    ZSetHashMap();
    ~ZSetHashMap();

    void add(std::string key, int score, std::string member);
    void rem(std::string key, std::string member);
    void score(std::string key, std::string member);
    void rank(std::string key, std::string member);
};

ZSetHashMap::ZSetHashMap()
{
}

ZSetHashMap::~ZSetHashMap()
{
}

void ZSetHashMap::add(std::string key, int score, std::string member)
{
    int hash = getHash(key);

    ZNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->key == key)
        {
            tmp->set.ZAdd(score, member);
            return;
        }
        tmp = tmp->next;
    }

    ZNode *node = new ZNode(key);
    node->next = arr[hash];
    arr[hash] = node;
    node->set.ZAdd(score, member);
}

void ZSetHashMap::rem(std::string key, std::string member)
{
    int hash = getHash(key);

    ZNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->key == key)
        {
            tmp->set.ZRem(member);
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Key Not Found" << '\n';
}

void ZSetHashMap::score(std::string key, std::string member)
{
    int hash = getHash(key);

    ZNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->key == key)
        {
            tmp->set.ZScore(member);
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Key Not Found" << '\n';
}

void ZSetHashMap::rank(std::string key, std::string member)
{
    int hash = getHash(key);

    ZNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->key == key)
        {
            tmp->set.ZRank(member);
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Key Not Found" << '\n';
}