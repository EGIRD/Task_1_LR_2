#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include "date.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({"Дата", "След. день", "Пред. день", "Високосный год", "Номер недели", "До дня рождения", "Разница в днях"});
    ui->tableWidget->verticalHeader()->setVisible(true); // Скрываем нумерацию строк
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Растягиваем колонки
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->tableWidget->horizontalHeader()->setDefaultSectionSize(200); // Минимальная ширина колонок

    connect(ui->CurrentEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
    connect(ui->BirthdayEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTable()
{
    // Получаем текущую дату из QLineEdit
    QString currentDateStr = ui->CurrentEdit->text();
    Date currentDate = parseDate(currentDateStr);

    // Получаем дату дня рождения из QLineEdit
    QString birthdayDateStr = ui->BirthdayEdit->text();
    Date birthdayDate = parseDate(birthdayDateStr);

    // Очищаем таблицу перед обновлением
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        if (ui->tableWidget->item(1, col)) {
            delete ui->tableWidget->item(1, col); // Удаляем старые элементы
        }
    }

    // Добавляем значения во вторую строку
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(currentDate.toString())));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(currentDate.NextDay().toString())));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(currentDate.PreviousDate().toString())));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(currentDate.IsLeap() ? "Да" : "Нет"));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString::number(currentDate.WeekNumber())));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(QString::number(currentDate.DaysTillYourBirthday(birthdayDate))));
    ui->tableWidget->setItem(0, 6, new QTableWidgetItem(QString::number(currentDate.Duration(birthdayDate))));

    if (birthdayDateStr.isEmpty()) {
        // Если дата дня рождения не введена, выводим 0
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem("0"));
        ui->tableWidget->setItem(0, 6, new QTableWidgetItem("0"));
    } else {
        // Если дата дня рождения введена, вычисляем значения
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem(QString::number(currentDate.DaysTillYourBirthday(birthdayDate))));
        ui->tableWidget->setItem(0, 6, new QTableWidgetItem(QString::number(currentDate.Duration(birthdayDate))));
    }
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
