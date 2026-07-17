#include "LinkCutTree.h"

LCTNode::LCTNode(int w, bool edge)
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    rev = false;
    weight = w;
    isEdge = edge;
    max_ptr = this;
    edgeSrc = nullptr;
    edgeDest = nullptr;
}

LinkCutTree::LinkCutTree() {}
LinkCutTree::~LinkCutTree() {}

bool LinkCutTree::isRoot(LCTNode *x)
{
    if (!x)
        return true;
    return !x->parent || (x->parent->left != x && x->parent->right != x);
}

void LinkCutTree::pushUp(LCTNode *x)
{
    if (!x)
        return;
    x->max_ptr = x;
    if (x->left && x->left->max_ptr->weight > x->max_ptr->weight)
    {
        x->max_ptr = x->left->max_ptr;
    }
    if (x->right && x->right->max_ptr->weight > x->max_ptr->weight)
    {
        x->max_ptr = x->right->max_ptr;
    }
}

void LinkCutTree::pushDown(LCTNode *x)
{
    if (x && x->rev)
    {
        LCTNode *temp = x->left;
        x->left = x->right;
        x->right = temp;
        if (x->left)
            x->left->rev ^= 1;
        if (x->right)
            x->right->rev ^= 1;
        x->rev = false;
    }
}

void LinkCutTree::updatePath(LCTNode *x)
{
    if (!isRoot(x))
        updatePath(x->parent);
    pushDown(x);
}

void LinkCutTree::rotate(LCTNode *x)
{
    LCTNode *y = x->parent;
    LCTNode *z = y->parent;
    int k = (y->right == x);
    if (!isRoot(y))
    {
        if (z->left == y)
            z->left = x;
        else
            z->right = x;
    }
    x->parent = z;
    if (k == 0)
    {
        y->left = x->right;
        if (x->right)
            x->right->parent = y;
        x->right = y;
    }
    else
    {
        y->right = x->left;
        if (x->left)
            x->left->parent = y;
        x->left = y;
    }
    y->parent = x;
    pushUp(y);
    pushUp(x);
}

void LinkCutTree::splay(LCTNode *x)
{
    updatePath(x);
    while (!isRoot(x))
    {
        LCTNode *y = x->parent;
        LCTNode *z = y->parent;
        if (!isRoot(y))
        {
            if ((y->left == x) ^ (z->left == y))
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
}

void LinkCutTree::access(LCTNode *x)
{
    for (LCTNode *y = nullptr; x != nullptr; y = x, x = x->parent)
    {
        splay(x);
        x->right = y;
        pushUp(x);
    }
}

void LinkCutTree::makeroot(LCTNode *x)
{
    access(x);
    splay(x);
    x->rev ^= 1;
    pushDown(x);
}

LCTNode *LinkCutTree::findroot(LCTNode *x)
{
    access(x);
    splay(x);
    pushDown(x);
    while (x->left)
    {
        x = x->left;
        pushDown(x);
    }
    splay(x);
    return x;
}

void LinkCutTree::split(LCTNode *x, LCTNode *y)
{
    makeroot(x);
    access(y);
    splay(y);
}

void LinkCutTree::link(LCTNode *x, LCTNode *y)
{
    makeroot(x);
    if (findroot(y) != x)
    {
        x->parent = y;
    }
}

void LinkCutTree::cut(LCTNode *x, LCTNode *y)
{
    makeroot(x);
    access(y);
    splay(y);

    if (y->left == x && x->parent == y && x->right == nullptr)
    {
        y->left = nullptr;
        x->parent = nullptr;
        pushUp(y);
    }
}

void LinkCutTree::addEdge(LCTNode *u, LCTNode *v, int weight, long long &mst_weight)
{
    if (u == v)
        return;

    LCTNode *edgeNode = new LCTNode(weight, true);
    edgeNode->edgeSrc = u;
    edgeNode->edgeDest = v;

    if (findroot(u) != findroot(v))
    {
        link(u, edgeNode);
        link(edgeNode, v);
        mst_weight += weight;
    }
    else
    {
        split(u, v);
        LCTNode *maxE = v->max_ptr;


        if (weight < maxE->weight)
        {
            mst_weight = mst_weight - maxE->weight + weight;
            cut(maxE, maxE->edgeSrc);
            cut(maxE, maxE->edgeDest);

            link(u, edgeNode);
            link(edgeNode, v);
            delete maxE;
        }
        else
        {
            delete edgeNode;
        }
    }
}