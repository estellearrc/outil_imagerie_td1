#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <fstream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int slider_pos; //slider pos value
int slider_max; //slider max value
VideoCapture cap;

bool exists_file (const char *filename) {
    ifstream f(filename);
    return f.good();
}

void onTrackbarSlide(int, void*)
{
    cap.set(CV_CAP_PROP_POS_FRAMES, slider_pos);
    std::cout << "to go to frame number = " << slider_pos << "\n" << std::endl;
}

void
process(const char* vidname)
{
  bool exist = exists_file(vidname);
  if(!exist){
    std::cerr<<"The file doesn't exist, check its location.\n"<<std::endl;
    exit(EXIT_FAILURE);
  }

  cap = VideoCapture(vidname);
  Mat frame;
  namedWindow("video",1);

  double fps  = cap.get(CV_CAP_PROP_FPS);
  double width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  double height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  double nbOfFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);

  std::cout << "fps =" << fps << " number of frames =" << nbOfFrames << "\n" << std::endl;
  std::cout << "width =" << width << " height =" << height << "\n" << std::endl;
  
  slider_pos = 0;
  slider_max = nbOfFrames;
  //make trackbar call back
  createTrackbar("slider", "video", &slider_pos, slider_max, onTrackbarSlide);


  while(1){
    cap >> frame;
    if(!frame.data)
      break;
    int currentFrame = cap.get(CV_CAP_PROP_POS_FRAMES);
    if(currentFrame >= 1000){
      if(slider_pos >= 1000){
        cap.set(CV_CAP_PROP_POS_FRAMES, slider_pos);
      }
      else{
        cap.set(CV_CAP_PROP_POS_FRAMES, 1000);
      }
    }

    std::stringstream sstm;
    sstm << "frame number = " << cap.get(CV_CAP_PROP_POS_FRAMES) ;
    string result = sstm.str();
    putText(frame, result, Point2f(20,20), FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255,255));
    imshow("video",frame);

    char c=(char)waitKey(30);
    if(c==27)
      break;
  }
  cap.release();
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
