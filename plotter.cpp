#include "plotter.h"
#include <QString>
#include <fstream>
#include <iostream>
#include <QtWidgets>
#include "node.h"
graficador::graficador()
{
    this->contador = 0;
}

graficador::graficador(node *raiz)
{
    this->grafo = "";
    this->raiz = raiz;
    this->contador = 0;
}

QString graficador::graficar()
{
    grafo = "digraph G{";
    grafo += "node[shape=\"box\"];";
    grafo += "node0[label=\"" + escapar("[" +raiz->tipo +"," + QString::number(raiz->tipo_)+ "("+ QString::number(raiz->linea)+","+ QString::number(raiz->columna)+")"+","+raiz->valor + "]") + "\"];\n";
    this->contador = 1;
    recorrerAST("node0", raiz);
    grafo += "}";
    return grafo;
}

void graficador::recorrerAST(QString padre, node *hijo)
{
    if(hijo == nullptr) return;
    int x = 0;
    for (x = 0 ; x < hijo->hijos.count() ; x++)
    {
        node *node = hijo->hijos[x];
        QString nombreHijo = "node" +  QString::number(contador);//  this->contador;
        grafo += nombreHijo + "[label=\"" + escapar("[" +node->tipo +"," + QString::number(node->tipo_)+ "("+ QString::number(node->linea)+","+ QString::number(node->columna)+")" + "," + node->valor + "]") + "\"];\n";
        grafo += padre + "->" + nombreHijo + ";\n";
        contador++;
        recorrerAST(nombreHijo, node);
    }
}

QString graficador::escapar(QString cadena)
{
    cadena = cadena.replace("\\", "\\\\");
    cadena = cadena.replace("\"", "\\\"");
    return cadena;
}

void graficador:: generarImagen()
{
    QFileInfo fi("temp");

    graficar();
    QString grafoDOT = this->grafo;
    QString path = fi.absolutePath() +"/";
    QFile qFile(path+"grafo.txt");
    if(qFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&qFile); out << grafoDOT;
        qFile.close();
    }
    QString cadenaComando = "dot -Tjpg " + path + "grafo.txt -o " + path+"grafo.jpg ";
    system(cadenaComando.toUtf8().constData());

}
