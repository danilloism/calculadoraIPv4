#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include "QString"

namespace dnn {

    class Utilitarios
    {
    public:
        static QString IntParaBin(int &inteiro);
        static int BinParaInt(QString &binario);
    };

}

#endif // UTILITARIOS_H
