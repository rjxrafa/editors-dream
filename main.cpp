/* We, Ara Mico Segismundo and Rafa Betita do hereby certify that we
 * have derived no assistance for this project or examination from any
 * sources whatever, whether oral, written, or in print. We also understand
 * that if it is found that we have received
 * unauthorized assistance, then we receive a failing grade.
 *
 * This program uses the editor's dream program and applies it to a gui.
 * It will tell the user an estimated reading level, words, top 10 words,
 * paragraphs, and time it takes to process.
 */
#include "include/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
