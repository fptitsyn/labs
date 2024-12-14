#include "modifydialog.h"
#include "ui_modifydialog.h"

ModifyDialog::ModifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query -> prepare("UPDATE albums SET name = :name,"
                     "creator = :creator, genre = :genre WHERE ID = :ID");
    query -> bindValue(":ID", tempId);
    query -> bindValue(":name", ui->lineEdit->text());
    query -> bindValue(":creator", ui->lineEdit_2->text());
    query -> bindValue(":genre", ui->lineEdit_3->text());
    if (query -> exec()) {
        close();
    }
}

void ModifyDialog::sendingId(int id)
{
    tempId = id;
    QSqlQuery *query = new QSqlQuery();
    query -> prepare("SELECT Name, Creator, Genre FROM albums "
                     "WHERE ID = :ID");
    query -> bindValue(":ID", id);
    QMessageBox *mess = new QMessageBox();
    mess -> setText(query->lastQuery());
    mess -> show();
    if (query -> exec()) {
        query->next();
        ui->lineEdit->setText(query->value(0).toString());
        ui->lineEdit_2->setText(query->value(1).toString());
        ui->lineEdit_3->setText(query->value(2).toString());
    }
}
