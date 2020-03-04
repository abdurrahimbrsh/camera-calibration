#include "calibration_mono.h"
#include "opencv2/core/types_c.h"

using namespace cv;

Calibration::Calibration (int board_width, int board_height, float square_width, float square_height)
: boardSize (board_width, board_height), squareSize (square_width, square_height)
{

}

void Calibration::InitCalibration ()
{
	imagePoints.clear ();
}

void Calibration::SetFilePath(string path) {
    m_sPath = path;
}

int Calibration::FindChessboard (Mat &view, bool reg)
{
	imageSize = view.size();

    Mat viewGray;
    cvtColor (view, viewGray, COLOR_BGR2GRAY);

	vector<Point2f> pointbuf;
    bool found = findChessboardCorners (view, boardSize, pointbuf,
                                        CALIB_CB_FAST_CHECK);
//        CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

	if (found) {
		// improve the found corners' coordinate accuracy
		cornerSubPix (viewGray, pointbuf, Size(1,1),
            Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1 ));

		if (reg) {
			imagePoints.push_back (pointbuf);
		}
		drawChessboardCorners (view, boardSize, Mat(pointbuf), found);
	}
	return imagePoints.size();
}

bool Calibration::RunCalibration (int nW, int nH)
{
	vector<vector<Point3f> > objectPoints(1);

	for( int i = 0; i < boardSize.height; i++ ) {
		for( int j = 0; j < boardSize.width; j++ ) {
			objectPoints[0].push_back (Point3f (j*squareSize.width, i*squareSize.height, 0.f));
		}
	}
	objectPoints.resize(imagePoints.size(),objectPoints[0]);

	int flags = 0;
	// flags |= CV_CALIB_ZERO_TANGENT_DIST;
	// flags |= CV_CALIB_FIX_PRINCIPAL_POINT;

	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
	Mat distCoeffs   = Mat::zeros(8, 1, CV_64F);

	vector<Mat> rvecs, tvecs;
	double rms = calibrateCamera (objectPoints, imagePoints, imageSize, cameraMatrix,
        distCoeffs, rvecs, tvecs, flags|CALIB_FIX_K4|CALIB_FIX_K5);
		///*|CV_CALIB_FIX_K3*/|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);

	bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);
	if (ok) {
//		FileStorage fs("calibration_data.yml", FileStorage::WRITE );

        FileStorage fs(m_sPath, FileStorage::WRITE );

		fs << "camera_matrix" << cameraMatrix;
		fs << "distortion_coefficients" << distCoeffs;
		fs << "imageSize" << imageSize;
        double scale = nW / 640.0;
        double fx = cameraMatrix.at<double>(0, 0);
        double fy = cameraMatrix.at<double>(1, 1);
        double cx = cameraMatrix.at<double>(0, 2);
        double cy = cameraMatrix.at<double>(1, 2);
        double k1 = distCoeffs.at<double>(0, 0);
        double k2 = distCoeffs.at<double>(1, 0);
        double p1 = distCoeffs.at<double>(2, 0);
        double p2 = distCoeffs.at<double>(3, 0);
        double k3 = distCoeffs.at<double>(4, 0);

        string stxtPath = m_sPath.append(".txt");
        std::ofstream fs1(stxtPath);

//        FileStorage fs1(stxtPath, FileStorage::WRITE );
        fs1 << "fx=" << std::to_string(fx * scale * nW)<< "/" <<nW << "\n";
        fs1 << "fy=" << std::to_string(fy * scale * nH)<< "/" <<nH << "\n";
        fs1 << "cx=" << std::to_string(cx * scale * nW)<< "/" <<nW << "\n";
        fs1 << "cy=" << std::to_string(cy * scale * nH)<< "/" <<nH << "\n";
        fs1 << "k1=" << k1 << "\n";
        fs1 << "k2=" << k2 << "\n";
        fs1 << "p1=" << p1 << "\n";
        fs1 << "p2=" << p2 << "\n";
        fs1 << "k3=" << k3;
        fs1.close();
		initUndistortRectifyMap (cameraMatrix, distCoeffs, Mat(),
			getOptimalNewCameraMatrix (cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
			imageSize, CV_16SC2, map1, map2);
	}

	return ok;
}

bool Calibration::LoadCalibrationData (string sPath)
{
    m_sPath = sPath;
    FileStorage fs(m_sPath, FileStorage::READ);
	if (fs.isOpened ()) {
		Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
		Mat distCoeffs   = Mat::zeros(8, 1, CV_64F);

		fs["camera_matrix"] >> cameraMatrix;
		fs["distortion_coefficients"] >> distCoeffs;
		FileNode is = fs["imageSize"];
		imageSize.width = is[0];
		imageSize.height = is[1];

		initUndistortRectifyMap (cameraMatrix, distCoeffs, Mat(),
			getOptimalNewCameraMatrix (cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
			imageSize, CV_16SC2, map1, map2);

		return true;
	}
	return false;
}

void Calibration::Undistort (const Mat &view, Mat &rview)
{
	if (map1.data && map2.data) {
		remap(view, rview, map1, map2, INTER_LINEAR);
	}
}
