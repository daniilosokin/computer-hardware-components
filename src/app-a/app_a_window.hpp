#ifndef APP_A_WINDOW_HPP
#define APP_A_WINDOW_HPP

#include "app_a_window_ui.h"

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

class AppAWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppAWindow(QWidget *parent = nullptr);
    ~AppAWindow();

private slots:
    void on_apply_period_button_clicked();
    void on_start_app_b_button_clicked();
    void on_terminate_app_b_button_clicked();
    void on_start_app_c_button_clicked();
    void on_terminate_app_c_button_clicked();
    void on_beep_button_clicked();
    void handle_process_app_b_finished(int exit_code, QProcess::ExitStatus exit_status);
    void handle_process_app_c_finished(int exit_code, QProcess::ExitStatus exit_status);

private:
    AppAWindowUi* ui;
    QProcess *process_app_b;
    QProcess *process_app_c;
    bool beep_enabled;
    bool terminate_requested_app_b;
    bool terminate_requested_app_c;
};

#endif