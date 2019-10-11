#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void 
process(const char* imsname)
{
  std::cout<<"\n\n\n ===================================================\n EXERCICE 3 : PIXELS LOOPS \n ===================================================" <<std::endl;

  Mat ims = imread(imsname,CV_LOAD_IMAGE_COLOR);
  Size s = ims.size();
  std::cout<<"Image size H = " << s.height << " W = " << s.width << "\n" <<std::endl;


  double t = (double)getTickCount();
  for(int r = 0; r < ims.rows; r++) {
    // We obtain a pointer to the beginning of row r
    Vec3b* ptr = ims.ptr<Vec3b>(r);
    for(int c = 0; c < ims.cols; c++) {
      // We invert the blue and red values of the pixel
      ptr[c] = Vec3b(64*ptr[c][0]/64+64/2, 64*ptr[c][1]/64+64/2, 64*ptr[c][2]/64+64/2);
    }
  }t = ((double)getTickCount() - t)/getTickFrequency();
  cout << "Access with pointers. Times passed in seconds: " << t << endl;


  t = (double)getTickCount();
  Mat_<Vec3b>::iterator it = ims.begin<Vec3b>();
  Mat_<Vec3b>::iterator itEnd = ims.end<Vec3b>();
  for( ; it != itEnd; ++it)
  {
    (*it)[0] = 64*(*it)[0]/64+64/2;
    (*it)[1] = 64*(*it)[1]/64+64/2;
    (*it)[2] = 64*(*it)[2]/64+64/2;
  }
  t = ((double)getTickCount() - t)/getTickFrequency();
  cout << "Access with iterators. Times passed in seconds: " << t << endl;
  

  t = (double)getTickCount();
  // do something ...
  for (int i = 0; i < s.height; i++){
		for(int j = 0; j < s.width; j++){
			ims.at<Vec3b>(i, j)[0] = 64*ims.at<Vec3b>(i, j)[0]/64 + 64/2;
      ims.at<Vec3b>(i, j)[1] = 64*ims.at<Vec3b>(i, j)[1]/64 + 64/2;
      ims.at<Vec3b>(i, j)[2] = 64*ims.at<Vec3b>(i, j)[2]/64 + 64/2;
		}
	}
  t = ((double)getTickCount() - t)/getTickFrequency();
  cout << "Access with 'at' method. Times passed in seconds: " << t << endl;


  t = (double)getTickCount();
  // do something ...
  ims = 64*ims/64+64/2;
  t = ((double)getTickCount() - t)/getTickFrequency();
  cout << "Access with opencv operator redinition. Times passed in seconds: " << t << endl;
}

void 
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
  exit(EXIT_FAILURE);
}

#define param 1
int 
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  return EXIT_SUCCESS;  
}
