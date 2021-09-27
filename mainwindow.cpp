#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , telaListagem(nullptr)
    , ui(new Ui::MainWindow)
    , ip(0)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->lineEditMascara->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ip;
    delete ui;
}

void MainWindow::limparTela() const{
    ui->radioButtonCIDR_Sim->isChecked() ? ui->lineEditMascara->setEnabled(false), ui->lineEditCIDR->setEnabled(true) : ui->lineEditMascara->setEnabled(true), ui->lineEditCIDR->setEnabled(false);
    ui->lineEditEndereco->setText("");
    ui->lineEditCIDR->setText("");
    ui->lineEditMascara->setText("");
}

void MainWindow::on_radioButtonCIDR_Sim_clicked()
{
    ui->lineEditMascara->setEnabled(false);
    ui->lineEditCIDR->setEnabled(true);
}


void MainWindow::on_radioButtonCIDR_Nao_clicked()
{
    ui->lineEditMascara->setEnabled(true);
    ui->lineEditCIDR->setEnabled(false);
}


void MainWindow::on_pushButtonCalcular_clicked()
{
    try {
        delete ip;
        ip = new dnn::Endereco(ui->lineEditEndereco->text(), ui->radioButtonCIDR_Sim->isChecked() ? ui->spinBoxCIDR->text() : ui->lineEditMascara->text());

        if(ui->spinBoxNumSubRedes->value() > ip->getQtdeSubRedes() && ui->spinBoxNumSubRedes->value() > 1) throw QString("Quantidade de sub-redes fornecida ultrapassa quantidade de sub-redes da rede! Valor máx de sub-redes: "+QString::number(ip->getQtdeSubRedes()));
        telaListagem = new telaResultados(ip, ui->spinBoxNumSubRedes->value());
        telaListagem->setModal(true);
        telaListagem->setAttribute (Qt::WA_DeleteOnClose);
        telaListagem->show();


    }  catch (QString &erro) {
        QMessageBox::information(this,"ERRO DO SISTEMA", erro);
    }

}

