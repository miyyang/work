#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main()
{
    Mat src, dst1, dst2;
    Mat result;
    
    // initial params
    Mat kernel1 = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    Mat kernel2 = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Point anchor = Point(-1, -1);   // kernel center
    double delta = 0;
    int ddepth = -1;                // same as src.depth();;
    
    // load image
    // src = imread("/Users/yangzhi/Desktop/cv_lab/blood1.bmp");
    src = imread("/Users/yangzhi/Desktop/cv_lab/map.bmp");
    cvtColor(src, src, CV_RGB2GRAY);
    
    // apply filter
    imshow("original picture", src);
    filter2D(src, dst1, ddepth , kernel1, anchor, delta, BORDER_DEFAULT);
    imshow("kernel1", dst1);
    filter2D(src, dst2, ddepth , kernel2, anchor, delta, BORDER_DEFAULT);
    imshow("kernel2", dst2);
    
    cv::max(dst1, dst2, result);
    imshow("Sobel result", result);
    
    waitKey(0);
    return 0;
}