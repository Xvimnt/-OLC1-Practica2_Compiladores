#include "error.h"

error::error()
{

}

error::error(QString valor,QString tipo, int fila,int columna)
{
    this->value = valor;
    this->type = tipo;
    this->row = fila;
    this->col = columna;
}

error::error(QString valor,QString tipo, int fila,int columna, QString description)
{
    this->value = valor;
    this->type = tipo;
    this->row = fila;
    this->col = columna;
    this->desc = description;
}
