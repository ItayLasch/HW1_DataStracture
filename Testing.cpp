#include "library1.h"
#include "AVLTree.h"

int main()
{
    AVLTree<int,int> tr = AVLTree<int,int>();
    tr.AddItem(10,10);
    tr.AddItem(4, 4);
    tr.AddItem(18, 18);
    tr.AddItem(3, 3);
    tr.AddItem(6, 6);
    tr.AddItem(14, 14);
    tr.AddItem(1, 1);
    /*tr.AddItem(0, 0);
    tr.AddItem(50, 50);
    tr.AddItem(45, 45);
    tr.AddItem(41, 41);*/
    std::cout << "size: " << tr.getSize() << std::endl;
    tr.print();
    std::cout << std::endl;

/*
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
*/
    return 0;
}