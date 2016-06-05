#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void myequalizeHist(Mat in, Mat &out)
{
    // calculate hist
    MatND hist;
    const int channel[1]={0};
    const int histsize[1]={256};
    float histrange[2]={0, 255};
    const float* range[1]={histrange};
    calcHist(&in, 1, channel, Mat(), hist, 1, histsize, range);
    
    // calculate lookup table
    float scale[256];
    float lookupTable[256];
    Mat lookupFunc(cv::Size(1, 256), CV_8U);
    int total_length = in.cols * in.rows;
    for (int i =0; i < 256; i++)
    {
        scale[i] = hist.at<float>(i) / total_length *255;
        if (i == 0)
            lookupTable[i] = scale[i];
        else
            lookupTable[i] = lookupTable[i -1] + scale[i];
    }
    for (int i =0; i <256; i++) {
        lookupFunc.at<uchar>(i) = static_cast<uchar>(lookupTable[i]);
    }
    
    // convert
    LUT(in, lookupFunc, out);
}

int main()
{
    // load image
    Mat temp_img;
    Mat img;
    Mat standard_new_img;
    Mat my_new_img;
    temp_img = imread("/Users/yangzhi/Desktop/cv_lab/pout.bmp");
    cvtColor(temp_img, img, CV_RGB2GRAY);
    imshow("original picture", img);
    
    // standard equalizeHist
    equalizeHist(img, standard_new_img);
    imshow("standard equalizeHist picture", standard_new_img);
    
    // my equalizeHist
    myequalizeHist(img, my_new_img);
    imshow("my equalizeHist picture", my_new_img);
    
    waitKey(0);
    return 0;
    
}

