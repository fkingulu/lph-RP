#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


class Detector {
	Mat _img;
	vector<Point> _points;
public:
	Detector(){}
	void set_img(Mat& img) {
		_img = img;
	}
	void Detect() {
		Mat imgGray, imgCanny, imgDil;
		cvtColor(_img, imgGray, COLOR_BGR2GRAY);
		Canny(_img, imgCanny, 25, 75);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgCanny, imgDil, kernel);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		for (const vector<Point>& contour : contours) {
			Moments moment = moments(contour);
			Point center(moment.m10 / moment.m00, moment.m01 / moment.m00);
			_points.push_back(center);
		}

		drawContours(_img, contours, -1, Scalar(255, 0, 255), 2);
	}
	void print() {
		for (int i = 0; i < _points.size(); i++)
			cout << "(" <<  _points[i].x << "," << _points[i].y << ")" << endl;
	}
};

void main()
{
	Mat img = imread("Resources/shapes.png");
	Detector A;
	A.set_img(img);
	A.Detect();
	A.print();
	waitKey(0);
}