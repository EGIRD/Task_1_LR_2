#include "mainwindow.h"
#include "ui_mainwindow.h"
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

    connect(ui->CurrentEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
    connect(ui->BirthdayEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::updateTable);
    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::on_openFileButton_clicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addDateButton_clicked);
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

    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        if (ui->tableWidget->item(1, col)) {
            delete ui->tableWidget->item(1, col); // Удаляем старые элементы
        }
    }

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(currentDate.toString())));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(currentDate.NextDay().toString())));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(currentDate.PreviousDate().toString())));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(currentDate.IsLeap() ? "Да" : "Нет"));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString::number(currentDate.WeekNumber())));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(QString::number(currentDate.DaysTillYourBirthday(birthdayDate))));
    ui->tableWidget->setItem(0, 6, new QTableWidgetItem(QString::number(currentDate.Duration(birthdayDate))));

    if (birthdayDateStr.isEmpty()) {
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem("0"));
        ui->tableWidget->setItem(0, 6, new QTableWidgetItem("0"));
    } else {
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

void MainWindow::on_openFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt)");
    if (!filePath.isEmpty()) {
        QVector<Date> dates = readDatesFromFile(filePath);
        displayDates(dates);
    }
}

void MainWindow::on_addDateButton_clicked()
{
    QString dateStr = ui->CurrentEdit->text();
    QStringList parts = dateStr.split('.');
    if (parts.size() == 3) {
        int day = parts[0].toInt();
        int month = parts[1].toInt();
        int year = parts[2].toInt();
        Date newDate(day, month, year);

        // Добавляем дату в файл
        QFile file("date.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << dateStr << "\n";
            file.close();
        }
        // Обновляем таблицу
        QVector<Date> dates = readDatesFromFile("date.txt");
        displayDates(dates);
    }
}

QVector<Date> MainWindow::readDatesFromFile(const QString& filePath) {
    QVector<Date> dates;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            Date date = parseDate(line);
            if (!date.toString().empty()) {
                dates.append(date);
            }
        }
        file.close();
    }
    return dates;
}

void MainWindow::displayDates(const QVector<Date>& dates) {
    ui->tableWidget->setRowCount(dates.size());
    for (int i = 0; i < dates.size(); ++i) {
        Date currentDate = dates[i];
        Date nextDay = currentDate.NextDay();
        int difference = (i < dates.size() - 1) ? currentDate.Duration(dates[i + 1]) : 0;

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(currentDate.toString())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(nextDay.toString())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(currentDate.PreviousDate().toString())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(currentDate.IsLeap() ? "Да" : "Нет"));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(currentDate.WeekNumber())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem("0")); // По умолчанию
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(difference)));
    }
}
