#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    Ui::MainWindow *ui;
    QProcess *process_app_b;
    QProcess *process_app_c;
    bool beep_enabled;
    bool terminate_requested_app_b;
    bool terminate_requested_app_c;
};

#endif // MAIN_WINDOW_HPP