#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>

#include "hogtrain.h"
#include <ctime>

//#include "svm_common.h"
//#include "svm_learn.h"

using namespace cv;
using namespace std;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

//int edgeThresh = 1;
//int lowThreshold =130;
//int const max_lowThreshold = 130;
//int ratio = 3;
//int kernel_size = 3;
//const char* window_name = "Edge Map";
//int samples = 20;

//int lowThreshold =15;
//int ratio = 4;
//int kernel_size = 3;
//int samples = 20;
//const char* window_name = "Edge Map";

int lowThreshold =60;
int ratio = 1;
int kernel_size = 3;
int samples = 20;
const char* window_name = "Edge Map";

//SVM s;

int random(int low, int high) {
	srand(static_cast<unsigned int>(time(0)));
    return rand() % (high - low + 1) + low;
}

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void batchCannypos(){
	Mat dst = Mat::zeros(128,64, CV_64FC1);
//	Mat dst = Mat::zeros(128,64, CV_16U);

//	src = imread("img/base/pos/flopped_manual_1.jpg",6); // CV_BGR2GRAY = 6
////	cvtColor(src, src, 6); // CV_BGR2GRAY = 6
//	imshow( window_name, src);waitKey(0);
//	equalizeHist(src,src_gray);
//	imshow( window_name, src_gray);waitKey(0);
//	cout << "M = "<< endl << " "  << src_gray << endl;
//	blur( src, detected_edges, Size(3,3) );
//	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
//	dst = detected_edges;

	char buffer[200];

	for(int i=1;i<874;i++){

		snprintf(buffer,sizeof(char)*60,"img/base/pos/flopped_manual_%i.jpg",i);
//		printf(buffer);
		src = imread(buffer,6); // CV_BGR2GRAY = 6

		// Enhance image if dark or bright
//		equalizeHist(src,src);

		blur( src, detected_edges, Size(3,3) );
		Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
		detected_edges.convertTo(detected_edges,CV_64FC1);
		addWeighted(dst,1,detected_edges,0.00001,0.0,dst);
	}

	for(int i=1;i<874;i++){

			snprintf(buffer,sizeof(char)*60,"img/base/pos/manual_%i.jpg",i);
			src = imread(buffer,6); // CV_BGR2GRAY = 6

//			equalizeHist(src,src);

			blur( src, detected_edges, Size(3,3) );
			Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
			detected_edges.convertTo(detected_edges,CV_64FC1);
			addWeighted(dst,1,detected_edges,0.00001,0.0,dst);
		}

	double max,min;

//	normalize(dst,dst,3200, CV_64FC1); // NORM_MINMAX = 32
	minMaxLoc(dst, &min, &max);

	addWeighted(dst,1/max*255,dst,0,0.0,dst);
	dst.convertTo(dst,CV_8U);

	imshow( window_name, dst);waitKey(0);

//	cout << "M = "<< endl << " "  << dst << endl;
//	cout << "Max = " << max << endl;
	imwrite("output-pos.jpg",dst);
	waitKey(0);
}

void batchCannyneg(){
	Mat dst = Mat::zeros(128,64, CV_64FC1);
//	Mat dst = Mat::zeros(128,64, CV_64FC4);
	char buffer[200];
//	for(int i=1;i<289;i++){
	for(int i=1;i<198;i++){

		snprintf(buffer,sizeof(char)*60,"img/base/neg/serial/%i.jpg",i);
		src = imread(buffer,6); // CV_BGR2GRAY = 6

		blur( src, detected_edges, Size(3,3) );
		Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
		detected_edges.convertTo(detected_edges,CV_64FC1);

		for(int j=0;j<samples;j++){
			cv::Rect roi( random(1,detected_edges.cols-65), random(1,detected_edges.rows-129), 64, 128);
			//copies input image in roi
			cv::Mat image_roi = detected_edges( roi );
			addWeighted(dst,1,image_roi,0.00001,0.0,dst);
		}

	}

	double max,min;

//	normalize(dst,dst,3200, CV_64FC1); // NORM_MINMAX = 32
	minMaxLoc(dst, &min, &max);

	addWeighted(dst,1/max*255,dst,0,0.0,dst);
	dst.convertTo(dst,CV_8U);

	imshow( window_name, dst);waitKey(0);

//	cout << "M = "<< endl << " "  << dst << endl;
//	cout << "Max = " << max << endl;
	imwrite("output-neg.jpg",dst);
	waitKey(0);
}

void canny(){
	Mat dst = Mat::zeros(128,64, CV_64FC1);
	char buffer[200];
	snprintf(buffer,sizeof(char)*60,"img/analysis/lowres.jpg");
	//		printf(buffer);
	src = imread(buffer,6); // CV_BGR2GRAY = 6

			// Enhance image if dark or bright
	//		equalizeHist(src,src);

	blur( src, detected_edges, Size(3,3) );
	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
	detected_edges.convertTo(detected_edges,CV_64FC1);


	detected_edges.convertTo(detected_edges,CV_8U);

	imshow( window_name, detected_edges);waitKey(0);
	imwrite("img/analysis/pos-edge.jpg",detected_edges);
}

void cannyneg(){
	Mat dst = Mat::zeros(128,64, CV_64FC1);
	char buffer[200];
	snprintf(buffer,sizeof(char)*60,"img/base/neg/serial/84.jpg");
	src = imread(buffer,6); // CV_BGR2GRAY = 6
	blur( src, detected_edges, Size(3,3) );
	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
	detected_edges.convertTo(detected_edges,CV_8U);

	cout << "Width = " << src.cols << endl;
	cout << "Height = " << src.rows << endl;

//	cout << "X = " << random(0,src.cols-65)<< endl;
//	cout << "Y = " << random(0,src.cols-129) << endl;


	//defines roi
//	cv::Rect roi( roiVertexXCoordinate, roiVertexYCoordinate, roiWidth, roiHeight );
	cv::Rect roi( random(0,src.cols-65), random(0,src.rows-129), 64, 128);
	//copies input image in roi
	cv::Mat image_roi = detected_edges( roi );
	imshow( window_name, image_roi);waitKey(0);
	imwrite("my-edge.jpg",detected_edges);
}



/** @function main */
int main( int argc, char** argv )
{
//	batchCannypos();
//	batchCannyneg();
//	cannyneg();
	canny();

	cout << "ENDS" << endl;

//	cout << random(0,100) << endl;

//	svm_learn_classification();

	// POSITIVES TRAIN
//	hogtrain("img/base/pos/manual_","data/trained.data1",1,1,50);

	// NEGATIVES TRAIN
//	hogtrain("img/train/neg/no_person_","data/trained.data1",0,1,50);

	// POSITIVES TEST
//	hogtrain("img/test/pos/manual_","data/test.data1",1,101,150);

	// NEGATIVES TEST
//	hogtrain("img/test/neg/0000","data/test.data1",0,1431,1440);

	return 0;
}




