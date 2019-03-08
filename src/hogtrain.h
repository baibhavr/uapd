/*
 * hogopen.h
 *
 *  Created on: Nov 18, 2013
 *      Author: baibhav
 */

#include <unistd.h>
#include <fstream>
#include <sstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "highgui.h"

#include <opencv2/core/core.hpp>
#include "opencv2/objdetect/objdetect.hpp"

#ifndef HOGOPEN_H_
#define HOGOPEN_H_

using namespace cv;
using namespace std;

void hogtrain(string path,string trained,int flag,int a,int b){
	stringstream myString,filename;
	HOGDescriptor d;
	vector<float> descriptorsValues;
	vector<Point> locations;

	if ( flag != 0){
	// EXTRACT HOG FROM ALL PICTURES

		for (int i = a; i <= b; i++){
			filename << path << i << ".jpg";

			ifstream my_file(filename.str().c_str());
			if (my_file.good())
				{
					my_file.close();
					cout << filename.str() << endl;
					Mat img_raw,img;
					img_raw = imread(filename.str(), 1); // load as color image
			//		resize(img_raw, img_raw, Size(64,128) );

					cvtColor(img_raw, img, 6); // CV_RGB2GRAY =6

					d.compute( img, descriptorsValues, Size(32,32), Size(0,0), locations);

					// STORE HOG OF POSITIVE PICTURES

					myString << flag << " " ;
					for (size_t n = 1; n <= descriptorsValues.size(); n++)
						myString << n << ":" << descriptorsValues[ n ] << " ";
					myString << endl;
					filename.str("");
					img.release();
					img_raw.release();
				}
			my_file.close();
		}

	}

	else{
		for (int i = a; i <= b; i++) {
			filename << path << i << ".png";

			ifstream my_file(filename.str().c_str());
			if (my_file.good())
				{
					cout << filename.str() << endl;
					Mat img_raw, img, bigimg;
					bigimg = imread(filename.str(), 1); // load as color image

					Rect myROI(10,10,64,128);
					img_raw = bigimg(myROI);

					//		resize(img_raw, img_raw, Size(64,128) );
					cvtColor(img_raw, img, 6); // CV_RGB2GRAY =6

					d.compute(img, descriptorsValues, Size(32, 32), Size(0, 0),
							locations);

					// STORE HOG OF POSITIVE PICTURES

					myString << flag << " ";
					for (size_t n = 1; n <= descriptorsValues.size(); n++)
						myString << n << ":" << descriptorsValues[n] << " ";
					myString << endl;
					filename.str("");
					img.release();
					img_raw.release();
				}
			my_file.close();
		}

	}

//	cout << myString.str() << endl;
	// Write to file
	ofstream myFile(trained.c_str(), ios::app); // ios::out //ios::app
	myFile << myString.str();
	myFile.close();

}
#endif /* HOGOPEN_H_ */
