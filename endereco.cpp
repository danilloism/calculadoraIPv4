#include "endereco.h"

namespace dnn {

    Endereco::Endereco(QString &endereco, QString &mascara):
            mascara("")
        {
            try {
                if(!this->validaEndereco(endereco, octetosEndereco)) throw QString("Erro");
                this->validaMascara(mascara);
                this->validaClasse();
            }  catch (QString &erro) {
                throw QString(erro);
        }
    }

    QString Endereco::getEndereco() const
    {
        if(octetosEndereco.isEmpty()) return "Endereço não validado.";

        QString endereco;
        for(int i=0; i<4; i++){
            endereco.append(QString::number(octetosEndereco.at(i)));
            endereco.append(".");
        }
        endereco.chop(1);
        return endereco;
    }

    QString Endereco::getEnderecoBin() const
    {
        if(octetosEndereco.isEmpty()) return "Endereço não validado.";
        QString bin;
        for(int i=0; i<4; i++){
            bin.append(Utilitarios::toBinary(octetosEndereco.at(i)));
            bin.append(".");
        }
        bin.chop(1);
        return bin;
    }

    QString Endereco::getMascaraBin()
    {
        QString bin;
        QString mask;
        QList<int> octetos;

        if(ehCIDR(this->mascara)){

            mask = this->maskConvertCIDRToDottedDecimal();
            if(!validaEndereco(mask, octetos)) throw QString("erro");
            for(int i=0; i<4; i++){
                bin.append(Utilitarios::toBinary(octetos.at(i)));
                bin.append(".");
            }
            bin.chop(1);
            return bin;

        }

        if(!validaEndereco(this->mascara, octetos)) throw QString("erro");
        for(int i=0; i<4; i++){
            bin.append(Utilitarios::toBinary(octetos.at(i)));
            bin.append(".");
        }
        bin.chop(1);
        return bin;
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
                if(parseEndereco.at(i).at(0).digitValue() == 0) throw QString("erro");
                if(parseEndereco.at(i).toInt() < 0 && parseEndereco.at(i).toInt() > 255) return false;
                for(int j=0; j<parseEndereco.at(i).size(); j++)
                    if(!(parseEndereco.at(i).at(j).digitValue() >= 0 && parseEndereco.at(i).at(j).digitValue() <= 9)) return false;
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
            if(lista.at(3) > 252) throw QString("erro");
            this->mascara = mascara;
        } else {
            throw QString("erro");
        }
    }

    void Endereco::validaClasse()
    {
        if(octetosEndereco.isEmpty()) throw QString("erro");
        if(octetosEndereco.at(0) >= 0 && octetosEndereco.at(0) <=127) classe = 'A';
        if(octetosEndereco.at(0) >= 128 && octetosEndereco.at(0) <=191) classe = 'B';
        if(octetosEndereco.at(0) >= 192 && octetosEndereco.at(0) <=223) classe = 'C';
        if(octetosEndereco.at(0) >= 224 && octetosEndereco.at(0) <=239) classe = 'D';
        if(octetosEndereco.at(0) >= 240 && octetosEndereco.at(0) <=255) classe = 'E';
        else throw QString("erro");

    }

    QString Endereco::maskConvertCIDRToDottedDecimal()
    {
        if(!ehCIDR(this->mascara)) throw QString("erro");

        QString mask;
        if(this->getClasse() == "A"){
            mask = "255.";

            QString bin = Utilitarios::toBinary(octetosEndereco.at(1));
            int quantidadeUmsNaMascara = 0, octetoDecimal = 0;
            while(bin.size()<8) bin.insert(0,"0");
            for(int i=0; bin.at(i).digitValue() == 1; i++) quantidadeUmsNaMascara += 1;
            for(int i=7;quantidadeUmsNaMascara!=0;i--, quantidadeUmsNaMascara--) octetoDecimal += pow(2,i);

            mask.append(QString::number(octetoDecimal));
            mask.append(".0.0");
        } else if(this->getClasse() == "B"){
            mask = "255.255.";

            QString bin = Utilitarios::toBinary(octetosEndereco.at(2));
            int quantidadeUmsNaMascara = 0, octetoDecimal = 0;
            while(bin.size()<8) bin.insert(0,"0");
            for(int i=0; bin.at(i).digitValue() == 1; i++) quantidadeUmsNaMascara += 1;
            for(int i=7;quantidadeUmsNaMascara!=0;i--, quantidadeUmsNaMascara--) octetoDecimal += pow(2,i);

            mask.append(QString::number(octetoDecimal));
            mask.append(".0");
        } else if(this->getClasse() == "C"){
            mask = "255.255.255.";

            QString bin = Utilitarios::toBinary(octetosEndereco.at(3));
            int quantidadeUmsNaMascara = 0, octetoDecimal = 0;
            while(bin.size()<8) bin.insert(0,"0");
            for(int i=0; bin.at(i).digitValue() == 1; i++) quantidadeUmsNaMascara += 1;
            for(int i=7;quantidadeUmsNaMascara!=0;i--, quantidadeUmsNaMascara--) octetoDecimal += pow(2,i);

            mask.append(QString::number(octetoDecimal));
        } else{
            return "Classe do endereço não esta validada.";
        }

        return mask;
    }

    int Endereco::maskConvertDottedDecimalToCIDR()
    {
        if(ehCIDR(this->mascara)) throw QString("erro");

        int mask;
        if(this->getClasse() == "A"){
            mask = 8;

            QString bin = Utilitarios::toBinary(octetosEndereco.at(1));
            while(bin.size()<8) bin.insert(0,"0");
            for(int i=0; bin.at(i).digitValue() == 1; i++) mask += 1;
        } else if(this->getClasse() == 'B'){
            mask = 16;

            QString bin = Utilitarios::toBinary(octetosEndereco.at(2));
            while(bin.size()<8) bin.insert(0,"0");
            for(int i=0; bin.at(i).digitValue() == 1; i++) mask += 1;
        } else if(this->getClasse() == 'C'){
            mask = 24;

            QString bin = Utilitarios::toBinary(octetosEndereco.at(3));
            while(bin.size()<8) bin.insert(0,"0");
            for(int i=0; bin.at(i).digitValue() == 1; i++) mask += 1;
        } else{
            throw QString("erro");
        }

        return mask;
    }
}

