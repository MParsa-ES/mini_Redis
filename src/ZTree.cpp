#include "ZTree.h"
#include <iostream>

ZTree::ZTree()
{
    null = new Node(0, "");
    null->right = null;
    null->left = null;
    null->color = BLACK;
    null->size = 0;
    root = null;
}

ZTree::~ZTree()
{
    deleteTree(root);
    delete null;
}

void ZTree::deleteTree(Node *x)
{
    if (x != null)
    {
        deleteTree(x->left);
        deleteTree(x->right);
        delete x;
    }
}

bool ZTree::isLess(int s1, const std::string &m1, int s2, const std::string &m2)
{
    if (s1 != s2)
        return s1 < s2;
    return m1 < m2;
}

void ZTree::leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != null)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == null)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

void ZTree::rightRotate(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if (y->right != null)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == null)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;

    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

void ZTree::insert(int score, std::string member)
{
    Node *newNode = new Node(score, member);
    newNode->right = null;
    newNode->left = null;

    if (root == null)
    {
        newNode->color = BLACK;
        newNode->parent = null;
        root = newNode;
        return;
    }

    Node *current = root;
    Node *parentEl = null;
    while (current != null)
    {
        parentEl = current;
        if (isLess(score, member, current->score, current->member))
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parentEl;
    if (isLess(score, member, parentEl->score, parentEl->member))
        parentEl->left = newNode;
    else
        parentEl->right = newNode;

    // Cascade subtree size updates upward
    Node *temp = newNode->parent;
    while (temp != null)
    {
        temp->size++;
        temp = temp->parent;
    }

    insertFixup(newNode);
}

void ZTree::insertFixup(Node *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent->parent->left == z->parent)
        {
            Node *uncle = z->parent->parent->right;
            if (uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z->parent->right == z)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            Node *uncle = z->parent->parent->left;
            if (uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z->parent->left == z)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

int ZTree::getRank(int score, std::string member)
{
    Node *current = root;
    int rankAccumulator = 0;

    while (current != null)
    {
        if (score == current->score && member == current->member)
        {
            // Rank is the number of elements strictly smaller than it
            return rankAccumulator + current->left->size;
        }
        if (isLess(score, member, current->score, current->member))
        {
            current = current->left;
        }
        else
        {
            // If moving right, skip over the entire left subtree plus the current parent node
            rankAccumulator += current->left->size + 1;
            current = current->right;
        }
    }
    return -1;
}

void ZTree::transplant(Node *first, Node *second)
{
    if (first->parent == null)
        root = second;
    else if (first == first->parent->left)
        first->parent->left = second;
    else
        first->parent->right = second;
    second->parent = first->parent;
}

ZTree::Node *ZTree::minimum(Node *x)
{
    while (x != null && x->left != null)
        x = x->left;
    return x;
}

void ZTree::del(int score, std::string member)
{
    Node *current = root;
    while (current != null)
    {
        if (score == current->score && member == current->member)
            break;
        if (isLess(score, member, current->score, current->member))
            current = current->left;
        else
            current = current->right;
    }

    if (current == null)
        return;

    Node *successor = current;
    Color successor_original_color = current->color;
    Node *x = null;

    if (current->left == null)
    {
        Node *temp = current;
        while (temp != root)
        {
            temp = temp->parent;
            temp->size--;
        }
        x = current->right;
        transplant(current, current->right);
    }
    else if (current->right == null)
    {
        Node *temp = current;
        while (temp != root)
        {
            temp = temp->parent;
            temp->size--;
        }
        x = current->left;
        transplant(current, current->left);
    }
    else
    {
        successor = minimum(current->right);
        successor_original_color = successor->color;
        x = successor->right;

        if (successor->parent == current)
        {
            Node *temp = current;
            while (temp != root)
            {
                temp = temp->parent;
                temp->size--;
            }
            x->parent = successor;
        }
        else
        {
            Node *temp = successor;
            while (temp != root)
            {
                temp = temp->parent;
                temp->size--;
            }
            transplant(successor, successor->right);
            successor->right = current->right;
            successor->right->parent = successor;
        }
        transplant(current, successor);
        successor->left = current->left;
        successor->left->parent = successor;
        successor->color = current->color;
        successor->size = successor->left->size + successor->right->size + 1;
    }

    if (successor_original_color == BLACK)
        deleteFixup(x);
    delete current;
}

void ZTree::deleteFixup(Node *x)
{
    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}