#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>

template <class T>
class AVLTree
{
    template<class T>
    class Node
    {
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
            //add roll functions*******************************************************************************************************
        }


       
        void removeItem(int id){
            if(!this->isExists(id)){
                throw PlayerNotExsist();
            }
            Node<T> node_to_remove = FindItem(id);
            if(node_to_remove->left == nullptr){
                node_to_remove->right->parent = node_to_remove->parent;
                node_to_remove->parent
            }
            
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
        
        class PlayerNotExsist(): public std::exception

    private:
        //log(n- size of the tree)
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
        //log(n- size of the tree)
        //return the node
        Node<T> FindItem(int id){
            if(this == nullptr){ return nullptr;}
            if(this->data->getID() == id){return this;}
            if(this->data->getID() > id){
                return this->left->FindItem(id);
            }
            return this->right->FindItem(id);
        }
        //log(n- size of the tree)
        //return the node
        Node<T> FindItem(int level, int id){
            if(this == nullptr){ return nullptr;}
            if(this->data->getID() == id){return this;}
            if(this->data->level > level || (this->data->level == level && this->data->level > id)){
                return this->left->FindItem(level, id));
            }
            return this->right->FindItem(id);
        }
        //log(n- size of the tree)
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




};

#endif
