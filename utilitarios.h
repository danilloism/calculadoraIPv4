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
        static QString bin1Complement(QString binario);
        static QString bin2Complement(QString binario);
        static QString binSum(QString binario1, QString binario2);
        static QString binSubtraction(QString minuendo, QString subtraendo);
    };

}

#endif // UTILITARIOS_H
