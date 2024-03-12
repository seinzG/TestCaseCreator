/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QWidget *page_4;
    QLabel *label_13;
    QLineEdit *ri_le;
    QLabel *label_8;
    QComboBox *valid_cb;
    QLabel *label_9;
    QTextEdit *note_le;
    QPushButton *pushButton;
    QComboBox *type_cb;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *author_line;
    QLabel *label_11;
    QTextEdit *er_le;
    QLabel *label_7;
    QLabel *label_10;
    QTextEdit *testDes_le;
    QComboBox *testSuite_cb;
    QLineEdit *func_le;
    QLabel *label;
    QComboBox *autoAvai_cb;
    QDateEdit *dateEdit;
    QLabel *label_2;
    QLabel *label_12;
    QLabel *label_4;
    QTextEdit *steps_le;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(454, 718);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        stackedWidget->addWidget(page_4);

        gridLayout->addWidget(stackedWidget, 3, 1, 1, 3);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 4, 0, 1, 1);

        ri_le = new QLineEdit(centralwidget);
        ri_le->setObjectName(QStringLiteral("ri_le"));

        gridLayout->addWidget(ri_le, 14, 0, 1, 4);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 10, 0, 1, 1);

        valid_cb = new QComboBox(centralwidget);
        valid_cb->setObjectName(QStringLiteral("valid_cb"));

        gridLayout->addWidget(valid_cb, 12, 1, 1, 1);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setScaledContents(false);

        gridLayout->addWidget(label_9, 12, 0, 1, 1);

        note_le = new QTextEdit(centralwidget);
        note_le->setObjectName(QStringLiteral("note_le"));

        gridLayout->addWidget(note_le, 16, 0, 1, 4);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 17, 2, 1, 1);

        type_cb = new QComboBox(centralwidget);
        type_cb->setObjectName(QStringLiteral("type_cb"));
        type_cb->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(type_cb, 1, 1, 1, 2);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        author_line = new QLineEdit(centralwidget);
        author_line->setObjectName(QStringLiteral("author_line"));

        gridLayout->addWidget(author_line, 0, 1, 1, 3);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 13, 0, 1, 1);

        er_le = new QTextEdit(centralwidget);
        er_le->setObjectName(QStringLiteral("er_le"));

        gridLayout->addWidget(er_le, 11, 0, 1, 4);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 8, 0, 1, 1);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setScaledContents(false);

        gridLayout->addWidget(label_10, 12, 2, 1, 1);

        testDes_le = new QTextEdit(centralwidget);
        testDes_le->setObjectName(QStringLiteral("testDes_le"));

        gridLayout->addWidget(testDes_le, 6, 0, 1, 4);

        testSuite_cb = new QComboBox(centralwidget);
        testSuite_cb->setObjectName(QStringLiteral("testSuite_cb"));

        gridLayout->addWidget(testSuite_cb, 2, 1, 1, 3);

        func_le = new QLineEdit(centralwidget);
        func_le->setObjectName(QStringLiteral("func_le"));

        gridLayout->addWidget(func_le, 4, 1, 1, 3);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setScaledContents(false);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        autoAvai_cb = new QComboBox(centralwidget);
        autoAvai_cb->setObjectName(QStringLiteral("autoAvai_cb"));

        gridLayout->addWidget(autoAvai_cb, 12, 3, 1, 1);

        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit, 1, 3, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setScaledContents(false);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 15, 0, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        steps_le = new QTextEdit(centralwidget);
        steps_le->setObjectName(QStringLiteral("steps_le"));

        gridLayout->addWidget(steps_le, 9, 0, 1, 4);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 17, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 454, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Functionality:", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Expected Result:", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Valid TCs:", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Cancel", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Test case ID:", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Test Description:", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Related Issue:", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Steps:", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Automation:", nullptr));
        label->setText(QApplication::translate("MainWindow", "Author:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Type:", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Note:", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Testsuite:", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
