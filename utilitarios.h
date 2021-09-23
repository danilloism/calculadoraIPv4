#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include "QString"

namespace dnn {

    class Utilitarios
    {
    public:
        static QString toBinary(int inteiro);
        static QString binAND(QString binario1, QString binario2);
        static QString binOR(QString binario1, QString binario2);
        static QString binOneComplement(QString binario);
    };

}

#endif // UTILITARIOS_H
