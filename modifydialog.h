#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class ModifyDialog;
}

class ModifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyDialog(QWidget *parent = nullptr);
    ~ModifyDialog();

private slots:
    void on_pushButton_clicked();
    void sendingId(int);

private:
    Ui::ModifyDialog *ui;
    int tempId;
};

#endif // MODIFYDIALOG_H
