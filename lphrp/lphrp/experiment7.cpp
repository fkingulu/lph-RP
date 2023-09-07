#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void getContours(Mat imgDil, Mat img) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -2, Scalar(0, 0, 2), 2);

	for (int i = 0; i < contours.size(); i++) 
	{
		int area = contourArea(contours[i]);

		Point centre;
		for (int j = 0; j < contours[i].size(); j++) {
			centre.x += contours[i][j].x;
			centre.y += contours[i][j].y;
		}
		centre.x /= contours[i].size();
		centre.y /= contours[i].size();

		cout << centre << endl;

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());

		string objtype;

		if (area > 1000)
		{
			float curve = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * curve, true);
			boundRect[i] = boundingRect(conPoly[i]);

			//int objCon = (int)conPoly[i].size();
			//if (objCon == 3){
			//	objtype = "triangle";
			//}
			//else if (objCon == 4) {
			//	objtype == "rectangle";
			//}
			//else{
			//	objtype == "circle";
			//}
			//cout << objtype << endl;
			rectangle(img, boundRect[i], Scalar(255, 0, 255), 5);
		}
	}
}

int main()
{
	Mat img = imread("Resources/shapes.png");
	Mat imgCanny, imgDil;
	cvtColor(img, imgCanny, COLOR_RGB2GRAY);

	Canny(img, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);
	imshow("origin", img);
	waitKey(0);
}