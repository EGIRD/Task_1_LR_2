#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "date.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"Свойства", "Значения"});

    connect(ui->CurrentEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
    connect(ui->BirthdayEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTable()
{
    QString currentDateStr = ui->CurrentEdit->text();
    Date currentDate = parseDate(currentDateStr);

    QString birthdayDateStr = ui->BirthdayEdit->text();
    Date birthdayDate = parseDate(birthdayDateStr);

    ui->tableWidget->setRowCount(0);

    addRow("След. день", QString::fromStdString(currentDate.NextDay().toString()));
    addRow("Пред. день", QString::fromStdString(currentDate.PreviousDate().toString()));
    addRow("Високосный год", currentDate.IsLeap() ? "Да" : "Нет");
    addRow("День недели", QString::number(currentDate.WeekNumber()));
    addRow("День рождения", QString::number(currentDate.DaysTillYourBirthday(birthdayDate)));
    addRow("Разница", QString::number(currentDate.Duration(birthdayDate)));

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

Date MainWindow::parseDate(const QString &dateStr)
{
    QStringList parts = dateStr.split('.');
    if (parts.size() == 3) {
        int day = parts[0].toInt();
        int month = parts[1].toInt();
        int year = parts[2].toInt();
        return Date(day, month, year);
    }
    return Date();
}

void MainWindow::addRow(const QString &property, const QString &value)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(property));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(value));
}
