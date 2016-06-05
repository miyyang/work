#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int window[9];

uchar myfilter2d(Mat kernel)
{
    double ret = 0;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            ret += window[y * 3 + x] * kernel.at<float>(y, x);
    if (ret > 255) ret = 255;
    if (ret < 0) ret = 0;
    uchar temp = (uchar)ret;
    return temp;
}

int main()
{
    Mat src, dst;
    
    // initial params
    Mat kernel1 = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    Mat kernel2 = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Point anchor = Point(-1, -1);   // kernel center
    double delta = 0;
    int ddepth = -1;                // same as src.depth();;
    
    // load image
    src = imread("/Users/yangzhi/Desktop/cv_lab/blood1.bmp");
    //src = imread("/Users/yangzhi/Desktop/cv_lab/map.bmp");
    cvtColor(src, src, CV_RGB2GRAY);
    
    // apply filter
    imshow("original picture", src);
    filter2D(src, dst, ddepth , kernel1, anchor, delta, BORDER_DEFAULT);
    imshow("sobel result 1", dst);
    filter2D(src, dst, ddepth , kernel2, anchor, delta, BORDER_DEFAULT);
    imshow("sobel result 2", dst);
    
    // my implementation 2
    for (int y = 1; y < src.rows - 1; y++)
        for (int x = 1; x < src.cols - 1; x++)
        {
            window[0] = src.at<uchar>(y - 1, x - 1);
            window[1] = src.at<uchar>(y + 1, x + 1);
            window[2] = src.at<uchar>(y - 1, x + 1);
            window[3] = src.at<uchar>(y + 1, x - 1);
            window[4] = src.at<uchar>(y, x - 1);
            window[5] = src.at<uchar>(y, x + 1);
            window[6] = src.at<uchar>(y - 1, x);
            window[7] = src.at<uchar>(y + 1, x);
            window[8] = src.at<uchar>(y, x);
            dst.at<uchar>(y, x) =  myfilter2d(kernel2);
        }
    imshow("my sobel result 2", dst);
    
    waitKey(0);
    return 0;
}