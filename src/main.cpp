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

#include "ewclib.h"


#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(char argc, char *argv[]) {
    cv::Mat_<cv::Vec3b> image1;

    int camera_number = 0;
    if (argc == 2) {
        camera_number = stoi(argv[1]);
    }
    int is_error = EWC_Open(camera_number, 1280, 720, 30, camera_number, MEDIASUBTYPE_RGB24);
    EWC_SetValue(camera_number, EWC_FOCUS, 0.0);
    image1 = cv::Mat_<cv::Vec3b>(720, 1280);

    char file_name[256];
    int itr = 0;
    while (1) {
        EWC_GetImage(camera_number, image1.data);

        imshow("image1", image1);
        if (waitKey(33) == 32) { // 32 = space key
            printf("%d.jpg\n", itr);
            sprintf_s(file_name, "%d.jpg", itr++);
            imwrite(file_name, image1);
        }

        if (waitKey(1) == 27) { break; }
    }
    return 0;
}