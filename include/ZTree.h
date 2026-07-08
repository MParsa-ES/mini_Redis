#ifndef ZTREE_H
#define ZTREE_H

#include <string>

class ZTree
{
private:
    enum Color
    {
        BLACK,
        RED
    };

    struct Node
    {
        int score;
        std::string member;
        int size;
        Node *parent;
        Node *left;
        Node *right;
        Color color;

        Node(int s, std::string m)
            : score(s), member(m), size(1), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
    };

    Node *root;
    Node *null;

    Node *minimum(Node *x);
    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void insertFixup(Node *z);
    void deleteFixup(Node *x);
    void transplant(Node *first, Node *second);
    void deleteTree(Node *x);

    bool isLess(int s1, const std::string &m1, int s2, const std::string &m2);

public:
    ZTree();
    ~ZTree();

    void insert(int score, std::string member);
    void del(int score, std::string member);
    int getRank(int score, std::string member);
};

#endif