#ifndef APP_A_WINDOW_UI_H
#define APP_A_WINDOW_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class AppAWindowUi
{
public:
    QWidget* central_widget;
    QVBoxLayout* vertical_layout;
    QHBoxLayout* horizontal_layout;
    QLineEdit* period_line_edit;
    QPushButton* apply_period_button;
    QSpacerItem* horizontal_spacer_period;
    QPushButton* start_app_b_button;
    QPushButton* terminate_app_b_button;
    QSpacerItem* horizontal_spacer_app_b;
    QPushButton* start_app_c_button;
    QPushButton* terminate_app_c_button;
    QSpacerItem* horizontal_spacer_app_c;
    QPushButton* beep_button;

    void setupUi(QMainWindow* app_a_window)
    {
        if (app_a_window->objectName().isEmpty())
            app_a_window->setObjectName("app_a_window");

        app_a_window->resize(275, 260);

        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(app_a_window->sizePolicy().hasHeightForWidth());

        app_a_window->setSizePolicy(sizePolicy);
        app_a_window->setMinimumSize(QSize(275, 260));
        app_a_window->setMaximumSize(QSize(275, 260));

        central_widget = new QWidget(app_a_window);
        central_widget->setObjectName("central_widget");

        vertical_layout = new QVBoxLayout(central_widget);
        vertical_layout->setObjectName("vertical_layout");

        horizontal_layout = new QHBoxLayout();
        horizontal_layout->setObjectName("horizontal_layout");
        period_line_edit = new QLineEdit(central_widget);
        period_line_edit->setObjectName("period_line_edit");

        horizontal_layout->addWidget(period_line_edit);

        apply_period_button = new QPushButton(central_widget);
        apply_period_button->setObjectName("apply_period_button");

        horizontal_layout->addWidget(apply_period_button);


        vertical_layout->addLayout(horizontal_layout);

        horizontal_spacer_period = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        vertical_layout->addItem(horizontal_spacer_period);

        start_app_b_button = new QPushButton(central_widget);
        start_app_b_button->setObjectName("start_app_b_button");

        vertical_layout->addWidget(start_app_b_button);

        terminate_app_b_button = new QPushButton(central_widget);
        terminate_app_b_button->setObjectName("terminate_app_b_button");

        vertical_layout->addWidget(terminate_app_b_button);

        horizontal_spacer_app_b = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        vertical_layout->addItem(horizontal_spacer_app_b);

        start_app_c_button = new QPushButton(central_widget);
        start_app_c_button->setObjectName("start_app_c_button");

        vertical_layout->addWidget(start_app_c_button);

        terminate_app_c_button = new QPushButton(central_widget);
        terminate_app_c_button->setObjectName("terminate_app_c_button");

        vertical_layout->addWidget(terminate_app_c_button);

        horizontal_spacer_app_c = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        vertical_layout->addItem(horizontal_spacer_app_c);

        beep_button = new QPushButton(central_widget);
        beep_button->setObjectName("beep_button");

        vertical_layout->addWidget(beep_button);

        app_a_window->setCentralWidget(central_widget);

        retranslateUi(app_a_window);

        QMetaObject::connectSlotsByName(app_a_window);
    }

    void retranslateUi(QMainWindow* app_a_window)
    {
        app_a_window->setWindowTitle(QCoreApplication::translate("app_a_window", "A", nullptr));
        apply_period_button->setText(QCoreApplication::translate("app_a_window", "Apply period T", nullptr));
        start_app_b_button->setText(QCoreApplication::translate("app_a_window", "Start app B", nullptr));
        terminate_app_b_button->setText(QCoreApplication::translate("app_a_window", "Terminate app B", nullptr));
        start_app_c_button->setText(QCoreApplication::translate("app_a_window", "Start app C", nullptr));
        terminate_app_c_button->setText(QCoreApplication::translate("app_a_window", "Terminate app C", nullptr));
        beep_button->setText(QCoreApplication::translate("app_a_window", "Beep (OFF)", nullptr));
    }

};

#endif
