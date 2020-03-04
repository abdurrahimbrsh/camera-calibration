#pragma once

#include <opencv2/opencv.hpp>
#include <QStandardPaths>

using namespace std;

class Calibration {
public:
	Calibration (int board_width, int board_height, float square_width, float square_height);

	void InitCalibration ();
    int FindChessboard (cv::Mat &view, bool reg = false);
    bool RunCalibration (int nW, int nH);
    bool LoadCalibrationData (string sPath);
    void Undistort (const cv::Mat &view, cv::Mat &rview);
    void SetFilePath(string path);

private:
    const cv::Size boardSize;
    const cv::Size2f squareSize;

    vector<vector<cv::Point2f> > imagePoints;
    cv::Size imageSize;
    cv::Mat map1, map2;
    string m_sPath;
};
