#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <qstring.h>
#include <resultado.h>
#include "node.h"
#include "var.h"
#include <math.h>
#include <map>

class semantic
{

public:
    std::list<var> errores;
    std::map<std::string, var*> variables;
    semantic();
    Resultado recorrer( node *raiz);
    QString resultado;
};

#endif //SEMANTIC_H
