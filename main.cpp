/*
 * I, Rafa Betita and Ara Mico Segismundo, do hereby certify that I have
 * derived no assistance for this project or examination from any sources
 * whatever, whether oral, written, or in print. I also understand that
 * if it is found that I have received unauthorized assistance, then I
 * and the individuals involved will receive a failing grade.
 */
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
  //  cout<<"Syllables: "<<book.syllableCounter("air")<<endl;
//    EditorAssistBinaryTree book1;
//    book1.insertion();
//    book1.extraction();
//    EditorAssistBinaryTree book;
//    book.Display();
    EditorAssistBinaryTree book1;
    book1.Run();
    EditorAssistHeap book2;
    book2.Run();

    //  f2.waitForFinished();
//    bst::BinaryTree<int> a;
//    a << 10 << 20 << 30 << 40 << 50;
//    cout << a;

    return 0;
}
