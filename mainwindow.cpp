#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    connectionDlg = new ConnectionDialog();
    connectionDlg->show();
}


void MainWindow::on_updatePushButton_clicked()
{
    qmodel = new QSqlTableModel();
    qmodel->setQuery("SELECT * FROM Albums");
    ui->tableView->setModel(qmodel);
}


void MainWindow::on_addAction_triggered()
{
    addDlg = new AddDataDialog();
    addDlg->show();
}

