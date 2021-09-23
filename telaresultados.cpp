#include "telaresultados.h"
#include "ui_telaresultados.h"

telaResultados::telaResultados(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaResultados)
{
    ui->setupUi(this);
}

telaResultados::~telaResultados()
{
    delete ui;
}
