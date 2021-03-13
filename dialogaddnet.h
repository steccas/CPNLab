#ifndef DIALOGADDNET_H
#define DIALOGADDNET_H

#include <QDialog>
#include "manager.h"

namespace Ui {
class dialogAddNet;
}

class dialogAddNet : public QDialog
{
    Q_OBJECT

public:
    explicit dialogAddNet(QWidget *parent = 0, QString contId = "contId");
    ~dialogAddNet();

public slots:
    void apply();
    void abort();

signals:
    void refresh();

private:
    Ui::dialogAddNet *ui;
    manager* uiMan;
    void popComboBox();

    void setupBtns();

    QString contId;
};

#endif // DIALOGADDNET_H
