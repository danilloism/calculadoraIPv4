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
        int qtdSubRedes;
        int qtdHosts;
        Endereco* primeiroHost;
        Endereco* ultimoHost;
        bool ehCIDR(QString &mascara)const;
        bool validaEndereco(QString endereco, QList<int> &listaOctetos) const;
        void validaMascara(QString &mascara);
        void validaClasse();
        QString maskConvertCIDRToDottedDecimal();
        int maskConvertDottedDecimalToCIDR();

    public:
        Endereco(QString endereco, QString mascara);
        QString getEndereco() const;
        QString getEnderecoBin() const;
        QString getMascara() const{return mascara;}
        QString getMascaraBin();
        QChar getClasse() const{return classe;}
        Endereco* getSubRedeAtual();
        Endereco* getSubRedePrimeiroHost()const;
        Endereco* getSubRedeUltimoHost()const;
        Endereco* getSubRedeBroadcast()const;
        int getQuantidadeHosts()const;
        QList<Endereco> getSubredes()const{return subRedes;}
        void setSubRede(Endereco subRede){subRedes.push_back(subRede);}

    };

}

#endif // ENDERECO_H
