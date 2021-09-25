#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , telaListagem(nullptr)
    , ui(new Ui::MainWindow)
    , ip(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->lineEditMascara->setEnabled(false);
}

MainWindow::~MainWindow()
{
    if(telaListagem) delete telaListagem;
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
        ip = new dnn::Endereco(ui->lineEditEndereco->text(), ui->radioButtonCIDR_Sim->isChecked() ? ui->lineEditCIDR->text() : ui->lineEditMascara->text());
        telaListagem = new telaResultados(ip, this);
        telaListagem->setModal(true);
        telaListagem->show();
    }  catch (QString &erro) {
        QMessageBox::information(this,"ERRO DO SISTEMA", erro);
    }

}

