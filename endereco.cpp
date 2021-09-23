#include "endereco.h"

namespace dnn {

    Endereco::Endereco(QString &endereco, QString &mascara):
            mascara(""),
            classe(),
            octetos()
        {
            try {
                if(!this->validaEndereco(endereco, octetos)) throw QString("Erro");
                this->validaMascara(mascara);
                this->validaClasse();
            }  catch (QString &erro) {
                throw QString(erro);
        }
    }

    QString Endereco::getEndereco() const
    {
        if(octetos.isEmpty()) return "Endereço não validado.";

        QString endereco;
        for(int i=0; i<4; i++){
            endereco.append(octetos.at(i));
            endereco.append(".");
        }
        endereco.chop(1);
        return endereco;
    }


    bool Endereco::ehCIDR(QString &mascara)const
    {
        if(mascara.size() == 2 && mascara.toInt() > 0 && mascara.toInt() < 31) return true;
        return false;

    }

    bool Endereco::validaEndereco(QString &endereco, QList<int> &listaOctetos)
    {
        QStringList parseEndereco = endereco.split(QLatin1Char('.'));

        if(parseEndereco.count() == 4){
            for(int i=0; i<4; i++){
                if(parseEndereco.at(i) == "") parseEndereco.replace(i, "0");
                if(parseEndereco.at(i).at(0) == "0") throw QString("erro");
                if(parseEndereco.at(i).toInt() < 0 && parseEndereco.at(i).toInt() > 255) return false;
                for(int j=0; j<parseEndereco.at(i).size(); j++)
                    if(!(parseEndereco.at(i).at(j) >= '0' && parseEndereco.at(i).at(j) <='9')) return false;
                listaOctetos.append(parseEndereco.at(i).toInt());
            }
            return true;
        }else{
            return false;
        }
    }

    void Endereco::validaMascara(QString &mascara)
    {

        QList<int> lista;
        if(ehCIDR(mascara)){
            this->mascara = mascara;
        } else if(validaEndereco(mascara, lista)){
            if(lista.at(4) > 252) throw QString("erro");
            this->mascara = mascara;
        } else {
            throw QString("erro");
        }
    }

    void Endereco::validaClasse()
    {
        if(octetos.isEmpty()) throw QString("erro");
        if(octetos.at(0) >= 0 && octetos.at(0) <=127) classe = 'A';
        if(octetos.at(0) >= 128 && octetos.at(0) <=191) classe = 'B';
        if(octetos.at(0) >= 192 && octetos.at(0) <=223) classe = 'C';
        if(octetos.at(0) >= 224 && octetos.at(0) <=239) classe = 'D';
        if(octetos.at(0) >= 240 && octetos.at(0) <=255) classe = 'E';
        else throw QString("erro");

    }
}

