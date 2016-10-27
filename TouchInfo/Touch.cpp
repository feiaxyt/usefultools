#include "Touch.h"

string Touch::windowName = "DefaultWinName";
Mat Touch :: image;
Mat Touch :: timage;
Point Touch :: p1 = Point(0,0);
Point Touch :: p2 = Point(0,0);
Rect Touch :: trect = Rect(0,0,0,0);

Touch::Touch(const Mat *img)
{
	assert(img != NULL);
	img->copyTo(image);
	image.copyTo(timage);
}

void Touch:: setImage(const Mat *img)
{
	img->copyTo(image);
	image.copyTo(timage);
}
void Touch:: showImage(string winName, const Mat *img)
{
	if(img != NULL)
	{
		img->copyTo(image);
		image.copyTo(timage);
	}
	imshow(winName,image);
	waitKey(0);
}
Point Touch:: getTouchPoint(string winName,const Mat *img)
{
	if(img != NULL)
	{
		img->copyTo(image);
		image.copyTo(timage);
	}
	image.copyTo(timage);
	imshow(winName,image);
	windowName = winName;
	Point *point = NULL;
	param.point = point;
	param.acts = GETPOINT;
	setMouseCallback(winName,onMouse,&param);
	char keyboard = waitKey(0);
	while((int)keyboard != ENTERPRESS)
	{
		keyboard = waitKey(0);
	}
	if (param.point!=NULL)
		return *param.point;
	return NULL;
}
Rect Touch:: getRect(string winName,const Mat *img)
{
	if(img != NULL)
	{
		img->copyTo(image);
		image.copyTo(timage);
	}
	image.copyTo(timage);
	imshow(winName,image);
	windowName = winName;
	param.rect = &trect;
	param.acts = GETRECT;
	setMouseCallback(winName,onMouse,&param);
	char keyboard = waitKey(0);
	while((int)keyboard != ENTERPRESS)
	{
		keyboard = waitKey(0);
	}
	return *param.rect;
}

void Touch::onMouse(int mouseEvent, int x, int y, int flag, void* param)
{
	TouchParam* tParam = (TouchParam*)param;
	switch(mouseEvent) 
	{ 
	case CV_EVENT_LBUTTONDOWN:
		p1 = Point(x,y);
		if(tParam->acts == GETPOINT)
		{
			tParam->point = &p1;
			Mat tempMat = Mat(image.rows,image.cols,image.type());
			image.copyTo(tempMat);
			circle(tempMat,p1,3,Scalar::all(255),4);
			int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
			double fontScale = 1;
			int thickness = 2;
			int baseline=0;
			string text = "";
			text+="x=";
			char chari[10];
			sprintf_s(chari,5,"%d",p2.x);
			text+=chari;
			text+=",y=";
			sprintf_s(chari,5,"%d",p2.y);
			text+=chari;
			Size textSize = getTextSize(text, fontFace,
								fontScale, thickness, &baseline);
			baseline += thickness;
			Point textOrg((p1.x+10 + textSize.width > image.cols? image.cols-textSize.width:p1.x + 10),
				  (p1.y + 40 + textSize.height > image.rows?image.rows-textSize.height:p1.y+40));
			putText(tempMat,text,textOrg,fontFace,fontScale,Scalar::all(255),thickness);
			imshow(windowName,tempMat);
			tempMat.copyTo(timage);
		}
		break;
	case CV_EVENT_MOUSEMOVE:
		{
			p2 = Point(x,y);
			p2.x = p2.x < 0?0:p2.x;
			p2.y = p2.y < 0?0:p2.y;
			p2.x = p2.x > image.cols-1?image.cols-1:p2.x;
			p2.y = p2.y > image.rows-1?image.rows-1:p2.y;
			Mat tempMat = Mat(image.rows,image.cols,image.type());
			timage.copyTo(tempMat);
			if(tParam->acts == GETRECT && (flag & CV_EVENT_FLAG_LBUTTON))
			{
				image.copyTo(tempMat);
				rectangle(tempMat,p1,p2,Scalar::all(255));
				tempMat.copyTo(timage);
				int x,y,w,h;
				w = abs(p1.x-p2.x)+1;
				h = abs(p2.y-p1.y)+1;
				if(p1.y < p2.y)
					y = p1.y;
				else
					y = p2.y;
				if(p1.x <  p2.x)
					x = p1.x;
				else
					x = p2.x;
				tParam->rect->x = x;
				tParam->rect->y = y;
				tParam->rect->width = w;
				tParam->rect->height = h;
			}
			int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
			double fontScale = 1;
			int thickness = 3;
			int baseline=0;
			string text = "";
			text+="x=";
			char chari[10];
			sprintf_s(chari,5,"%d",p2.x);
			text+=chari;
			text+=",y=";
			sprintf_s(chari,5,"%d",p2.y);
			text+=chari;
			Size textSize = getTextSize(text, fontFace,
								fontScale, thickness, &baseline);
			baseline += thickness;
			Point textOrg((image.cols - textSize.width),
				  (image.rows - textSize.height));
			putText(tempMat,text,textOrg,fontFace,fontScale,Scalar::all(255),thickness);
			imshow(windowName,tempMat);
			break;	
		}
	case CV_EVENT_LBUTTONUP: 

		break; 
	case CV_EVENT_LBUTTONDBLCLK:

		break;
	 } 
}