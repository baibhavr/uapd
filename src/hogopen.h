/*
 * hogopen.h
 *
 *  Created on: Nov 18, 2013
 *      Author: baibhav
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/core/core.hpp>
#include "opencv2/objdetect/objdetect.hpp"



#ifndef HOGOPEN_H_
#define HOGOPEN_H_

using namespace cv;
using namespace std;

void write(string filename){
	stringstream myString;
	int array[] = {1,3,4,5};

	int size = (sizeof(array)/sizeof(*array));

	for(int i=0;i<size;i++){
		myString << i << ":" << array[i] << " ";
	}

	ofstream File(filename.c_str(), ios::out); //ios::app

	File << myString.str() << endl;

	File.close();
}

void displayHog(){
	Mat img_raw = imread("img/1.jpg", 1); // load as color image

	resize(img_raw, img_raw, Size(64,128) );

	Mat img;
	cvtColor(img_raw, img, 6); // CV_RGB2GRAY =6

	stringstream myString;

//	hog(image, orientations=9, pixels_per_cell=(8, 8),
//	        cells_per_block=(2, 2), visualise=False, normalise=True):

	// (winSize.width - blockSize.width) % blockStride.width == 0
	// (64 - 18) % 9
	HOGDescriptor d;
//	d.blockSize=Size(18,18);
//	d.cellSize=Size(6,6);
//	d.blockStride=Size(9,9);
//	d.nbins = 9;

	// Size(128,64), //winSize
	// Size(16,16), //blocksize
	// Size(8,8), //blockStride,
	// Size(8,8), //cellSize,
	// 9, //nbins,
	// 0, //derivAper,
	// -1, //winSigma,
	// 0, //histogramNormType,
	// 0.2, //L2HysThresh,
	// 0 //gammal correction,
	// //nlevels=64
	//);

	// void HOGDescriptor::compute(const Mat& img, vector<float>& descriptors,
	//                             Size winStride, Size padding,
	//                             const vector<Point>& locations) const
	vector<float> descriptorsValues;
	vector<Point> locations;
//	d.compute( img, descriptorsValues, Size(0,0), Size(0,0), locations);

	d.compute( img, descriptorsValues, Size(32,32), Size(0,0), locations);

	cout << "HOG descriptor size is " << d.getDescriptorSize() << endl;
	cout << "img dimensions: " << img.cols << " width x " << img.rows << "height" << endl;
	cout << "Found " << descriptorsValues.size() << " descriptor values" << endl;
	cout << "Nr of locations specified : " << locations.size() << endl;

//	HOG descriptor length = #Blocks * #CellsPerBlock * #BinsPerCell
//	                       = (64/8-1) * (128/8-1) * (2*2) * 9
//	                       = 7        * 15        *  4    * 9
//	                       = 3780

//	Dalal
//	3x3 cell blocks of 6x6 pixel cells with 9


	for (size_t n = 1; n <= descriptorsValues.size(); n++)
//	    cout << descriptorsValues[ n ] << " ";
		myString << n << ":" << descriptorsValues[ n ] << " ";
	cout << endl;



}
#endif /* HOGOPEN_H_ */
