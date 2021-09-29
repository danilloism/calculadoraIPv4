#include "endereco.h"

namespace dnn {

    Endereco::Endereco(QString endereco, QString mascara):
            mascara(""),
            qtdSubRedes(0),
            qtdHosts(0),
            primeiroHost(0),
            ultimoHost(0),
            subRedeAtual(0),
            subRedeBroadcast(0)
        {
            try {
                if(!this->validaEndereco(endereco, octetosEndereco)) throw QString("Erro ao validar endereço! Endereço deve estar no formato <0.0.0.0>, não pode haver haver zeros não significativos e cada número deve ser menor que 255!");
                this->validaClasse();
                this->validaMascara(mascara);
                this->setQtdeHosts();
                this->setqtdeSubRedes();
                classe == 'D' || classe == 'E' ? throw QString("Endereços de classe D e E não são válidos para essas operações.") : 0;
            }  catch (QString &erro) {
                throw QString(erro);
        }
    }

    Endereco::~Endereco()
    {
        delete subRedeAtual;
        delete primeiroHost;
        delete ultimoHost;
        delete subRedeBroadcast;
        qDeleteAll(subRedes);
        subRedes.clear();
    }

    QString Endereco::getEndereco() const
    {
        if(octetosEndereco.isEmpty()) throw QString("Endereço não validado.");

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
        if(octetosEndereco.isEmpty()) throw QString("Endereço não validado.");
        QString bin = "";

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

        try {
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
        }  catch (QString &erro) {throw erro;}

    }

    Endereco *Endereco::getSubRedeAtual()
    {
        try {
            setSubRedeAtual();
            return subRedeAtual;
        }  catch (QString &erro) {
            throw erro;
        }

    }

    Endereco *Endereco::getSubRedePrimeiroHost()
    {
        try {
            setSubRedePrimeiroHost();
            return primeiroHost;
        }  catch (QString &erro) {
            throw erro;
        }

    }

    Endereco *Endereco::getSubRedeUltimoHost()
    {
        try {
            setSubRedeUltimoHost();
            return ultimoHost;
        }  catch (QString &erro) {
            throw erro;
        }

    }

    Endereco *Endereco::getSubRedeBroadcast()
    {
        try {
            setSubRedeBroadcast();
            return subRedeBroadcast;
        }  catch (QString &erro) {
            throw erro;
        }

    }

    QList<Endereco *> *Endereco::getSubredes() const
    {
        try {
            QList<Endereco*>* aux = new QList<Endereco*>;

            for(int i=0; i<subRedes.size();i++){
                aux->push_back(subRedes[i]);
            }

            return aux;
        }  catch(std::bad_alloc){throw QString("Erro! Memória não alocada.");}
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
        }  catch(std::bad_alloc){throw QString("Erro! Memória não alocada.");}
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
            QString hostBin = subRedeAtual->getEnderecoBin().replace(31,1,"1");
            QString enderecoHost = "";

            for(int i=0; i<32;i+=8){
                enderecoHost += QString::number(stoi(hostBin.mid(i,8).toStdString(),nullptr,2)) + ".";
            }
            enderecoHost.chop(1);
            primeiroHost = new Endereco(enderecoHost,mascara);



        }  catch (QString &erro) {
            throw erro;
        }  catch(std::bad_alloc){throw QString("Erro! Memória não alocada.");}
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
        } catch(std::bad_alloc){throw QString("Erro! Memória não alocada.");}
    }

    bool Endereco::ehCIDR(QString mascara)const
    {
        if(mascara.size() > 0 && mascara.toInt() >= 8 && mascara.toInt() <= 30) return true;
        return false;

    }

    void Endereco::preencherSubRedes(int n)
    {
        QString mask;
        if(!ehCIDR(this->mascara)) mask = maskConvertDottedDecimalToCIDR();
        else mask = mascara;
        QString subRedeBin = getEnderecoBin();
        QString endereco = "";
        QStringList teste;


        if(this->getClasse() == "A"){
            if(mask.toInt()>8){
                int maskPos = 8;
                int qntdDe1 = mask.toInt() - 8;
                subRedeBin.replace(maskPos,32-maskPos,"");

                int potencia = pow(2,qntdDe1);
                int intervalo = 0;

                for(int i = 0; i<n; i++, intervalo+=potencia){
                    endereco += QString::number(stoi(subRedeBin.mid(0,8).toStdString(),nullptr,2)) + ".";
                    endereco += QString::number(intervalo);
                    Endereco *objeto = new Endereco(endereco,mascara);
                    setSubRede(objeto);
                    endereco = "";
                }
            }

        } else if(this->getClasse() == "B"){

            if(mask.toInt()>16){
                int maskPos = 16;
                int qntdDe1 = mask.toInt() - 16;
                subRedeBin.replace(maskPos,32-maskPos,"");

                int potencia = pow(2,qntdDe1);
                int intervalo = 0;
                int indice = 0;

                for(int i = 0; i<n; i++, intervalo+=potencia){
                    for(int j=0; j<16;j+=8) endereco += QString::number(stoi(subRedeBin.mid(j,8).toStdString(),nullptr,2)) + ".";
                    if(intervalo>255){
                        intervalo = 0;
                        indice++;
                    }
                    if(indice == 0){
                        endereco += QString::number(intervalo);

                        if(endereco.count(".")<3) endereco.append(".0");
                    }else{
                        endereco+="255."+QString::number(intervalo);
                    }
                    Endereco *objeto = new Endereco(endereco,mascara);
                    setSubRede(objeto);
                    endereco = "";
                }
            }

        } else if(this->getClasse() == "C"){
            if(mask.toInt()>24){
                int maskPos = 24;
                int qntdDe1 = mask.toInt() - 24;
                subRedeBin.replace(maskPos,32-maskPos,"");

                int potencia = pow(2,qntdDe1);
                int intervalo = 0;

                for(int i = 0; i<n; i++, intervalo+=potencia){
                    for(int j=0; j<24;j+=8) endereco += QString::number(stoi(subRedeBin.mid(j,8).toStdString(),nullptr,2)) + ".";
                    endereco += QString::number(intervalo);
                    Endereco *objeto = new Endereco(endereco,mascara);
                    setSubRede(objeto);
                    endereco = "";
                }
            }

        }

    }

    void Endereco::setqtdeSubRedes()
    {
        try {
            QString maskCIDR = "";
            if(!ehCIDR(mascara)) maskCIDR = maskConvertDottedDecimalToCIDR();
            else maskCIDR = mascara;

            int limite = 0;

            if(this->getClasse() == "A"){
                if(maskCIDR.toInt()>8){
                    int maskPos = 8;
                    int qntdDe1 = maskCIDR.toInt() - 8;

                    for(int i = maskPos; qntdDe1 >0; i++, qntdDe1--) limite++;
                }else{
                    qtdSubRedes = 1;
                }
            } else if(this->getClasse() == "B"){

                if(maskCIDR.toInt()>16){
                    int maskPos = 16;
                    int qntdDe1 = maskCIDR.toInt()-16;
                    for(int i = maskPos; qntdDe1 >0; i++, qntdDe1--) limite++;
                }else{
                    qtdSubRedes = 1;
                }

            } else if(this->getClasse() == "C"){

                if(maskCIDR.toInt()>24){
                    int maskPos = 24;
                    int qntdDe1 = maskCIDR.toInt()-24;
                    for(int i = maskPos; qntdDe1 >0; i++, qntdDe1--) limite++;
                }else{
                    qtdSubRedes = 1;
                }

            } else{
                throw QString("Classe do endereço inválida.");
            }

            qtdSubRedes = pow(2,limite);
        }  catch (QString &erro) {
            throw erro;
        }

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
        if(ehCIDR(mascara) && getClasse() == "A" && mascara.toInt()>=8 && mascara.toInt()<=30){
            this->mascara = mascara;
        } else if(ehCIDR(mascara) && getClasse() == "B" && mascara.toInt()>=16 && mascara.toInt()<=30){
            this->mascara = mascara;
        }else if(ehCIDR(mascara) && getClasse() == "C" && mascara.toInt()>=24 && mascara.toInt()<=30){
            this->mascara = mascara;
        }else if(validaEndereco(mascara, lista)){
            if(getClasse() == "A" && (lista.at(0) != 255 || lista.at(3)>252)) throw QString("Máscara inválida");
            else if(getClasse() == "B" && (lista.at(0) != 255 || lista.at(1) !=255 || lista.at(3)>252)) throw QString("Máscara inválida");
            else if(getClasse() == "C" && (lista.at(0) != 255 || lista.at(1) !=255 || lista.at(2) !=255 || lista.at(3)>252)) throw QString("Máscara inválida");
            this->mascara = mascara;
        }else {
            throw QString("Mascára Inválida. Para CIDR, os valores devem ser: (>=8 & <=30) "
                          "para endereços classe A. (>=16 & <=30) para endereços classe B. "
                          "(>=24 & <=30) para endereços classe C.");
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
        if(!ehCIDR(this->mascara)) throw QString("Máscara não é CIDR.");

        QString mask;
        if(this->getClasse() == "A"){
            mask = "255.";
            QString octetos = "";
            if(mascara>8){
                int maskPos = 8;
                int qntdDe1 = mascara.toInt() - 8;

                for(int i = maskPos; qntdDe1 >0; i++, qntdDe1--) octetos.append("1");
                while(octetos.size() < 24) octetos.append("0");
                for(int i = 0; i < 24; i+=8) mask += QString::number(stoi(octetos.mid(i,8).toStdString(),nullptr,2)) + ".";
                mask.chop(1);
            }else{
                mask += "0.0.0";
            }


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

            QString octeto = "";

            if(mascara>24){
                int maskPos = 24;
                int qntdDe1 = mascara.toInt()-24;
                for(int i = maskPos; qntdDe1 >0; i++, qntdDe1--) octeto.append("1");
                while(octeto.size() < 8) octeto.append("0");
                mask += QString::number(stoi(octeto.toStdString(),nullptr,2));
            }else{
                mask += "0";
            }

        } else{
            throw QString("Classe do endereço não esta validada.");
        }

        return mask;
    }

    QString Endereco::maskConvertDottedDecimalToCIDR()const
    {
        if(ehCIDR(this->mascara)) throw QString("Máscara já é CIDR.");
        return QString::number(getMascaraBin().count("1"));
    }

}
