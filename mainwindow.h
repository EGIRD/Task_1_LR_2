#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidgetItem>
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

private:
    Ui::MainWindow *ui;
    Date parseDate(const QString &dateStr);
    void addRow(const QString &property, const QString &value);
};
#endif // MAINWINDOW_H
