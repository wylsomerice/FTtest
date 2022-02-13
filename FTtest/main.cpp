#include "mainwindow.h"
#include <thread>
#include <QApplication>
#include <QObject>
#include <QSerialPort>
#include <QModbusDevice>

void firstThread()
{

}

void secondThread()
{

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::thread t1(firstThread);
    std::thread t2(secondThread);


    return a.exec();
}
