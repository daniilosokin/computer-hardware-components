#ifndef APP_B_WINDOW_UI_H
#define APP_B_WINDOW_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

class AppBWindowUi
{
public:
    QWidget* central_widget;
    QHBoxLayout* horizontal_layout;
    QLineEdit* period_line_edit;
    QPushButton* apply_period_button;

    void setupUi(QMainWindow* app_b_window)
    {
        if (app_b_window->objectName().isEmpty())
            app_b_window->setObjectName("app_b_window");

        app_b_window->resize(275, 50);

        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(app_b_window->sizePolicy().hasHeightForWidth());

        app_b_window->setSizePolicy(sizePolicy);
        app_b_window->setMinimumSize(QSize(275, 50));
        app_b_window->setMaximumSize(QSize(275, 50));

        central_widget = new QWidget(app_b_window);
        central_widget->setObjectName("central_widget");

        horizontal_layout = new QHBoxLayout(central_widget);
        horizontal_layout->setObjectName("horizontal_layout");

        period_line_edit = new QLineEdit(central_widget);
        period_line_edit->setObjectName("period_line_edit");

        horizontal_layout->addWidget(period_line_edit);

        apply_period_button = new QPushButton(central_widget);
        apply_period_button->setObjectName("apply_period_button");

        horizontal_layout->addWidget(apply_period_button);

        app_b_window->setCentralWidget(central_widget);

        retranslateUi(app_b_window);

        QMetaObject::connectSlotsByName(app_b_window);
    }

    void retranslateUi(QMainWindow* app_b_window)
    {
        app_b_window->setWindowTitle(QCoreApplication::translate("app_b_window", "B", nullptr));
        apply_period_button->setText(QCoreApplication::translate("app_b_window", "Apply period T", nullptr));
    }

};

#endif
