#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <webcam.h>
#include <libwebcam.h>
 
int
switchFocus (CHandle handle)
{
 
  CControlId controlId = CC_AUTO_FOCUS;
  CResult ret = C_SUCCESS;
  CControlValue value;
 
  ret = c_get_control (handle, controlId, &value);
  if (ret) {
    std::cout << "Error : c_get_control(): " << ret << ")\n";
  }
 
  if (value.value == 1) {
    value.value = 0;
  } else {
    value.value = 1;
  }
 
  ret = c_set_control (handle, controlId, &value);
  if (ret) {
    std::cout << "Error : c_get_control(): " << ret << ")\n";
  }
 
  ret = c_get_control (handle, controlId, &value);
  if (ret) {
    std::cout << "Error : c_get_control(): " << ret << ")\n";
  }
 
  return value.value;
}
 
 
int
main (int argc, char *argv[])
{
 
  CResult ret = C_SUCCESS;
  CHandle handle = 0;
  int focus = 0;
 
  cv::VideoCapture cap (0);
  if (!cap.isOpened ()) {
    return 1;
  }
  cv::Size cap_size (640, 480);
  cap.set (CV_CAP_PROP_FRAME_WIDTH, cap_size.width);
  cap.set (CV_CAP_PROP_FRAME_HEIGHT, cap_size.height);
 
  int fps = 15;
 
  cv::VideoWriter writer ("sample10.avi", CV_FOURCC ('X', 'V', 'I', 'D'),
              fps, cap_size);
  cv::namedWindow ("Capture", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
 
  ret = c_init ();
  if (ret) {
    std::cout << "Error : c_init(): " << ret << ")\n";
    return 1;
  }
 
  handle = c_open_device ("video0");
  if (!handle) {
    std::cout << "Error : c_open_device():\n";
    c_cleanup ();
    return 2;
  }
  focus = switchFocus (handle);
 
  bool f_loop = true;
  while (f_loop) {
    char *msg;
    cv::Mat frame;
    cap >> frame;
    if (focus == 0) {
      msg = (char *) "Auto Focus is off";
    } else {
      msg = (char *) "Auto Focus is on";
    }
    cv::putText (frame, msg, cv::Point (50,50),
         cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar (100, 50, 50), 5,
         CV_AA);
    cv::imshow ("Capture", frame);
    writer << frame;
 
    switch (cv::waitKey (10)) {
    case 'f':
      focus = switchFocus (handle);
      break;
    case 'q':
      f_loop = false;
      break;
    default:
      break;
    }
  }
  c_close_device (handle);
  c_cleanup ();
 
  return 0;
}
