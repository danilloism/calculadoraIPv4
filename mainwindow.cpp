#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->lineEditMascara->setEnabled(false);
    //QList<int> teste;
    //for(int i=0;i<3;i++) teste.append(i);
    //int i = 0;
    //i = pow(2,7) + pow(2,6);
    //ui->lineEditEndereco->setText(QString::number(i));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    telaResultados telaResultados;
    telaResultados.setModal(true);
    telaResultados.exec();
}

