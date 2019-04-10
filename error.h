#ifndef ERROR_H
#define ERROR_H
#include <QString>
#include <QDebug>
class error
{

public:
    error();
    error(QString valor,QString tipo, int fila,int columna);
    error(QString valor,QString tipo, int fila,int columna, QString description);
    QString value, type, desc;
    int row, col;
};

#endif // ERROR_H
