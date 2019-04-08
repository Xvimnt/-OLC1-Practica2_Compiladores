#ifndef VAR_H
#define VAR_H
#include <QString>

class var
{
private:
       QString value;
       int type;
public:
    var();
    var(QString valor,int type);
    QString getValue();
    QString getTypeName();
    int getType();
};

#endif // VAR_H
