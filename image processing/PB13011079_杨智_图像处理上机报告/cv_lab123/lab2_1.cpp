#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

void add_noise(Mat& in, Mat& out, double ratio)
{
    out = in.clone();
    int noisepixels = in.cols * in.rows * ratio;
    for (int i = 0; i < noisepixels; i++)
    {
        int x = rand() % in.cols;
        int y = rand() % in.rows;
        int w = rand() % 2;
        out.at<uchar>(y, x) = w ? 255 : 0;
    }
}

int main()
{
    Mat src, noise_src, dst;
    add_noise(src, noise_src, 0.03);
    
    // initial params
    Mat kernel = (Mat_<float>(3, 3) << 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9);
    Point anchor = Point(-1, -1);   // kernel center
    double delta = 0;
    int ddepth = -1;                // same as src.depth();;
    
    // load image
    src = imread("/Users/yangzhi/Desktop/cv_lab/lena.bmp");
    cvtColor(src, src, CV_BGR2GRAY);
    // src = imread("/Users/yangzhi/Desktop/cv_lab/map.bmp");
    add_noise(src, noise_src, 0.03);
    
    // apply filter
    filter2D(noise_src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT);
    imshow("original image", src);
    imshow("original image with 3% noise", noise_src);
    imshow("average filter result", dst);
    
    waitKey(0);
    return 0;
}