#include "mainwindow.h"

#include <QApplication>
#include <QLoggingCategory>
#include <thread>

int main(int argc, char *argv[])
{
    // TODO uncomment this line before release
    // right now we always need it
    QLoggingCategory::setFilterRules(QStringLiteral("qt.modbus* = true"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::thread thread1(MainWindow readFunction);
    std::thread thread2(MainWindow readFunction);

    return a.exec();
}

