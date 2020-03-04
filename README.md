# CameraCalibrationTool
1. Using.
- Open CameraCalibratorTool.exe and click "Show Tool Box" button. 
- Input rtsp url. 
	i.e if url is "rtsp://192.168.1.23:1220/test", then only input "192.168.1.23:1220/test" except "rtsp://"
- Click "Connect" and input username and password.
	if username and pwd aren't set, then plz keep blank..
- Click "OK"

- After some seconds, rtsp will be play in main window. 

== Calibration. 

- Click "Calibration" button. 
- In front of the camera, plz put the chessboard and move with different angle, different position and different pose.
	Chessboard is 10*7 grid, size of each cell grid is 2.5 * 2.5 (cm).
	Program will capture the images automatically. (1 image per one second, total 20).
	While calibrating, "Calibrating ... " will be appeared in main windows.
	After calibration, this text will be disappeared.
- After calibration, rtsp stream frame will be undistorted. 

That's all. 

2. Build. 
- Install QT5.12.4 (include Qt Creater4.9)
- In Qt Creater, open the *.pro file. 
- In left panel, click "Projects" and select "Desktop Qt 5.12.4 MSVC2017 64bit" and "Build".
- Rebuild 
- Run.

