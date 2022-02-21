#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <thread>
#include <chrono>

#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QStandardItemModel>
#include <QStatusBar>
#include <QSerialPort>
#include <QModbusDataUnit>
#include <QTimer>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::readSlave1()
{
    if (auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 1000, 1),1)) {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &MainWindow::readReady);
        else
            delete reply;
    } else {
        statusBar()->showMessage(tr("Read error: ") + modbusDevice->errorString(), 5000);
    }
}

 void MainWindow::readSlave2()
 {
     if (auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 2000, 1),2)) {
         if (!reply->isFinished())
             connect(reply, &QModbusReply::finished, this, &MainWindow::readReady);
         else
             delete reply;
     } else {
         statusBar()->showMessage(tr("Read error: ") + modbusDevice->errorString(), 5000);
     }
 }

void MainWindow::on_readButton_clicked()
{
//    std::thread thread2([this]{readSlave2();});
//    thread2.join();

//    std::thread thread1([this]{readSlave1();});
//    thread1.join();
    
    readSlave1();
    readSlave2();
}

void MainWindow::on_writeButton_clicked()
{
    if (!modbusDevice)
        return;
    statusBar()->clearMessage();

    QModbusDataUnit writeUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 1000, 1);
    for (uint i = 0; i < writeUnit.valueCount(); i++) {

            writeUnit.setValue(i, ui->dataToSend->text().toInt());
    }

    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, 1)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::ProtocolError) {
                    statusBar()->showMessage(tr("Write response error: %1 (Mobus exception: 0x%2)")
                        .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
                        5000);
                } else if (reply->error() != QModbusDevice::NoError) {
                    statusBar()->showMessage(tr("Write response error: %1 (code: 0x%2)").
                        arg(reply->errorString()).arg(reply->error(), -1, 16), 5000);
                }
                reply->deleteLater();
            });
        } else {
            reply->deleteLater();
        }
    } else {
        statusBar()->showMessage(tr("Write error: ") + modbusDevice->errorString(), 5000);
    }

}

void MainWindow::on_connectButton_clicked()
{
    statusBar()->clearMessage();
    modbusDevice = new QModbusRtuSerialMaster(this);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                "COM1");
            modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                QSerialPort::EvenParity);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                QSerialPort::Baud19200);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                QSerialPort::Data8);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
               QSerialPort::OneStop);



        modbusDevice->setTimeout(1000);
        modbusDevice->setNumberOfRetries(3);
        if (!modbusDevice->connectDevice()) {
            statusBar()->showMessage(tr("Connect failed: ") + modbusDevice->errorString(), 5000);
        } else {
           statusBar()->showMessage(tr("Device connected"));
           ui->connectButton->setDisabled(true);
        }

}

void MainWindow::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        for (uint i = 0; i < unit.valueCount(); i++) {
            const QString entry = tr("Slave_Addr %1, Value: %2").arg(unit.startAddress() + i)
                                     .arg(QString::number(unit.value(i),
                                          unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
            if(unit.startAddress() == 1000){
            ui->readValue->addItem(entry);
            }else ui->readValue2->addItem(entry);

        }
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        statusBar()->showMessage(tr("Read response error: %1 (Mobus exception: 0x%2)").
                                    arg(reply->errorString()).
                                    arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
    } else {
        statusBar()->showMessage(tr("Read response error: %1 (code: 0x%2)").
                                    arg(reply->errorString()).
                                    arg(reply->error(), -1, 16), 5000);
    }

    reply->deleteLater();

}
