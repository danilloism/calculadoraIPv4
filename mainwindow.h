#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QObject>
#include <QMainWindow>
#include <telaresultados.h>
#include <endereco.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    telaResultados* telaListagem;

private slots:
    void on_radioButtonCIDR_Sim_clicked();

    void on_radioButtonCIDR_Nao_clicked();

    void on_pushButtonCalcular_clicked();

/*signals:
    void sendData(QStringList data);*/

    void on_pushButtonLimpar_clicked();

private:
    Ui::MainWindow *ui;
    void limparTela()const;
    dnn::Endereco* ip;
};
#endif // MAINWINDOW_H
