#ifndef RenderWidget_h__
#define RenderWidget_h__

#include <QOpenGLWidget>
#include <QMutex>
#include "opencv2/opencv.hpp"

class CRenderWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    CRenderWidget(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *ev);
    virtual void setPixmap(const QImage &pixmap);
    cv::Mat QImage2Mat(QImage const& src);
    QImage Mat2QImage(cv::Mat const& src);

protected:
    QImage m_currentFrame;
    QMutex m_pixmapMutex;
};
#endif // RenderWidget_h__
