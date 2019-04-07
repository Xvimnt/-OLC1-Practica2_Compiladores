#include "error.h"

error::error()
{

}

error::error(QString value,QString type, int row,int col)
{
    this->value = value;
    this->type = type;
    this->row = row;
    this->col = col;
}

error::error(QString value,QString type, int row,int col, QString description)
{
    this->value = value;
    this->type = type;
    this->row = row;
    this->col = col;
    this->desc = description;
}
