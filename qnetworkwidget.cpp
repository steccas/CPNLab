#include <iostream>
#include "qnetworkwidget.h"
#include "ui_qnetworkwidget.h"

QNetworkWidget::QNetworkWidget(QWidget *parent, QString id, QString name) :
    QFrame(parent),
    ui(new Ui::QNetworkWidget)
{
    ui->setupUi(this);
    this->id = id;
    this->name = name;
    idS = id.toStdString();
    uiMan = new manager();
    this->subnet = QString::fromStdString(uiMan->getNetSubnet(idS));
    ui->labelId->setText(this->id);
    ui->labelName->setText(this->name);
    ui->labelSubnet->setText(subnet);
    delete ui->labelSubnet;
    connect(ui->deleteNet, SIGNAL (released()), this, SLOT (deleteN()));
}

QNetworkWidget::~QNetworkWidget()
{
    delete ui;
}

void QNetworkWidget::deleteN() {
    string res = uiMan->getDocker()->delNet(idS);
    if(idS == res){
        emit refresh();
        return;
    }
    return;
}
