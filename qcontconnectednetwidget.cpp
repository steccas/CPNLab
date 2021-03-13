#include "qcontconnectednetwidget.h"
#include "ui_qcontconnectednetwidget.h"

QContConnectedNetWidget::QContConnectedNetWidget(QWidget *parent, QString id, QString name, QString contId) :
    QFrame(parent),
    ui(new Ui::QContConnectedNetWidget)
{
    ui->setupUi(this);
    this->id = id;
    this->name = name;
    idS = id.toStdString();
    this->contId = contId;
    uiMan = new manager();
    this->subnet = QString::fromStdString(uiMan->getNetSubnet(idS));
    ui->labelName->setText(this->name);
    ui->labelIf->setText(subnet);
    delete ui->labelIf;
    connect(ui->removeBtn, SIGNAL (released()), this, SLOT (disconnectN()));
}

QContConnectedNetWidget::~QContConnectedNetWidget()
{
    delete ui;
}

void QContConnectedNetWidget::disconnectN() {
    uiMan->getDocker()->disconnect(contId.toStdString(), idS);

    emit refresh();
}
