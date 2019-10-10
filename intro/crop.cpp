#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname, int i0, int j0, int w, int h)
{
	Mat image;
	image=imread(imsname,CV_LOAD_IMAGE_COLOR);
	Mat imgcrop(h, w, CV_8UC3);
	for (int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			imgcrop.at<Vec3b>(i, j) = image.at<Vec3b>(i0 + i, j0 + j);
		}
	}
  imwrite("crop.png", imgcrop);

  Mat imgCropRect = image(Rect(j0,i0,w,h));
  imwrite("crop-cv.png", imgCropRect);

  Mat diff = imgcrop - imgCropRect;
  imshow("diff",diff);
  waitKey(0);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname i0 j0 w h\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 5
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[5]), atoi(argv[4]));
  return EXIT_SUCCESS;
}
