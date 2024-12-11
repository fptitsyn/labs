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


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_ID;
    temp_ID = ui->tableView->model()->data(ui->tableView->
                                           model()->index(index.row(),0)).toInt();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT Name, Creator, Genre FROM albums WHERE ID =:ID");
    query->bindValue(":ID",temp_ID);
    ui->idInput->setText(QString::number(temp_ID));
    if (query->exec()) {
        query->next();
        ui->nameInput->setText(query->value(0).toString());
        ui->creatorInput->setText(query->value(1).toString());
        ui->genreInput->setText(query->value(2).toString());
    }
}


void MainWindow::on_deletePushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM albums WHERE ID=:ID");
    query->bindValue(":ID", ui->idInput->text());
    QMessageBox *messageBox = new QMessageBox();
    if (query->exec()) {
        messageBox->setText("Запись удалена успешно");
        messageBox->show();

        ui->idInput->clear();
        ui->nameInput->clear();
        ui->creatorInput->clear();
        ui->genreInput->clear();

        MainWindow::on_updatePushButton_clicked();
    }
}

