#include <iostream>
#include "dialogaddnet.h"
#include "ui_dialogaddnet.h"

dialogAddNet::dialogAddNet(QWidget *parent, QString contId) :
    QDialog(parent),
    ui(new Ui::dialogAddNet)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Connect Network"));

    uiMan = new manager();
    this->contId = contId;

    setupBtns();
    popComboBox();
}

dialogAddNet::~dialogAddNet()
{
    delete ui;
}

void dialogAddNet::popComboBox() {
    vector<string> nets = uiMan->readNetworksNames();

    for (vector <string>::iterator it=nets.begin(); it != nets.end(); ++it) {
        QString name = QString::fromStdString(*it);
        if (name != "" && name != "" && name != "bridge" && name != "host" && name != "none") {
            ui->comboBox->addItem(name);
            //cout << *it << endl;
        }
    }
}

void dialogAddNet::setupBtns() {
    connect(ui->buttonBox, SIGNAL (accepted()), this, SLOT (apply()));
    connect(ui->buttonBox, SIGNAL (rejected()), this, SLOT (abort()));
}

void dialogAddNet::apply() {
    QString net = ui->comboBox->currentText();
    uiMan->getDocker()->connect(contId.toStdString(), net.toStdString());
    string contIdS=contId.toStdString();
    vector <string> iFaces = uiMan->readContIfs(contIdS);
    for (vector <string>::iterator it=iFaces.begin(); it != iFaces.end(); ++it){
        QString iFace = QString::fromStdString(*it);
        string eth = iFace.toStdString() + " 0.0.0.0";
        uiMan->getDocker()->ifconfig(contIdS, eth);
    }
    emit refresh();
    delete this;
}

void dialogAddNet::abort() {
    delete this;
}
