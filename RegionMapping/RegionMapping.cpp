#include <iostream>
#include <fstream>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace cv;
using namespace std;

// parameters
double radius = 2.78;
int x_value = 184;
int y_value = 195;


void mapping_test(const char* txtPath, const char* imagePath, const char* savePath) {
	ifstream in(txtPath);
	char line[1024];
	char* pch;

	// load image
	Mat sourceImage = imread(imagePath, 1);
	int height = sourceImage.rows;
	int width = sourceImage.cols;

	while (in) {
		printf("============ \n");
		in.getline(line, 255);  // delim defaults to '\n'
		//cout << line << endl;

		pch = strtok(line, " ");
		if (pch != NULL) {
			char* xminValue = pch;
			char* yminValue = strtok(NULL, " ");
			char* xmaxValue = strtok(NULL, " ");
			char* ymaxValue = strtok(NULL, " ");

			int xmin = atoi(xminValue) / radius + x_value;
			int ymin = atoi(yminValue) / radius + y_value;
			int xmax = atoi(xmaxValue) / radius + x_value;
			int ymax = atoi(ymaxValue) / radius + y_value;
						
			for (int i = ymin; i <= ymax; i++) {
				for (int j = xmin; j <= xmax; j++) {
					sourceImage.at<Vec3b>(i, j) = 0;
				}
			}

		}
	}


	imshow("sourceImage", sourceImage);
	imwrite(savePath, sourceImage);
	waitKey(0);

	in.close();
}

void main() {
	mapping("DetectionUsingLocalFocalLengths.txt", "ShortFocalLengthImage.png", "MappingResult.png");
}
