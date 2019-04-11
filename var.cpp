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

QString var::getTypeName(){
    switch(this->type){
        case 1:
        return "int";
        break;
        case 2:
        return "string";
        break;
        case 3:
        return "bool";
        break;
        case 4:
        return "char";
        break;
        case 5:
        return "double";
        break;
        case 28:
        return "array";
        break;
        default:
        return "undefined";
        break;
    }
}

int var::getType(){
    return type;
}
