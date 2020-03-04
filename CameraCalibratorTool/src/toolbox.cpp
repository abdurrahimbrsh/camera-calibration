#include "toolbox.h"
#include "ui_toolbox.h"
#include "credentialdlg.h"

using namespace std;

ToolBox::ToolBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolBox)
{
    ui->setupUi(this);
    connectSlots();
    connect(this, SIGNAL(signalConnect(std::string)), parent, SLOT(openRTSP(std::string)));
//    connect(this, SIGNAL(signalDisconnect()), parent, SLOT(closeRTSP()));
    connect(this, SIGNAL(signalCalibration()), parent, SLOT(doCalibration()));
}

ToolBox::~ToolBox()
{
    delete ui;
}

void ToolBox::connectSlots()
{
    connect(ui->connectBtn, SIGNAL(clicked(bool)), this, SLOT(connectBtnClicked()));   
//    connect(ui->disconnectBtn, SIGNAL(clicked(bool)), this, SLOT(disconnectBtnClicked()));
    connect(ui->calibrateBtn, SIGNAL(clicked(bool)), this, SLOT(calibrateBtnClicked()));
}

void ToolBox::connectBtnClicked()
{
    CredentialDlg dlg;
    dlg.exec();
    if(dlg.bOK) {
        string url = "rtsp://";
        string sUser = dlg.strUser;
        string sPwd = dlg.strPwd;
        string ip = ui->ipEdit->text().toStdString();
        if(!sUser.empty() || !sPwd.empty()) {
            url.append(sUser);
            url.append(":");
            url.append(sPwd);
            url.append("@");
            url.append(ip);
        }
        else{
            url.append(ip);
        }

        emit signalConnect(url);
    }
}

void ToolBox::disconnectBtnClicked()
{
//    emit signalDisconnect();
}

void ToolBox::calibrateBtnClicked()
{
    emit signalCalibration();
}
