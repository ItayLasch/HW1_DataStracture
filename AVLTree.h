#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Exceptions.h"

template <class T>
class AVLTree;

template <class T>
class Node
{
public:
    T data;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    int height;

    Node(T data) : data(data), left(nullptr), right(nullptr), parent(nullptr) {}
    ~Node() = default;
    Node(const Node &other) = default;
    Node &operator=(const Node &other) = default;
    T getDataNode()
    {
        return this->data;
    }

    //O(logn) n - size of the tree
    void AddItemAux(T new_data)
    {

        if (this->left == nullptr && this->right == nullptr)
        {
            Node<T> *new_node = new Node<T>(new_data);
            if (this->data > new_data)
            {
                this->left = new_node;
            }
            else
            {
                this->right = new_node;
            }
            new_node->parent = this;
        }
        else if (this->data > new_data)
        {
            if (this->left == nullptr)
            {
                Node<T> *new_node = new Node<T>(new_data);
                this->left = new_node;
                new_node->parent = this;
            }
            else
            {
                this->left->AddItemAux(new_data);
            }
        }
        else
        {
            if (this->right == nullptr)
            {
                Node<T> *new_node = new Node<T>(new_data);
                this->right = new_node;
                new_node->parent = this;
            }
            else
            {
                this->right->AddItemAux(new_data);
            }
        }

        this->height++;
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
        if(curr == nullptr)
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

public:
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
        delete (node);
    }

    //O(logn) n - size of the tree
    //return the node
    Node<T> FindItem(int id)
    {
        if (this == nullptr)
        {
            return nullptr;
        }
        if (this->data->getID() == id)
        {
            return this;
        }
        if (this->data->getID() > id)
        {
            return this->left->FindItem(id);
        }
        return this->right->FindItem(id);
    }
    //O(logn) n - size of the tree
    //return the node
    Node<T> FindItem(int level, int id)
    {
        if (this == nullptr)
        {
            return nullptr;
        }
        if (this->data->getID() == id)
        {
            return this;
        }
        if (this->data->level > level || (this->data->level == level && this->data->id > id))
        {
            return this->left->FindItem(level, id);
        }
        else
        {
            return this->right->FindItem(id);
        }
    }

    //get the min Node. O(logn), n-size of the tree
    Node<T> *GetMinNode(Node<T> *curr)
    {
        Node<T>* temp = curr;
        while(temp->left != nullptr){
            temp = temp->left;
        }
        return temp;
    }

    AVLTree() : root(nullptr), size(0){};
    
    ~AVLTree()
    {
        deleteTree(root);
    }

    AVLTree(const AVLTree &other) : size(other.size)
    {
        root = copy_tree(other.root, nullptr);
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

        if (this->root == curr){
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
        if(curr->right != nullptr){
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

        if(this->root == curr){
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

    void print_tree(Node<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        print_tree(node->left);
        std::cout << node->data << " ";
        print_tree(node->right);
    }

    void AddItem(const T new_data)
    {
        if (this->root == nullptr)
        {
            root = new Node<T>(new_data);
        }
        else
            this->root->AddItemAux(new_data);
        this->size++;
        
    }

    void removeItem(int id)
    {
        if (!this->isExists(id))
        {
            throw PlayerNotExsist();
        }
        Node<T> *node_to_remove = FindItem(id);
        if (node_to_remove->left == nullptr)
        {
            node_to_remove->right->parent = node_to_remove->parent;
            if (node_to_remove == node_to_remove->parent->left)
            {
                node_to_remove->parent->left = node_to_remove->right;
            }
            else
            {
                node_to_remove->parent->right = node_to_remove->right;
            }
        }
        else if (node_to_remove->right == nullptr)
        {
            node_to_remove->left->parent = node_to_remove->parent;
            if (node_to_remove == node_to_remove->parent->left)
            {
                node_to_remove->parent->left = node_to_remove->left;
            }
            else
            {
                node_to_remove->parent->right = node_to_remove->left;
            }
        }
        else
        {
            Node<T> *temp = GetMinNode(node_to_remove->right);
            replaceNodes(temp, node_to_remove);
            if (node_to_remove->right != nullptr)
            {
                node_to_remove->right = node_to_remove->parent;
            }
            node_to_remove->parent->left = node_to_remove->right;
        }
        delete (node_to_remove);
        this->size--;
        //add roll functions**********************************************************************************************************
    }

    int getSize()
    {
        return this->size;
    }

    bool isExists(int id)
    {
        if (this->FindItem(id) == nullptr)
        {
            return false;
        }
        return true;
    }

    T getData(int id)
    {
        Node<T> *temp = FindItem(id);
        if (temp == nullptr)
            return nullptr;

        return temp->getDataNode();
    }

    //O(logn) n-number of players in the group
    T getMax()
    {
        if (this->root == nullptr)
        {
            throw EmptyDataSystem();
        }
        Node<T> *temp = this->root;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp->data;
    }

    void print()
    {
        print_tree(root);
    }

    
};

#endif
