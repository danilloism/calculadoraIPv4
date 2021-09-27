#include "telaresultados.h"
#include "ui_telaresultados.h"

telaResultados::telaResultados(dnn::Endereco* endereco, int qtdSubRedes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaResultados),
    dados(0),
    qtdeSubRedes(qtdSubRedes)
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




    listarResultado();
    //ui->tableWidgetInformacoes->insertRow()


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
    dados->preencherSubRedes(qtdeSubRedes);

    QList<dnn::Endereco*> *lista = dados->getSubredes();
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

    }
}
