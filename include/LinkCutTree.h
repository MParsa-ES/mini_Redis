#ifndef LINK_CUT_TREE_H
#define LINK_CUT_TREE_H

struct LCTNode {
    LCTNode* left;
    LCTNode* right;
    LCTNode* parent;
    bool rev;
    int weight;
    bool isEdge;
    
    LCTNode* max_ptr;
    LCTNode* edgeSrc;
    LCTNode* edgeDest;

    LCTNode(int w = -1000000000, bool edge = false);
};

class LinkCutTree {
private:
    bool isRoot(LCTNode* x);
    void pushUp(LCTNode* x);
    void pushDown(LCTNode* x);
    void updatePath(LCTNode* x);
    void rotate(LCTNode* x);
    void splay(LCTNode* x);
    void access(LCTNode* x);
    void makeroot(LCTNode* x);
    LCTNode* findroot(LCTNode* x);
    void split(LCTNode* x, LCTNode* y);
    void link(LCTNode* x, LCTNode* y);
    void cut(LCTNode* x, LCTNode* y);

public:
    LinkCutTree();
    ~LinkCutTree();
    
    void addEdge(LCTNode* u, LCTNode* v, int weight, long long& mst_weight);
};

#endif