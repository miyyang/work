#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main()
{
    // set params
    double fa, fb;
    scanf("%lf %lf", &fa, &fb);
    // initial lookup table
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
    {
        int temp = i * fa + fb;
        temp = (temp > 255)? 255 : temp;
        temp = (temp < 0)? 0 : temp;
        p[i] = saturate_cast<uchar>(i * fa + fb);
    }
    // display picture
    Mat img = imread("/Users/yangzhi/Desktop/cv_lab/lena.bmp");
    cvtColor(img, img, CV_BGR2GRAY);
    imshow("original picture", img);
    Mat new_img;
    LUT(img, lookUpTable, new_img);
    imshow("modified picture", new_img);
    waitKey(0);
    return 1;
}