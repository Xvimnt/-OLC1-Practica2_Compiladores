#ifndef PLOTTER_H
#define PLOTTER_H
#include "node.h"
#include <fstream>
#include <iostream>

class graficador
{
public:
    graficador();
    graficador(node *raiz);
    node *raiz;
    int contador;
    QString grafo;
    QString graficar();
    void recorrerAST(QString padre, node *hijo);
    QString escapar(QString cadena);
    void generarImagen();

};

#endif // PLOTTER_H