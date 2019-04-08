#ifndef ERROR_H
#define ERROR_H
#include <QString>

class error
{

public:
    error();
    error(QString value,QString type, int row,int col);
    error(QString value,QString type, int row,int col, QString description);
    QString value, type, desc;
    int row, col;
};

#endif // ERROR_H
