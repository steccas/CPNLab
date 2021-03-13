#include <iostream>
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    std::cout <<"Stecca si laurea, forse"<< std::endl;

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}