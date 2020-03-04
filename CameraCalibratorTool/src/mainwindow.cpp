#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <time.h>
#include <QMessageBox>
#include "calibration_mono.h"
#include "Util.h"
#include "opencv2/opencv.hpp"
#include <QFileDialog>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

static const int nframes = 20;
static Calibration calib(9, 6, 0.250f / 10, 0.174f / 7);
static bool reg_chessboard = false;
static bool g_bCalibrate = false;
static bool g_bUndistort = false;
static int g_nTotalFrame = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_vlcInstance(NULL)
  , m_vlcMediaPlayer(NULL)
  , m_pvlcMedia(NULL)
  , m_videobuf(NULL)
  , m_frameWidth(0)
  , m_frameHeight(0)
{
    ui->setupUi(this);
    initUi();
    connectSlots();

    char const* vlc_args[] =
    {
        "-I",
        "dummy",
        "--ignore-config",
    };

    m_vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    m_vlcMediaPlayer = libvlc_media_player_new (m_vlcInstance);
    calib.InitCalibration();
//    if(calib.LoadCalibrationData("C:\\Users\\Silverstar\\Documents\\test.yml"))
//        g_bUndistort = true;
}


MainWindow::~MainWindow()
{
    libvlc_media_release(m_pvlcMedia);
    libvlc_media_player_stop(m_vlcMediaPlayer);
    libvlc_media_player_release(m_vlcMediaPlayer);
    libvlc_release(m_vlcInstance);
    SAFE_DELETE_ARRAY(m_videobuf);

    delete ui;
}

void MainWindow::initUi()
{
    toolBox = new ToolBox(this);
    toolBox->setModal(false);
    toolBox->hide();
}

void MainWindow::connectSlots()
{
    connect(ui->showToolBoxBtn, SIGNAL(clicked(bool)), this, SLOT(showToolBox()));
}

void MainWindow::showToolBox()
{
    toolBox->show();
}

char* MainWindow::GetVideoBuf() const
{
    return m_videobuf;
}

void MainWindow::AllocVideoBuf(int width, int height)
{
    m_videobuf = new char[(width * height) << 2];
}

void* MainWindow::PreDecode_cb(void *opaque, void **planes)
{
    MainWindow* obj = (MainWindow*)opaque;
    *planes = obj->GetVideoBuf();

    return obj->GetVideoBuf();
}

void MainWindow::HandleStream_cb(void *opaque, void *picture, void *const *planes)
{
    Q_UNUSED(opaque);
    Q_UNUSED(picture);
    Q_UNUSED(planes);
    // TODO - image processing
//     if (picture != NULL)
//     {
//         CPlayerView* obj = (CPlayerView*)opaque;
//         Mat img(Size(obj->m_frameWidth, obj->m_frameHeight), CV_8UC4, picture);

//         imshow("123", img);
//         waitKey(1);
//     }
}

void MainWindow::Render_cb(void *opaque, void *picture)
{
    time_t start, end;
    time(&start);
    MainWindow* obj = (MainWindow*)opaque;
    QImage qimg;
    if (picture != NULL)
    {
        try {
            MainWindow* obj = (MainWindow*)opaque;
            Mat image(Size(obj->m_frameWidth, obj->m_frameHeight), CV_8UC4, picture);
            // resize
            int nW = 640, nH = 0;
            nH = nW  * (obj->m_frameHeight) / (obj->m_frameWidth) ;
            Mat img;
            cv::resize(image, img, cv::Size(nW, nH), cv::INTER_TAB_SIZE);
//            img = temp.clone();
             // Calibration Processing.
             if(g_bCalibrate) {
                 if(g_nTotalFrame % 30 == 0)
                     reg_chessboard = true;

                 g_nTotalFrame += 1;

                 int iframes = calib.FindChessboard(img, reg_chessboard);
                 char buffer [120];
                 sprintf (buffer, "Calibrating ... ( %d of %d) ", iframes, nframes);
                 putText(img,
                              buffer,
                              Point(5,50), // Coordinates
                              FONT_HERSHEY_DUPLEX, // Font
                              1.0, // Scale. 2.0 = 2x bigger
                              Scalar(0,143,143), 2);

                 if (iframes >= nframes) {
                     if (calib.RunCalibration(obj->m_frameWidth, obj->m_frameHeight)) {
                        g_bUndistort = true;
                     }
                     else {

                     }
                     g_bCalibrate = false;
                     g_nTotalFrame = 0;
                 }
                 reg_chessboard = false;
             }

             if(g_bUndistort) {
                 Mat temp = img.clone();
                 calib.Undistort(temp, img);
             }

             qimg = CVHelper::Mat2QImage(img);
        }
        catch(...) {
            qimg = QImage((uchar*)picture, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);
        }
    }
    else
        qimg = QImage((uchar*)picture, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);

    obj->ui->RenderWidget->setPixmap(qimg);
    time(&end);
    double dif = difftime (end,start);

}

void MainWindow::OnPause()
{
    libvlc_media_player_pause(m_vlcMediaPlayer);
}

void MainWindow::OnPlay()
{
    try {
        libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);

        if (state == libvlc_Playing)
        {
            return;
        }

        libvlc_media_player_play(m_vlcMediaPlayer);

        while (state == libvlc_NothingSpecial || state == libvlc_Opening)
        {
            state = libvlc_media_player_get_state(m_vlcMediaPlayer);
            MSleep(100);
        }

        if (state == libvlc_Error)
        {
            return;
        }

        libvlc_media_track_t **tracks = NULL;
        bool bFindResolution = false;

        while (!bFindResolution)
        {
            unsigned tracksCount = libvlc_media_tracks_get(m_pvlcMedia, &tracks);

            if (tracks != NULL)
            {
                for (unsigned i = 0; i < tracksCount; i++)
                {
                    if (tracks[i]->i_type == libvlc_track_video
                        && tracks[i]->video->i_height != 0
                        && tracks[i]->video->i_width != 0)
                    {
                        m_frameWidth = tracks[i]->video->i_width;
                        m_frameHeight = tracks[i]->video->i_height;
                        bFindResolution = true;
                        break;
                    }
                }
            }

            libvlc_media_tracks_release(tracks, tracksCount);
            MSleep(100);
        }


        // [workaround]: I don't know how to change format (libvlc_video_set_format) after playing...
        // reconnect the stream
        libvlc_media_player_stop(m_vlcMediaPlayer);

        libvlc_video_set_format(m_vlcMediaPlayer, "RV32", m_frameWidth, m_frameHeight, m_frameWidth << 2);
        SAFE_DELETE_ARRAY(m_videobuf);
        AllocVideoBuf(m_frameWidth, m_frameHeight);

        libvlc_media_player_play(m_vlcMediaPlayer);
    }
    catch(...) {
        return;
    }
}

void MainWindow::openRTSP(string url) {
    try{
        g_bCalibrate = false;
        g_bUndistort = false;

        OnPause();

        m_pvlcMedia = libvlc_media_new_location(m_vlcInstance, url.c_str());
        libvlc_media_player_set_media(m_vlcMediaPlayer, m_pvlcMedia);

        libvlc_video_set_callbacks(m_vlcMediaPlayer, PreDecode_cb, HandleStream_cb, Render_cb, this);
    }
    catch(...)
    {
        return;
    }

    OnPlay();
}

void MainWindow::closeRTSP() {
    g_bCalibrate = false;
    g_bUndistort = false;
//    OnPause();
}

void MainWindow::doCalibration() {
    QString documentFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QString filename =  QFileDialog::getSaveFileName(
          this,
          "Save Calibration Parameter",
          documentFolder,
          "Calibration files (*.yml)");

    if(filename.isNull() )
    {
        QMessageBox msgBox;
        msgBox.setText("Please save calibration file.");
        msgBox.exec();
        return;
    }
    calib.InitCalibration();
    calib.SetFilePath(filename.toStdString());
//    QMessageBox msgBox;
//    msgBox.setText("Calibration is running!!!");
//    msgBox.exec();

    g_bCalibrate = true;
    g_bUndistort = false;
}
