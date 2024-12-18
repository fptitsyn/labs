#ifndef PRINTGRAPH_H
#define PRINTGRAPH_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class PrintGraph;
}

class PrintGraph : public QDialog
{
    Q_OBJECT

public:
    explicit PrintGraph(QWidget *parent = nullptr);
    ~PrintGraph();

private:
    Ui::PrintGraph *ui;
};

#endif // PRINTGRAPH_H
