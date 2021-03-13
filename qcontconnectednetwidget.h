#ifndef QCONTCONNECTEDNETWIDGET_H
#define QCONTCONNECTEDNETWIDGET_H

#include <QFrame>
#include "manager.h"

namespace Ui {
class QContConnectedNetWidget;
}

class QContConnectedNetWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QContConnectedNetWidget(QWidget *parent = 0, QString id = "id", QString name = "name", QString contId = "idCont");
    ~QContConnectedNetWidget();

public slots:
    void disconnectN();

signals:
    void refresh();

private:
    Ui::QContConnectedNetWidget *ui;
    manager* uiMan;
    QString id, name, subnet, contId;
    string idS;
};

#endif // QCONTCONNECTEDNETWIDGET_H
