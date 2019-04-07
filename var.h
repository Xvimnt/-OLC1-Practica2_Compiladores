#ifndef VAR_H
#define VAR_H
#include <QString>

class var
{
private:
       QString value, type;
public:
    var();
    var(QString valor,QString type);
    QString getValue();
};

#endif // VAR_H
