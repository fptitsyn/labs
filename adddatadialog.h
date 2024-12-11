#ifndef ADDDATADIALOG_H
#define ADDDATADIALOG_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

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

private:
    Ui::AddDataDialog *ui;
};

#endif // ADDDATADIALOG_H
