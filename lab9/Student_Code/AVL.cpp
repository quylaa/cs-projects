// Written by Aleks Christensen

#include "AVL.h"

AVL::AVL() : root(NULL) {}
AVL::~AVL(){}

int AVL::diff(Node* lroot)
{
    if (lroot == NULL) return 0;
    int l, r;
    lroot->left ? l = lroot->left->getHeight() : l = 0;
    lroot->right ? r = lroot->right->getHeight() : r = 0;
    return l - r;
}

bool AVL::addn(int data, Node*& lroot)
{
    if (lroot == NULL) {
        lroot = new Node(data, NULL, NULL);
        return true;
    }
    else if (data == lroot->getData()) return false;
    else if (data < lroot->getData()) {
        if (!addn(data, lroot->left)) return false;
        lroot = balance(lroot);
    }
    else if (data > lroot->getData()) {
        if (!addn(data, lroot->right)) return false;
        lroot = balance(lroot);
    }
    return true;
}

bool AVL::removen(int data, Node*& lroot)
{
    if (lroot == NULL) return false;
    if (data < lroot->getData()) {
        if (removen(data, lroot->left)) lroot = balance(lroot);
    }
    else if (data > lroot->getData()) {
        if (removen(data, lroot->right)) lroot = balance(lroot);
    }
    else {
        Node* tmp = lroot;
        if (lroot->left == NULL) lroot = lroot->right;
        else if (lroot->right == NULL) lroot = lroot->left;
        else replace(lroot, lroot->left);

        delete tmp;
        return true;
    }
}

void AVL::replace(Node*& lroot, Node*& nroot)
{
    if (nroot->right) replace(lroot, nroot->right);
    else {
        lroot->data = nroot->data;
        lroot = nroot;
        nroot = nroot->left;
    }
}

Node* AVL::rotR(Node* lroot)
{
    Node* tmp = lroot->left;
    lroot->left = tmp->right;
    tmp->right = lroot;
    lroot = tmp;
    return tmp;
}

Node* AVL::rotL(Node* lroot)
{
    Node* tmp = lroot->right;
    lroot->right = tmp->left;
    tmp->left = lroot;
    lroot = tmp;
    return tmp;
}

Node* AVL::RR(Node* lroot)
{
    return rotL(lroot);
}

Node* AVL::RL(Node* lroot)
{
    Node* tmp = lroot->right;
    lroot->right = rotR(tmp);
    return rotL(lroot);
}

Node* AVL::LR(Node* lroot)
{
    Node* tmp = lroot->left;
    lroot->left = rotL(tmp);
    return rotR(lroot);
}

Node* AVL::LL(Node* lroot)
{
    return rotR(lroot);
}

Node* AVL::balance(Node* lroot)
{
    int h = diff(lroot);
    if (h > 1) {
        if (diff(lroot->left) > 0) lroot = LL(lroot);
        else lroot = LR(lroot);
    }
    else if (h < -1) {
        if (diff(lroot->right) > 0) lroot = RL(lroot);
        else lroot = RR(lroot);
    }
    return lroot;
}

Node* AVL::getRootNode()
{
    return root;
}

bool AVL::add(int data)
{
    return addn(data, root);
}

bool AVL::remove(int data)
{
    return removen(data, root);
}
