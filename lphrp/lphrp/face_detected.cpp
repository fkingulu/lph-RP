#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void main()
{
	VideoCapture cap(0);
	Mat img;

	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) 
		cout << "empty!" << endl;

	while (true)
	{
		cap.read(img);
		vector<Rect> faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0), 3);
			putText(img, "handsome", { faces[i].x,faces[i].y - 5 }, FONT_HERSHEY_COMPLEX_SMALL, 3, Scalar(100, 0, 100), 3);
		}

		resize(img, img, Size(), 1.2, 1.2);
		imshow("Webcam", img);
		waitKey(10);
	}
}