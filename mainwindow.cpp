#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <string>
#include <QtWidgets/QListWidgetItem>
#include <iostream>
#include "manager.h"
#include "qnetworkwidget.h"
#include "dialognewnet.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("CPNLab"));

    uiMan = new manager();
    //uiMan->getDocker()->startDocker();

    p = parent;

    bool service = uiMan->dockerService();

    if (!service) delete this;

    popContList();
    popNetList();

    setUpBtns();

    setWindowIcon(QIcon(":./resources/logoApp.png"));
}

void MainWindow::popContList() {
    vector <string> conts = uiMan->readContainersId();
    vector <string> status = uiMan->readContainersStatus();
    vector <string> names = uiMan->readContainersNames();
    vector <string>::iterator it2=status.begin();
    vector <string>::iterator it3=names.begin();

    for (vector <string>::iterator it=conts.begin(); it != conts.end(); ++it){
        QString id = QString::fromStdString(*it);
        QString st = QString::fromStdString(*it2);
        QString name = QString::fromStdString(*it3);
        if(id != "") {
            QContainerWidgetExam* elem = new QContainerWidgetExam(this, name, id, st);
            ui->gridLayoutCont->addWidget(elem);
            //cout << *it << endl;
        }
        ++it2;
        ++it3;
    }
}

void MainWindow::popNetList() {
    vector <string> nets = uiMan->readNetworksId();
    vector <string> names = uiMan->readNetworksNames();
    vector <string>::iterator it2=names.begin();

    for (vector <string>::iterator it=nets.begin(); it != nets.end(); ++it){
        QString id = QString::fromStdString(*it);
        QString name = QString::fromStdString(*it2);
        if(id != "" && name != "" && name != "none" && name != "bridge" && name != "host") {
            QNetworkWidget* elem = new QNetworkWidget(this, id, name);
            connect(elem, SIGNAL(refresh()), this, SLOT(refresh()));
            ui->gridLayoutNet->addWidget(elem);
        }
        ++it2;
    }
    ui->gridLayoutNet->setAlignment(Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete p;
    delete uiMan;
    delete ui;
}

void MainWindow::addCont() {
    dialogNewCont* win = new dialogNewCont(this);
    connect(win, SIGNAL(refresh()), this, SLOT(refresh()));
    win->show();
    //clearWidgets(ui->gridLayoutCont);
}

void MainWindow::addNet() {
    dialogNewNet* win = new dialogNewNet(this);
    connect(win, SIGNAL(refresh()), this, SLOT(refresh()));
    win->show();
}

Ui::MainWindow* MainWindow::getUi() {
    return ui;
}

QWidget *MainWindow::getP() {
    return p;
}

void MainWindow::refresh() {
    clearWidgets(ui->gridLayoutNet);
    clearWidgets(ui->gridLayoutCont);
    popContList();
    popNetList();
}

void MainWindow::clearWidgets(QLayout* layout) {
    if (! layout)
        return;
    while (auto item = layout->takeAt(0)) {
        delete item->widget();
        clearWidgets(item->layout());
    }
}

void MainWindow::setUpBtns() {
    connect(ui->addBtn, SIGNAL (released()), this, SLOT (addCont()));
    connect(ui->addBtnNet, SIGNAL (released()), this, SLOT (addNet()));
    connect(ui->delAllContButton, SIGNAL (released()), this, SLOT (delConts()));
    connect(ui->delAllNetBtn, SIGNAL (released()), this, SLOT (delNets()));
}

void MainWindow::delConts() {
    uiMan->getDocker()->deleteAllConts();
}

void MainWindow::delNets() {
    uiMan->getDocker()->prune();
}
