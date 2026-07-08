#include "ZSetHashMap.h"

ZSetHashMap::ZSetHashMap()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        arr[i] = nullptr;
    }
}

ZSetHashMap::~ZSetHashMap()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        ZNode *current = arr[i];
        while (current != nullptr)
        {
            ZNode *temp = current;
            current = current->next;
            delete temp;
        }
        arr[i] = nullptr;
    }
}

int ZSetHashMap::getHash(std::string member)
{
    long long hash = 5381;
    for (auto &&c : member)
    {
        hash = hash * 33 + c;
    }
    return hash % CAPACITY;
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