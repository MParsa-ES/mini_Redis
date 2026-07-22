#include "ZSet.h"

ZSet::ZSet()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        arr[i] = nullptr;
    }
}

ZSet::~ZSet()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        ZHashNode *current = arr[i];
        while (current != nullptr)
        {
            ZHashNode *temp = current;
            current = current->next;
            delete temp;
        }
        arr[i] = nullptr;
    }
}

int ZSet::getHash(std::string member)
{
    long long hash = 5381;
    for (auto &&c : member)
    {
        hash = hash * 33 + c;
    }
    return hash % CAPACITY;
}

void ZSet::ZAdd(int score, std::string member)
{
    int hash = getHash(member);

    ZHashNode *tmp = arr[hash];
    while (tmp != nullptr)
    {
        if (tmp->member == member)
        {
            if (score == tmp->score)
                return;
            tree.del(tmp->score, member);
            tree.insert(score, member);
            tmp->score = score;
            std::cout << "0" << '\n';
            return;
        }
        tmp = tmp->next;
    }
    ZHashNode *node = new ZHashNode(member, score);
    node->next = arr[hash];
    arr[hash] = node;
    tree.insert(score, member);
    std::cout << "1" << '\n';
}

void ZSet::ZRem(std::string member)
{
    int hash = getHash(member);

    ZHashNode *tmp = arr[hash];
    ZHashNode *prev = nullptr;
    while (tmp != nullptr)
    {
        if (tmp->member == member)
        {
            if (prev == nullptr)
                arr[hash] = tmp->next;
            else
                prev->next = tmp->next;

            tree.del(tmp->score, member);
            std::cout << "1" << '\n';
            delete (tmp);
            return;
        }

        prev = tmp;
        tmp = tmp->next;
    }
    std::cout << "0" << '\n';
}

void ZSet::ZScore(std::string member)
{
    int hash = getHash(member);

    ZHashNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->member == member)
        {
            std::cout << tmp->score << '\n';
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "NULL" << '\n';
}

void ZSet::ZRank(std::string member)
{
    int hash = getHash(member);

    ZHashNode *tmp = arr[hash];

    while (tmp != nullptr)
    {
        if (tmp->member == member)
        {
            int rank = tree.getRank(tmp->score, member);
            if (rank == -1)
                break;
            std::cout << rank << '\n';
            return;
        }
        tmp = tmp->next;
    }
    std::cout << "Member Not Found in Set" << '\n';
}