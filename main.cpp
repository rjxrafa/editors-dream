//#include "mainwindow.h"
#include <iostream>
#include "binarytree.h"
//#include <QApplication>

using namespace std;
int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

  bst::BinaryTree<int> a;

  a << 25;
  a << 13;
  a << 43;
  a << 55;

  a.PrintTree(a.root());



  return 0;
}
