#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int myfilter2d(int* window, Mat kernel)
{
    int ret = 0;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            ret += window[x * 3 + y] * kernel.at<uchar>(y, x);
    return ret;
}

int main()
{
    Mat src, dst;
    
    // initial params
    Mat kernel1 = (Mat_<float>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
    Mat kernel2 = (Mat_<float>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
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
    imshow("Laplacian result 1", dst);
    filter2D(src, dst, ddepth , kernel2, anchor, delta, BORDER_DEFAULT);
    imshow("Laplacian result 2", dst);
    
    // my implementation
    for (int y = 1; y < noise_src.rows - 1; y++)
        for (int x = 1; x < noise_src.cols - 1; x++)
        {
            window[0] = noise_src.at<uchar>(y - 1, x - 1);
            window[1] = noise_src.at<uchar>(y + 1, x + 1);
            window[2] = noise_src.at<uchar>(y - 1, x + 1);
            window[3] = noise_src.at<uchar>(y + 1, x - 1);
            window[4] = noise_src.at<uchar>(y, x - 1);
            window[5] = noise_src.at<uchar>(y, x + 1);
            window[6] = noise_src.at<uchar>(y - 1, x);
            window[7] = noise_src.at<uchar>(y + 1, x);
            window[8] = noise_src.at<uchar>(y, x);
            int temp = myfilter2d(window, kernel1);
            my_dst.at<uchar>(y, x) = temp;
        }
    waitKey(0);
    return 0;
}