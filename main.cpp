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

void hello()
{
    EditorAssistHeap book;
    book.insertion();
    //book.extraction();
}

void hello2()
{
    EditorAssistBinaryTree book;
    book.insertion();
   // book.extraction();
}

int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

   QApplication app(argc, argv);
   QFuture<void> f1 = run(hello);
   QFuture<void> f2 = run(hello2);
   f1.waitForFinished();
   f2.waitForFinished();

  return 0;
}
