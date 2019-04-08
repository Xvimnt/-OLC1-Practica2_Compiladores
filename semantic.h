#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <qstring.h>
#include <resultado.h>
#include "node.h"
#include "var.h"
#include "error.h"
#include <math.h>
#include <map>
#include "QList"

class semantic
{

public:
    QList<error*> errores;
    std::map<QString, var*> variables;
    semantic();
    Resultado recorrer( node *raiz);
    QString resultado;
    QString console;
};

#endif //SEMANTIC_H
