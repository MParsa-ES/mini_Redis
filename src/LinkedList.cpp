#include <string>
#include <iostream>

struct Node
{
    Node *prev;
    Node *next;
    std::string value;

    Node(std::string value)
    {
        this->value = value;
        prev = nullptr;
        next = nullptr;
    }
};

class LinkedList
{
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    LinkedList();
    ~LinkedList();
    void addToFront(std::string value);
    void addToBack(std::string value);
    void delFront();
    void delBack();
    void printRange(int start, int end);
};

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
        delete (head);
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node *node = head;
    head = head->next;
    head->prev = nullptr;
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
        delete (head);
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node *node = tail;
    tail = tail->prev;
    tail->next = nullptr;
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
    free(node);
}
