#include "app_b_window.hpp"

#include <QMessageBox>

AppBWindow::AppBWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new AppBWindowUi)
{
    ui->setupUi(this);
}

AppBWindow::~AppBWindow()
{
    delete ui;
}

void AppBWindow::on_apply_period_button_clicked()
{
    QString period = ui->period_line_edit->text();
    // Здесь должна быть логика обновления периода в других приложениях
}