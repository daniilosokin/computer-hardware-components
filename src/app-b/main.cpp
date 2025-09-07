#include "main_window.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app_b(argc, argv);
    MainWindow window_app_b;
    window_app_b.show();
    return app_b.exec();
}