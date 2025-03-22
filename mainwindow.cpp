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
    ui->tableWidget->setShowGrid(false);

    for(int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        ui->tableWidget->setColumnWidth(col,150);
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setVisible(true);

    connect(ui->CurrentEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
    connect(ui->BirthdayEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
    connect(ui->AnotherEdit, &QLineEdit::returnPressed, this, &MainWindow::updateTable);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::updateTable);
    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::on_openFileButton_clicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addDateButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow:: validateInput(const QString &input) {
    QRegularExpression regExp("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[0-2])\\.\\d{4}$");
    return regExp.match(input).hasMatch();
}

bool MainWindow::validateInputs() {
    QString currentDateStr = ui->CurrentEdit->text();
    QString birthdayDateStr = ui->BirthdayEdit->text();
    QString anotherDateStr = ui->AnotherEdit->text();

    if (currentDateStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле текущей даты не может быть пустым!");
        return false;
    }
    if (!validateInput(currentDateStr)) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат текущей даты!");
        return false;
    }

    if (!birthdayDateStr.isEmpty() && !validateInput(birthdayDateStr)) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат даты рождения!");
        return false;
    }

    if (!anotherDateStr.isEmpty() && !validateInput(anotherDateStr)) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат произвольной даты!");
        return false;
    }

    return true;
}

void MainWindow::updateTable()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(1);

    static bool isUpdating = false; // Флаг для предотвращения повторного вызова
    if (isUpdating) return;
    isUpdating = true;

    if (!validateInputs()) {
        isUpdating = false;
        return;
    }

    QString currentDateStr = ui->CurrentEdit->text();
    Date currentDate = parseDate(currentDateStr);

    if(currentDate.toString().empty()) {
        return;
    }

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(currentDate.toString())));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(currentDate.NextDay().toString())));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(currentDate.PreviousDate().toString())));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(currentDate.IsLeap() ? "Да" : "Нет"));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString::number(currentDate.WeekNumber())));

    QString birthdayDateStr = ui->BirthdayEdit->text();
    Date birthdayDate = parseDate(birthdayDateStr);



    if (birthdayDateStr.isEmpty() || birthdayDate.toString().empty()) {
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem("0"));
    } else {
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem(QString::number(currentDate.DaysTillYourBirthday(birthdayDate))));
    }

    QString anotherDateStr = ui->AnotherEdit->text();
    Date anotherDate = parseDate(anotherDateStr);

    if (!anotherDateStr.isEmpty() && !anotherDate.toString().empty()) {
        int duration = currentDate.Duration(anotherDate);
        ui->tableWidget->setItem(0, 6, new QTableWidgetItem(QString::number(duration)));
    } else {
        ui->tableWidget->setItem(0, 6, new QTableWidgetItem("0"));
    }

    isUpdating = false;
    ui->tableWidget->update();
}

Date MainWindow::parseDate(const QString &dateStr)
{
    QStringList parts = dateStr.split('.');
    if (parts.size() == 3) {
        int day = parts[0].toInt();
        int month = parts[1].toInt();
        int year = parts[2].toInt();

        QDate date(year, month, day);
        if (date.isValid()) {
            return Date(day, month, year);
        }
    }
    return Date();
}

void MainWindow::on_openFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt)");
    if (!filePath.isEmpty()) {
        currentFilePath = filePath; // Сохраняем путь к файлу
        QVector<Date> dates = readDatesFromFile(filePath);
        displayDates(dates);
    }
}

void MainWindow::on_addDateButton_clicked()
{
    if (currentFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала откройте файл!");
        return;
    }

    QString dateStr = ui->CurrentEdit->text().trimmed();
    if (dateStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите дату!");
        return;
    }

    Date newDate = parseDate(dateStr);
    if (newDate.toString().empty()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат даты! Введите дату в формате ДД.ММ.ГГГГ.");
        return;
    }

    // Открываем файл для добавления данных
    QFile file(currentFilePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
        return;
    }

    QTextStream out(&file);
    out << dateStr << "\n";
    file.close();

    // Обновляем таблицу
    QVector<Date> dates = readDatesFromFile(currentFilePath);
    displayDates(dates);
}

QVector<Date> MainWindow::readDatesFromFile(const QString& filePath) {
    QVector<Date> dates;
    QFile file(filePath);

    if (!file.exists()) {
        QMessageBox::warning(this, "Ошибка", "Файл не найден!");
        return dates;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл!");
        return dates;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        Date date = parseDate(line);
        if (!date.toString().empty()) {
            dates.append(date);
        } else {
            QMessageBox::warning(this, "Ошибка", "Некорректный формат даты в файле: " + line);
        }
    }

    file.close();
    return dates;
}

void MainWindow::on_editDateButton_clicked()
{
    // Получаем выбранную строку в таблице
    int row = ui->tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите дату для редактирования!");
        return;
    }

    // Получаем новую дату из поля ввода
    QString newDateStr = ui->CurrentEdit->text().trimmed();
    Date newDate = parseDate(newDateStr);
    if (newDate.toString().empty()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат даты!");
        return;
    }

    // Читаем все даты из файла
    QVector<Date> dates = readDatesFromFile("dates.txt");

    // Заменяем выбранную дату на новую
    if (row < dates.size()) {
        dates[row] = newDate;
    }

    // Перезаписываем файл
    QFile file("dates.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
        return;
    }

    QTextStream out(&file);
    for (const Date& date : dates) {
        out << QString::fromStdString(date.toString()) << "\n";
    }
    file.close();

    // Обновляем таблицу
    displayDates(dates);
}

void MainWindow::on_deleteDateButton_clicked()
{
    if (currentFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала откройте файл!");
        return;
    }

    int row = ui->tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите дату для удаления!");
        return;
    }

    QVector<Date> dates = readDatesFromFile(currentFilePath);
    if (row < dates.size()) {
        dates.remove(row);
    }

    // Перезаписываем файл
    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
        return;
    }

    QTextStream out(&file);
    for (const Date& date : dates) {
        out << QString::fromStdString(date.toString()) << "\n";
    }
    file.close();

    // Обновляем таблицу
    displayDates(dates);
}

void MainWindow::displayDates(const QVector<Date>& dates) {
    ui->tableWidget->setRowCount(dates.size());

    // Получаем текущую дату из поля ввода
    QString currentDateStr = ui->CurrentEdit->text();
    Date currentDate = parseDate(currentDateStr);


    // Если поле пустое или дата некорректна, используем системную дату
    if (currentDate.toString().empty()) {
        QDate sysDate = QDate::currentDate();
        currentDate = Date(sysDate.day(), sysDate.month(), sysDate.year());
    }

    // Отображаем даты из файла
    for (int i = 0; i < dates.size(); ++i) {
        Date fileDate = dates[i];
        Date nextDay = fileDate.NextDay();
        int difference = currentDate.Duration(fileDate); // Разница с текущей датой

        // Заполняем таблицу
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(fileDate.toString())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(nextDay.toString())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(fileDate.PreviousDate().toString())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(fileDate.IsLeap() ? "Да" : "Нет"));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(fileDate.WeekNumber())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(currentDate.DaysTillYourBirthday(fileDate))));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(difference)));
    }
}
