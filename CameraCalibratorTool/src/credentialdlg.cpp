#include "credentialdlg.h"
#include "ui_credentialdlg.h"

CredentialDlg::CredentialDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CredentialDlg)
{
    ui->setupUi(this);
    connectSlots();
    bOK = false;
}

CredentialDlg::~CredentialDlg()
{
    delete ui;
}

void CredentialDlg::connectSlots()
{
    connect(ui->btnOK, SIGNAL(clicked(bool)), this, SLOT(btnOKClicked()));
    connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(btnCancelClicked()));
}

void CredentialDlg::btnOKClicked()
{
    strUser = ui->editUser->text().toStdString();
    strPwd = ui->editPwd->text().toStdString();
    bOK = true;
    this->close();
}

void CredentialDlg::btnCancelClicked()
{
    bOK = false;
    this->close();
}
