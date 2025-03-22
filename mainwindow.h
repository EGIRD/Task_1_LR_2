#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include "date.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateTable();
    void on_openFileButton_clicked();
    void on_addDateButton_clicked();
    void on_deleteDateButton_clicked();
    void on_editDateButton_clicked();

private:
    Ui::MainWindow *ui;
    Date parseDate(const QString &dateStr);
    QString currentFilePath;
    void addRow(const QString &property, const QString &value);
    void clearInputs();
    QVector<Date> readDatesFromFile(const QString &filePath); // Чтение дат из файла
    void displayDates(const QVector<Date>& dates);
    bool validateInput(const QString &input);
    bool validateInputs();

};
#endif // MAINWINDOW_H
