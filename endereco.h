#ifndef ENDERECO_H
#define ENDERECO_H

#include "QList"
#include "utilitarios.h"
#include "math.h"

namespace dnn {

    class Endereco
    {
    private:
        QString mascara;
        QChar classe;
        QList<int> octetosEndereco;
        QList<Endereco> subRedes;
        QList<Endereco> hosts;
        int qtdSubRedes;
        int qtdHosts;

        bool ehCIDR(QString &mascara)const;
        bool validaEndereco(QString &endereco, QList<int> &listaOctetos);
        void validaMascara(QString &mascara);
        void validaClasse();
        QString maskConvertCIDRToDottedDecimal();
        int maskConvertDottedDecimalToCIDR();

    public:
        Endereco(QString &endereco, QString &mascara);
        QString getEndereco() const;
        QString getEnderecoBin() const;
        QString getMascara() const{return mascara;}
        QString getMascaraBin();
        QChar getClasse() const{return classe;}
        Endereco getSubRedePrimeiroHost()const;
        Endereco getSubRedeUltimoHost()const;
        Endereco getSubRedeBroadcast()const;
        int getQuantidadeHosts()const;
        QList<Endereco> getSubredes()const{return subRedes;}
        QList<Endereco> getHosts()const{return hosts;}

    };

}

#endif // ENDERECO_H
