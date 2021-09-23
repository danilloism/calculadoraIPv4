#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->lineEditMascara->setEnabled(false);
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

