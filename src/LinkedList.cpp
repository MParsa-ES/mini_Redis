#include <string>

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
