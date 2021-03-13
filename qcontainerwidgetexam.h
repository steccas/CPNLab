#ifndef QCONTAINERWIDGETEXAM_H
#define QCONTAINERWIDGETEXAM_H

#include <QFrame>
#include "manager.h"

namespace Ui {
class QContainerWidgetExam;
}

class QContainerWidgetExam : public QFrame
{
    Q_OBJECT

public:
    explicit QContainerWidgetExam(QWidget *parent = 0, QString name = "name", QString id = "id", QString status = "status");
    ~QContainerWidgetExam();

public slots:
    void openTerminal();
    void onOff();
    void refreshR();
    void deleteC();
    void conNet();
    void refresh();

private:
    Ui::QContainerWidgetExam *ui;
    manager* uiMan;
    QString id;
    string idS;
    string route;
    QString status;

    void start();
    void stop();
    void setupBtns();

    void refreshStatus();
    void popNetList();

    void clearWidgets(QLayout *layout);
};

#endif // QCONTAINERWIDGETEXAM_H
