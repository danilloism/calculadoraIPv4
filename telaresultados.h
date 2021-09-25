#ifndef TELARESULTADOS_H
#define TELARESULTADOS_H

#include <QDialog>
#include <endereco.h>

namespace Ui {
class telaResultados;
}

class telaResultados : public QDialog
{
    Q_OBJECT

public:
    explicit telaResultados(dnn::Endereco *endereco, QWidget *parent = nullptr);
    ~telaResultados();

private slots:
    void on_pushButton_clicked();

private:
    Ui::telaResultados *ui;
    dnn::Endereco* dados;

/*public slots:
    void getData(QStringList data);*/
};

#endif // TELARESULTADOS_H
