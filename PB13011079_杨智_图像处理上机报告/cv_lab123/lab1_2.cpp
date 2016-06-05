#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main()
{
    // set params
    double x1, y1, x2, y2;
    printf("intput x1 y1 x2 y2\n");
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    // initial lookup table
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
    {
        if (i < x1)
            p[i] = saturate_cast<uchar>(y1 / x1 * i);
        else if (i >= x1 && i <= x2)
            p[i] = saturate_cast<uchar>((y2 - y1) / (x2 - x1) * (i - x1) + y1);
        else
            p[i] = saturate_cast<uchar>((255 - y2) / (255 - x2) * (i - x2) + y2);
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