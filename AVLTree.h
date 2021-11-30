#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <memory>
#include "Exceptions.h"

template <class T>
class AVLTree;

template <class T>
class Node
{

    T data;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    int height;

public:
    Node(T data) : data(data), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
    ~Node() = default;
    Node(const Node &other) = default;
    Node &operator=(const Node &other) = default;
    T getDataNode()
    {
        return this->data;
    }

    int static GetHeight(Node<T> *node)
    {
        if (node == nullptr)
        {
            return -1;
        }

        return node->height;
    }

    int BFcalc(Node<T> *curr)
    {
        if (curr == nullptr)
        {
            throw NullArg();
        }
        return GetHeight(curr->left) - GetHeight(curr->right);
    }

    friend AVLTree<T>;
};

template <class T>
class AVLTree
{
    Node<T> *root;
    int size;

    //O(logn) n - size of the tree
    Node<T> *copy_tree(Node<T> *other, Node<T> *parent)
    {
        if (other == nullptr)
        {
            return nullptr;
        }
        Node<T> *new_node = new Node<T>(other->data);
        new_node->parent = parent;
        new_node->height = other->height;
        new_node->left = copy_tree(other->left, new_node);
        new_node->right = copy_tree(other->right, new_node);
        return new_node;
    }

    void deleteTree(Node<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        Node<T> *temp = node;
        node = nullptr;
        delete (temp);
    }

    //O(logn) n - size of the tree
    //return the node
    template <class Key>
    Node<T> *FindItem(Node<T> *curr, Key key)
    {
        if (curr == nullptr)
        {
            return nullptr;
        }
        if (curr->data == key)
        {
            return curr;
        }
        if (curr->data > key)
        {
            return FindItem(curr->left, key);
        }
        return FindItem(curr->right, key);
    }

    Node<T> *Getpredecessor(Node<T> *curr)
    {
        Node<T> *temp = curr;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }

    Node<T> *GetSuccesor(Node<T> *curr)
    {
        Node<T> *temp = curr;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }

    Node<T> *fixTree(Node<T> *curr)
    {
        int bf = curr->BFcalc(curr);
        if (bf == 2)
        {
            if (curr->BFcalc(curr->left) >= 0)
            {
                LL(curr);
            }
            else
            { //bf = -1
                LR(curr);
            }
            return curr->parent;
        }
        else if (bf == -2)
        {
            if (curr->BFcalc(curr->right) <= 0)
            {
                RR(curr);
            }
            else
            {
                RL(curr);
            }
            return curr->parent;
        }

        return curr;
    }

    void LL(Node<T> *curr)
    {
        if (curr == nullptr)
            return;

        Node<T> *temp = curr->left;
        curr->left = curr->left->right;
        if (curr->left != nullptr)
        {
            curr->left->parent = curr;
        }

        temp->right = curr;
        temp->parent = curr->parent;

        if (curr->parent != nullptr && curr == curr->parent->left)
        {
            curr->parent->left = temp;
        }
        else if (curr->parent != nullptr && curr == curr->parent->right)
        {
            curr->parent->right = temp;
        }

        if (this->root == curr)
        {
            this->root = temp;
        }
        curr->parent = temp;
        curr->height--;
        temp->height = std::max(temp->GetHeight(temp->left), temp->GetHeight(temp->right)) + 1;
    }

    void RR(Node<T> *curr)
    {
        if (curr == nullptr)
            return;

        Node<T> *temp = curr->right;
        curr->right = curr->right->left;
        if (curr->right != nullptr)
        {
            curr->right->parent = curr;
        }

        temp->left = curr;
        temp->parent = curr->parent;

        if (curr->parent != nullptr && curr == curr->parent->left)
        {
            curr->parent->left = temp;
        }
        else if (curr->parent != nullptr && curr == curr->parent->right)
        {
            curr->parent->right = temp;
        }

        if (this->root == curr)
        {
            this->root = temp;
        }
        curr->parent = temp;
        curr->height--;
        temp->height = std::max(temp->GetHeight(temp->left), temp->GetHeight(temp->right)) + 1;
    }

    void RL(Node<T> *curr)
    {
        LL(curr->right);
        RR(curr);
    }

    void LR(Node<T> *curr)
    {
        RR(curr->left);
        LL(curr);
    }

    //O(logn) n - size of the tree
    template <class Key>
    void AddItemAux(Node<T> *curr, T new_data, Key key)
    {
        Node<T> *new_node = new Node<T>(new_data);
        if (curr->left == nullptr && curr->right == nullptr) //curr == leaf
        {
            if (curr->data > key)
            {
                curr->left = new_node;
            }
            else
            {
                curr->right = new_node;
            }
            new_node->parent = curr;
        }
        else if (curr->data > key)
        {
            if (curr->left == nullptr)
            {
                curr->left = new_node;
                new_node->parent = curr;
            }
            else
            {
                AddItemAux(curr->left, new_data, key);
            }
        }
        else
        {
            if (curr->right == nullptr)
            {
                curr->right = new_node;
                new_node->parent = curr;
            }
            else
            {
                AddItemAux(curr->right, new_data, key);
            }
        }

        curr->height = std::max(curr->GetHeight(curr->left), curr->GetHeight(curr->right)) + 1;
        fixTree(curr);
    }

    template <class Key>
    Node<T> *deleteNodeRec(Node<T> *curr, Key key)
    {
        if (curr == nullptr)
        {
            return curr;
        }

        //We now locate in recursion the location of the node we want to remove
        if (curr->data > key) ///////////////
        {
            curr->left = deleteNodeRec(curr->left, key);
        }
        else if (curr->data < key) /////////////////////
        {
            curr->right = deleteNodeRec(curr->right, key);
        }
        else
        {
            Node<T> *node_replace;
            if (curr->left == nullptr && curr->right == nullptr) // the node is a leaf
            {
                if (this->root == curr)
                {
                    this->root = nullptr;
                }
                delete curr;
                return nullptr;
            }
            else
            {
                if (curr->left != nullptr)
                {
                    node_replace = Getpredecessor(curr->left);
                    if (node_replace != curr->left)
                    {
                        node_replace->left = curr->left;
                        if (node_replace->left != nullptr)
                        {
                            node_replace->left->parent = node_replace;
                        }
                    }
                    node_replace->right = curr->right;
                    if (node_replace->right != nullptr)
                    {
                        node_replace->right->parent = node_replace;
                    }
                }
                else if (curr->right != nullptr)
                {
                    node_replace = GetSuccesor(curr->right);
                    if (node_replace != curr->right)
                    {
                        node_replace->right = curr->right;
                        if (node_replace->right != nullptr)
                        {
                            node_replace->right->parent = node_replace;
                        }
                    }
                    node_replace->left = curr->left;
                    if (node_replace->left != nullptr)
                    {
                        node_replace->left->parent = node_replace;
                    }
                }

                if (node_replace->parent->left == node_replace)
                {
                    node_replace->parent->left = nullptr;
                }
                else
                {
                    node_replace->parent->right = nullptr;
                }
                node_replace->parent = curr->parent;
                Node<T> *temp = curr;
                if (this->root == curr)
                {
                    this->root = node_replace;
                }
                curr = node_replace;
                delete temp;
            }
        }

        if (curr == nullptr)
            return nullptr;

        //update height
        curr->height = std::max(curr->GetHeight(curr->left), curr->GetHeight(curr->right)) + 1;

        //Fixing the Tree
        return fixTree(curr);
    }

    void inOrderToArrayAux(Node<T> *curr, T *arr, int size, int *index)
    {
        if (curr == nullptr || *index >= size)
        {
            return;
        }
        inorder_to_array(curr->left, arr, index);
        arr[*(++index)] = curr->data;
        inorder_to_array(curr->right, arr, index);
    }

    void print_tree(Node<T> *node)
    {
        if (size == 0)
        {
            return;
        }
        if (node == nullptr)
        {
            return;
        }
        if (node->left != nullptr)
        {
            print_tree(node->left);
        }
        std::cout << node->data << " ";
        if (node->right != nullptr)
        {
            print_tree(node->right);
        }
    }

public:
    AVLTree() : root(nullptr), size(0){};

    ~AVLTree()
    {
        deleteTree(root);
    }

    AVLTree(const AVLTree &other) : size(other.size)
    {
        root = copy_tree(other.root, nullptr);
    }

    template <class Key>
    void AddItem(const T new_data, Key key)
    {
        if (this->root == nullptr)
        {
            root = new Node<T>(new_data);
        }
        else
            AddItemAux(root, new_data, key);
        this->size++;
    }

    template <class Key>
    void removeItem(Key key)
    {
        deleteNodeRec(this->root, key);
        size--;
    }

    int getSize()
    {
        return this->size;
    }

    template <class Key>
    bool isExists(Key key)
    {
        if (this->FindItem(this->root, key) == nullptr)
        {
            return false;
        }
        return true;
    }

    Node<T> *getRoot()
    {
        return this->root;
    }

    template <class Key>
    T getData(Key key)
    {
        Node<T> *temp = FindItem(this->root, key);
        if (temp == nullptr)
            return nullptr;

        return temp->getDataNode();
    }

    T FindMax()
    {
        Node<T> *temp = this->root;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }

        return temp->data;
    }

    void inOrderToArray(T* arr, int size){
        int i = 0;
        inOrderToArrayAux(this->root, arr, size, &i);
    }

    void print()
    {
        print_tree(root);
    }


    static void TransferItems(Node<T> *curr, AVLTree<T> &other_tree);
};

template <class T>
void AVLTree<T>::TransferItems(Node<T> *curr, AVLTree<T> &other_tree)
{
    if (curr == nullptr)
    {
        return;
    }

    transferRec(curr->left, other_tree);
    other_tree.AddItem(curr->data, curr->data);
    transferRec(curr->right, other_tree);
}


#endif
