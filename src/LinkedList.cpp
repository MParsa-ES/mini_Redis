#include <string>
#include <iostream>
#include <LinkedList.h>

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

LinkedList::~LinkedList()
{
    Node *node = head;
    while (node != nullptr)
    {
        Node *temp = node;
        node = temp->next;
        delete (temp);
    }
    head = nullptr;
    tail = nullptr;
}

void LinkedList::addToFront(std::string value)
{
    Node *node = new Node(value);
    if (head == nullptr)
    {
        head = node;
        tail = node;
        return;
    }
    node->next = head;
    head->prev = node;
    head = node;
}

void LinkedList::addToBack(std::string value)
{
    Node *node = new Node(value);
    if (tail == nullptr)
    {
        head = node;
        tail = node;
        return;
    }

    node->prev = tail;
    tail->next = node;
    tail = node;
}

void LinkedList::delFront()
{
    if (head == tail)
    {
        if (head == nullptr)
        {
            return;
        }
        std::cout << head->value << '\n';
        delete (head);
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node *node = head;
    head = head->next;
    head->prev = nullptr;
    std::cout << node->value << '\n';
    delete (node);
}

void LinkedList::delBack()
{
    if (head == tail)
    {
        if (head == nullptr)
        {
            return;
        }
        std::cout << tail->value << '\n';
        delete (head);
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node *node = tail;
    tail = tail->prev;
    tail->next = nullptr;
    std::cout << node->value << '\n';
    delete (node);
}

void LinkedList::printRange(int start, int end)
{
    int cnt = 0;
    Node *node = head;
    while (cnt <= end && node != nullptr)
    {
        if (cnt >= start)
        {
            std::cout << node->value << '\n';
        }
        node = node->next;
        cnt++;
    }
}
