#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void 
process(const char* imsname)
{
  Mat ims = imread(imsname,CV_LOAD_IMAGE_COLOR);
  Size s = ims.size();
  std::cout<<"Image size H = " << s.height << " W = " << s.width << "\n" <<std::endl;

  time_t start,end;
  time(&start);
  //code here
  time(&end);
  double time_elapsed = difftime(end,start);
  std::cout<<"Elapsed time = " << time_elapsed << " seconds \n" <<std::endl;
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
