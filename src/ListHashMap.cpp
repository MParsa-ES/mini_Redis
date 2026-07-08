#include "ListHashMap.h"
#include <iostream>

ListHashMap::ListHashMap()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        arr[i] = nullptr;
    }
}

ListHashMap::~ListHashMap()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        ListHashNode *node = arr[i];
        while (node != nullptr)
        {
            ListHashNode *temp = node;
            node = node->next;
            delete temp;
        }

        arr[i] = nullptr;
    }
}

int ListHashMap::getHash(std::string key)
{
    long long hash = 5381;
    for (auto &&c : key)
    {
        hash = hash * 33 + c;
    }
    return hash % CAPACITY;
}

void ListHashMap::lpush(std::string key, std::string value)
{
    int hash = getHash(key);

    ListHashNode *block = arr[hash];
    while (block != nullptr)
    {
        if (block->key == key)
        {
            block->values.addToFront(value);
            return;
        }
        block = block->next;
    }
    ListHashNode *tmp = new ListHashNode(key);
    tmp->values.addToFront(value);
    tmp->next = arr[hash];
    arr[hash] = tmp;
}

void ListHashMap::rpush(std::string key, std::string value)
{
    int hash = getHash(key);

    ListHashNode *block = arr[hash];
    while (block != nullptr)
    {
        if (block->key == key)
        {
            block->values.addToBack(value);
            return;
        }
        block = block->next;
    }
    ListHashNode *tmp = new ListHashNode(key);
    tmp->values.addToBack(value);
    tmp->next = arr[hash];
    arr[hash] = tmp;
}

void ListHashMap::lpop(std::string key)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        std::cout << "NULL" << '\n';
        return;
    }
    ListHashNode *block = arr[hash];
    while (block != nullptr)
    {
        if (block->key == key)
        {
            block->values.delFront();
            return;
        }
        block = block->next;
    }
    std::cout << "NULL" << '\n';
}
void ListHashMap::rpop(std::string key)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        std::cout << "NULL" << '\n';
        return;
    }
    ListHashNode *block = arr[hash];
    while (block != nullptr)
    {
        if (block->key == key)
        {
            block->values.delBack();
            return;
        }
        block = block->next;
    }
    std::cout << "NULL" << '\n';
}

void ListHashMap::lrange(std::string key, int start, int end)
{
    int hash = getHash(key);
    if (arr[hash] == nullptr)
    {
        std::cout << "Key Not Found" << '\n';
        return;
    }
    ListHashNode *block = arr[hash];
    while (block != nullptr)
    {
        if (block->key == key)
        {
            block->values.printRange(start, end);
            return;
        }
        block = block->next;
    }
    std::cout << "Key Not Found" << '\n';
}