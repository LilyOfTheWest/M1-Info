#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>

using namespace std;

int main() {

        cv::Mat mat;
        mat = cv::imread("img.jpg");
        cvNamedWindow("hello");
        cv::imshow("hello",mat);

        cvWaitKey(0);

        return 0;
}
