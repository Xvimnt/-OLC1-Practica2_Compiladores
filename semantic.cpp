#include "semantic.h"

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
    ASIGNACION = 22
};

semantic::semantic()
{
    resultado = "";
}

Resultado semantic::recorrer(node *raiz)
{
    Resultado r = Resultado();
    r.linea = raiz->linea; // Nos servirán para una posible reporte de error de tipos.
    r.columna = raiz->columna;
    switch (raiz->tipo_)
    {
    case INT:
    {
        r.tipo = INT;
        r.valor = raiz->valor;
    }
    break;
    case BOOL:
    {
        r.tipo = BOOL;
        r.valor = raiz->valor;
    }
    break;
    case DOUBLE:
    {
        r.tipo = DOUBLE;
        r.valor = raiz->valor;
    }
    break;
    case STRING:
    {
        r.tipo = STRING;
        r.valor = raiz->valor;
    }
    break;
    case CHAR:
    {
        r.tipo = CHAR;
        r.valor = raiz->valor;
    }
    break;
    case ASIGNACION:
    {
        //Este es un identificador
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        //Este es un signo igual
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
    }
    break;
    case IGUALACION:
    {
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() < op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
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
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() < op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            break;
            }
        }
        break;
        default:
        {
            /*Aqui debe ir el código para reportar el error de tipos*/
        }
        break;
        }
    }
    break;
    case AND:
    {
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            }
        }
        break;
        default:
        {
            /*Aqui debe ir el código para reportar el error de tipos*/
        }
        break;
        }
    }
    break;
    case OR:
    {
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            }
        }
        break;
        default:
        {
            /*Aqui debe ir el código para reportar el error de tipos*/
        }
        break;
        }
    }
    break;
    case MAYORQUE:
    {
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() > op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
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
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() > op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            break;
            }
        }
        break;
        default:
        {
            /*Aqui debe ir el código para reportar el error de tipos*/
        }
        break;
        }
    }
    break;
    case MENOROIGUAL:
    {
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() <= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
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
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() <= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            break;
            }
        }
        break;
        default:
        {
            /*Aqui debe ir el código para reportar el error de tipos*/
        }
        break;
        }
    }
    break;
    case MAYOROIGUAL:
    {
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() >= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
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
            case DOUBLE:
            {
                r.tipo = BOOL;
                bool result = (op1.valor.toDouble() >= op2.valor.toDouble());
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            break;
            }
        }
        break;
        default:
        {
            /*Aqui debe ir el código para reportar el error de tipos*/
        }
        break;
        }
    }
    break;
    case SUMA:
    {
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            break;
            }
        }
        break;
        case STRING:
        {

            /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            break;
            }
        }
        break;
        case STRING:
        {

            /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
            default:
            {
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            break;
            }
        }
        break;
        case STRING:
        {

            /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
        node der = raiz->hijos.at(1);
        Resultado op2 = recorrer(&der);
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
            }
            break;
            }
        }
        break;
        case STRING:
        {
            /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
                /*Aqui debe ir el código para reportar el error de tipos*/
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
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
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
            /*Aqui debe ir el código para reportar el error de tipos*/
        }
        break;
        }
    }
    break;
    case DECREASE:
    {
        node iz = raiz->hijos.at(0);
        Resultado op1 = recorrer(&iz);
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
            /*Aqui debe ir el código para reportar el error de tipos*/
        }
        break;
        }
    }
    break;
    }
    return r;
}
