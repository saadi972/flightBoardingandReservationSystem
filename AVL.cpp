#include "../include/AVL.h"

AVLNode::AVLNode(Flight f)
{
    data = f;
    left = nullptr;
    right = nullptr;
    height = 1;
}

AVL::AVL()
{
    root = nullptr;
}

int AVL::heightOf(AVLNode* n)
{
    return (n == nullptr ? 0 : n->height);
}

int AVL::getBalance(AVLNode* n)
{
    if (!n) return 0;
    return heightOf(n->left) - heightOf(n->right);
}

AVLNode* AVL::rightRotate(AVLNode* y)
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(heightOf(y->left), heightOf(y->right)) + 1;
    x->height = max(heightOf(x->left), heightOf(x->right)) + 1;

    return x;
}

AVLNode* AVL::leftRotate(AVLNode* x)
{
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(heightOf(x->left), heightOf(x->right)) + 1;
    y->height = max(heightOf(y->left), heightOf(y->right)) + 1;

    return y;
}

AVLNode* AVL::insertNode(AVLNode* node, Flight f)
{
    if (!node)
        return new AVLNode(f);

    if (f.flightID < node->data.flightID)
        node->left = insertNode(node->left, f);
    else if (f.flightID > node->data.flightID)
        node->right = insertNode(node->right, f);
    else
        return node;

    node->height = 1 + max(heightOf(node->left), heightOf(node->right));

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && f.flightID < node->left->data.flightID)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && f.flightID > node->right->data.flightID)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && f.flightID > node->left->data.flightID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && f.flightID < node->right->data.flightID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVL::insert(Flight f)
{
    root = insertNode(root, f);
}

void AVL::inorderTraversal(AVLNode* node, vector<Flight>& list)
{
    if (!node) return;

    inorderTraversal(node->left, list);
    list.push_back(node->data);
    inorderTraversal(node->right, list);
}

void AVL::getAllFlights(vector<Flight>& list)
{
    inorderTraversal(root, list);
}

vector<Flight> AVL::getAllFlightsVector()
{
    vector<Flight> list;
    inorderTraversal(root, list);
    return list;
}

Flight* AVL::search(string id)
{
    AVLNode* curr = root;

    while (curr != nullptr)
    {
        if (id == curr->data.flightID)
            return &curr->data;

        if (id < curr->data.flightID)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return nullptr;
}
