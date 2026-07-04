#include <string>
#include <iostream>
#include <chrono>
#include <HashMap.h>

HashMap::HashMap()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        arr[i] = nullptr;
    }
}

HashMap::~HashMap()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        if (arr[i] == nullptr)
        {
            continue;
        }
        if (arr[i]->next == nullptr)
        {
            delete (arr[i]);
            arr[i] = nullptr;
        }

        HashNode *node = arr[i];
        while (node != nullptr)
        {
            HashNode *temp = node;
            node = node->next;
            delete temp;
        }

        arr[i] = nullptr;
    }
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

void HashMap::deleteExpiredNodes(int hash)
{
    HashNode *tmp = arr[hash];
    HashNode *prev = nullptr;

    while (tmp != nullptr)
    {
        if (checkTTL(tmp) == 0)
        {
            HashNode *toBeDeleted = tmp;
            tmp = tmp->next;
            if (prev == nullptr)
                arr[hash] = tmp;
            else
                prev->next = tmp;

            delete toBeDeleted;
        }
        else
        {
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

void HashMap::set(std::string key, std::string value)
{
    int hash = getHash(key);
    deleteExpiredNodes(hash);

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
            tmp->ttl = -1;
            tmp->editTime = std::chrono::steady_clock::now();
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
    deleteExpiredNodes(hash);

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
    deleteExpiredNodes(hash);

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

    while (tmp != nullptr && tmp->next != nullptr)
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
    deleteExpiredNodes(hash);

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

void HashMap::expire(std::string key, int sec)
{
    int hash = getHash(key);
    deleteExpiredNodes(hash);

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
    deleteExpiredNodes(hash);

    if (arr[hash] == nullptr)
    {
        std::cout << -2 << '\n';
        return;
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
