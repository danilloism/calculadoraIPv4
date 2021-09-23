#ifndef TELARESULTADOS_H
#define TELARESULTADOS_H

#include <QDialog>

namespace Ui {
class telaResultados;
}

class telaResultados : public QDialog
{
    Q_OBJECT

public:
    explicit telaResultados(QWidget *parent = nullptr);
    ~telaResultados();

private:
    Ui::telaResultados *ui;
};

#endif // TELARESULTADOS_H
