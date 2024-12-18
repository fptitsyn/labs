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
#include "printdialog.h"
#include "ui_printdialog.h"
#include "printgraph.h"
#include "ui_printgraph.h"

#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

    void on_action_2_triggered();

signals:
    void sendId(int);

private:
    Ui::MainWindow *ui;
    ConnectionDialog *connectionDlg;
    AddDataDialog *addDlg;
    QSqlQueryModel *qmodel;
    ModifyDialog *modifyDialog;
    PrintDialog *printDialog;

    QString img;

    PrintGraph *printGraph;

    bool isDataDisplayed;
    int GlobId;
};
#endif // MAINWINDOW_H
