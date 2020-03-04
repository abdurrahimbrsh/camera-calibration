#ifndef CREDENTIALDLG_H
#define CREDENTIALDLG_H

#include <QDialog>


namespace Ui {
class CredentialDlg;
}

class CredentialDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CredentialDlg(QWidget *parent = 0);
    ~CredentialDlg();
    std::string strUser, strPwd;
    bool bOK;

private:
    Ui::CredentialDlg *ui;
    void connectSlots();

private slots:
    void btnOKClicked();
    void btnCancelClicked();
};

#endif // CREDENTIALDLG_H
