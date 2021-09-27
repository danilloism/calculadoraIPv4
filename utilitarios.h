#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include "QString"
#include <QStringList>

namespace dnn {

    class Utilitarios
    {
    public:
        static QString toBinary(int inteiro);
        static QString binAND(QString binario1, QString binario2);
        static QString binOR(QString binario1, QString binario2);
        static QString bin1Complement(QString binario);
        static QString bin2Complement(QString binario);
        static QStringList binCombinations(int n);
    };

}

#endif // UTILITARIOS_H
