#include <string>
#include <iostream>
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

HashMap::HashMap()
{
}

HashMap::~HashMap()
{
}

int HashMap::getHash(std::string key)
{
    long long hash = 5381;
    for (auto &&c : key)
    {
        hash = hash * 33 + c;
    }
    return hash % CAPACITY;
}

int HashMap::checkTTL(HashNode *node)
{
    if (node->ttl == -1)
    {
        return -1;
    }
    auto elapsed = std::chrono::steady_clock::now() - node->editTime;
    int remainingTime = node->ttl - std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
    return remainingTime > 0 ? remainingTime : 0;
}

void HashMap::set(std::string key, std::string value)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        arr[hash] = new HashNode(key, value);
        return;
    }
    HashNode *tmp = arr[hash];
    while (tmp != nullptr)
    {
        if (tmp->key == key && checkTTL(tmp) > 0)
        {
            tmp->value = value;
            return;
        }
        tmp = tmp->next;
    }
    HashNode *node = new HashNode(key, value);
    node->next = arr[hash];
    arr[hash] = node;
}

void HashMap::get(std::string key)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        std::cout << "Key Not Found" << '\n';
        return;
    }

    HashNode *tmp = arr[hash];
    while (tmp != nullptr)
    {
        if (tmp->key == key && checkTTL(tmp) > 0)
        {
            std::cout << tmp->value << '\n';
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Key Not Found" << '\n';
}

void HashMap::del(std::string key)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        std::cout << "Key Not Found" << '\n';
        return;
    }
    if (arr[hash]->key == key && checkTTL(arr[hash]) > 0)
    {
        HashNode *tmp = arr[hash];
        arr[hash] = arr[hash]->next;
        delete (tmp);
        return;
    }

    HashNode *tmp = arr[hash];
    while (tmp->next != nullptr)
    {
        if (tmp->next->key == key && checkTTL(tmp->next) > 0)
        {
            HashNode *node = tmp->next;
            tmp->next = tmp->next->next;
            delete (node);
            return;
        }
        tmp = tmp->next;
    }
}

void HashMap::exists(std::string key)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        std::cout << "0" << '\n';
        return;
    }

    HashNode *tmp = arr[hash];
    while (tmp != nullptr)
    {
        if (tmp->key == key && checkTTL(tmp) > 0)
        {
            std::cout << 1 << '\n';
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "0" << '\n';
}

void HashMap::expire(std::string key, int sec)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        std::cout << "Key Not Found" << '\n';
    }
    HashNode *tmp = arr[hash];
    while (tmp != nullptr)
    {
        if (tmp->key == key)
        {
            tmp->ttl = sec;
            tmp->editTime = std::chrono::steady_clock::now();
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Key Not Found" << '\n';
}

void HashMap::TTL(std::string key)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        std::cout << -2 << '\n';
    }
    HashNode *tmp = arr[hash];
    while (tmp != nullptr)
    {
        if (tmp->key == key)
        {
            int ttl = checkTTL(tmp);
            if (ttl > 0)
            {
                std::cout << ttl << '\n';
            }
            else if (ttl == -1)
            {
                std::cout << "-1" << '\n';
            }
            return;
        }
        tmp = tmp->next;
    }
    std::cout << -2 << '\n';
}
