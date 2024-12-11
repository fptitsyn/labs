#include "adddatadialog.h"
#include "ui_adddatadialog.h"

AddDataDialog::AddDataDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDataDialog)
{
    ui->setupUi(this);
}

AddDataDialog::~AddDataDialog()
{
    delete ui;
}

void AddDataDialog::on_addPushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("INSERT INTO albums (Name, Creator, Genre)"
                   "VALUES(:name,:creator,:genre)");
    query->bindValue(":name", ui->nameInput->text());
    query->bindValue(":creator", ui->creatorInput->text());
    query->bindValue(":genre", ui->genreInput->text());
    QMessageBox *mess = new QMessageBox();
    if (!query->exec())
    {
        mess->setText("Запрос составлен неверно!");

    }
    else {
        mess -> setText("Альбом добавлен!");
        ui->nameInput->clear();
        ui->creatorInput->clear();
        ui->genreInput->clear();
    }
    mess->show();
}

