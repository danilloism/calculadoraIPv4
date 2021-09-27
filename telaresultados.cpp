#include "telaresultados.h"
#include "ui_telaresultados.h"

telaResultados::telaResultados(dnn::Endereco* endereco, int qtdSubRedes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaResultados),
    dados(0),
    qtdeSubRedes(qtdSubRedes),
    lista(0)
{
    ui->setupUi(this);

    //Preenchendo informações sobre ip informado;
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
        QMessageBox::information(this,"Atenção!", "Endereço informado não possui sub-redes! Apenas hosts.");
        ui->tabDecimal->setEnabled(false);
        ui->tabBinario->setEnabled(false);
        ui->tableWidgetInformacoes->verticalHeaderItem(3)->setText("Rede:");
        ui->tableWidgetInformacoes->verticalHeaderItem(4)->setText("Broadcast:");
        ui->tableWidgetInformacoes->verticalHeaderItem(5)->setText("Primeiro host:");
        ui->tableWidgetInformacoes->verticalHeaderItem(6)->setText("Último host:");
        ui->tableWidgetInformacoes->verticalHeaderItem(7)->setText("Quant. hosts na rede:");

    }else{
        QTableWidgetItem *quantidadeSubRedes = new QTableWidgetItem(QString::number(dados->getQtdeSubRedes()));
        ui->tableWidgetInformacoes->setItem(8,0,quantidadeSubRedes);
        dados->preencherSubRedes(qtdeSubRedes);
        lista = dados->getSubredes();
        listarResultado();
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

void telaResultados::listarResultado() const
{

    QList<dnn::Endereco*>::iterator iterLista;

    for(iterLista = lista->begin(); iterLista != lista->end(); iterLista++){
        dnn::Endereco *objeto = *iterLista;

        QString subRede = objeto->getEndereco();
        QString broadcast = objeto->getSubRedeBroadcast()->getEndereco();
        QString primeiroHost = objeto->getSubRedePrimeiroHost()->getEndereco();
        QString ultimoHost = objeto->getSubRedeUltimoHost()->getEndereco();
        QString quantidadeHosts = QString::number(objeto->getQuantidadeHosts());

        QTableWidgetItem *item1 = new QTableWidgetItem(subRede);
        QTableWidgetItem *item2 = new QTableWidgetItem(broadcast);
        QTableWidgetItem *item3 = new QTableWidgetItem(primeiroHost);
        QTableWidgetItem *item4 = new QTableWidgetItem(ultimoHost);
        QTableWidgetItem *item5 = new QTableWidgetItem(quantidadeHosts);

        int linha = ui->tableWidgetListagemDecimal->rowCount();
        ui->tableWidgetListagemDecimal->insertRow(linha);
        ui->tableWidgetListagemDecimal->setItem(linha, 0, item1);
        ui->tableWidgetListagemDecimal->setItem(linha, 1, item2);
        ui->tableWidgetListagemDecimal->setItem(linha, 2, item3);
        ui->tableWidgetListagemDecimal->setItem(linha, 3, item4);
        ui->tableWidgetListagemDecimal->setItem(linha, 4, item5);

        QString subRedeBin = objeto->getEnderecoBin();
        QString broadcastBin = objeto->getSubRedeBroadcast()->getEnderecoBin();
        QString primeiroHostBin = objeto->getSubRedePrimeiroHost()->getEnderecoBin();
        QString ultimoHostBin = objeto->getSubRedeUltimoHost()->getEnderecoBin();

        QTableWidgetItem *item1Decimal = new QTableWidgetItem(subRedeBin);
        QTableWidgetItem *item2Decimal = new QTableWidgetItem(broadcastBin);
        QTableWidgetItem *item3Decimal = new QTableWidgetItem(primeiroHostBin);
        QTableWidgetItem *item4Decimal = new QTableWidgetItem(ultimoHostBin);

        int linhaBin = ui->tableWidgetListagemBinaria->rowCount();
        ui->tableWidgetListagemBinaria->insertRow(linhaBin);
        ui->tableWidgetListagemBinaria->setItem(linhaBin, 0, item1Decimal);
        ui->tableWidgetListagemBinaria->setItem(linhaBin, 1, item2Decimal);
        ui->tableWidgetListagemBinaria->setItem(linhaBin, 2, item3Decimal);
        ui->tableWidgetListagemBinaria->setItem(linhaBin, 3, item4Decimal);


    }
}
