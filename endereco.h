#ifndef ENDERECO_H
#define ENDERECO_H
#include "QList"
#include "utilitarios.h"
#include "math.h"
#include <QRegExpValidator>

namespace dnn {

    class Endereco
    {
    private:
        QString mascara;
        QChar classe;
        QList<int> octetosEndereco;
        QList<Endereco*> subRedes;
        int qtdSubRedes;
        int qtdHosts;
        Endereco* primeiroHost;
        Endereco* ultimoHost;
        Endereco* subRedeAtual;
        Endereco* subRedeBroadcast;
        bool validaEndereco(QString endereco, QList<int> &listaOctetos) const;
        void validaMascara(QString &mascara);
        void validaClasse();
        void setSubRedeAtual();
        void setSubRedePrimeiroHost();
        void setSubRedeUltimoHost();
        void setSubRedeBroadcast();
        void setQtdeHosts();
        void setqtdeSubRedes();
        void setSubRede(Endereco *subRede){subRedes.push_back(subRede);}


    public:
        Endereco(QString endereco, QString mascara);
        ~Endereco();
        QString getEndereco() const;
        QString getEnderecoBin() const;
        QString getMascara() const{return mascara;}
        QString getMascaraBin()const;
        QChar getClasse() const{return classe;}
        Endereco* getSubRedeAtual();
        Endereco* getSubRedePrimeiroHost();
        Endereco* getSubRedeUltimoHost();
        Endereco* getSubRedeBroadcast();
        int getQuantidadeHosts()const{return qtdHosts;}
        QList<Endereco*>* getSubredes()const;
        QString maskConvertCIDRToDottedDecimal() const;
        QString maskConvertDottedDecimalToCIDR() const;
        bool ehCIDR(QString mascara)const;
        int getQtdeSubRedes(){return qtdSubRedes;}
        void preencherSubRedes(int n);
        bool possuiSubRedes()const{return (qtdSubRedes == 1) ? false : true;}


    };

}

#endif // ENDERECO_H
