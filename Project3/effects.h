#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

class Effects
{
public:
	Effects();

	cv::Mat blur(const cv::Mat& frame, int kernel_size);

	cv::Mat getMask(const cv::Mat& frame, double lowerthreshhold, double upperthreshhold);

	cv::Mat changeContrast(const cv::Mat& frame, double scalar);

	cv::Mat outline(const cv::Mat& frame);

	cv::Mat removeMask(const cv::Mat& frame);

	cv::Mat createFaceOutline(const cv::Mat& frame, int k_size, double c, double l_t, double h_t);

	int toOdd(int num);

	cv::Mat flipImage(const cv::Mat& mat);
};