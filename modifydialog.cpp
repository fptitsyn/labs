#include "modifydialog.h"
#include "ui_modifydialog.h"

ModifyDialog::ModifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
    //ui -> label_3 -> setScaledContents(true);
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT name from genres");
    while (queryCombo -> next()) {
        ui->comboBox->addItem(queryCombo->value(0).toString());
    }
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query -> prepare("UPDATE albums SET name = :name,"
                     "creator = :creator, catID = :genre, ImagePath = :image WHERE ID = :ID");
    query -> bindValue(":ID", tempId);
    query -> bindValue(":name", ui->lineEdit->text());
    query -> bindValue(":creator", ui->lineEdit_2->text());
    query -> bindValue(":genre", ui->comboBox->currentIndex()+1);
    query -> bindValue(":image", img);
    if (query -> exec()) {
        close();
    }
}

void ModifyDialog::sendingId(int id)
{
    tempId = id;
    QSqlQuery *query = new QSqlQuery();
    query -> prepare("SELECT Name, Creator, ImagePath, catID FROM albums "
                     "WHERE ID = :ID");
    query -> bindValue(":ID", id);
    QMessageBox *mess = new QMessageBox();
//    mess -> setText(query->lastQuery());
//    mess -> show();
    if (query -> exec()) {
        query->next();
        ui->lineEdit->setText(query->value(0).toString());
        ui->lineEdit_2->setText(query->value(1).toString());
        ui->comboBox->setCurrentIndex(query->value(3).toInt()-1);
        ui -> label_4 -> setPixmap(query -> value(2).toString());
    }
}

void ModifyDialog::on_toolButton_clicked()
{
    img = QFileDialog::getOpenFileName(0, "Открыть файл", img, "*.jpg");
    ui->label_4->setPixmap(img);
}

