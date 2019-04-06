#ifndef VAR_H
#define VAR_H
#include <QString>

class var
{
private:
       QString value;
public:
    var();
    var(QString valor);
    QString getValue();
};

#endif // VAR_H
