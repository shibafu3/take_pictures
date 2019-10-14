#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
/*OpenCVライブラリ*/
#include <opencv2/opencv.hpp>
//Matとか行列モジュール
#include <opencv2/core/core.hpp>
//GUIモジュール
#include <opencv2/highgui/highgui.hpp>
//キャリブレーションモジュール
#include <opencv2/calib3d/calib3d.hpp>
#include "webcam.h"




#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    Mat image1;


    VideoCapture cap1(0);
    if (!cap1.isOpened()) { return -1; }
    cap1.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

    if (c_init()) { cout << "Error : c_init():" << endl; return 1; }

    CHandle handle = c_open_device ("video0");
    if (!handle) { cout << "Error : c_open_device():\n"; c_cleanup (); return 2; }

    CControlValue value;
    if (c_get_control(handle, CControlId(CC_FOCUS_ABSOLUTE), &value)) { std::cout << "Error : c_get_control(): " << endl; }
    cout << value.value << endl;

    value.value = 0;
    if (c_set_control(handle, CControlId(CC_AUTO_FOCUS), &value)) { std::cout << "Error : c_set_control(): " << endl; }
    if (c_set_control(handle, CControlId(CC_FOCUS_ABSOLUTE), &value)) { std::cout << "Error : c_set_control(): " << endl; }


    char file_name[256];
    int itr = 0;
    while (1) {
        cap1 >> image1;

        imshow("image1", image1);
        if (waitKey(33) == 32) { // 32 = space key
            printf("%d.jpg\n", itr);
            sprintf(file_name, "%d.jpg", itr++);
            imwrite(file_name, image1);
        }

        if (waitKey(1) == 27) { break; }
    }
    cap1.release();
    c_close_device (handle);
    c_cleanup ();
    return 0;
}