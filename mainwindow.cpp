#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "var.h"
#include <qfiledialog.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <semantic.h> // Nuestro parser
#include <parser.h>   // Nuestro parser
#include <scanner.h>  // Nuestro scanner
#include <plotter.h>  // Graficador
#include <node.h>     //Nuestra clase nodo
#include <QDesktopServices>
#include <QFile>
#include <QFileInfo>
#include "error.h"
#include <QDebug>
#include <QTableWidgetItem>

static QString path;
extern node *root;
static bool correcto;
extern int linea;   // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;
QList<error *> globalErrors;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    path = QFileDialog::getOpenFileName(this,
                                        tr("OLC1 Interpreter"), "/home/", tr("OLC1 Interpreter (*.fi)"));

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "error", file.errorString());
    }

    QTextStream in(&file);

    ui->txtInput->setText(in.readAll());
    file.close();
}

void MainWindow::on_actionGuardar_triggered()
{
    if (path.isEmpty())
    {
        saveAs();
    }
    else
    {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, "error", file.errorString());
        }
        QTextStream out(&file);
        out << ui->txtInput->toPlainText() << endl;
        file.close();
        QMessageBox::information(this, "Guardar", "Guardado Exitosamente");
    }
}

void MainWindow::saveAs()
{
    path = QFileDialog::getSaveFileName(this,
                                        tr("OLC1 Interpreter"), "/home/", tr("OLC1 Interpreter (*.fi)"));

    QFile file(path + ".fi");
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, "error", file.errorString());
    }

    QTextStream out(&file);
    out << ui->txtInput->toPlainText() << endl;
    file.close();
    QMessageBox::information(this, "Guardar", "Guardado Exitosamente");
}

void MainWindow::on_actionGuardar_Como_triggered()
{
    saveAs();
}

void MainWindow::showVariables(std::map<QString, var *> variables)
{

    std::map<QString, var *>::iterator it;

    ui->tbVar->setRowCount(variables.size());

    int row = 0;
    for (it = variables.begin(); it != variables.end(); it++)
    {
        QTableWidgetItem *name = new QTableWidgetItem();
        name->setText(it->first);
        ui->tbVar->setItem(row, 0, name);
        QTableWidgetItem *value = new QTableWidgetItem();
        value->setText(it->second->getValue());
        ui->tbVar->setItem(row, 1, value);
        QTableWidgetItem *type = new QTableWidgetItem();
        type->setText(it->second->getTypeName());
        ui->tbVar->setItem(row, 2, type);
        row++;
    }
}

void MainWindow::on_actionCompilar_triggered()
{
    QString programa = ui->txtInput->toPlainText();
    YY_BUFFER_STATE buffer = yy_scan_string(programa.toUtf8().constData());

    /*Limpiamos los contadores
            ya que son variables globales*/
    errores.clear();
    linea = 0;
    columna = 0;
    yylineno = 0;

    if (yyparse() == 0 && errores.count() == 0) // Si nos da un número negativo, signifca error.
    {

        //Iniciando el analiziz semantico
        semantic *interprete = new semantic();
        interprete->recorrer(root);

        if (interprete->errores.count() == 0)
        {
            showVariables(interprete->variables);

            QMessageBox::information(this, "Exito", "Entrada Correcta");
            correcto = true;
        }
        else
        {
            QMessageBox::information(this, "Error", "Error en la fase de analisis semantico");
            correcto = false;
        }
    }
    else
    {
        QMessageBox::information(this, "Error", "Error en la fase de analisis");
        correcto = false;
    }
}

void MainWindow::on_actionAST_triggered()
{
    if (correcto)
    {
        /*Instanciamos un graficador y graficamos*/
        graficador *graf = new graficador(root);
        graf->generarImagen();
        QMessageBox::information(this, "Exito", "Arbol Generado Correctamente");
    }
    else
    {
        QMessageBox::information(this, "Error", "Su entrada ha sido incorrecta, o no se ha analizado");
    }
}

std::string getErrors()
{
    std::string result = "<table>\n<thead><tr class=\"row100 head\"><th class=\"cell100 column1\">Fila</th>";
    result += "<th class=\"cell100 column2\">Columna</th><th class=\"cell100 column3\">Token</th><th class=\"cell100 column4\">Tipo</th>";
    result += "</tr></thead></table></div>";
    /*
                                <div class="table100-body js-pscroll">
                                    <table>
                                        <tbody>
                                            <tr class="row100 body">
                                                <td class="cell100 column1">Virtual Cycle</td>
                                                <td class="cell100 column2">Gym</td>
                                                <td class="cell100 column3">8:00 AM - 9:00 AM</td>
                                                <td class="cell100 column4">Randy Porter</td>
                                                <td class="cell100 column5">20</td>
                                            </tr>
                                        </tbody>
                                    </table>*/
    return result;
}

void MainWindow::on_actionErrores_triggered()
{
    if (correcto)
    {
        QMessageBox::information(this, "Error", "Su entrada ha sido correcta, no hay errores que mostrar o no se ha analizado");
        return;
    }
    std::string index;
    index = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<title>Table V04</title>\n<meta charset=\"UTF-8\">";
    index += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    index += "<link rel=\"icon\" type=\"image/png\" href=\"images/icons/favicon.ico\"/>";
    index += "<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/bootstrap/css/bootstrap.min.css\">";
    index += "<link rel=\"stylesheet\" type=\"text/css\" href=\"fonts/font-awesome-4.7.0/css/font-awesome.min.css\">";
    index += "<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/animate/animate.css\">";
    index += "<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/select2/select2.min.css\">";
    index += "<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/perfect-scrollbar/perfect-scrollbar.css\">";
    index += "<link rel=\"stylesheet\" type=\"text/css\" href=\"css/util.css\">";
    index += "<link rel=\"stylesheet\" type=\"text/css\" href=\"css/main.css\">";
    index += "</head>\n<body>\n<div class=\"limiter\">\n<div class=\"container-table100\">\n<div class=\"wrap-table100\">";
    index += "<div class=\"table100 ver3 m-b-110\">\n<div class=\"table100-head\">";
    index += getErrors();
    index += "\n</div>\n</div>\n</div>\n</div>\n</div>";
    index += "<script src=\"vendor/jquery/jquery-3.2.1.min.js\"></script>";
    index += "<script src=\"vendor/bootstrap/js/popper.js\"></script>";
    index += "<script src=\"vendor/bootstrap/js/bootstrap.min.js\"></script>";
    index += "<script src=\"vendor/select2/select2.min.js\"></script>";
    index += "<script src=\"vendor/perfect-scrollbar/perfect-scrollbar.min.js\"></script>";
    index += "<script>$('.js-pscroll').each(function(){var ps = new PerfectScrollbar(this);$(window).on('resize', function(){";
    index += "ps.update();})});</script><script src=\"js/main.js\"></script></body></html>";

    QFileInfo fi("temp");
    QString path = fi.absolutePath() + "/";
    //QDesktopServices::openUrl(QUrl::fromLocalFile(path+"index.html"));
}
