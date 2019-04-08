#include "error.h"

error::error()
{

}

error::error(QString value,QString type, int row,int col)
{
    qDebug() << "nuevo error " << value << " tipo " << type;
    this->value = value;
    this->type = type;
    this->row = row;
    this->col = col;
}

error::error(QString value,QString type, int row,int col, QString description)
{
    qDebug() << "nuevo error " << value << " tipo " << type << " description " << description;
    this->value = value;
    this->type = type;
    this->row = row;
    this->col = col;
    this->desc = description;
}
