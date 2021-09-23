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




}
