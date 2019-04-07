#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "var.h"
#include <qfiledialog.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <semantic.h>  // Nuestro parser
#include <parser.h>  // Nuestro parser
#include <scanner.h>  // Nuestro scanner
#include <plotter.h> // Graficador
#include <node.h> //Nuestra clase nodo
#include <QDesktopServices>
#include <QFile>
#include <QFileInfo>
#include "error.h"

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

private:
    Ui::MainWindow *ui;
    void saveAs();
    void showVariables(std::map<QString, var*> variables);
};

#endif // MAINWINDOW_H
