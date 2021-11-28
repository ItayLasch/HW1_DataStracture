#include "AVLTree.h"


int main()
{
    AVLTree<int> tr = AVLTree<int>();
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
    tr.print();
    std::cout << std::endl;

    tr.removeItem(40);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(18);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(0);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(7);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(20);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(4);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(45);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(41);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(9);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    tr.removeItem(50);
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

    return 0;
}