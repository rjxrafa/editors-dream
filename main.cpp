//#include "mainwindow.h"
#include <iostream>
#include "binarytree.h"
#include "editorassistheap.h"
#include "editorassistbinarytree.h"
//#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QString>
#include <qtconcurrentrun.h>
#include <QApplication>

using namespace QtConcurrent;

//void hello()
//{
//    EditorAssistHeap book;
//    book.insertion();
//    book.extraction();
//}

//void hello2()
//{
//    EditorAssistBinaryTree book;
//    book.insertion();
//    book.extraction();
//}
using namespace std;
int main(int argc, char *argv[]) {
    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    //    return a.exec();
    //   QApplication app(argc, argv);
    //   QFuture<void> f1 = run(hello);
    //   QFuture<void> f2 = run(hello2);
    //   f1.waitForFinished();
    EditorAssistHeap book;
    cout<<"Syllables: "<<book.syllableCounter("air")<<endl;
//    book.insertion();
//    book.extraction();
    //  f2.waitForFinished();
    //  bst::BinaryTree<int> a;
    return 0;
}
