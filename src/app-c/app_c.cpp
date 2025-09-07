#include "app_c_window.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app_c(argc, argv);
    AppAWindow window_app_c;
    window_app_c.show();
    return app_c.exec();
}