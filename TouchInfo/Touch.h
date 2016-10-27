//提供一些在图像上标记点和矩形框的信息。
#ifndef TOUCH_H_INCLUDED
#define TOUCH_H_INCLUDED

#include <iostream>
#include <opencv.hpp>
using namespace std;
using namespace cv;

#define ENTERPRESS 13

class Touch
{
public:
	Touch(){};
	~Touch(){};
    Touch(const Mat *img);
    void setImage(const Mat *img);
	void showImage(string winName, const Mat *img = NULL);
	/*回车获取结果*/
    Point getTouchPoint(string winName,const Mat *img = NULL);
    Rect getRect(string winName,const Mat *img = NULL);
	/*****************/
private:
	enum Action
	{
		GETPOINT,
		GETRECT
	};
	struct TouchParam
	{
		Point *point;
		Rect *rect;
		Action acts;
	};
	static void onMouse(int mouseEvent, int x, int y, int flag, void* param);
    static Mat image;
	static Mat timage;
	static string windowName;
	static Point p1,p2;
	static Rect trect;
	TouchParam param;
};
#endif
