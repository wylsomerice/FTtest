#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>
#include <QModbusDevice>
#include <QtSerialPort/QSerialPortInfo>
#include <QModbusClient>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //порт
    serial = new QSerialPort();
    serial->setPortName("COM1");
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

      //modbus device
//    device->setConnectionParameter(0,"COM1");
//    device->setConnectionParameter(1,QSerialPort::NoParity);
//    device->setConnectionParameter(2,QSerialPort::Baud9600);
//    device->setConnectionParameter(3,QSerialPort::Data8);
//    device->setConnectionParameter(4,QSerialPort::OneStop);
//    device->setConnectionParameter(5,"502");
//    device->setConnectionParameter(6,"127.0.0.1");
    device->stateChanged(QModbusDevice::ConnectedState);

    //данные
    data = new QModbusDataUnit();
    data->setStartAddress(1000);
    data->setRegisterType(QModbusDataUnit::Coils);
    data->setValue(0,1212);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readyReadSlot()
 {
    if(serial->isOpen())
        ui->statusBar->showMessage("connected");
    else
    {
       ui->statusBar->showMessage("connection error");
    }
 }

void MainWindow::on_readButton_clicked()
{
    QString addr = QString::number(data->value(0x3E8));
    ui->textEdit->setText(addr);
}

void MainWindow::on_writeButton_clicked()
{
    data->setValue(0x3E8,1212);
    data->value(0x3E8);
    //QString str = ui->dataToSend->text();
}

void MainWindow::on_connectButton_clicked()
{
    readyReadSlot();
}

