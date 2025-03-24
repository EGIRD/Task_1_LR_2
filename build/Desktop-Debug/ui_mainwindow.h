/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QLineEdit *CurrentEdit;
    QLabel *Currenlabel;
    QLineEdit *BirthdayEdit;
    QLabel *Birthdlabel;
    QPushButton *updateButton;
    QPushButton *openFileButton;
    QPushButton *addButton;
    QLabel *AnotherLabel;
    QLineEdit *AnotherEdit;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(846, 755);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 10, 841, 331));
        CurrentEdit = new QLineEdit(centralwidget);
        CurrentEdit->setObjectName("CurrentEdit");
        CurrentEdit->setGeometry(QRect(40, 390, 131, 31));
        Currenlabel = new QLabel(centralwidget);
        Currenlabel->setObjectName("Currenlabel");
        Currenlabel->setGeometry(QRect(40, 360, 141, 31));
        BirthdayEdit = new QLineEdit(centralwidget);
        BirthdayEdit->setObjectName("BirthdayEdit");
        BirthdayEdit->setGeometry(QRect(40, 450, 131, 31));
        Birthdlabel = new QLabel(centralwidget);
        Birthdlabel->setObjectName("Birthdlabel");
        Birthdlabel->setGeometry(QRect(40, 420, 141, 31));
        updateButton = new QPushButton(centralwidget);
        updateButton->setObjectName("updateButton");
        updateButton->setGeometry(QRect(650, 360, 171, 51));
        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName("openFileButton");
        openFileButton->setGeometry(QRect(650, 420, 171, 51));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(650, 480, 171, 51));
        AnotherLabel = new QLabel(centralwidget);
        AnotherLabel->setObjectName("AnotherLabel");
        AnotherLabel->setGeometry(QRect(40, 480, 141, 31));
        AnotherEdit = new QLineEdit(centralwidget);
        AnotherEdit->setObjectName("AnotherEdit");
        AnotherEdit->setGeometry(QRect(40, 510, 131, 31));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(650, 540, 171, 51));
        editButton = new QPushButton(centralwidget);
        editButton->setObjectName("editButton");
        editButton->setGeometry(QRect(650, 600, 171, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 846, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Currenlabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \320\264\320\260\321\202\320\260", nullptr));
        Birthdlabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\275\321\214 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        updateButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        openFileButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        AnotherLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\270\320\267\320\262\320\276\320\273\321\214\320\275\320\260\321\217 \320\264\320\260\321\202\320\260", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
