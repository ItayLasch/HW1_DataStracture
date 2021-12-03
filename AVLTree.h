#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <memory>
#include "Exceptions.h"

template <class T, class Key>
class AVLTree;

template <class T, class Key>
class Node
{
    Key key;
    T data;
    Node<T, Key> *left;
    Node<T, Key> *right;
    Node<T, Key> *parent;
    int height;

    Node(Key &key, T& data) :key(key), data(data), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
    ~Node() = default;
    Node(const Node<T, Key> &other) = default;
    Node &operator=(const Node &other) = default;
    Key getKeyNode()
    {
        return this->key;
    }

    T getDataNode()
    {
        return this->data;
    }

    int static GetHeight(Node<T,Key> *node)
    {
        if (node == nullptr){
            return -1;
        }
        return node->height;
    }

    int BFcalc(Node<T, Key> *curr)
    {
        if (curr == nullptr)
        {
            throw NullArg();
        }
        return GetHeight(curr->left) - GetHeight(curr->right);
    }
    friend AVLTree<T,Key>;
};

template <class T, class Key>
class AVLTree
{
    Node<T,Key> *root;
    int size;

    //O(logn) n - size of the tree
    Node<T, Key> *copy_tree(Node<T, Key> *other, Node<T, Key> *parent)
    {
        if (other == nullptr)
        {
            return nullptr;
        }
        Node<T, Key> *new_node = new Node<T, Key>(other->key, other->data);
        new_node->parent = parent;
        new_node->height = other->height;
        new_node->left = copy_tree(other->left, new_node);
        new_node->right = copy_tree(other->right, new_node);
        return new_node;
    }

    void deleteTree(Node<T, Key> *node)
    {
        if (node == nullptr){
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    //O(logn) n - size of the tree
    //return the node
    Node<T, Key> *FindItem(Node<T, Key> *curr, Key& key)
    {
        if (curr == nullptr)
        {
            return nullptr;
        }
        if (curr->key == key)
        {
            return curr;
        }
        if (curr->key > key)
        {
            return FindItem(curr->left, key);
        }
        return FindItem(curr->right, key);
    }

    Node<T, Key> *Getpredecessor(Node<T, Key> *curr)
    {
        Node<T, Key> *temp = curr;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }

    Node<T, Key> *GetSuccesor(Node<T, Key> *curr)
    {
        Node<T, Key> *temp = curr;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }

    Node<T, Key> *fixTree(Node<T, Key> *curr)
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

    void LL(Node<T, Key> *curr)
    {
        if (curr == nullptr)
            return;

        Node<T, Key> *temp = curr->left;
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

    void RR(Node<T, Key> *curr)
    {
        if (curr == nullptr)
            return;

        Node<T, Key> *temp = curr->right;
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

    void RL(Node<T, Key> *curr)
    {
        LL(curr->right);
        RR(curr);
    }

    void LR(Node<T, Key> *curr)
    {
        RR(curr->left);
        LL(curr);
    }

    //O(logn) n - size of the tree
    void AddItemAux(Node<T, Key> *curr, T& new_data, Key& key)
    {
        Node<T, Key> *new_node = new Node<T, Key>(key, new_data);
        if (curr->left == nullptr && curr->right == nullptr) //curr == leaf
        {
            if (curr->key > key)
            {
                curr->left = new_node;
            }
            else
            {
                curr->right = new_node;
            }
            new_node->parent = curr;
        }
        else if (curr->key > key)
        {
            if (curr->left == nullptr)
            {
                curr->left = new_node;
                new_node->parent = curr;
            }
            else
            {
                delete new_node;
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
                delete new_node;
                AddItemAux(curr->right, new_data, key);
            }
        }

        curr->height = std::max(curr->GetHeight(curr->left), curr->GetHeight(curr->right)) + 1;
        fixTree(curr);
    }

    Node<T, Key> *deleteNodeRec(Node<T, Key> *curr,const Key& key)
    {
        if (curr == nullptr)
        {
            return curr;
        }

        //We now locate in recursion the location of the node we want to remove
        if (curr->key > key) 
        {
            curr->left = deleteNodeRec(curr->left, key);
        }
        else if (curr->key < key) 
        {
            curr->right = deleteNodeRec(curr->right, key);
        }
        else
        {
            Node<T, Key> *node_replace;
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
                Node<T, Key> *temp = curr;
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

    void inOrderToArraysAux(Node<T,Key> *curr, T *arrData, Key *arrKey, int size, int *index)
    {
        if (curr == nullptr || *index >= size)
        {
            return;
        }
        inOrderToArraysAux(curr->left, arrData, arrKey, size, index);
        arrData[*(index)] = curr->data;
        arrKey[*(index)] = curr->key;
        (*index)++;
        inOrderToArraysAux(curr->right, arrData, arrKey, size, index);
    }

    static Node<T, Key> *sortedArrayToBST_helper(T *arrData, Key* arrKey, int start, int end,int size_limit)//A - array of *Node
    {
        // continue while this branch has values to process
        if(start > end){
            return nullptr;
        }
        // Get the middle element and make it root
        int mid = start + (end - start)/2;
        if(mid == size_limit)
        {
            return nullptr;
        }
        Node<T, Key>* curr = new Node<T, Key>(arrKey[mid], arrData[mid]);
        // Recursively construct the left subtree
        // and make it left child of root
        curr->left = sortedArrayToBST_helper(arrData, arrKey, start, mid - 1, size_limit);
        // Recursively construct the right subtree
        // and make it right child of root
        curr->right = sortedArrayToBST_helper(arrData, arrKey, mid + 1, end, size_limit);
        return curr;
    }

    static void sortedArrayToBST(T *AData, Key *AKey, int n, AVLTree<T, Key> &new_tree)
    {
        new_tree.root = sortedArrayToBST_helper(AData, AKey, 0, n,n);
    }

    void print_tree(Node<T, Key> *node)
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
        std::cout << node->key << " ";
        if (node->right != nullptr)
        {
            print_tree(node->right);
        }
    }

public:
    AVLTree() : root(nullptr), size(0){};

    ~AVLTree()
    {
        //std::cout<< "delete tree of: " << typeid(root->data)->name() << "\n";
        deleteTree(root);
    }

    AVLTree(const AVLTree<T, Key> &other) : size(other.size)
    {
        root = copy_tree(other.root, nullptr);
    }

    AVLTree &operator=(const AVLTree &other)
    {
        if (this == &other){
            return *this;
        }

        this->deleteTree(this->root);
        this->root = this->copy_tree(other.root, nullptr);
        this->size = other.size;

        return *this;
    }

    void AddItem(T& new_data, Key key)
    {
        if (this->root == nullptr)
        {
            this->root = new Node<T, Key>(key,new_data);
        }
        else
            AddItemAux(root, new_data, key);
        this->size++;
    }

    void removeItem(const Key& key)
    {
        deleteNodeRec(this->root, key);
        size--;
    }

    int getSize()
    {
        return this->size;
    }

    bool isExists(Key &key)
    {
        if (this->FindItem(this->root, key) == nullptr)
        {
            return false;
        }
        return true;
    }

    Node<T, Key> *getRoot()
    {
        return this->root;
    }

    T getData(Key& key)
    {
        Node<T, Key> *temp = FindItem(this->root, key);
        if (temp == nullptr)
            return nullptr;

        return temp->getDataNode();
    }

    T FindMax()
    {
        Node<T, Key> *temp = this->root;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }

        return temp->data;
    }

    static void AVLTreeMerge(AVLTree<T, Key> &tr1, AVLTree<T, Key>& tr2, AVLTree<T, Key>& merge_tree){
        int s1 = tr1.getSize();
        int s2 = tr2.getSize();
        merge_tree.size = s1 + s2;
        T *arrData1 = new T[s1];
        T *arrData2 = new T[s2];
        T *arrDataNew = new T[s1 + s2];
        Key *arrKey1 = new Key[s1];
        Key *arrKey2 = new Key[s2];
        Key *arrKeyNew = new Key[s1 + s2];
        tr1.inOrderToArrays(arrData1, arrKey1, s1);
        tr2.inOrderToArrays(arrData2, arrKey2, s2);
        int index1 = 0, index2 = 0, index_new = 0;
        while(index_new < s1 + s2){//merge the 2 arrays into 1
            if(index1 == s1){
                arrKeyNew[index_new] = arrKey2[index2];
                arrDataNew[index_new++] = arrData2[index2++];
                continue;
            }
            if(index2 == s2){
                arrKeyNew[index_new] = arrKey1[index1];
                arrDataNew[index_new++] = arrData1[index1++];
                continue; 
            }
            if(arrKey1[index1] > arrKey2[index2]){
                arrKeyNew[index_new] = arrKey2[index2];
                arrDataNew[index_new++] = arrData2[index2++];
                continue;
            }
            arrKeyNew[index_new] = arrKey1[index1];
            arrDataNew[index_new++] = arrData1[index1++];
            
        }
        AVLTree<T,Key>::sortedArrayToBST(arrDataNew, arrKeyNew, s1 + s2, merge_tree);
        delete[] arrData1;
        delete[] arrData2;
        delete[] arrDataNew;
        delete[] arrKey1;
        delete[] arrKey2;
        delete[] arrKeyNew;
    }

    void inOrderToArrays(T* arrData, Key* arrKey, int size){
        int i = 0;
        inOrderToArraysAux(this->root, arrData, arrKey, size, &i);
    }

    template<typename Func>
    void Inorder(Func f)
    {
        try{
            nodeInorder(this->root, f);
        }
        catch (std::exception &e){}
    }

    template <typename Func>
    void nodeInorder(Node<T, Key>* node, Func f)
    {
        if(node == nullptr)
        {
            return;
        }

        nodeInorder(node->left, f);
        if(node->data != nullptr){
            f(node->data);
        }
        nodeInorder(node->right, f);
    }


    
    void print()
    {
        print_tree(root);
    }
};

#endif
