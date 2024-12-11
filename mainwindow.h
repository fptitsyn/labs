#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include "adddatadialog.h"
#include "ui_adddatadialog.h"
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_updatePushButton_clicked();

    void on_addAction_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_deletePushButton_clicked();

private:
    Ui::MainWindow *ui;
    ConnectionDialog *connectionDlg;
    AddDataDialog *addDlg;
    QSqlQueryModel *qmodel;
};
#endif // MAINWINDOW_H
