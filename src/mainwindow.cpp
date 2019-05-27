#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "include/editorassistheap.h"
#include "include/editorassistbinarytree.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_File_triggered()
{

    EditorAssistBinaryTree ay;
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                "All files (*.*);;Text File (*.txt)"
                );
    QMessageBox::information(
                this,tr("Book Name"),fileName
                );

    ay.QtInsertion(fileName);
    ui->textBrowser_3->setText(ay.QtOutput());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{

}

void MainWindow::on_tab_2_customContextMenuRequested(const QPoint &pos)
{

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
