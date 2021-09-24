#include "telaresultados.h"
#include "ui_telaresultados.h"

telaResultados::telaResultados(const dnn::Endereco* endereco, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaResultados),
    dados(nullptr)
{
    ui->setupUi(this);
    *dados = *endereco;
}

telaResultados::~telaResultados()
{
    if(dados) delete dados;
    delete ui;
}

void telaResultados::on_pushButton_clicked()
{
    this->close();
}

/*void telaResultados::getData(QStringList data)
{
    dataFromMainWindow.append(data.at(0));
    dataFromMainWindow.append(data.at(0));
    dataFromMainWindow.append(data.at(0));
}*/

