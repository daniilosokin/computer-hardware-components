#include "main_window.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication b(argc, argv);
    MainWindow w;
    w.show();
    return b.exec();
}