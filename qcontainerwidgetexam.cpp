#include <QtCore/QProcess>
#include <QtWidgets/QMessageBox>
#include <iostream>
#include "qcontainerwidgetexam.h"
#include "ui_qcontainerwidgetexam.h"
#include "qcontconnectednetwidget.h"
#include "dialogaddnet.h"

QContainerWidgetExam::QContainerWidgetExam(QWidget *parent, QString name, QString id, QString status) :
    QFrame(parent),
    ui(new Ui::QContainerWidgetExam)
{
    ui->setupUi(this);
    uiMan = new manager();

    ui->ContIdLabel->setText(id);
    ui->ContNameLabel->setText(name);
    this->status = status;
    ui->ContStatusLabel->setText(status);
    idS = id.toStdString();
    this->id = id;
    popNetList();
    refresh();
    setupBtns();
}

QContainerWidgetExam::~QContainerWidgetExam()
{
    delete ui;
}

void QContainerWidgetExam::openTerminal() {
    QProcess* proc = new QProcess();
    proc->start("konsole -e \"bash -c 'docker attach " + id + "';bash");
    proc->waitForStarted();
}

void QContainerWidgetExam::start() {
    uiMan->getDocker()->start(idS);
    uiMan->getDocker()->routeDel(idS, "default");
    vector <string> iFaces = uiMan->readContIfs(idS);
    for (vector <string>::iterator it=iFaces.begin(); it != iFaces.end(); ++it){
        QString iFace = QString::fromStdString(*it);
        string eth = iFace.toStdString() + " 0.0.0.0";
        cout << eth;
        uiMan->getDocker()->ifconfig(idS, eth);
    }
    refresh();
}

void QContainerWidgetExam::stop() {
    uiMan->getDocker()->stop(idS);
    refresh();
}

void QContainerWidgetExam::refreshR() {
    route = uiMan->getDocker()->route(idS);
    ui->ContRTextBrowser->setText(QString::fromStdString(route));
}

void QContainerWidgetExam::deleteC() {
    stop();
    uiMan->getDocker()->delCont(idS);
    delete this;
}

void QContainerWidgetExam::setupBtns() {
    connect(ui->ContTermOpenBtn, SIGNAL (released()), this, SLOT (openTerminal()));
    connect(ui->ContDelBtn, SIGNAL (released()), this, SLOT (deleteC()));
    connect(ui->ContBtnRRefresh, SIGNAL (released()), this, SLOT (refresh()));
    connect(ui->onOffBtn, SIGNAL (released()), this, SLOT (onOff()));
    connect(ui->netConnectBtn, SIGNAL (released()), this, SLOT (conNet()));
}

void QContainerWidgetExam::refreshStatus() {
    string statusS = uiMan->getDocker()->getContStatus(idS);
    status = QString::fromStdString(statusS);
    ui->ContStatusLabel->setText(status);
}

void QContainerWidgetExam::refresh() {
    refreshR();
    refreshStatus();
    clearWidgets(ui->gridLayoutNet);
    popNetList();
}

void QContainerWidgetExam::onOff() {
    refreshStatus();
    cout << status.toStdString() << "\n";
    if(status == "exited") start();
    else if(status == "running") stop();
    else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Container status abnormal!");
        messageBox.setFixedSize(100,50);
    }
    refresh();
    return;
}

void QContainerWidgetExam::popNetList() {
    vector <string> nets = uiMan->readContainerNetworks(idS);

    for (vector <string>::iterator it=nets.begin(); it != nets.end(); ++it){
        QString id = QString::fromStdString(*it);
        string nameS = uiMan->getNetName(id.toStdString());
        nameS.erase(remove(nameS.begin(), nameS.end(), '\n'), nameS.end());
        QString name = QString::fromStdString(nameS);
        if(id != "" && name != "" && name != "none" && name != "bridge" && name != "host") {
            QContConnectedNetWidget* elem = new QContConnectedNetWidget(this, id, name, this->id);
            connect(elem, SIGNAL(refresh()), this, SLOT(refresh()));
            ui->gridLayoutNet->addWidget(elem);
        }
    }
    ui->gridLayoutNet->setAlignment(Qt::AlignTop);
}

void QContainerWidgetExam::conNet() {
    dialogAddNet* win = new dialogAddNet(this, id);
    connect(win, SIGNAL(refresh()), this, SLOT(refresh()));
    win->show();
}

void QContainerWidgetExam::clearWidgets(QLayout* layout) {
    if (! layout)
        return;
    while (auto item = layout->takeAt(0)) {
        delete item->widget();
        clearWidgets(item->layout());
    }
}