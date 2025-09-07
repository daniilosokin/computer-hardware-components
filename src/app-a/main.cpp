#include "main_window.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app_a(argc, argv);
    MainWindow window_app_a;
    window_app_a.show();
    return app_a.exec();
}