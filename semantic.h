#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <qstring.h>
#include <resultado.h>
#include "node.h"
#include <math.h>

class semantic
{
public:
    semantic();
    Resultado recorrer( node *raiz);
    QString resultado;
};

#endif //SEMANTIC_H
