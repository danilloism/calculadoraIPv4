#include "endereco.h"

namespace dnn {

    Endereco::Endereco(QString &endereco, QString &mascara):
            mascara(""),
            classe(),
            octectos()
        {
            this->validaEndereco(endereco);
        }


    bool Endereco::ehCIDR()
    {
        if(this->mascara.size()==2) return true;
        return false;

    }

    void Endereco::validaEndereco(QString &endereco)
    {
        QStringList parseEndereco = endereco.split(QLatin1Char('.'));

        if(parseEndereco.count() == 4){
            for(int i=0; i<4; i++){
                if(parseEndereco.at(i) == "") parseEndereco.replace(i, "0");
                if(parseEndereco.at(i).at(0) == "0") throw QString("erro");
                if(parseEndereco.at(i).toInt() < 0 && parseEndereco.at(i).toInt() > 255) throw QString("erro");
                for(int j=0; j<parseEndereco.at(i).size(); j++)
                    if(!(parseEndereco.at(i).at(j) >= '0' && parseEndereco.at(i).at(j) <='9')) throw QString("erro");
                octectos.append(parseEndereco.at(i).toInt());
            }

        }else{
            throw QString("erro");
        }
    }

    void Endereco::validaMascara(QString &mascara)
    {
        this->mascara = mascara;
        //if(this->mascara.size()==2 && ())
    }

    void Endereco::validaClasse()
    {
        if(ehCIDR()){

        }
    }
}

