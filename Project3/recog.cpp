#include "recog.h"

Recog::Recog() {

}

cv::Mat Recog::getNearestNeighbour(const cv::Mat& mat) { //returns altered matrix using nearest neighbour
	return mat;
}
cv::Mat Recog::getCentroid(const cv::Mat& mat) { //returns altered matrix using centeroid method
	return mat;
}
cv::Mat Recog::compare(const cv::Mat& mat1, const cv::Mat& mat2) { //matrix comparison, which one is better, returns best matrix
	cv::Mat mat;
	return mat;
}
double Recog::getScore(const cv::Mat& mat) { //gives a rating for how good the result is comparatively, SNR similarity
	return 0.0;
}
bool Recog::isAcceptableResult(double score) { //gives a result of if the result is acceptable, accoring to score
	double threshhold = 1/2; //some arbitrary number 0-1
	return score >= threshhold;
}