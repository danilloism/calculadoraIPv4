#include "telaresultados.h"
#include "ui_telaresultados.h"

telaResultados::telaResultados(dnn::Endereco* endereco, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaResultados),
    dados(nullptr)
{
    ui->setupUi(this);

    //ui->tableWidgetListagemBinaria->setColumnWidth()

    dados = endereco;
    dnn::Endereco* subRedeAtual = dados->getSubRedeAtual();
    dnn::Endereco* broadcast = subRedeAtual->getSubRedeBroadcast();
    dnn::Endereco* primeiroH = subRedeAtual->getSubRedePrimeiroHost();
    dnn::Endereco* ultimoH = subRedeAtual->getSubRedeUltimoHost();
    QTableWidgetItem *enderecoInformado = new QTableWidgetItem("Decimal: "+dados->getEndereco());
    QTableWidgetItem *enderecoInformadoBin = new QTableWidgetItem("Binário: "+dados->getEnderecoBin());
    QTableWidgetItem *mascaraEnderecoInformadoCIDR = dados->ehCIDR(dados->getMascara()) ? new QTableWidgetItem("CIDR: "+dados->getMascara()) : new QTableWidgetItem("CIDR: "+dados->maskConvertDottedDecimalToCIDR());
    QTableWidgetItem *mascaraEnderecoInformado = dados->ehCIDR(dados->getMascara()) ? new QTableWidgetItem("Decimal: "+dados->maskConvertCIDRToDottedDecimal()) : new QTableWidgetItem("Decimal: "+dados->getMascara());
    QTableWidgetItem *mascaraEnderecoInformadoBin = new QTableWidgetItem("Binário: "+dados->getMascaraBin());
    QTableWidgetItem *subRedeEnderecoInformado = new QTableWidgetItem("Decimal: "+subRedeAtual->getEndereco());
    QTableWidgetItem *subRedeEnderecoInformadoBin = new QTableWidgetItem("Binário: "+subRedeAtual->getEnderecoBin());
    QTableWidgetItem *broadcastSubRedeEnderecoInformado = new QTableWidgetItem("Decimal: "+broadcast->getEndereco());
    QTableWidgetItem *broadcastSubRedeEnderecoInformadoBin = new QTableWidgetItem("Binário: "+broadcast->getEnderecoBin());
    QTableWidgetItem *primeiroHost = new QTableWidgetItem("Decimal: "+primeiroH->getEndereco());
    QTableWidgetItem *primeiroHostBin = new QTableWidgetItem("Binário: "+primeiroH->getEnderecoBin());
    QTableWidgetItem *ultimoHost = new QTableWidgetItem("Decimal: "+ultimoH->getEndereco());
    QTableWidgetItem *ultimoHostBin = new QTableWidgetItem("Binário: "+ultimoH->getEnderecoBin());
    QTableWidgetItem *qntdHosts = new QTableWidgetItem(QString::number(dados->getQuantidadeHosts()));

    ui->tableWidgetInformacoes->setColumnWidth(1,350);

    ui->tableWidgetInformacoes->setItem(0,0,enderecoInformado);
    ui->tableWidgetInformacoes->setItem(0,1,enderecoInformadoBin);
    ui->tableWidgetInformacoes->setItem(1,0,mascaraEnderecoInformado);
    ui->tableWidgetInformacoes->setItem(1,1,mascaraEnderecoInformadoBin);
    ui->tableWidgetInformacoes->setItem(1,2,mascaraEnderecoInformadoCIDR);
    ui->tableWidgetInformacoes->setItem(2,0,subRedeEnderecoInformado);
    ui->tableWidgetInformacoes->setItem(2,1,subRedeEnderecoInformadoBin);
    ui->tableWidgetInformacoes->setItem(3,0,broadcastSubRedeEnderecoInformado);
    ui->tableWidgetInformacoes->setItem(3,1,broadcastSubRedeEnderecoInformadoBin);
    ui->tableWidgetInformacoes->setItem(4,0,primeiroHost);
    ui->tableWidgetInformacoes->setItem(4,1,primeiroHostBin);
    ui->tableWidgetInformacoes->setItem(5,0,ultimoHost);
    ui->tableWidgetInformacoes->setItem(5,1,ultimoHostBin);
    ui->tableWidgetInformacoes->setItem(6,0,qntdHosts);





    //ui->tableWidgetInformacoes->insertRow()


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

