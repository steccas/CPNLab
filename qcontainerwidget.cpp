#include <QtCore/QProcess>
#include "qcontainerwidget.h"
#include "ui_qcontainerwidget.h"

QContainerWidget::QContainerWidget(QWidget *parent, QString name, QString id, QString status) :
    QWidget(parent),
    ui(new Ui::QContainerWidget)
{
    ui->setupUi(this);
    uiMan = new manager();

    ui->ContIdLabel->setText(id);
    ui->ContNameLabel->setText(name);
    this->status = status;
    ui->ContStatusLabel->setText(status);
    idS = id.toStdString();
    this->id = id;
    refresh();
    setupBtns();
}

QContainerWidget::~QContainerWidget()
{
    delete ui;
}

void QContainerWidget::openTerminal() {
    QProcess* proc = new QProcess();
    proc->start("konsole -e \"bash -c 'docker attach " + id + "';bash");
    proc->waitForStarted();
}

void QContainerWidget::start() {
    uiMan->getDocker()->start(idS);
    refresh();
}

void QContainerWidget::stop() {
    uiMan->getDocker()->stop(idS);
    refresh();
}

void QContainerWidget::add() {
    //apri form add e poi routeAdd();
    refresh();
}

void QContainerWidget::refreshR() {
    route = uiMan->getDocker()->route(idS);
    ui->ContRTextBrowser->setText(QString::fromStdString(route));
}

void QContainerWidget::deleteC() {
    stop();
    uiMan->getDocker()->delCont(idS);
    delete this;
}

void QContainerWidget::deleteR() {
    //apri form del e poi routeDel();
    refreshR();
}

void QContainerWidget::setupBtns() {
    connect(ui->ContTermOpenBtn, SIGNAL (released()), this, SLOT (openTerminal()));
    connect(ui->ContStartBtn, SIGNAL (released()), this, SLOT (start()));
    connect(ui->ContStopBtn, SIGNAL (released()), this, SLOT (stop()));
    connect(ui->ContDelBtn, SIGNAL (released()), this, SLOT (deleteC()));
    connect(ui->ContBtnRAdd, SIGNAL (released()), this, SLOT (add()));
    connect(ui->ContBtnRDel, SIGNAL (released()), this, SLOT (deleteR()));
    connect(ui->ContBtnRRefresh, SIGNAL (released()), this, SLOT (refreshR()));
}

void QContainerWidget::refreshStatus() {
    status = QString::fromStdString(uiMan->getDocker()->getContStatus(idS));
    ui->ContStatusLabel->setText(status);
}

void QContainerWidget::refresh() {
    refreshR();
    refreshStatus();
}


