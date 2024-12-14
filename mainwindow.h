#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include "adddatadialog.h"
#include "ui_adddatadialog.h"
#include <QSqlQueryModel>
#include "modifydialog.h"
#include "ui_modifydialog.h"

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

    void on_editPushButton_clicked();

    void CustomMenuReq(QPoint);

    void DelRecAction();

    void ModRecAction();

signals:
    void sendId(int);

private:
    Ui::MainWindow *ui;
    ConnectionDialog *connectionDlg;
    AddDataDialog *addDlg;
    QSqlQueryModel *qmodel;
    ModifyDialog *modifyDialog;

    bool isDataDisplayed;
    int GlobId;
};
#endif // MAINWINDOW_H
