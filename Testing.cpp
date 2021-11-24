#include "AVLTree.h"


int main()
{
    AVLTree<int> tr = AVLTree<int>();
    std::cout << "size: " << tr.getSize() << std::endl;

    tr.AddItem(9);
    tr.AddItem(18);
    tr.AddItem(7);
    tr.AddItem(20);
    tr.AddItem(40);
    tr.AddItem(4);
    tr.AddItem(0);
    tr.AddItem(50);
    tr.AddItem(45);
    tr.AddItem(41);
    std::cout << "size: " << tr.getSize() << std::endl;

    std::cout << std::endl;
    tr.print();
}