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
        QList<int> octetos;
        bool ehCIDR(QString &mascara)const;
        bool validaEndereco(QString &endereco, QList<int> &listaOctetos);
        void validaMascara(QString &mascara);
        void validaClasse();

    public:
        Endereco(QString &endereco, QString &mascara);
        QString getEndereco() const;
        QString getEnderecoBin(QList<int> &listaOctetos) const;
        QString getMascara() const{return mascara;}
        QString getMascaraBin()const;
        QChar getClasse() const{return classe;}
    };

}

#endif // ENDERECO_H
