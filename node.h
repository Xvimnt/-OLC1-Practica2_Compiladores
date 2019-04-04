#ifndef NODE_H
#define NODE_H
#include "QString"
#include "qlist.h"

class node
{
public:
    node(); // Constructor
    node(int l, int c, QString t, QString v);    
    void add(node n);
    QString tipo;
    QString valor;
    int linea;
    int columna;
    int tipo_; // Este nos servirá para la ejecución, ya que aquí no hay swicht(QString); vamos a hacer un Swicht(int);
    QList<node> hijos;
    int getTipo();
};

#endif // NODE_H