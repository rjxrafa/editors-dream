//#include "mainwindow.h"
#include <iostream>
#include "binarytree.h"
#include "editorassistheap.h"
#include "editorassistbinarytree.h"
#include <QThread>
#include <QDebug>
#include <QString>
#include <qtconcurrentrun.h>
#include <QApplication>

using namespace QtConcurrent;
using namespace std;

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
//    EditorAssistHeap book;
//    cout<<"Syllables: "<<book.syllableCounter("air")<<endl;
//  EditorAssistBinaryTree book;
//  book.insertion();
//  book.extraction();
    //  f2.waitForFinished();
    bst::BinaryTree<int> a;
    a << 10 << 20 << 30 << 40 << 50;
    cout << a;

    return 0;
}
