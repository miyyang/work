#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    // load image
    Mat temp_img;
    Mat img;
    MatND hist;
    temp_img = imread("/Users/yangzhi/Desktop/cv_lab/pout.bmp");
    cvtColor(temp_img, img, CV_RGB2GRAY);
    imshow("original picture", temp_img);
    
    // calculate hist
    printf("input lower bound and upper bound\n");
    float low, up;
    scanf("%f %f", &low, &up);
    const int channel[1]={0};
    const int histsize[1]={256};
    float histrange[2]={low, up};
    const float* range[1]={histrange};
    calcHist(&img, 1, channel, Mat(), hist, 1, histsize, range);
    
    // draw hist
    int length = up - low + 1;
    int height = 256;
    int wide = 2;
    double max;
    minMaxLoc(hist, 0, &max, 0, 0);
    Mat hist_img = Mat::zeros(height, length * wide, CV_8UC3);
    for(int i = 0; i < length; i++)
    {
        int img_high = cvRound(hist.at<float>(i) * height / max);
        rectangle(hist_img, Point(i * wide, height-1),
                  Point((i + 1) * wide - 1, height - img_high),
                  CV_RGB(255,255,255));
    }
    char temp[50];
    sprintf(temp, "hist from range (%d, %d)", (int)low, (int)up);
    imshow(temp, hist_img);
    waitKey(0);
    return 0;
    
}

