#include "var.h"

var::var()
{
    value = "";
}

var::var(QString valor){
    value = valor;
}

QString var::getValue(){
    return value;
}
