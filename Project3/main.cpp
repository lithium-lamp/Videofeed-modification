#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <algorithm>

#include "effects.h"

int main()
{
    //Open the default video camera
    cv::VideoCapture cap(0);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        std::cout << "Cannot open the video camera" << std::endl;
        std::cin.get(); //wait for any key press
        return -1;
    }

    double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "Resolution of the video : " << dWidth << " x " << dHeight << std::endl;

    //std::string window_name = "My Camera Feed";
    //cv::namedWindow(window_name); //create a window called "My Camera Feed"

    std::string filtered_window_name = "My Camera Feed (filtered)";
    cv::namedWindow(filtered_window_name); //create a window called "My Camera Feed (filtered)"

    //Create trackbar to change kernel size
    int iSliderValue1 = 25;
    cv::createTrackbar("Kernel size", filtered_window_name, &iSliderValue1, 100);

    //Create trackbar to change contrast
    int iSliderValue2 = 50;
    cv::createTrackbar("Contrast", filtered_window_name, &iSliderValue2, 100);

    //Create trackbar to change low threshhold
    int iSliderValue3 = 50;
    cv::createTrackbar("Low Threshhold", filtered_window_name, &iSliderValue3, 100);

    //Create trackbar to change high threshhold
    int iSliderValue4 = 5;
    cv::createTrackbar("high Threshhold", filtered_window_name, &iSliderValue4, 10);

    
    Effects e;

    while (true)
    {
        cv::Mat frame;
        cv::Mat filteredFrame;

        bool bSuccess = cap.read(frame); // read a new frame from video 

        //Breaking the while loop if the frames cannot be captured
        if (bSuccess == false)
        {
            std::cout << "Video camera is disconnected" << std::endl;
            std::cin.get(); //Wait for any key press
            break;
        }

        
        int k_size = iSliderValue1;
        double c = iSliderValue2 / 50.0;
        double l_t = iSliderValue3;
        double h_t = iSliderValue4;


        filteredFrame = e.createFaceOutline(frame, k_size, c, l_t, h_t);

        filteredFrame = e.flipImage(filteredFrame);

        //show the frame in the created window
        imshow(filtered_window_name, filteredFrame);

        //imshow(filtered_window_name, filteredFrame);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop 
        if (cv::waitKey(10) == 27)
        {
            std::cout << "Esc key is pressed by user. Stoppig the video" << std::endl;
            break;
        }
    }

    return 0;
}

