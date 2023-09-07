#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	CascadeClassifier FaceClassifier;
	FaceClassifier.load("Resources/haarcascade_frontalface_default.xml");

	VideoCapture cap(0);
	Mat img;

	while (true)
	{
		cap.read(img);
		vector<Rect> faces;
		FaceClassifier.detectMultiScale(img, faces, 1.1, 10);
		for (int i = 0; i < faces.size(); i++) {
			Mat imgFace = img(faces[i]);
			rectangle(img, faces[i], Scalar(0, 255, 0), 5);
			string windowname = "Face" + to_string(i);
			imshow(windowname, imgFace);
			imwrite("Resources/Faces" + windowname, imgFace);
		}

		imshow("Camera1", img);
		waitKey(1);
	}
}