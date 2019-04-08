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
    MENOROIGUAL = 15,
    MAYOROIGUAL = 16,
    OR = 17,
    AND = 18,
    INCREASE = 19,
    DECREASE = 20,
    PRINT = 21,
    ASIGNACION = 22,
    IDEN = 25,
    MINUS = 26
};

semantic::semantic()
{
    resultado = "";
    console = "";
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
        if (variables.find(node_->valor) == variables.end())
        {
                errores.append(new error(node_->valor, "Error Semantico", r.linea, r.columna, "Variable no inicializada"));
        }
        else
        {
            var *temp = variables[node_->valor];
            qDebug() << "regresando e valor de " << node_->valor << " es " << temp->getValue(); 
            r.tipo = temp->getType();
            r.valor = temp->getValue();
        }
    }
    break;
    case PRINT:
    {
        node *son = node_->hijos.at(0);
        Resultado op1 = recorrer(son);

        console += op1.valor + "\n";
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
        qDebug() << "asignando e valor de " << iz->valor << " es " << op2.valor; 
        variables[iz->valor] = new var(op2.valor, op2.tipo);
    }
    break;
    case IGUALACION:
    {
        node *iz = node_->hijos.at(0);
        Resultado op1 = recorrer(iz);
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        qDebug() << "comparando igualacion que con: " << op1.valor << " y " << op2.valor;
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                int result = op1.valor == op2.valor;
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
        qDebug() << "comparando diferenciacion con: " << op1.valor << " y " << op2.valor;

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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                int result = op1.valor != op2.valor;
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
        qDebug() << "comparando menor que con: " << op1.valor << " y " << op2.valor;

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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
        qDebug() << "comparando and con: " << op1.valor << " y " << op2.valor;
        switch (op1.tipo)
        {
        case BOOL:
        {
            switch (op2.tipo)
            {
            case BOOL:
            {
                r.tipo = BOOL;
                int result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
        qDebug() << "comparando or con: " << op1.valor << " y " << op2.valor;

        switch (op1.tipo)
        {
        case BOOL:
        {
            switch (op2.tipo)
            {
            case BOOL:
            {
                r.tipo = BOOL;
                int result = op1.valor.toInt() + op2.valor.toInt();
                if(result > 0){
                 r.valor = "1";
                }else r.valor = "0";
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
        qDebug() << "comparando mayor que con: " << op1.valor << " y " << op2.valor;
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
        qDebug() << "comparando menor que igual con: " << op1.valor << " y " << op2.valor;

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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
        qDebug() << "comparando mayor que igual con: " << op1.valor << " y " << op2.valor;

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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
            errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
            QString val = "-" + op1.valor;
            errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                int result = op1.valor.toInt() + op2.valor.toInt();
                if(result > 0){
                 r.valor = "1";
                }else r.valor = "0";
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                int result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {
            QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
            QString val = op1.valor + "++";
            errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
            QString val = op1.valor + "--";
            errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
