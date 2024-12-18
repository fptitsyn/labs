#ifndef ADDDATADIALOG_H
#define ADDDATADIALOG_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class AddDataDialog;
}

class AddDataDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddDataDialog(QWidget *parent = nullptr);
    ~AddDataDialog();

private slots:
    void on_addPushButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::AddDataDialog *ui;

    QString img;
};

#endif // ADDDATADIALOG_H
