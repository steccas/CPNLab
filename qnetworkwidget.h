#ifndef QNETWORKWIDGET_H
#define QNETWORKWIDGET_H

#include <QFrame>
#include <Qt>
#include <QFlags>
#include "manager.h"

namespace Ui {
class QNetworkWidget;
}

class QNetworkWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QNetworkWidget(QWidget *parent = 0, QString id = "id", QString name = "name");
    ~QNetworkWidget();

public slots:
    void deleteN();

signals:
    void refresh();

private:
    Ui::QNetworkWidget *ui;
    manager* uiMan;
    QString id, name, subnet;
    string idS;
};

#endif // QNETWORKWIDGET_H
