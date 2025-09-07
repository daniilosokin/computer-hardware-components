#ifndef APP_C_WINDOW_UI_H
#define APP_C_WINDOW_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

class AppCWindowUi
{
public:
    QWidget* central_widget;
    QHBoxLayout* horizontal_layout;
    QLineEdit* period_line_edit;
    QPushButton* apply_period_button;

    void setupUi(QMainWindow* app_c_window)
    {
        if (app_c_window->objectName().isEmpty())
            app_c_window->setObjectName("app_c_window");

        app_c_window->resize(275, 50);

        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(app_c_window->sizePolicy().hasHeightForWidth());

        app_c_window->setSizePolicy(sizePolicy);
        app_c_window->setMinimumSize(QSize(275, 50));
        app_c_window->setMaximumSize(QSize(275, 50));

        central_widget = new QWidget(app_c_window);
        central_widget->setObjectName("central_widget");

        horizontal_layout = new QHBoxLayout(central_widget);
        horizontal_layout->setObjectName("horizontal_layout");

        period_line_edit = new QLineEdit(central_widget);
        period_line_edit->setObjectName("period_line_edit");

        horizontal_layout->addWidget(period_line_edit);

        apply_period_button = new QPushButton(central_widget);
        apply_period_button->setObjectName("apply_period_button");

        horizontal_layout->addWidget(apply_period_button);

        app_c_window->setCentralWidget(central_widget);

        retranslateUi(app_c_window);

        QMetaObject::connectSlotsByName(app_c_window);
    }

    void retranslateUi(QMainWindow* app_c_window)
    {
        app_c_window->setWindowTitle(QCoreApplication::translate("app_c_window", "C", nullptr));
        apply_period_button->setText(QCoreApplication::translate("app_c_window", "Apply period T", nullptr));
    }

};

#endif
