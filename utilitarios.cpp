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

        while(binario2.size()<binario1.size()) binario2.prepend('0');
        while(binario1.size()<binario2.size()) binario1.prepend('0');

        for(int i=0; i<binario1.size(); i++){
            resultado.append(QString::number(binario1.at(i).digitValue() & binario2.at(i).digitValue()));
        }

        while(resultado.size()<32) resultado.prepend('0');

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

    QString Utilitarios::bin2Complement(QString binario)
    {
        QString bin = bin1Complement(binario);
        for(int i = bin.size()-1; i>=0; i--){
            if(bin.at(bin.size()-1).digitValue() == 0){
                bin = bin.replace(bin.size()-1,1,"1");
                break;
            }else{
                bin = bin.replace(bin.size()-1,1,"0");
            }
        }
        return bin;
    }

    QString Utilitarios::binSum(QString binario1, QString binario2)
    {
        while(binario2.size()<binario1.size()) binario2.prepend('0');
        while(binario1.size()<binario2.size()) binario1.prepend('0');

        std::string result = ""; // Initialize result
            int s = 0;          // Initialize digit sum

            // Traverse both strings starting from last
            // characters
            int i = binario1.toStdString().size() - 1, j = binario2.toStdString().size() - 1;
            while (i >= 0 || j >= 0 || s == 1)
            {
                // Comput sum of last digits and carry
                s += ((i >= 0)? binario1.toStdString()[i] - '0': 0);
                s += ((j >= 0)? binario2.toStdString()[j] - '0': 0);

                // If current digit sum is 1 or 3, add 1 to result
                result = char(s % 2 + '0') + result;

                // Compute carry
                s /= 2;

                // Move to next digits
                i--; j--;
            }
            return QString::fromStdString(result);
        /*int tamanho = binario1.size();
        int carry = 0;
        QString bin("");

        for(int i = tamanho-1; i>=0; i--){
            if(carry == 0 &&
             ((binario1.at(tamanho-1).digitValue() == 0 && binario2.at(tamanho-1).digitValue() == 1) ||
              (binario1.at(tamanho-1).digitValue() == 1 && binario2.at(tamanho-1).digitValue() == 0))){

                bin = bin.prepend("1");

            }else if(carry == 0 &&
                    (binario1.at(tamanho-1).digitValue() == 0 && binario2.at(tamanho-1).digitValue() == 0)){

                bin = bin.prepend("0");

            }else if(carry == 0 &&
                    (binario1.at(tamanho-1).digitValue() == 1 && binario2.at(tamanho-1).digitValue() == 1)){

                bin.append("0");
                carry++;

            }else if(carry == 1 &&
                     (binario1.at(tamanho-1).digitValue() == 0 && binario2.at(tamanho-1).digitValue() == 0)){

                carry--;
                bin = bin.prepend("1");

            }else if(carry == 1 &&
                     ((binario1.at(tamanho-1).digitValue() == 0 && binario2.at(tamanho-1).digitValue() == 1) ||
                      (binario1.at(tamanho-1).digitValue() == 1 && binario2.at(tamanho-1).digitValue() == 0))){

                bin = bin.prepend("0");

            }else if(carry == 1 &&
                    (binario1.at(tamanho-1).digitValue() == 1 && binario2.at(tamanho-1).digitValue() == 1)){

                bin.prepend("1");

            }
        }

        if(carry == 1) bin.prepend("1");
        return bin;*/
    }


    QString Utilitarios::bin1Complement(QString binario)
    {
        QString resultado("");
        for(int i=0; i<binario.size(); i++) binario.at(i).digitValue() == 1 ? resultado.append(QString::number(0)) : resultado.append(QString::number(1));
        return resultado;
    }




}
