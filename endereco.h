#ifndef ENDERECO_H
#define ENDERECO_H

#include "QList"
#include "utilitarios.h"

namespace dnn {

    class Endereco
    {
    private:
        QString mascara;
        QChar classe;
        QList<int> octectos;
        bool ehCIDR();
        void validaEndereco(QString &endereco);
        void validaMascara(QString &mascara);
        void validaClasse();

    public:
        Endereco(QString &endereco, QString &mascara);
        QString getEndereco() const;
        QString getMascara() const{return mascara;}
        QChar getClasse() const{return classe;}
    };

}

#endif // ENDERECO_H
