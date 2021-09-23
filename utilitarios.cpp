#include "utilitarios.h"

namespace dnn {

    QString Utilitarios::toBinary(int inteiro)
    {
        QString bin;
        while(inteiro!=0){
                bin = (inteiro%2==0 ? "0" : "1") + bin;
                inteiro/=2;
        }
        return bin;
    }

    QString Utilitarios::binAND(QString binario1, QString binario2)
    {
        QString resultado("");

        while(binario2.size()<binario1.size()) binario2.insert(0,"0");
        while(binario1.size()<binario2.size()) binario1.insert(0,"0");

        for(int i=0; i<binario1.size(); i++){
            resultado.append(QString::number(binario1.at(i).digitValue() & binario2.at(i).digitValue()));
        }

        return resultado;
    }

    QString Utilitarios::binOR(QString binario1, QString binario2)
    {
        QString resultado("");

        while(binario2.size()<binario1.size()) binario2.insert(0,"0");
        while(binario1.size()<binario2.size()) binario1.insert(0,"0");

        for(int i=0; i<binario1.size(); i++){
            resultado.append(QString::number(binario1.at(i).digitValue() | binario2.at(i).digitValue()));
        }

        return resultado;
    }

    QString Utilitarios::binOneComplement(QString binario)
    {
        QString resultado("");
        for(int i=0; i<binario.size(); i++) binario.at(i).digitValue() == 1 ? resultado.append(QString::number(0)) : resultado.append(QString::number(1));
        return resultado;
    }




}
