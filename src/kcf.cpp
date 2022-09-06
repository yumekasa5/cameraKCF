#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>


#define OUTPUT_VIDEO_NAME "../output/tracvideo.mp4"

using namespace std;
using namespace cv;
int main( int argc, char** argv ){
  // show help
  
  // declares all required variables
  Rect2d roi;
  Mat frame;
  // create a tracker object
  Ptr<Tracker> tracker = TrackerKCF::create();
  
  // set input video
  VideoCapture cap(0);
  
  //VideoCapture cap(0);
  cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,480); 
  //get bounding box
  cap >> frame;

  roi=selectROI("tracker",frame);
  //quit if ROI was not selected
  if(roi.width==0 || roi.height==0)
    return 0;
  // initialize the tracker
  tracker->init(frame,roi);

  //record the video
  string filename=OUTPUT_VIDEO_NAME;
  int fourcc=VideoWriter::fourcc('M','P','4','V');
  double fps=30.0;
  cout<<"framerate="<<fps<<endl;
  VideoWriter writer(filename,fourcc,fps,frame.size());
  
  // perform the tracking process
  printf("Start the tracking process, press ESC to quit.\n");
  for ( ;; ){
    //get frame from the video
    cap >> frame;

    // stop the program if no more images
    if(frame.rows==0 || frame.cols==0)
      break;
    // update the tracking result
    tracker->update(frame,roi);

    // calculate center of roi
    cv::Point2d center = cv::Point2d(roi.x + roi.width/2 , roi.y + roi.height/2 );

    // draw the tracking object
    rectangle( frame, roi, Scalar( 255, 0, 0 ), 2, 1 );
    cv::circle(frame, center, 1, cv::Scalar(0,255,0), -1);
      
    writer<<frame;

    // show image with the tracked object
    imshow("tracker",frame);
    //quit on ESC button
    if(waitKey(1)==27)break;
  }

  return 0;
}
