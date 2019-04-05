#ifndef S  SEMANTIC_H
#define S  SEMANTIC_H
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

#endif // SSEMANTIC_H