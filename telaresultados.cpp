#include "telaresultados.h"
#include "ui_telaresultados.h"

telaResultados::telaResultados(dnn::Endereco* endereco, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaResultados),
    dados(0),
    lista(0)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    try {
        dados = endereco;
        dnn::Endereco* subRedeAtual = dados->getSubRedeAtual();
        dnn::Endereco* broadcast = dados->getSubRedeBroadcast();
        dnn::Endereco* primeiroH = dados->getSubRedePrimeiroHost();
        dnn::Endereco* ultimoH = dados->getSubRedeUltimoHost();
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
        QTableWidgetItem *classe = new QTableWidgetItem(dados->getClasse());

        ui->tableWidgetInformacoes->setColumnWidth(1,350);
        ui->tableWidgetInformacoes->setColumnWidth(2,110);

        ui->tableWidgetInformacoes->setItem(0,0,classe);
        ui->tableWidgetInformacoes->setItem(1,0,enderecoInformado);
        ui->tableWidgetInformacoes->setItem(1,1,enderecoInformadoBin);
        ui->tableWidgetInformacoes->setItem(2,0,mascaraEnderecoInformado);
        ui->tableWidgetInformacoes->setItem(2,1,mascaraEnderecoInformadoBin);
        ui->tableWidgetInformacoes->setItem(2,2,mascaraEnderecoInformadoCIDR);
        ui->tableWidgetInformacoes->setItem(3,0,subRedeEnderecoInformado);
        ui->tableWidgetInformacoes->setItem(3,1,subRedeEnderecoInformadoBin);
        ui->tableWidgetInformacoes->setItem(4,0,broadcastSubRedeEnderecoInformado);
        ui->tableWidgetInformacoes->setItem(4,1,broadcastSubRedeEnderecoInformadoBin);
        ui->tableWidgetInformacoes->setItem(5,0,primeiroHost);
        ui->tableWidgetInformacoes->setItem(5,1,primeiroHostBin);
        ui->tableWidgetInformacoes->setItem(6,0,ultimoHost);
        ui->tableWidgetInformacoes->setItem(6,1,ultimoHostBin);
        ui->tableWidgetInformacoes->setItem(7,0,qntdHosts);


        if(!dados->possuiSubRedes()){
            QMessageBox::information(0,"Atenção!", "Endereço informado não possui sub-redes! Apenas hosts.");
            ui->tableWidgetInformacoes->verticalHeaderItem(3)->setText("Rede:");
            ui->tableWidgetInformacoes->verticalHeaderItem(4)->setText("Broadcast:");
            ui->tableWidgetInformacoes->verticalHeaderItem(5)->setText("Primeiro host:");
            ui->tableWidgetInformacoes->verticalHeaderItem(6)->setText("Último host:");
            ui->tableWidgetInformacoes->verticalHeaderItem(7)->setText("Quant. hosts na rede:");
            ui->tableWidgetInformacoes->removeRow(8);

        }else{
            QTableWidgetItem *quantidadeSubRedes = new QTableWidgetItem(QString::number(dados->getQtdeSubRedes()));
            ui->tableWidgetInformacoes->setItem(8,0,quantidadeSubRedes);
        }
    }  catch (QString &erro) {
        QMessageBox::information(this,"ERRO DO SISTEMA", erro);
    }

}

telaResultados::~telaResultados()
{
    delete ui;
}

void telaResultados::on_pushButton_clicked()
{
    this->close();
}
