#ifndef ERROR_H
#define ERROR_H
#include <QString>

class error
{
private:
       QString value, type;
       int row, col;

public:
    error();
    error(QString value,QString type, int row,int col);
};

#endif // ERROR_H
