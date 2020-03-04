#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calibration_mono.h"
#include <QMainWindow>
#include "vlc/vlc.h"
#include "toolbox.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ToolBox* toolBox;

    void initUi();
    void connectSlots();

private slots:
    void showToolBox();
    void openRTSP(std::string url);
    void closeRTSP();
    void doCalibration();

public:
    char* GetVideoBuf() const;
    void OpenVideo(const char* rtsp);

private:
    void AllocVideoBuf(int width, int height);

    static void* PreDecode_cb(void *opaque, void **planes);
    static void HandleStream_cb(void *opaque, void *picture, void *const *planes);
    static void Render_cb(void *opaque, void *picture);

    void OnPause();
    void OnPlay();

private:
    char * m_videobuf;
    int m_frameWidth;
    int m_frameHeight;

    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_pvlcMedia;
};

#endif // MAINWINDOW_H
