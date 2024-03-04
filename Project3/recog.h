#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

class Recog
{
public:
	Recog();

	cv::Mat getNearestNeighbour(const cv::Mat& mat); //returns altered matrix using nearest neighbour

	cv::Mat getCentroid(const cv::Mat & mat); //returns altered matrix using centeroid method

	cv::Mat compare(const cv::Mat& mat1, const cv::Mat& mat2); //matrix comparison, which one is better, returns best matrix

	double getScore(const cv::Mat& mat); //gives a rating for how good the result is comparatively, SNR similarity

	bool isAcceptableResult(double score); //gives a result of if the result is acceptable, accoring to score
};