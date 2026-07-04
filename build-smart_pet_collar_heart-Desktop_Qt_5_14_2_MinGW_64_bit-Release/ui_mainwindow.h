/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_state;
    QVBoxLayout *verticalLayout;
    QLabel *label_temp;
    QHBoxLayout *horizontalLayout;
    QLabel *label_step_num;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_heart;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_spo2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_lon;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_lat;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QSpinBox *spinBox_temp_thre;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QSpinBox *spinBox_xinlv_thre;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QSpinBox *spinBox_spo2_thre;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pbtn_clear;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pbtn_start_alarm;
    QPushButton *pbtn_close_alarm;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(360, 634);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(36);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_state = new QLabel(centralwidget);
        label_state->setObjectName(QString::fromUtf8("label_state"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(22);
        label_state->setFont(font1);
        label_state->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_state);


        verticalLayout_5->addLayout(verticalLayout_6);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_temp = new QLabel(centralwidget);
        label_temp->setObjectName(QString::fromUtf8("label_temp"));
        label_temp->setFont(font1);
        label_temp->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_temp);


        verticalLayout_5->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_step_num = new QLabel(centralwidget);
        label_step_num->setObjectName(QString::fromUtf8("label_step_num"));
        label_step_num->setFont(font1);
        label_step_num->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_step_num);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_heart = new QLabel(centralwidget);
        label_heart->setObjectName(QString::fromUtf8("label_heart"));
        label_heart->setFont(font1);
        label_heart->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_heart);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_spo2 = new QLabel(centralwidget);
        label_spo2->setObjectName(QString::fromUtf8("label_spo2"));
        label_spo2->setFont(font1);
        label_spo2->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_spo2);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_lon = new QLabel(centralwidget);
        label_lon->setObjectName(QString::fromUtf8("label_lon"));
        label_lon->setFont(font1);
        label_lon->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_lon);


        verticalLayout_5->addLayout(horizontalLayout_8);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_lat = new QLabel(centralwidget);
        label_lat->setObjectName(QString::fromUtf8("label_lat"));
        label_lat->setFont(font1);
        label_lat->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_lat);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 300, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_2);

        spinBox_temp_thre = new QSpinBox(centralwidget);
        spinBox_temp_thre->setObjectName(QString::fromUtf8("spinBox_temp_thre"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox_temp_thre->sizePolicy().hasHeightForWidth());
        spinBox_temp_thre->setSizePolicy(sizePolicy1);
        spinBox_temp_thre->setFont(font1);
        spinBox_temp_thre->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_temp_thre->setValue(40);

        horizontalLayout_6->addWidget(spinBox_temp_thre);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout_6->addWidget(label_3);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_7->addWidget(pushButton);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_5);

        spinBox_xinlv_thre = new QSpinBox(centralwidget);
        spinBox_xinlv_thre->setObjectName(QString::fromUtf8("spinBox_xinlv_thre"));
        spinBox_xinlv_thre->setFont(font1);
        spinBox_xinlv_thre->setMaximum(200);
        spinBox_xinlv_thre->setValue(130);

        horizontalLayout_10->addWidget(spinBox_xinlv_thre);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_10->addWidget(label_4);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_9->addWidget(pushButton_2);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_7);

        spinBox_spo2_thre = new QSpinBox(centralwidget);
        spinBox_spo2_thre->setObjectName(QString::fromUtf8("spinBox_spo2_thre"));
        spinBox_spo2_thre->setFont(font1);
        spinBox_spo2_thre->setValue(90);

        horizontalLayout_11->addWidget(spinBox_spo2_thre);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_11->addWidget(label_6);


        verticalLayout_5->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_12->addWidget(pushButton_3);


        verticalLayout_5->addLayout(horizontalLayout_12);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pbtn_clear = new QPushButton(centralwidget);
        pbtn_clear->setObjectName(QString::fromUtf8("pbtn_clear"));

        horizontalLayout_3->addWidget(pbtn_clear);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pbtn_start_alarm = new QPushButton(centralwidget);
        pbtn_start_alarm->setObjectName(QString::fromUtf8("pbtn_start_alarm"));

        horizontalLayout_4->addWidget(pbtn_start_alarm);

        pbtn_close_alarm = new QPushButton(centralwidget);
        pbtn_close_alarm->setObjectName(QString::fromUtf8("pbtn_close_alarm"));

        horizontalLayout_4->addWidget(pbtn_close_alarm);


        verticalLayout_5->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\256\240\347\211\251\351\241\271\345\234\210\347\233\221\346\216\247\345\271\263\345\217\260", nullptr));
        label_state->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\347\246\273\347\272\277", nullptr));
        label_temp->setText(QCoreApplication::translate("MainWindow", "\344\275\223\346\270\251", nullptr));
        label_step_num->setText(QCoreApplication::translate("MainWindow", "\346\255\245\346\225\260", nullptr));
        label_heart->setText(QCoreApplication::translate("MainWindow", "\345\277\203\347\216\207", nullptr));
        label_spo2->setText(QCoreApplication::translate("MainWindow", "\350\241\200\346\260\247", nullptr));
        label_lon->setText(QCoreApplication::translate("MainWindow", "\347\273\217\347\272\254\345\272\246", nullptr));
        label_lat->setText(QCoreApplication::translate("MainWindow", "\347\273\217\347\272\254\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\344\275\223\346\270\251\351\230\210\345\200\274:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\272\246", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\344\275\223\346\270\251\351\230\210\345\200\274", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\277\203\347\216\207\351\230\210\345\200\274:", nullptr));
        label_4->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\345\277\203\347\216\207\351\230\210\345\200\274", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\241\200\346\260\247\351\230\210\345\200\274:", nullptr));
        label_6->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\350\241\200\346\260\247\351\230\210\345\200\274", nullptr));
        pbtn_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\346\255\245\346\225\260", nullptr));
        pbtn_start_alarm->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257\346\212\245\350\255\246", nullptr));
        pbtn_close_alarm->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\346\212\245\350\255\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
