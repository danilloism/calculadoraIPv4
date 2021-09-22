#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->lineEditMascara->setEnabled(false);
    QString teste = "0.0.0.0";
    ui->lineEditEndereco->setText(QString::number(teste.split(QLatin1Char('.')).count()));
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

