#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QDialog>


namespace Ui {
    class ToolBox;
}

class ToolBox : public QDialog
{
    Q_OBJECT

public:
    explicit ToolBox(QWidget *parent = 0);
    ~ToolBox();

signals:
    void signalConnect(std::string url);
    void signalDisconnect();
    void signalCalibration();

private:
    Ui::ToolBox *ui;

    void connectSlots();

private slots:
    void connectBtnClicked();
    void disconnectBtnClicked();
    void calibrateBtnClicked();

//protected:
//    void closeEvent(QCloseEvent *ev);
};

#endif // TOOLBOX_H
