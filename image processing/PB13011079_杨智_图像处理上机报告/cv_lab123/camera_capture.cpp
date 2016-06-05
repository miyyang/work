#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

IplImage* doCanny(IplImage* image_input,
                  double lowThresh,
                  double highThresh,
                  double aperture)
{
    if(image_input->nChannels != 1)
        return (0);
    
    IplImage* image_output = cvCreateImage(cvGetSize(image_input),
                                           image_input->depth,
                                           image_input->nChannels);
    
    cvCanny(image_input,image_output,lowThresh,highThresh,aperture);
    
    return(image_output);
}


int main(int argc, char* argv[])
{
    cvNamedWindow("Camera" , CV_WINDOW_AUTOSIZE );
    
    CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
    
    //assert(capture != NULL);
    
    IplImage *frame = 0;
    frame = cvQueryFrame(capture);
    
    IplImage *frame_edge = cvCreateImage(cvGetSize(frame),
                                         IPL_DEPTH_8U,
                                         1);
    while(1)
    {
        frame = cvQueryFrame(capture);
        if(!frame) break;
        
        cvConvertImage(frame,frame_edge,0);
        frame = cvCloneImage(frame_edge);
        
        frame_edge = doCanny(frame_edge,70,90,3);
        
        cvShowImage("Camera",frame_edge);
        char c = cvWaitKey(15);
        if(c == 27)  break;
    }
    
    cvReleaseCapture(&capture);
    cvReleaseImage( &frame_edge );
    cvReleaseImage( &frame);
    
    
    return (int)0;
}