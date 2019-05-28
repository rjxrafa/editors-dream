#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "include/editorassistheap.h"
#include "include/editorassistbinarytree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_File_triggered();

    void on_actionExit_triggered();

    void tabDisplay(const EditorAssistBinaryTree &b);

    void on_actionSave_Info_triggered();

private:
    Ui::MainWindow *ui;
    QString fileName;
    double secs;
};

#endif // MAINWINDOW_H
