#include "endereco.h"

namespace dnn {

    Endereco::Endereco(QString endereco, QString mascara):
            mascara(""),
            qtdSubRedes(0),
            qtdHosts(0),
            primeiroHost(nullptr),
            ultimoHost(nullptr),
            subRedeAtual(nullptr),
            subRedeBroadcast(nullptr)
        {
            try {
                if(!this->validaEndereco(endereco, octetosEndereco)) throw QString("Erro construtor");
                this->validaMascara(mascara);
                this->validaClasse();
                this->setQtdeHosts();
                classe == 'D' || classe == 'E' ? throw QString("Endereços de classe D e E não são válidos para essas operações.") : 0;
            }  catch (QString &erro) {
                throw QString(erro);
        }
    }

    Endereco::~Endereco()
    {
        if(primeiroHost) delete primeiroHost;
        if(ultimoHost) delete ultimoHost;
        if(subRedeAtual) delete subRedeAtual;
        if(subRedeBroadcast) delete subRedeBroadcast;
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
        QString bin = "";

        /*for(int i=0; i<4; i++){
            if(octetosEndereco.at(i) == 0) bin.append("00000000");
            else bin.append(Utilitarios::toBinary(octetosEndereco.at(i)));

        }*/

        for(int i=0; i<4; i++){
            int octetAtI = octetosEndereco.at(i);
            QString octetBin = Utilitarios::toBinary(octetAtI);
            while(octetAtI != 0 && octetBin.size() < 8) octetBin.prepend("0");
            octetAtI == 0 ? bin.append("00000000") : bin.append(octetBin);
        }
        return bin;
    }

    QString Endereco::getMascaraBin() const
    {
        QString bin;
        QString mask;
        QList<int> octetos;

        if(ehCIDR(this->mascara)) {
            mask = maskConvertCIDRToDottedDecimal();
        }else{
            mask = mascara;
        }

        if(!validaEndereco(mask, octetos)) throw QString("erro getMaskBin");

        for(int i=0; i<4; i++){
            int octetAtI = octetos.at(i);
            QString octetBin = Utilitarios::toBinary(octetAtI);
            while(octetAtI != 0 && octetBin.size() < 8) octetBin.prepend("0");
            octetAtI == 0 ? bin.append("00000000") : bin.append(octetBin);
        }

        return bin;
    }

    Endereco *Endereco::getSubRedeAtual()
    {
        setSubRedeAtual();
        return subRedeAtual;
    }

    Endereco *Endereco::getSubRedePrimeiroHost()
    {
        setSubRedePrimeiroHost();
        return primeiroHost;
    }

    Endereco *Endereco::getSubRedeUltimoHost()
    {
        setSubRedeUltimoHost();
        return ultimoHost;
    }

    Endereco *Endereco::getSubRedeBroadcast()
    {
        setSubRedeBroadcast();
        return subRedeBroadcast;
    }

    void Endereco::setSubRedeBroadcast()
    {
        try {
            QString resultadoOperacaoOR = Utilitarios::binOR(getEnderecoBin(),Utilitarios::bin1Complement(getMascaraBin()));
            QString enderecoSubRede = "";
            for(int i=0; i<32;i+=8) enderecoSubRede += QString::number(stoi(resultadoOperacaoOR.mid(i,8).toStdString(),nullptr,2)) + ".";
            enderecoSubRede.chop(1);
            subRedeBroadcast = new Endereco(enderecoSubRede,getMascara());
        }  catch (QString &erro) {
            throw erro;
        }
    }

    void Endereco::setQtdeHosts()
    {
        QString maskComplement = Utilitarios::bin1Complement(getMascaraBin());
        int qtd = 0;
        for(int i = 31; maskComplement.at(i).digitValue() != 0; i--){
            qtd += pow(2,31-i);
        }
        qtd -= 1;
        qtdHosts = qtd;
    }

    void Endereco::setSubRedeAtual()
    {
        try {
            if(octetosEndereco.isEmpty()) throw QString("erro subRedeAtual");
            QString resultadoOperacaoAND = Utilitarios::binAND(getEnderecoBin(),getMascaraBin());
            QString enderecoSubRede = "";
            for(int i=0; i<32;i+=8){
                enderecoSubRede += QString::number(stoi(resultadoOperacaoAND.mid(i,8).toStdString(),nullptr,2)) + ".";
            }
            enderecoSubRede.chop(1);
            subRedeAtual = new Endereco(enderecoSubRede,mascara);
        }  catch (QString &erro) {
            throw erro;
        }
    }

    void Endereco::setSubRedePrimeiroHost()
    {
        try {
            QString hostBin = getEnderecoBin();
            hostBin = hostBin.replace(31,1,"1");
            QString enderecoHost = "";
            for(int i=0; i<32;i+=8){
                enderecoHost += QString::number(stoi(hostBin.mid(i,8).toStdString(),nullptr,2)) + ".";
            }
            enderecoHost.chop(1);
            primeiroHost = new Endereco(enderecoHost,mascara);
        }  catch (QString &erro) {
            throw erro;
        }
    }

    void Endereco::setSubRedeUltimoHost()
    {
        try {
            QString maskBin = getMascaraBin();
            QString hostBin = getEnderecoBin();
            QString enderecoHost = "";

            hostBin.replace(31,1,"0");
            for(int i = 30; i>=0 && maskBin.at(i).digitValue() == 0; i--) hostBin.replace(i,1,"1");
            for(int i=0; i<32;i+=8) enderecoHost += QString::number(stoi(hostBin.mid(i,8).toStdString(),nullptr,2)) + ".";

            enderecoHost.chop(1);
            ultimoHost = new Endereco(enderecoHost,mascara);
        }  catch (QString &erro) {
            throw erro;
        }
    }



        /*QString hostBin = subRedeBroadcast->getEnderecoBin();
        QString aux = Utilitarios::bin2Complement("00000000000000000000000000000001");
        hostBin = Utilitarios::binSum(hostBin, aux);
        aux = "";

        for(int i=0; i<32;i+=8) aux += QString::number(stoi(hostBin.mid(i,8).toStdString(),nullptr,2)) + ".";
        aux.chop(1);
        ultimoHost = new Endereco(aux,mascara);*/



    bool Endereco::ehCIDR(QString mascara)const
    {
        if(mascara.size() > 0 && mascara.toInt() > 0 && mascara.toInt() < 31) return true;
        return false;

    }

    bool Endereco::validaEndereco(QString endereco, QList<int> &listaOctetos)const
    {
        QStringList parseEndereco = endereco.split(QLatin1Char('.'));

        if(parseEndereco.count() == 4){
            for(int i=0; i<4; i++){
                if(parseEndereco.at(i) == "") parseEndereco.replace(i, "0");
                if(parseEndereco.at(i).length() > 1 && parseEndereco.at(i).at(0).digitValue() == 0) return false;
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
            if(lista.at(3) > 252) throw QString("erro valida mascara");
            this->mascara = mascara;
        } else {
            throw QString("erro else");
        }


    }

    void Endereco::validaClasse()
    {
        if(octetosEndereco.isEmpty()) throw QString("erro valida classe");
        if(octetosEndereco.at(0) >= 0 && octetosEndereco.at(0) <=127) classe = 'A';
        if(octetosEndereco.at(0) >= 128 && octetosEndereco.at(0) <=191) classe = 'B';
        if(octetosEndereco.at(0) >= 192 && octetosEndereco.at(0) <=223) classe = 'C';
        if(octetosEndereco.at(0) >= 224 && octetosEndereco.at(0) <=239) classe = 'D';
        if(octetosEndereco.at(0) >= 240 && octetosEndereco.at(0) <=255) classe = 'E';
    }

    QString Endereco::maskConvertCIDRToDottedDecimal()const
    {
        if(!ehCIDR(this->mascara)) throw QString("erro mask convert to decimal");

        QString mask;
        if(this->getClasse() == "A"){
            mask = "255.";

            int maskPos = 8;
            int qntdDe1 = 32 - mascara.toInt();
            QString octetos = "";
            for(int i = maskPos; qntdDe1 >0; i++, qntdDe1--) octetos.append("1");
            while(octetos.size() < 24) octetos.append("0");
            for(int i = 0; i < 24; i+=8) mask += QString::number(stoi(octetos.mid(i,8).toStdString(),nullptr,2)) + ".";
            mask.chop(1);
        } else if(this->getClasse() == "B"){

            mask = "255.255.";
            QString octetos = "";

            if(mascara>16){
                int maskPos = 16;
                int qntdDe1 = mascara.toInt()-16;
                for(int i = maskPos; qntdDe1 >0; i++, qntdDe1--) octetos.append("1");
                while(octetos.size() < 16) octetos.append("0");
                for(int i = 0; i < 16; i+=8) mask += QString::number(stoi(octetos.mid(i,8).toStdString(),nullptr,2)) + ".";
                mask.chop(1);
            }else{
                mask += "0.0";
            }

        } else if(this->getClasse() == "C"){
            mask = "255.255.255.";

            /*int maskPos = 24;
            int qntdDe1 = 32 - mascara.toInt();*/
            QString octeto = "";
            /*for(int i = maskPos; qntdDe1 > 0; i++, qntdDe1--) octeto.append("1");
            while(octeto.size() < 8) octeto.append("0");
            mask += QString::number(stoi(octeto.toStdString(),nullptr,2));*/

            if(mascara>24){
                int maskPos = 24;
                int qntdDe1 = mascara.toInt()-24;
                for(int i = maskPos; qntdDe1 >0; i++, qntdDe1--) octeto.append("1");
                while(octeto.size() < 8) octeto.append("0");
                mask += QString::number(stoi(octeto.toStdString(),nullptr,2));
            }else{
                mask += "0";
            }
            //for(int i=0; i<32;i+=8) m + ".";

            //QString bin = Utilitarios::toBinary(octetosEndereco.at(3));
            //int quantidadeUmsNaMascara = 0, octetoDecimal = 0;
            //while(bin.size()<8) bin.insert(0,"0");
            //or(int i=0; bin.at(i).digitValue() == 1; i++) quantidadeUmsNaMascara += 1;
            //for(int i=7;quantidadeUmsNaMascara!=0;i--, quantidadeUmsNaMascara--) octetoDecimal += pow(2,i);

            //mask.append(QString::number(octetoDecimal));
        } else{
            return "Classe do endereço não esta validada.";
        }

        return mask;
    }

    QString Endereco::maskConvertDottedDecimalToCIDR()const
    {
        if(ehCIDR(this->mascara)) throw QString("erro mask convert do cidr");

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

        return QString::number(mask);
    }

}
