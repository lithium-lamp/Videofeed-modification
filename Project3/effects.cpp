#include "effects.h"

Effects::Effects() {

}

cv::Mat Effects::blur(const cv::Mat& frame, int kernel_size) {
    cv::Mat mat;
    cv::GaussianBlur(frame, mat, cv::Size(kernel_size, kernel_size), 0);

	return mat;
}

cv::Mat Effects::getMask(const cv::Mat& frame, double lowerthreshhold, double upperthreshhold) {
    cv::Mat mat = frame;

    uint8_t* pixelPtr = (uint8_t*)frame.data;
    int cn = frame.channels();
    cv::Scalar_<uint8_t> bgrPixel;

    cv::Vec3b blackPixel;
    blackPixel.val[0] = 0; blackPixel.val[1] = 0; blackPixel.val[2] = 0;
    cv::Vec3b whitePixel;
    whitePixel.val[0] = 255; whitePixel.val[1] = 255; whitePixel.val[2] = 255;

    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            bgrPixel.val[0] = pixelPtr[i * frame.cols * cn + j * cn + 0]; // B
            bgrPixel.val[1] = pixelPtr[i * frame.cols * cn + j * cn + 1]; // G
            bgrPixel.val[2] = pixelPtr[i * frame.cols * cn + j * cn + 2]; // R

            double meanval = (bgrPixel.val[0] + bgrPixel.val[1] + bgrPixel.val[2]) / 3;

            if (meanval >= lowerthreshhold && meanval <= lowerthreshhold + upperthreshhold)
                mat.at<cv::Vec3b>(i, j) = whitePixel;
            else
                mat.at<cv::Vec3b>(i, j) = blackPixel;
        }
    }

    return mat;
}

cv::Mat Effects::changeContrast(const cv::Mat& frame, double scalar) {
    cv::Mat mat;

    frame.convertTo(mat, -1, scalar, 0);
    
    return mat;
}

cv::Mat Effects::outline(const cv::Mat& frame) { //picture given in black and white, only one channel relevant
    cv::Mat mat = frame;

    cv::Vec3b redPixel;
    redPixel.val[0] = 0; redPixel.val[1] = 0; redPixel.val[2] = 255; //only red channel given value

    int dim_of_line = 1;

    for (int i = 0; i < (frame.rows - dim_of_line); i++)
    {
        for (int j = 0; j < (frame.cols - dim_of_line); j++)
        {
            cv::Vec3b bgrPixel = frame.at<cv::Vec3b>(i, j);

            cv::Vec3b rightPixel = frame.at<cv::Vec3b>(i + 1, j);

            if (bgrPixel.val[0] == 255 && rightPixel.val[0] == 0) {
                mat.at<cv::Vec3b>(i, j) = redPixel;
                mat.at<cv::Vec3b>(i + 1, j) = redPixel;
                mat.at<cv::Vec3b>(i, j + 1) = redPixel;
                mat.at<cv::Vec3b>(i + 1, j + 1) = redPixel;
            }
            else if (bgrPixel.val[0] == 0 && rightPixel.val[0] == 255) {
                mat.at<cv::Vec3b>(i, j) = redPixel;
                mat.at<cv::Vec3b>(i + 1, j) = redPixel;
                mat.at<cv::Vec3b>(i, j + 1) = redPixel;
                mat.at<cv::Vec3b>(i + 1, j + 1) = redPixel;
            }
            
        }
    }

    return mat;
}

cv::Mat Effects::removeMask(const cv::Mat& frame) {
    cv::Mat mat = frame;

    cv::Vec3b blackPixel;
    blackPixel.val[0] = 0; blackPixel.val[1] = 0; blackPixel.val[2] = 0;

    cv::Vec3b redPixel;
    redPixel.val[0] = 0; redPixel.val[1] = 0; redPixel.val[2] = 255;
    
    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            cv::Vec3b framePixel = frame.at<cv::Vec3b>(i, j);

            if (framePixel.val[2] == 255 && framePixel.val[1] == 0 && framePixel.val[0] == 0)
                mat.at<cv::Vec3b>(i, j) = redPixel;
            else
                mat.at<cv::Vec3b>(i, j) = blackPixel;
        }
    }

    return mat;
}

cv::Mat Effects::createFaceOutline(const cv::Mat& frame, int k_size, double c, double l_t, double h_t) {
    cv::Mat filteredFrame = frame;
    cv::Mat mask;

    k_size = toOdd(k_size);

    filteredFrame = blur(filteredFrame, k_size); //kernel size must be odd

    filteredFrame = changeContrast(filteredFrame, c); //contrast increase
    
    mask = getMask(filteredFrame, l_t, h_t); //lowerthreshhold, upperthreshhold

    filteredFrame = outline(mask); //outline

    filteredFrame = removeMask(filteredFrame);

    //filteredFrame = blur(filteredFrame, 25); //kernel size must be odd

    //filteredFrame = changeContrast(filteredFrame, 5); //contrast increase

    cv::add(frame, filteredFrame, filteredFrame);

    return filteredFrame;
}

int Effects::toOdd(int num) {
    if (num % 2 == 0)
        num++;

    return num;
}

cv::Mat Effects::flipImage(const cv::Mat& mat) {
    cv::Mat dst;

    cv::flip(mat, dst, 1);

    return dst;
}