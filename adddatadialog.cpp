#include "adddatadialog.h"
#include "ui_adddatadialog.h"

AddDataDialog::AddDataDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDataDialog)
{
    ui->setupUi(this);

    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT name FROM genres");
    while (queryCombo->next())
    {
        ui->comboBox->addItem(queryCombo->value(0).toString());
    }
}

AddDataDialog::~AddDataDialog()
{
    delete ui;
}

void AddDataDialog::on_addPushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("INSERT INTO albums (Name, Creator, ImagePath, catID)"
                   "VALUES(:name,:creator, :image, :genre)");
    query->bindValue(":name", ui->nameInput->text());
    query->bindValue(":creator", ui->creatorInput->text());
    query->bindValue(":genre", ui->comboBox->currentIndex()+1);
    query->bindValue(":image", img);
    QMessageBox *mess = new QMessageBox();
    if (!query->exec())
    {
        mess->setText("Запрос составлен неверно!");
    }
    else {
        mess -> setText("Альбом добавлен!");
        ui->nameInput->clear();
        ui->creatorInput->clear();
        ui->label->clear();
    }
    mess->show();
}


void AddDataDialog::on_toolButton_clicked()
{
    img = QFileDialog::getOpenFileName(0, "Открыть файл", img, "*.jpg");
    ui->label->setPixmap(img);
}

