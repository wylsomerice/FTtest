#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QModbusDataUnit>
#include <QModbusClient>
#include <QThread>

#include <thread>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);


    ~MainWindow();

private slots:

    void on_readButton_clicked();

    void on_writeButton_clicked();

    void on_connectButton_clicked();

    void readReady();

    void readSlave1();

    void readSlave2();

private:
    Ui::MainWindow *ui;
    QModbusClient *modbusDevice;
    QModbusDataUnit *data;
    QTimer *timer;


};
#endif // MAINWINDOW_H
