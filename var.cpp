#include "var.h"

var::var()
{
    value = "";
}

var::var(QString valor,int type)
{
    value = valor;
    this->type = type;
}

QString var::getValue(){
    return value;
}

int var::getType(){
    return type;
}
