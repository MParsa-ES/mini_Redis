#include <string>
#include <iostream>

struct HashNode
{
    std::string key, value;
    HashNode *next;

    HashNode(std::string k, std::string v) : key(k), value(v), next(nullptr) {}
};

class HashMap
{
private:
    static const int CAPACITY = 100009;
    HashNode *arr[CAPACITY] = {nullptr};

    int getHash(std::string key);

public:
    HashMap();
    ~HashMap();

    void set(std::string key, std::string value);
    void get(std::string key);
    void del(std::string key);
    void exists(std::string key);
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
        if (tmp->key == key)
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
        if (tmp->key == key)
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
    if (arr[hash]->key == key)
    {
        HashNode *tmp = arr[hash];
        arr[hash] = arr[hash]->next;
        delete (tmp);
        return;
    }

    HashNode *tmp = arr[hash];
    while (tmp->next != nullptr)
    {
        if (tmp->next->key == key)
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
        if (tmp->key == key)
        {
            std::cout << 1 << '\n';
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "0" << '\n';
}
