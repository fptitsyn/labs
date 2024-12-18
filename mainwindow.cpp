#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableView,
            SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(CustomMenuReq(QPoint)));
    isDataDisplayed = false;
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
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT name FROM genres");
    while (queryCombo->next())
    {
        ui->comboBox->addItem(queryCombo->value(0).toString());
    }
    isDataDisplayed = true;
    qmodel = new QSqlQueryModel();
    qmodel->setQuery("SELECT a.name, b.name FROM Albums a inner join genres b on a.catID = b.ID");
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
    query->prepare("SELECT Name, Creator, catID, ImagePath FROM albums WHERE ID =:ID");
    query->bindValue(":ID",temp_ID);
    ui->idInput->setText(QString::number(temp_ID));
    if (query->exec()) {
        query->next();
        ui->nameInput->setText(query->value(0).toString());
        ui->creatorInput->setText(query->value(1).toString());
        ui->comboBox->setCurrentIndex(query->value(2).toInt()-1);
        img = query->value(3).toString();
        ui->imageLabel->setPixmap(img);
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
        ui->comboBox->clear();

        MainWindow::on_updatePushButton_clicked();
    }
}


void MainWindow::on_editPushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE albums SET name = :name, "
    "creator = :creator, catID = :genre, ImagePath = :image WHERE ID = :ID");
    query->bindValue(":ID",ui->idInput->text());
    query->bindValue(":name",ui->nameInput->text());
    query->bindValue(":creator",ui->creatorInput->text());
    query->bindValue(":genre",ui->comboBox->currentIndex()+1);
    query->bindValue(":image", img);
    query->exec();

//    ui->idInput->setText("");
//    ui->nameInput->setText("");
//    ui->creatorInput->setText("");
//    ui->genreInput->setText("");
//    ui->imageLabel->setText("");

    MainWindow::on_updatePushButton_clicked();
}


void MainWindow::CustomMenuReq(QPoint pos)
{
    if (isDataDisplayed) {
        QModelIndex index = ui->tableView->indexAt(pos);
        GlobId = ui->tableView->model()->data(ui->tableView->model()
                                              ->index(index.row(), 0)).toInt();
        QMenu *menu = new QMenu(this);
        QAction *ModRec = new QAction("Изменить...", this);
        QAction *DelRec = new QAction("Удалить", this);

        connect(ModRec, SIGNAL(triggered()), this, SLOT(ModRecAction()));
        connect(DelRec, SIGNAL(triggered()), this, SLOT(DelRecAction()));

        menu->addAction(ModRec);
        menu -> addAction(DelRec);

        menu -> popup(ui->tableView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::DelRecAction()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM albums WHERE ID = :ID");
    query -> bindValue(":ID", GlobId);
    query -> exec();
    MainWindow::on_updatePushButton_clicked();
}

void MainWindow::ModRecAction()
{
    modifyDialog = new ModifyDialog();
    connect(this, SIGNAL(sendId(int)), modifyDialog, SLOT(sendingId(int)));
    emit sendId(GlobId);
    modifyDialog -> show();
    disconnect(this, SIGNAL(sendId(int)), modifyDialog, SLOT(sendingId(int)));
}


void MainWindow::on_pushButton_clicked()
{
    printDialog = new PrintDialog();
    printDialog->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString str;
    str.append("<html><head></head><body><center>"
    +QString("Отчёт"));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("ID")+"</td>");
    str.append("<td>"+QString("Наименование")+"</td>");
    str.append("<td>"+QString("Категория")+"</td></tr>");
    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT * FROM albums");
    //query->next();
    while(query->next())
    {
        str.append("<tr>");
        str.append("<td>"
        +QString(query->value(0).toString())+"</td>");
        str.append("<td>"
        +QString(query->value(1).toString())+"</td>");
        str.append("<td>"
        +QString(query->value(2).toString())
        +"</td></tr>");
    }
    str.append("</table>");
    str.append("</center></body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString path = QFileDialog::getSaveFileName(NULL, "Сохранить", "Отчёт", "PDF(*.pdf)");
    if (path.isEmpty()) return;
    printer.setOutputFileName(path);
    QTextDocument doc;
    doc.setHtml(str);
    doc.print(&printer);
}

void MainWindow::on_toolButton_clicked()
{
    img = QFileDialog::getOpenFileName(0, "Открыть файл", img, "*.jpg");
    ui->imageLabel->setPixmap(img);
}


void MainWindow::on_action_2_triggered()
{
    printGraph = new PrintGraph();
    printGraph->show();
}

