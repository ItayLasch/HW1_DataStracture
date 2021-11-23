#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <iostream>

template <class T>
class AVLTree
{
    template<class T>
    class Node
    {
        private:
            T data;
            Node<T> *left;
            Node<T> *right;
            Node<T> *parent;
            int height;

            Node(T data) : data(data), left(nullptr), right(nullptr), parent(nullptr){}
            ~Node() = default;
            Node(const Node& other) = default;
            Node& operator=(const Node& other) = default;
            T getDataNode(){
                return this->data;
            }
            friend class AVLTree;
        };
    
        Node<T> root;
        int size;
    
        void replaceNodes(Node<T>* node1, Node<T>* node2){
            Node<T> temp = node1;
            bool parent1 = false;//node1 left son
            bool parent2 = false;//node2 left son
            node1->parent = node2->parent;
            node1->left = node2->left;
            node1->right = node2->right;
            node2->parent = temp->parent;
            node2->left = temp->left;
            node2->right = temp->right;
        }

        //O(logn) n - size of the tree
        Node<T> copy_tree(Node<T> other, Node<T> parent){
            if(other == nullptr){
                return nullptr;
            }
            Node<T> new_node(other->data);
            newNode->parent = parent;
            newNode->height = other->height;
            newNode->left = copy_tree(other->left, new_node);
            newNode->right = copy_tree(other->right, new_node);
            return new_node;
        }
        //O(logn) n - size of the tree
        //return the node
        Node<T> FindItem(int id){
            if(this == nullptr){ return nullptr;}
            if(this->data->getID() == id){return this;}
            if(this->data->getID() > id){
                return this->left->FindItem(id);
            }
            return this->right->FindItem(id);
        }
        //O(logn) n - size of the tree
        //return the node
        Node<T> FindItem(int level, int id){
            if(this == nullptr){ return nullptr;}
            if(this->data->getID() == id){return this;}
            if(this->data->level > level || (this->data->level == level && this->data->id > id)){
                return this->left->FindItem(level, id));
            }
            else{
                return this->right->FindItem(id);
            }
        }

        
        //O(logn) n - size of the tree
         void AddItemAux(new_data){
            if(this->left == nullptr && this->right == nullptr){
                if(this->data->id > new_data->id){
                    this->left = Node(new_data);
                    new_data->parent = *this;
                }
                else if(this->data->id > new_data=>id){
                    this->left->AddItemAux(new_data);
                }
                else{
                    this->right->addItemAux(new_data);
                }
            }
            this->heigth++;
        }
        //get the min Node. O(logn), n-size of the tree
        Node<T>* NodeToReplace(){
            if(this->left == nullptr){
                return this;
            }
            this->left->NodeToReplace();
        }

    public:

        AVLTree(): root(nullptr), size(0){};
        ~AVLTree() = default;
        AVLTree(const AVLTree& other): root(other->root), size(other->size){
            copy_tree(other->root, nullptr);
        }

        
        void AddItem(const T new_data){
            if(this->root == nullptr){
                root = Node(new_data);
                this->size++;
            }
            else
                this->root->AddItemAux(new_data);
                this->size++;
            //add roll functions*******************************************************************************************************
        }

        void removeItem(int id){
            if(!this->isExists(id)){
                throw PlayerNotExsist();
            }
            Node<T>* node_to_remove = FindItem(id);
            if(node_to_remove->left == nullptr){
                node_to_remove->right->parent = node_to_remove->parent;
                if(node_to_remove == node_to_remove->parent->left){
                    node_to_remove->parent->left = node_to_remove->right;
                }
                else{
                    node_to_remove->parent->right = node_to_remove->right;
                }
            }
            elif(node_to_remove->right == nullptr){
                node_to_remove->left->parent = node_to_remove->parent;
                if(node_to_remove == node_to_remove->parent->left){
                    node_to_remove->parent->left = node_to_remove->left;
                }
                else{
                    node_to_remove->parent->right = node_to_remove->left;
                }
            }
            else{
                Node<T>* temp = NodeToReplace(node_to_remove->right);
                replaceNodes(temp, node_to_remove);
                if(node_to_remove->right != nullptr){
                    node_to_remove->right = node_to_remove->parent;
                }
                node_to_remove->parent->left = node_to_remove->right;
            }
            delete(node_to_remove);
            this->size--;
            //add roll functions**********************************************************************************************************
        }

        bool isExists(int id){
            if(this->FindItem(id) == nullptr){
                return false;
            }
            return true;
        }

        T getData(int id)
        {
            Node<T> *temp = FindItem(id);
            if(temp == nullptr)
                return nullptr;

            return temp->getDataNode();
        }
        //O(logn) n-number of players in the group
        T getMax(){
            if(this->root == nullptr){
                throw EmptyDataSystem;
            }
            Node<T>* temp = this->root;
            while(temp->right != nullptr){
                temp = temp->right;
            }
            return temp->data;
        }

        void print_tree(Node<T>* node){
            if(this == nullptr){
                return;
            }
            print_tree(node->left);
            std::cout << node->data;
            print_tree(node->right);
        }
        class EmptyDataSystem(): public std::exception
        class PlayerNotExsist(): public std::exception

    

};

#endif
