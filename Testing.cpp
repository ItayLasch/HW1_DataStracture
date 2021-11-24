#include "AVLTree.h"


int main()
{
    AVLTree<int> tr = AVLTree<int>();
    std::cout << "size: " << tr.getSize() << std::endl;

    tr.AddItem(24);
    tr.AddItem(1);
    tr.AddItem(30);
    tr.AddItem(40);
    tr.AddItem(33);

    std::cout << "size: " << tr.getSize() << std::endl;

    tr.print();
    std::cout << std::endl;
    tr.RL(tr.root->right);
    tr.print();
}