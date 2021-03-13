#ifndef DIALOGNEWCONT_H
#define DIALOGNEWCONT_H

#include <QDialog>
#include <QMainWindow>
#include <vector>
#include <string>
#include "manager.h"
#include "mainwindow.h"

namespace Ui {
class dialogNewCont;
}

class dialogNewCont : public QDialog
{
    Q_OBJECT

public:
    explicit dialogNewCont(QWidget *parent = 0);
    ~dialogNewCont();

public slots:
    void apply();
    void abort();

signals:
    void refresh();

private:
    Ui::dialogNewCont *ui;
    manager* uiMan;
    void popComboBox();

    void setupBtns();
};

#endif // DIALOGNEWCONT_H
