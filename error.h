#ifndef ERROR_H
#define ERROR_H
#include <QString>

class error
{
private:
       QString value, type, desc;
       int row, col;

public:
    error();
    error(QString value,QString type, int row,int col);
    error(QString value,QString type, int row,int col, QString description);
};

#endif // ERROR_H
