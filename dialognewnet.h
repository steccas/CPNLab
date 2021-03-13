#ifndef DIALOGNEWNET_H
#define DIALOGNEWNET_H

#include <QDialog>
#include "manager.h"

namespace Ui {
class dialogNewNet;
}

class dialogNewNet : public QDialog
{
    Q_OBJECT

public:
    explicit dialogNewNet(QWidget *parent = 0);
    ~dialogNewNet();

public slots:
    void apply();
    void abort();

signals:
    void refresh();

private:
    Ui::dialogNewNet *ui;
    manager* uiMan;
    void setupBtns();
};

#endif // DIALOGNEWNET_H
