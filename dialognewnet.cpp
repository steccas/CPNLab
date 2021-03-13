#include <QtWidgets/QMessageBox>
#include <iostream>
#include "dialognewnet.h"
#include "ui_dialognewnet.h"

dialogNewNet::dialogNewNet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogNewNet)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle(tr("New Network"));

    uiMan = new manager();

    delete ui->lineEdit_2;
    delete ui->label_2;

    setupBtns();
}

dialogNewNet::~dialogNewNet()
{
    delete ui;
}

void dialogNewNet::setupBtns() {
    connect(ui->buttonBox, SIGNAL (accepted()), this, SLOT (apply()));
    connect(ui->buttonBox, SIGNAL (rejected()), this, SLOT (abort()));
}

void dialogNewNet::apply() {
    QString name = ui->lineEdit->text();
    string nameS = name.toStdString();
    //QString subnet = ui->lineEdit_2->text();
    //string subnetS = subnet.toStdString();

    if( nameS != "" && uiMan->isNotWhiteSpace(nameS)/* && subnetS != "" && uiMan->isNotWhiteSpace(subnetS)*/){
        //string gw = uiMan->createGwForExam(subnetS);
        string result = "error";
        //result = uiMan->getDocker()->addNet(nameS, subnetS, gw);
        result = uiMan->addNetExam(nameS);
        //cout << result;
        if(result != "invalid" && result != "already" && result != "") {
            emit refresh();
            delete this;
            return;
        }
        if(result == "invalid") {
            QMessageBox messageBox;
            //messageBox.critical(0,"Error","Can't create network! Check your subnet and network name. Use just letters and number to specify the network name");
            messageBox.critical(0,"Error","Can't create network! Check your network name. Use just letters and number to specify the network name");
            messageBox.setFixedSize(100,50);
            delete this;
            return;
        }
        if(result == "already"){
            QMessageBox messageBox;
            //messageBox.critical(0,"Error","Can't create network! Subnet or name already in use!");
            messageBox.critical(0,"Error","Can't create network! Name already in use!");
            messageBox.setFixedSize(100,50);
            delete this;
            return;
        }
    } else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Specify a name!");
        //messageBox.critical(0,"Error","Specify a name and a subnet (for example 10.0.0.1/24)");
        messageBox.setFixedSize(100,50);
        delete this;
        return;
    }
    /*QMessageBox messageBox;
    messageBox.critical(0,"Error","Unspecified error. Use just letters and number to specify the network name");
    messageBox.setFixedSize(100,50);
    delete this;
    return;*/
}

void dialogNewNet::abort() {
    delete this;
}
