#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui 
{ 
	class MainWindow; 
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_applyPeriodButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_HPP