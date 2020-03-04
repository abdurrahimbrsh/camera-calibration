#ifndef Util_h__
#define Util_h__

#include <QImage>
#include <QVector>
#include <QColor>
#include <QThread>
//#ifdef WIN32
//#include <windows.h>
//#else
//#include <unistd.h>
//#endif // win32

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define SAFE_DELETE_ARRAY(p) { if((p) != NULL) { delete[] (p);   (p)=NULL; } }

inline void MSleep (int milliseconds)
{
//#ifdef WIN32
//    Sleep(milliseconds);
//#else
//    usleep(milliseconds * 1000);
//#endif // win32
    QThread::msleep(milliseconds);
}

namespace CVHelper
{
    inline cv::Mat QImage2Mat(const QImage &src)
    {
        return cv::Mat(cv::Size(src.width(), src.height()), CV_8UC4, (void*)src.bits());
    }

    inline QImage Mat2QImage(const cv::Mat &src)
    {
//        return QImage(src.data, src.cols, src.rows, QImage::Format_ARGB32);
        cv::Mat temp; // make the same cv::Mat
        cv::cvtColor(src, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
        dest.bits(); // enforce deep copy, see documentation
        // of QImage::QImage ( const uchar * data, int width, int height, Format format )
        return dest;
    }

    inline cv::Vec3b QColor2Vec(const QColor &src)
    {
        return cv::Vec3b(src.blue(), src.green(), src.red());
    }

    inline std::vector<cv::Vec3b> QColor2Vec(const QVector<QColor> & src)
    {
        std::vector<cv::Vec3b> dest(src.size());

        for (int i = 0; i < src.size(); ++i)
        {
            dest[i] = QColor2Vec(src[i]);
        }

        return dest;
    }

    inline QColor Vec2QColor(const cv::Vec3b &src)
    {
        return QColor(src[2], src[1], src[0]);
    }

    inline QVector<QColor> Vec2QColor(const std::vector<cv::Vec3b> & src)
    {
        QVector<QColor> dest(src.size());

        for (size_t i = 0; i < src.size(); ++i)
        {
            dest[i] = Vec2QColor(src[i]);
        }

        return dest;
    }
}
#endif // Util_h__
