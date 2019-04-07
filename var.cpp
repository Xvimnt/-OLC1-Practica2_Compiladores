#include "var.h"

var::var()
{
    value = "";
}

var::var(QString valor,QString type)
{
    value = valor;
    this->type = type;
}

QString var::getValue(){
    return value;
}
