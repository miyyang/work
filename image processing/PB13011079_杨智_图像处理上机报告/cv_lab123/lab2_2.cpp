#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define WIDTH 3

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

void insertionSort(int a[])
{
    int temp, i , j;
    for(i = 0; i < WIDTH * WIDTH; i++){
        temp = a[i];
        for(j = i - 1; j >= 0 && temp < a[j]; j--)
            a[j + 1] = a[j];
        a[j+1] = temp;
    }
}

int main()
{
    Mat src, noise_src, standard_dst, my_dst;
    add_noise(src, noise_src, 0.03);
    
    // load image
    src = imread("/Users/yangzhi/Desktop/cv_lab/lena.bmp");
    cvtColor(src, src, CV_BGR2GRAY);
    // src = imread("/Users/yangzhi/Desktop/cv_lab/map.bmp");
    add_noise(src, noise_src, 0.03);
    
    // show image
    imshow("original image", src);
    imshow("original image with 3% noise", noise_src);
    
    // apply standard filter
    medianBlur(noise_src, standard_dst, 3);
    imshow("standard average filter result", standard_dst);
    
    // apply my filter
    int window[WIDTH * WIDTH];
    my_dst = Mat::zeros(noise_src.rows, noise_src.cols, noise_src.type());
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
            insertionSort(window);
            my_dst.at<uchar>(y, x) = window[4];
        }
    imshow("my average filter result", my_dst);
    
    waitKey(0);
    return 0;
}