#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    fileName = "";
    secs = 0;
}
/**
 * @brief MainWindow::on_actionNew_File_triggered
 * When file is pressed and chosen, gets filename
 * and puts them into two new trees
 */
void MainWindow::on_actionNew_File_triggered()
{
    EditorAssistBinaryTree bTree;
    EditorAssistHeap hTree;
    fileName = "";
    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                "All files (*.*);;Text File (*.txt)"
                );

    if(fileName != "")
    {
    hTree.timeTest(fileName.toStdString());
    bTree.QtInsertion(fileName);
    tabDisplay(bTree);
    secs = bTree.getSeconds();
    QMessageBox::information(
                this,tr("Runtime"),QString("Binary Tree Runtime: %1\n"
                                           "Heap Runtime: %2")
                .arg(bTree.getSeconds()).arg(hTree.getSeconds())
                );
    }
}
/**
 * Exits qt creator
 */
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
/**
 * @brief MainWindow::tabDisplay
 * Displays word information for letters
 */
void MainWindow::tabDisplay(const EditorAssistBinaryTree &b)
{
    ui->infoTab->setText(b.QtOutput());
    ui->tabA->setText(b.QtTabWords('A'));
    ui->tabB->setText(b.QtTabWords('B'));
    ui->tabC->setText(b.QtTabWords('C'));
    ui->tabD->setText(b.QtTabWords('D'));
    ui->tabE->setText(b.QtTabWords('E'));
    ui->tabF->setText(b.QtTabWords('F'));
    ui->tabG->setText(b.QtTabWords('G'));
    ui->tabH->setText(b.QtTabWords('H'));
    ui->tabI->setText(b.QtTabWords('I'));
    ui->tabJ->setText(b.QtTabWords('J'));
    ui->tabK->setText(b.QtTabWords('K'));
    ui->tabL->setText(b.QtTabWords('L'));
    ui->tabM->setText(b.QtTabWords('M'));
    ui->tabN->setText(b.QtTabWords('N'));
    ui->tabO->setText(b.QtTabWords('O'));
    ui->tabP->setText(b.QtTabWords('P'));
    ui->tabQ->setText(b.QtTabWords('Q'));
    ui->tabR->setText(b.QtTabWords('R'));
    ui->tabS->setText(b.QtTabWords('S'));
    ui->tabT->setText(b.QtTabWords('T'));
    ui->tabU->setText(b.QtTabWords('U'));
    ui->tabV->setText(b.QtTabWords('V'));
    ui->tabW->setText(b.QtTabWords('W'));
    ui->tabX->setText(b.QtTabWords('X'));
    ui->tabY->setText(b.QtTabWords('Y'));
    ui->tabZ->setText(b.QtTabWords('Z'));
}

/**
 * @brief MainWindow::on_actionSave_Info_triggered
 * Uses the seconds from the file opening
 * and saves all information to a new file
 */
void MainWindow::on_actionSave_Info_triggered()
{
    EditorAssistBinaryTree bTree;
    bTree.QtInsertion(fileName);
    bTree.setSeconds(secs);
    QString saveName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Name"),"",
                                                    tr("Text File (*.txt);;All files (*.*)"));
    bTree.QtWriteToFile(saveName.toStdString());

}
