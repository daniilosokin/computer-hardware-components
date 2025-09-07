#ifndef APP_B_WINDOW_HPP
#define APP_B_WINDOW_HPP

#include "app_b_window_ui.h"

#include <QMainWindow>

class AppBWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppBWindow(QWidget *parent = nullptr);
    ~AppBWindow();

private slots:
    void on_apply_period_button_clicked();

private:
    AppBWindowUi* ui;
};

#endif