#include "node.h"
#include <qdebug.h> // Para imprimir en consola.

node::node()
{
    tipo ="";
    valor = "";
    linea = 0;
    columna = 0;
    hijos =  QList<node*>();
}

node::node(int l, int c, QString t, QString v)
{
    linea = l;
    columna = c;
    tipo = t;
    valor = v;
    tipo_ = getTipo();
    hijos = QList<node*>();
}

void node::add(node *n)
{
    this->hijos.append(n);
}

int node::getTipo()
{
    if(this->tipo=="int"){return 1;}
    if(this->tipo=="string"){return 2;}
    if(this->tipo=="bool"){return 3;}
    if(this->tipo=="char"){return 4;}
    if(this->tipo=="double"){return 5;}
    if(this->tipo=="suma"){return 6;}
    if(this->tipo=="resta"){return 7;}
    if(this->tipo=="multi"){return 8;}
    if(this->tipo=="div"){return 9;}
    if(this->tipo=="potencia"){return 10;}
    if(this->tipo=="igualacion"){return 11;}
    if(this->tipo=="dif"){return 12;}
    if(this->tipo=="menque"){return 13;}
    if(this->tipo=="mayque"){return 14;}
    if(this->tipo=="menoig"){return 15;}
    if(this->tipo=="mayoig"){return 16;}
    if(this->tipo=="tor"){return 17;}
    if(this->tipo=="tand"){return 18;}
    if(this->tipo=="increase"){return 19;}
    if(this->tipo=="decrease"){return 20;}
    if(this->tipo=="print"){return 21;}
    if(this->tipo=="asignacion"){return 22;}
    if(this->tipo=="show"){return 23;}
    if(this->tipo=="if"){return 24;}
    if(this->tipo=="identificador"){return 25;}
    if(this->tipo=="minus"){return 26;}
    if(this->tipo=="for"){return 27;}
    if(this->tipo=="arreglo"){return 28;}
    if(this->tipo=="newDimension"){return 29;}
    if(this->tipo=="lista"){return 30;}
    if(this->tipo=="mList"){return 31;}
    if(this->tipo=="arregloIndex"){return 32;}
    if(this->tipo=="dimensions"){return 33;}
    if(this->tipo=="declaracion"){return 34;}
    if(this->tipo=="repeat"){return 35;}
    if(this->tipo=="indice"){return 36;}
    return 0;
}
