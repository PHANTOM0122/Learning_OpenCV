#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


//string filename = "mydata.xml";
//string filename = "mydata.yml";
string filename = "mydata.json";

void writeData();
void readData();

int main(){
	writeData();
	readData();
}

void writeData() {
	String name = "Jane";
	int age = 10;
	Point pt1(100, 200);
	vector<int> scores = { 80,90,50 };
	Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

	FileStorage fs(filename, FileStorage::WRITE);

	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}

	fs << "name" << name;
	fs << "age" << age;
	fs << "point" << pt1;
	fs << "scores" << scores;
	fs << "data" << mat1;

	fs.release();
}

void readData() {
	String name;
	int age;
	Point pt1;
	vector<int> scores;
	Mat mat1;

	FileStorage fs(filename, FileStorage::READ);

	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}

	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "point: " << pt1 << endl;
	cout << "scores: " << Mat(scores).t() << endl;
	cout << "data:\n" << mat1 << endl;
}