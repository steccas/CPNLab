#ifndef QCONTAINERWIDGET_H
#define QCONTAINERWIDGET_H

#include <QWidget>
#include "manager.h"

namespace Ui {
class QContainerWidget;
}

class QContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QContainerWidget(QWidget *parent = 0, QString name = "name", QString id = "id", QString status = "status");
    ~QContainerWidget();

public slots:
    void openTerminal();
    void start();
    void stop();
    void add();
    void refreshR();
    void deleteC();
    void deleteR();

private:
    Ui::QContainerWidget *ui;
    manager* uiMan;
    QString id;
    string idS;
    string route;
    QString status;

    void setupBtns();
    void refresh();
    void refreshStatus();
};

#endif // QCONTAINERWIDGET_H
