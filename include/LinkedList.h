#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

struct Node {
    Node* prev;
    Node* next;
    std::string value;

    Node(std::string val) : value(val), prev(nullptr), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList();
    ~LinkedList();
    
    void addToFront(std::string value);
    void addToBack(std::string value);
    void delFront();
    void delBack();
    void printRange(int start, int end);
};

#endif