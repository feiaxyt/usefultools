#include <iostream>
#include <opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	bool useCamera = 1;
	string videoName = "Seq_1.avi";
	VideoCapture capture;
	int startFrame = -1;
	int endFrame = -1;
	int totalFrameNumber = -1;
	bool pause = false;
	if (useCamera)
	{
		if (!capture.open(0))
		{
			cout << "error: could not start camera capture" << endl;
			return EXIT_FAILURE;
		}
		endFrame = INT_MAX;
	}
	else
	{
		if (!capture.open(videoName))
		{
			cout << "error: could not start video capture" << endl;
			return EXIT_FAILURE;
		}
		totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
		cout << "total frame number: " << totalFrameNumber << endl;
		endFrame = totalFrameNumber;
		double framRate = capture.get(CV_CAP_PROP_FPS);
		cout << "frame rate: " << framRate << endl;
	}
	Mat frame;
	int frameNumber = 1;
	int c = 0;
	while ((char)c != 27 && frameNumber <= endFrame)
	{
		if (!capture.read(frame))
		{
			cout << "fail to read frame!" << endl;
			exit(1);
		}
		if (useCamera)
		{
			flip(frame, frame, 1);
		}
		imshow("frame", frame);
		c = waitKey(1);
		cout << frameNumber << endl;
		frameNumber++;
		if (c == 'p') pause = true;
		while (pause)
		{
			c = waitKey(1);
			if (c == 'p') pause = false;
		}
	}
	return 0;
}