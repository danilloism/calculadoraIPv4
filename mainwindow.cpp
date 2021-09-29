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
    ui->lineEditEndereco->setValidator(new  QRegExpValidator(QRegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}")));
    ui->lineEditMascara->setValidator(new  QRegExpValidator(QRegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}")));
}

MainWindow::~MainWindow()
{
    delete ip;
    delete ui;
}

void MainWindow::limparTela() const{
    ui->radioButtonCIDR_Sim->isChecked() ? ui->lineEditMascara->setEnabled(false), ui->spinBoxCIDR->setEnabled(true) : ui->lineEditMascara->setEnabled(true), ui->spinBoxCIDR->setEnabled(false);
    ui->lineEditEndereco->setText("");
    ui->spinBoxCIDR->setValue(8);
    ui->lineEditMascara->setText("");
}

void MainWindow::on_radioButtonCIDR_Sim_clicked()
{
    ui->lineEditMascara->setEnabled(false);
    ui->spinBoxCIDR->setEnabled(true);
}


void MainWindow::on_radioButtonCIDR_Nao_clicked()
{
    ui->lineEditMascara->setEnabled(true);
    ui->spinBoxCIDR->setEnabled(false);
}


void MainWindow::on_pushButtonCalcular_clicked()
{
    try {
        delete ip;
        ip = new dnn::Endereco(ui->lineEditEndereco->text(), ui->radioButtonCIDR_Sim->isChecked() ? ui->spinBoxCIDR->text() : ui->lineEditMascara->text());

        telaListagem = new telaResultados(ip);
        telaListagem->setModal(true);
        telaListagem->setAttribute(Qt::WA_DeleteOnClose);
        telaListagem->show();

    }  catch (QString &erro) {
        QMessageBox::information(this,"ERRO DO SISTEMA", erro);
    }

}


void MainWindow::on_pushButtonLimpar_clicked()
{
    ui->lineEditEndereco->clear();
    ui->lineEditMascara->clear();
    ui->spinBoxCIDR->setValue(8);
}

