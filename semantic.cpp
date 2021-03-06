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
    SHOW = 23,
    IF = 24,
    IDEN = 25,
    MINUS = 26,
    FOR = 27,
    ARRAY = 28,
    DIMENSION = 29,
    LIST = 30,
    MLIST = 31,
    IDINDEX = 32,
    DIMS = 33,
    DECLARATION = 34,
    REPEAT = 35,
    ARRAS //Asignacion a array[]
};

semantic::semantic()
{
    resultado = "";
    console = "";
}

Resultado semantic::recorrer(node *node_)
{
    Resultado r = Resultado();
    if (node_ == nullptr)
        return r;

    r.linea = node_->linea; // Nos servirán para una posible reporte de error de tipos.
    r.columna = node_->columna;
    switch (node_->tipo_)
    {
    case ARRAS:
    {
        Resultado index = recorrer(node_->hijos.at(0));
        r.tipo = ARRAS;
        r.valor = "[" + index.valor + "]";
        Resultado op2 = recorrer(node_->hijos.at(1));
        if (op2.tipo != ARRAS)
        {
            currentArrayNewValue = new var(op2.valor, op2.tipo);
        }
        else
        {
            r.valor = r.valor + op2.valor;
        }
    }
    break;
    case SHOW:
    {
        Resultado title = recorrer(node_->hijos.at(0));
        Resultado msg = recorrer(node_->hijos.at(1));
        msgs.append(title.valor.replace("\"","") + "@@" + msg.valor.replace("\"",""));
    }
    break;
    case DECLARATION:
    {
        variables[node_->hijos.at(0)->valor] = new var("null", 0);
    }
    break;
    case ARRAY:
    {
        currentArrayId = node_->hijos.at(0)->valor;
        Resultado op1 = recorrer(node_->hijos.at(1));
        variables[currentArrayId] = new var(op1.valor, ARRAY);
    }
    break;
    case DIMENSION:
    {
        Resultado length = recorrer(node_->hijos.at(0));
        r.tipo = node_->tipo_;
        r.valor = "<" + length.valor + ">";

        if (node_->hijos.count() > 1)
        {
            //Quiere decir que hay mas dimensiones o esta decarada con una lista
            if (length.valor.toInt() < node_->hijos.at(1)->hijos.count())
            {
                //Si el numero de elementos del array sobrepasa el tamaño entonces es error semantico
                QString val = length.valor + " inferior a " + node_->hijos.at(1)->hijos.count();
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "Sobrepasada la cantidad de elementos"));
            }
            else
            {
                //hay mas dimensiones o esta recorriendo una lista
                Resultado plus = recorrer(node_->hijos.at(1));
                r.valor = r.valor + plus.valor;
            }
        }
    }
    break;
    case LIST:
    {
        //Como aquí hay una lista de operaciones, hacemos un for
        r.tipo = node_->tipo_;
        r.valor = "";
        for (int x = 0; x < node_->hijos.size(); x++)
        {
            node *element = node_->hijos.at(x);
            //id + [x] ASIGNAR AL DICCIONARIO index.valor
            Resultado index = recorrer(element);
            QString varName = currentArrayId + "[" + QString::number(x) + "]";
            variables[varName] = new var(index.valor, index.tipo);
        }
    }
    break;
    case MLIST:
    {
        //Como aquí hay una lista de operaciones, hacemos un for
        r.tipo = node_->tipo_;
        r.valor = "";

        for (int x = 0; x < node_->hijos.size(); x++)
        {
            node *lista = node_->hijos.at(x);
            if (lista->tipo_ == MLIST)
            {
                //es de 3 dimensiones
                for (int y = 0; y < lista->hijos.size(); y++)
                {
                    node *list = lista->hijos.at(y);
                    for (int z = 0; z < list->hijos.size(); z++)
                    {
                        node *element2 = list->hijos.at(z);
                        //id + [x][y][z] ASIGNAR AL DICCIONARIO index.valor
                        Resultado index2 = recorrer(element2);
                        QString name2 = currentArrayId + "[" + QString::number(x) + "]" + "[" + QString::number(y) + "]" + "[" + QString::number(z) + "]";
                        variables[name2] = new var(index2.valor, index2.tipo);
                    }
                }
            }
            else
            {
                //es de 2 dimensiones
                for (int y = 0; y < lista->hijos.size(); y++)
                {
                    node *element = lista->hijos.at(y);
                    //id + [x][y] ASIGNAR AL DICCIONARIO index.valor
                    Resultado index = recorrer(element);
                    QString name = currentArrayId + "[" + QString::number(x) + "]" + "[" + QString::number(y) + "]";
                    variables[name] = new var(index.valor, index.tipo);
                }
            }
        }
    }
    break;
    case REPEAT:
    {
        Resultado times = recorrer(node_->hijos.at(0));
        if (times.tipo != INT)
        {
            //Si el numero de veces no es entero entonces es error semantico
            QString val = times.valor + " no es un entero";
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
        }
        else
        {
            int end = times.valor.toInt();
            for (int i = 0; i < end; i++)
            {
                //Recorriendo el ciclo
                recorrer(node_->hijos.at(1));
            }
        }
    }
    break;
    case FOR:
    {
        Resultado assign = recorrer(node_->hijos.at(0));
        Resultado boolean = recorrer(node_->hijos.at(1));

        while (boolean.valor == "1")
        {
            //Recorriendo el ciclo
            recorrer(node_->hijos.at(3));
            //Actualizando el valor del iterador
            recorrer(node_->hijos.at(2));
            //verificando la condicion
            correciones = false;
            boolean = recorrer(node_->hijos.at(1));
            correciones = true;
        }
    }
    break;
    case IF:
    {
        node *temp = node_->hijos.at(0);
        Resultado op1 = recorrer(temp->hijos.at(0));
        Resultado op2;
        if (op1.valor == "1")
        {
            op2 = recorrer(temp->hijos.at(1));
        }
        else if (op1.valor == "0")
        {
            if ((node_->hijos.count() > 1) && (node_->hijos.at(1) != nullptr))
            {
                op2 = recorrer(node_->hijos.at(1));
            }
        }
        else
        {
            QString val = op1.valor + " no es un booleano";
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
        }
    }
    break;
    case IDEN:
    {
        if (variables.find(node_->valor) == variables.end())
        {
            if(correciones) errores.append(new error(node_->valor, "Error Semantico", r.linea, r.columna, "Variable no inicializada"));
        }
        else
        {
            var *temp = variables[node_->valor];
            r.tipo = temp->getType();
            r.valor = temp->getValue();
        }
    }
    break;
    case IDINDEX:
    {
        if (variables.find(node_->hijos.at(0)->valor) == variables.end())
        {
            if(correciones) errores.append(new error(node_->hijos.at(0)->valor, "Error Semantico", r.linea, r.columna, "Array no inicializado"));
        }
        else
        {
            //dimensions me devuelve un string de esta forma [x][y][z]
            Resultado dimensions = recorrer(node_->hijos.at(1));
            QString variableName = node_->hijos.at(0)->valor + "[" + dimensions.valor + "]";

            if (variables.find(variableName) == variables.end())
            {
                if(correciones) if(correciones) errores.append(new error(variableName, "Error Semantico", r.linea, r.columna, "index nulo"));
            }
            else
            {
                var *temp = variables[variableName];
                r.tipo = temp->getType();
                r.valor = temp->getValue();
            }
        }
    }
    break;
    case DIMS:
    {
        //Como aquí hay una lista de operaciones, hacemos un for
        r.tipo = node_->tipo_;
        Resultado index, index2, index3;
        //si nos piden array de mas dimensiones en vez de un switch hacemos un for
        switch (node_->hijos.size())
        {
        case 1:
            index = recorrer(node_->hijos.at(0));
            r.valor = index.valor ;
            break;
        case 2:
            index = recorrer(node_->hijos.at(0));
            index2 = recorrer(node_->hijos.at(1));
            r.valor = index.valor  + "]" + "[" + index2.valor ;
            break;
        case 3:
            index = recorrer(node_->hijos.at(0));
            index2 = recorrer(node_->hijos.at(1));
            index3 = recorrer(node_->hijos.at(2));
            r.valor =  index.valor + index2.valor + index3.valor;
            break;
        }
    }
    break;
    case PRINT:
    {
        node *son = node_->hijos.at(0);
        Resultado op1 = recorrer(son);

        console += op1.valor.replace("\""," ") + "\n";
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
        currentArrayId = iz->valor;
        //Este es un E u otro id
        node *der = node_->hijos.at(1);
        Resultado op2 = recorrer(der);
        //asignando variables

        if (op2.tipo != ARRAS)
        {
            variables[iz->valor] = new var(op2.valor, op2.tipo);
        }else
        {
            QString varName = iz->valor + op2.valor;
            variables[varName] = currentArrayNewValue;
        }
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
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                QByteArray ba2 = op1.valor.toLocal8Bit();
                int a = (int)ba2[1];
                bool result = (a == c);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                QByteArray ba2 = op1.valor.toLocal8Bit();
                int a = (int)ba2[1];
                bool result = (a != c);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                int result = op1.valor.toInt() * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                int result = op1.valor.toInt() + op2.valor.toInt();
                if (result > 0)
                {
                    r.valor = "1";
                }
                else
                    r.valor = "0";
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        default:
        {
            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toInt() + c;
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toDouble() + c;
                r.valor = QString::number(result);
            }
            break;

            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                r.valor = op1.valor + ba[1];
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                QByteArray ba2 = op1.valor.toLocal8Bit();
                int a = (int)ba2[1];
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = a + c;
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c + op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c + op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case STRING:
            {
                r.tipo = STRING;
                QByteArray ba = op1.valor.toLocal8Bit();
                r.valor = ba[1] + op2.valor;
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toInt() + c;
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = BOOL;
                int result = op1.valor.toInt() + op2.valor.toInt();
                if (result > 0)
                {
                    r.valor = "1";
                }
                else
                    r.valor = "0";
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toInt() - c;
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toDouble() - c;
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c - op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                QByteArray ba2 = op1.valor.toLocal8Bit();
                int a = (int)ba2[1];
                double result = a - c;
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c - op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toInt() * c;
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toDouble() * c;
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = INT;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = INT;
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                QByteArray ba2 = op1.valor.toLocal8Bit();
                int a = (int)ba2[1];
                double result = a * c;
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c * op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c * op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                int result = op1.valor.toInt() * c;
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                r.tipo = DOUBLE;
                QByteArray ba = op2.valor.toLocal8Bit();
                double result = op1.valor.toDouble() / (int)ba[1];
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                int result = op1.valor.toInt() / op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toDouble() / c;
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {

            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case INT:
            {
                r.tipo = DOUBLE;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            case CHAR:
            {
                r.tipo = DOUBLE;
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                QByteArray ba2 = op1.valor.toLocal8Bit();
                int a = (int)ba2[1];
                double result = a / c;
                r.valor = QString::number(result);
            }
            break;
            case BOOL:
            {
                r.tipo = INT;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c / op2.valor.toInt();
                r.valor = QString::number(result);
            }
            break;
            case DOUBLE:
            {
                r.tipo = DOUBLE;
                QByteArray ba = op1.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = c / op2.valor.toDouble();
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = op1.valor.toDouble() / c;
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                int result = pow(op1.valor.toInt(), c);
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                double result = pow(op1.valor.toDouble(), c);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
            }
            break;
            }
        }
        break;
        case STRING:
        {
            QString val = op1.valor + " " + op2.valor;
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
        }
        break;
        case CHAR:
        {
            switch (op2.tipo)
            {
            case CHAR:
            {
                r.tipo = INT;
                QByteArray ba = op2.valor.toLocal8Bit();
                int c = (int)ba[1];
                QByteArray ba2 = op1.valor.toLocal8Bit();
                int a = (int)ba2[1];
                int result = pow(a, c);
                r.valor = QString::number(result);
            }
            break;
            default:
            {
                QString val = op1.valor + " " + op2.valor;
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
                if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
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
            QByteArray ba = op1.valor.toLocal8Bit();
            int result = (int)ba[1];
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
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
        }
        break;
        }
        if (iz->getTipo() == IDEN)
        {
            variables[iz->valor] = new var(r.valor, r.tipo);
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
            QByteArray ba = op1.valor.toLocal8Bit();
            int result = (int)ba[1];
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
            if(correciones) errores.append(new error(val, "Error Semantico", r.linea, r.columna, "operacion invalida"));
        }
        break;
        }
        if (iz->getTipo() == IDEN)
        {
            variables[iz->valor] = new var(r.valor, r.tipo);
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
