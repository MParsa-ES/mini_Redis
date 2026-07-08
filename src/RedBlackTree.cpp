    #include <iostream>
#include <queue>

class RedBlackTree
{
private:
    enum Color
    {
        BLACK,
        RED
    };

    struct Node
    {
        int value;
        int size;
        Node *parent;
        Node *left;
        Node *right;
        Color color;

        Node(int value) : value(value), size(1), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
    };
    Node *root;
    Node *null = new Node(0);
    Node *minimum(Node *x);
    Node *successor(Node *x);

    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void deleteFixup(Node *x);
    void insertFixup(Node *z);
    void deleteTree(Node *x);
    void transplant(Node *first, Node *second);

public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(int value);
    void del(int value);
    void print();
    void getByRank(int rank);
};

RedBlackTree::RedBlackTree()
{
    null->right = null;
    null->left = null;
    null->color = BLACK;
    null->size = 0;
    this->root = this->null;
}

RedBlackTree::~RedBlackTree()
{
    deleteTree(this->root);
    delete null;
}

void RedBlackTree::deleteTree(Node *x)
{
    if (x != this->null)
    {
        deleteTree(x->left);
        deleteTree(x->right);
        delete (x);
    }
}

void RedBlackTree::leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != this->null)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == this->null)
    {
        this->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    // ----------------- update size
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

void RedBlackTree::rightRotate(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if (y->right != this->null)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == this->null)
    {
        this->root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    // ----------------- update size
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

void RedBlackTree::getByRank(int rank)
{
    if (rank > root->size)
    {
        std::cout << "invalid" << '\n';
        return;
    }
    Node *current = root;
    int temp;
    while (current != null)
    {
        temp = current->left->size + 1;
        if (temp == rank)
        {
            std::cout << current->value << '\n';
            return;
        }
        else if (rank < temp)
        {
            current = current->left;
        }
        else
        {
            rank = rank - temp;
            current = current->right;
        }
    }
}

void RedBlackTree::transplant(Node *first, Node *second)
{
    if (first->parent == this->null)
    {
        this->root = second;
    }
    else if (first == first->parent->left)
    {
        first->parent->left = second;
    }
    else
    {
        first->parent->right = second;
    }
    second->parent = first->parent;
}

RedBlackTree::Node *RedBlackTree::minimum(Node *x)
{
    while (x != this->null && x->left != this->null)
    {
        x = x->left;
    }
    return x;
}

RedBlackTree::Node *RedBlackTree::successor(Node *x)
{
    if (x->right != this->null)
    {
        return minimum(x->right);
    }
    Node *y = x->parent;
    while (y != this->null && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

void RedBlackTree::insert(int value)
{
    Node *newNode = new Node(value);
    newNode->right = null;
    newNode->left = null;

    if (this->root == this->null)
    {
        newNode->color = BLACK;
        newNode->parent = null;
        this->root = newNode;
        return;
    }
    Node *current = this->root;
    Node *currentParrent = this->null;
    while (current != null)
    {
        if (value > current->value)
        {
            currentParrent = current;
            current = current->right;
        }
        else if (value < current->value)
        {
            currentParrent = current;
            current = current->left;
        }
        else
        {
            delete (newNode);
            return;
        }
    }

    if (value > currentParrent->value)
    {
        currentParrent->right = newNode;
    }
    else
    {
        currentParrent->left = newNode;
    }
    newNode->parent = currentParrent;
    //-------------------------
    while (currentParrent != null)
    {
        currentParrent->size++;
        currentParrent = currentParrent->parent;
    }
    //--------------------------

    insertFixup(newNode);
}

void RedBlackTree::insertFixup(Node *z)
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
    this->root->color = BLACK;
}

void RedBlackTree::print()
{
    if (this->root == this->null)
    {
        return;
    }
    std::queue<Node *> Q;
    Q.push(this->root);
    while (!Q.empty())
    {
        Node *current = Q.front();
        std::cout << current->value << (current->color == BLACK ? "b" : "r") << " ";
        if (current->left != null)
        {
            Q.push(current->left);
        }
        if (current->right != null)
        {
            Q.push(current->right);
        }
        Q.pop();
    }
    std::cout << '\n';
}

void RedBlackTree::del(int value)
{
    Node *current = this->root;
    while (current != null)
    {
        if (current->value > value)
        {
            current = current->left;
        }
        else if (current->value < value)
        {
            current = current->right;
        }
        else
        {
            break;
        }
    }
    if (current == this->null)
    {
        return;
    }
    Node *successor = current;
    Color successor_original_color = current->color;
    Node *x = this->null;
    if (current->left == this->null)
    {
        // ---------------------
        Node *temp = current;
        while (temp != root)
        {
            temp = temp->parent;
            temp->size--;
        }
        // ----------------------
        x = current->right;
        transplant(current, current->right);
    }
    else if (current->right == this->null)
    {
        // ---------------------
        Node *temp = current;
        while (temp != root)
        {
            temp = temp->parent;
            temp->size--;
        }
        // ----------------------
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
            // ---------------------
            Node *temp = current;
            while (temp != root)
            {
                temp = temp->parent;
                temp->size--;
            }
            // ----------------------
            x->parent = successor;
        }
        else
        {
            // --------------------
            Node *temp = successor;
            while (temp != root)
            {
                temp = temp->parent;
                temp->size--;
            }
            // --------------------

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
    {
        deleteFixup(x);
    }
    delete current;
}

void RedBlackTree::deleteFixup(Node *x)
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

using namespace std;

int main()
{
    RedBlackTree RB;
    int q;
    char command;
    int value;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        cin >> command;
        cin >> value;
        switch (command)
        {
        case 'I':
            RB.insert(value);
            break;

        case 'D':
            RB.del(value);
            break;
        case 'S':
            RB.getByRank(value);
            break;
        }
    }
}