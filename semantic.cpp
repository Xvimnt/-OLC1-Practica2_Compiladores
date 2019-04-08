#include "semantic.h"
#include <iostream>
#include <QDebug>

enum Choice
{
    INT = 1,
    STRING = 2,
    BOOL = 3,
    CHAR = 4,
    DOUBLE = 5,
    SUMA = 6,
    RESTA = 7,
    MULTI = 8,
    DIV = 9,
    POTENCIA = 10,
    IGUALACION = 11,
    DIFERENCIACION = 12,
    MENORQUE = 13,
    MAYORQUE = 14,
    MAYOROIGUAL = 15,
    MENOROIGUAL = 16,
    OR = 17,
    AND = 18,
    INCREASE = 19,
    DECREASE = 20,
    RESERVED = 21,
    ASIGNACION = 22,
    IDEN = 25,
    MINUS = 26
};

semantic::semantic()
{
    resultado = "";
}

Resultado semantic::recorrer(node *node_)
{
    Resultado r = Resultado();
    r.linea = node_->linea; // Nos servirán para una posible reporte de error de tipos.
    r.columna = node_->columna;
    switch (node_->tipo_)
    {
    case IDEN:
    {
        var *temp = variables[node_->valor];
        r.tipo = temp->getType();
        r.valor = temp->getValue();
    }
    break;
    case INT:
    {
        r.tipo = INT;
        r.valor = node_->valor;
    }
    break;
    case BOOL:
    {
        r.tipo = BOOL;
        if (node_->valor == "true")
        {
            r.valor = "1";
        }
        else
        {
            r.valor = "0";
        }
    }
    break;
    case DOUBLE:
    {
        r.tipo = DOUBLE;
        r.valor = node_->valor;
    }
    break;
    case STRING:
    {
        r.tipo = STRING;
        r.valor = node_->valor;
    }
    break;
    case CHAR:
    {
        r.tipo = CHAR;
        r.valor = node_->valor;
    }
    break;
    case ASIGNACION:
    {
        //Este es un identificador
        node *iz = node_->hijos.at(0);
        //Este es un E u otro id
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        //asignando variables
        variables[iz->valor] = new var(op2.valor, op2.tipo);
    }
    break;
    case IGUALACION:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toInt() == op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() == op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {
            switch (op2.tipo)
            {
            case STRING:
            {
                r.tipo = BOOL;
                bool result = (op1.valor == op2.valor);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case CHAR:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toInt() == op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case BOOL:
        {
            switch (op2.tipo)
            {
            case BOOL:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.compare("true", Qt::CaseInsensitive) == op2.valor.compare("true", Qt::CaseInsensitive));
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        }
    }
    break;
    case DIFERENCIACION:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toInt() != op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() != op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {
            switch (op2.tipo)
            {
            case STRING:
            {
                r.tipo = BOOL;
                bool result = (op1.valor != op2.valor);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case CHAR:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toInt() != op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case BOOL:
        {
            switch (op2.tipo)
            {
            case BOOL:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.compare("true", Qt::CaseInsensitive) != op2.valor.compare("true", Qt::CaseInsensitive));
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        }
    }
    break;
    case MENORQUE:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toInt() < op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() < op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() < op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() < op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        }
    }
    break;
    case AND:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case BOOL:
        {
            switch (op2.tipo)
            {
            case BOOL:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.compare("true", Qt::CaseInsensitive) == 0 && op2.valor.compare("true", Qt::CaseInsensitive) == 0);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        }
    }
    break;
    case OR:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case BOOL:
        {
            switch (op2.tipo)
            {
            case BOOL:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.compare("true", Qt::CaseInsensitive) == 0 || op2.valor.compare("true", Qt::CaseInsensitive) == 0);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        }
    }
    break;
    case MAYORQUE:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toInt() > op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() > op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() > op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() > op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        }
    }
    break;
    case MENOROIGUAL:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toInt() <= op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() <= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() <= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() <= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        }
    }
    break;
    case MAYOROIGUAL:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toInt() >= op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() >= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() >= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() >= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        }
    }
    break;
    case MINUS:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        switch (op1.tipo)
        {
        case INT:
        {
            r.tipo = INT;
            int result = op1.valor.toInt() * -1;
            r.valor = QString::number(result);
        }
        break;
        case DOUBLE:
        {
            r.tipo = DOUBLE;
            double result = op1.valor.toDouble() * -1;
            r.valor = QString::number(result);
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        }
    }
    break;
    case SUMA:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                int result = op1.valor.toInt() + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case STRING:
            {
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case STRING:
            {
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
            }
            break;

            case CHAR:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;

            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
            }
            break;
            case DOUBLE:
            {
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
            }
            break;
            case STRING:
            {
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
            }
            break;
            case CHAR:
            {
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case STRING:
            {
                r.tipo = STRING;
                r.valor = op1.valor + op2.valor;
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case BOOL:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.compare("true", Qt::CaseInsensitive) == 0 || op2.valor.compare("true", Qt::CaseInsensitive) == 0);
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() + op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        }
    }
    break;
    case RESTA:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                int result = op1.valor.toInt() - op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() - op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() - op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() - op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() - op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() - op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() - op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() - op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() - op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() - op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() - op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case BOOL:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() - op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() - op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        }
    }
    break;
    case MULTI:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                int result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() * op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() * op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() * op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() * op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() * op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() * op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case BOOL:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() * op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.compare("true", Qt::CaseInsensitive) == 0 && op2.valor.compare("true", Qt::CaseInsensitive) == 0);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        }
    }
    break;
    case DIV:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                qDebug() << "convirtiendo " << op1.valor << " con " << op2.valor << "\n";
                QByteArray ba = op2.valor.toLocal8Bit();
                r.tipo = DOUBLE;
                int result = op1.valor.toInt() / ba[1];
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                qDebug() << "dividiendo " << op1.valor << " con " << op2.valor << "\n";
                int result = op1.valor.toInt() / op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                double result = op1.valor.toInt() / op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case BOOL:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = op1.valor.toDouble() / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        }
    }
    break;
    case POTENCIA:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        switch (op1.tipo)
        {
        case INT:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                int result = pow(op1.valor.toInt(), op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = pow(op1.valor.toDouble(), op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                int result = pow(op1.valor.toInt(), op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                int result = pow(op1.valor.toInt(), op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            }
        }
        break;
        case DOUBLE:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                double result = pow(op1.valor.toDouble(), op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                double result = pow(op1.valor.toDouble(), op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = DOUBLE;
                double result = pow(op1.valor.toDouble(), op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = DOUBLE;
                double result = pow(op1.valor.toDouble(), op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case CHAR:
            {
                r.tipo = INT;
                int result = pow(op1.valor.toInt(), op2.valor.toInt());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        case BOOL:
        {
            switch (op2.tipo)
            {
            case BOOL:
            {
                r.tipo = BOOL;
                int result = (op1.valor == op2.valor);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
            }
            break;
            }
        }
        break;
        }
    }
    break;
    case INCREASE:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        switch (op1.tipo)
        {
        case INT:
        {
            r.tipo = INT;
            int result = op1.valor.toInt();
            result++;
            r.valor = QString::number(result);
        }
        break;
        case CHAR:
        {
            r.tipo = INT;
            int result = op1.valor.toInt();
            result++;
            r.valor = QString::number(result);
        }
        break;
        case DOUBLE:
        {
            r.tipo = DOUBLE;
            double result = op1.valor.toDouble();
            result++;
            r.valor = QString::number(result);
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        }
    }
    break;
    case DECREASE:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        switch (op1.tipo)
        {
        case INT:
        {
            r.tipo = INT;
            int result = op1.valor.toInt();
            result--;
            r.valor = QString::number(result);
        }
        break;
        case CHAR:
        {
            r.tipo = INT;
            int result = op1.valor.toInt();
            result--;
            r.valor = QString::number(result);
        }
        break;
        case DOUBLE:
        {
            r.tipo = DOUBLE;
            double result = op1.valor.toDouble();
            result--;
            r.valor = QString::number(result);
        }
        break;
        default:
        {
            errores.append(new error(r.valor, "Error Semantico", r.linea, r.columna, "operacion invaida"));
        }
        break;
        }
    }
    break;
    default:
    {
        //Como aquí hay una lista de operaciones, hacemos un for
        r.tipo = node_->tipo_;
        for (int x = 0; x < node_->hijos.size(); x++)
        {
            node *nodo = node_->hijos.at(x);
            recorrer(nodo);
        }
    }
    }
    return r;
}
