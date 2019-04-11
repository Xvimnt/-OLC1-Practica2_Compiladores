#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "var.h"
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

    void on_actionGuardar_Como_triggered();

    void on_actionCompilar_triggered();

    void on_actionAST_triggered();

    void on_actionErrores_triggered();

    void on_actionNuevo_triggered();

private:
    Ui::MainWindow *ui;
    void saveAs();
    void showVariables(std::map<QString, var*> variables);
};

#endif // MAINWINDOW_H
