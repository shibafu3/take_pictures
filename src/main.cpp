#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"D:/home/Sources/opencv/opencv310/build/install/lib/opencv_world310d.lib")            // opencv_core
#else
//Releaseモードの場合
#pragma comment(lib,"D:/home/Sources/opencv/opencv310/build/install/lib/opencv_world310.lib") 
#endif


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




#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    Mat image1;


    VideoCapture cap1(0);
    if (!cap1.isOpened()) { return -1; }
    cap1.set(CV_CAP_PROP_FRAME_WIDTH, 960);
    cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 540);


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
    }
    cap1.release();
    return 0;
}