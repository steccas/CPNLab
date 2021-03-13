#include <iostream>
#include "dialognewcont.h"
#include "ui_dialognewcont.h"
#include "mainwindow.h"

using namespace std;

dialogNewCont::dialogNewCont(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogNewCont)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle(tr("New Container"));

    uiMan = new manager();

    setupBtns();
    popComboBox();
}

dialogNewCont::~dialogNewCont()
{
    delete ui;
}

void dialogNewCont::setupBtns(){
    connect(ui->buttonBox, SIGNAL (accepted()), this, SLOT (apply()));
    connect(ui->buttonBox, SIGNAL (rejected()), this, SLOT (abort()));
}

void dialogNewCont::popComboBox(){
    vector<string> nets = uiMan->readNetworksNames();

    for (vector <string>::iterator it=nets.begin(); it != nets.end(); ++it) {
        QString name = QString::fromStdString(*it);
        if (name != "" && name != "" && name != "bridge" && name != "host") {
            ui->comboBox->addItem(name);
            //cout << *it << endl;
        }
    }
}

void dialogNewCont::abort() {
    delete this;
}

void dialogNewCont::apply() {
    QString net = ui->comboBox->currentText();
    QString name = ui->lineEdit->text();
    string netS = net.toStdString();
    string nameS = name.toStdString();

    if( nameS != "" || uiMan->isNotWhiteSpace(nameS)){
        string id = uiMan->getDocker()->addCont(nameS, netS);
        //cout << id;
        uiMan->getDocker()->routeDel(nameS, "default");
        vector <string> iFaces = uiMan->readContIfs(nameS);
        for (vector <string>::iterator it=iFaces.begin(); it != iFaces.end(); ++it){
            QString iFace = QString::fromStdString(*it);
            string eth = iFace.toStdString() + " 0.0.0.0";
            cout << eth;
            uiMan->getDocker()->ifconfig(nameS, eth);
        }
        /*for(int i = 0; i<10 ; i++) {
            string eth = "eth" + to_string(i) + " 0.0.0.0"; //ifconfig | grep "eth" | awk -F'[: ]+' '{ print $1 }'
            uiMan->getDocker()->ifconfig(nameS, eth);
        }*/
        emit refresh();
    }
    delete this;
}
