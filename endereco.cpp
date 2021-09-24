#include "endereco.h"

namespace dnn {

    Endereco::Endereco(QString endereco, QString mascara):
            mascara(""),
            qtdSubRedes(0),
            qtdHosts(0),
            primeiroHost(nullptr),
            ultimoHost(nullptr)
        {
            try {
                if(!this->validaEndereco(endereco, octetosEndereco)) throw QString("Erro construtor");
                this->validaMascara(mascara);
                this->validaClasse();
                classe == 'D' || classe == 'E' ? throw QString("Endereços de classe D e E não são válidos para essas operações.") : 0;
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
        for(int i=0; i<4; i++) bin.append(Utilitarios::toBinary(octetosEndereco.at(i)));
        return bin;
    }

    QString Endereco::getMascaraBin()
    {
        QString bin;
        QString mask;
        QList<int> octetos;

        if(ehCIDR(this->mascara)){
            mask = this->maskConvertCIDRToDottedDecimal();
            if(!validaEndereco(mask, octetos)) throw QString("erro getMaskBin");
            for(int i=0; i<4; i++) bin.append(Utilitarios::toBinary(octetos.at(i)));
            return bin;
        }

        if(!validaEndereco(this->mascara, octetos)) throw QString("erro getMaskBin");
        for(int i=0; i<4; i++) bin.append(Utilitarios::toBinary(octetos.at(i)));
        return bin;
    }

    Endereco* Endereco::getSubRedeAtual()
    {
        try {
            if(octetosEndereco.isEmpty()) throw QString("erro subRedeAtual");
            QString resultadoOperacaoAND = Utilitarios::binAND(getEnderecoBin(),getMascaraBin());
            QString enderecoSubRede = "";
            for(int i=0; i<32;i+=8) enderecoSubRede += QString::number(stoi(resultadoOperacaoAND.mid(i,8).toStdString(),nullptr,2)) + ".";
            enderecoSubRede.chop(1);
            Endereco* subRede = new Endereco(enderecoSubRede,getMascara());
            return subRede;
        }  catch (QString &erro) {
            throw erro;
        }
    }

    Endereco *Endereco::getSubRedePrimeiroHost() const
    {

        if(this->getClasse() == "A"){

        } else if(this->getClasse() == "B"){

        } else if(this->getClasse() == "C"){

        } else{

        }
    }

    bool Endereco::ehCIDR(QString &mascara)const
    {
        if(mascara.size() == 2 && mascara.toInt() > 0 && mascara.toInt() < 31) return true;
        return false;

    }

    bool Endereco::validaEndereco(QString endereco, QList<int> &listaOctetos)const
    {
        QStringList parseEndereco = endereco.split(QLatin1Char('.'));

        if(parseEndereco.count() == 4){
            for(int i=0; i<4; i++){
                if(parseEndereco.at(i) == "") parseEndereco.replace(i, "0");
                if(parseEndereco.at(i).size() > 0 && parseEndereco.at(i).at(0).digitValue() == 0) return false;
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
        try {
            QList<int> lista;
            if(ehCIDR(mascara)){
                this->mascara = mascara;
            } else if(validaEndereco(mascara, lista)){
                if(lista.at(3) > 252) throw QString("erro valida mascara");
                this->mascara = mascara;
            } else {
                throw QString("erro else");
            }
        }  catch (QString &erro) {
            throw erro;
        }


    }

    void Endereco::validaClasse()
    {
        if(octetosEndereco.isEmpty()) throw QString("erro valida classe");
        else if(octetosEndereco.at(0) >= 0 && octetosEndereco.at(0) <=127) classe = 'A';
        else if(octetosEndereco.at(0) >= 128 && octetosEndereco.at(0) <=191) classe = 'B';
        else if(octetosEndereco.at(0) >= 192 && octetosEndereco.at(0) <=223) classe = 'C';
        else if(octetosEndereco.at(0) >= 224 && octetosEndereco.at(0) <=239) classe = 'D';
        else if(octetosEndereco.at(0) >= 240 && octetosEndereco.at(0) <=255) classe = 'E';
        else throw QString("erro valida classe");

    }

    QString Endereco::maskConvertCIDRToDottedDecimal()
    {
        if(!ehCIDR(this->mascara)) throw QString("erro mask convert");

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
        if(ehCIDR(this->mascara)) throw QString("erro mask convert");

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
            throw QString("erro mask convert");
        }

        return mask;
    }
}

