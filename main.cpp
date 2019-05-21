//#include "mainwindow.h"
#include <iostream>
#include "binarytree.h"
#include "editorassistheap.h"
#include "editorassistbinarytree.h"
#include <QThread>
//#include <QApplication>
int add() {
  for (unsigned int i = 0; i < 100000; ++i) {

  }
  return 2;
}

using namespace std;
int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
EditorAssistHeap book;
//EditorAssistBinaryTree book;
book.insertion();
//book.extraction();
//  QThread a,b;
//  a.create(add);
//  b.create(add);
//  a.start();
//  b.start();


  return 0;
}
