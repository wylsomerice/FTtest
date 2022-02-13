#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusDevice>
#include <QModbusClient>
#include <QModbusDataUnit>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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

    void readyReadSlot();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QModbusDevice *device;
    QByteArray *byteData;
    QModbusDataUnit *data;
};
#endif // MAINWINDOW_H
