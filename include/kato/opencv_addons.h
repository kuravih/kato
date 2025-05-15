#ifndef __KATO_FUNCTION_OPENCV_ADDONS_H__
#define __KATO_FUNCTION_OPENCV_ADDONS_H__

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/freetype.hpp> // Include the FreeType module
#include <string>

namespace kato::function
{
    const cv::Mat cvMean(const std::vector<cv::Mat> &);
    const cv::Mat cvFuseExposures(const std::vector<cv::Mat> &, const std::vector<uint> &, const float, const float threshold = 0.9);
    void cvCopy(const std::vector<cv::Mat> &, std::vector<cv::Mat> &);
    const std::string cvInfo(const cv::Mat &);
    const std::string cvInfo(const std::vector<cv::Mat> &);
    const std::string cvInfo(const std::vector<std::vector<cv::Mat>> &);
    const std::string cvTypeToString(const int);
    const float cvTypeMax(const int);
    const int cvTypeToSize(const int);
    cv::Ptr<cv::freetype::FreeType2> cvCustomFont(std::string);
    void cvPutText(cv::Mat&, std::string, cv::Point, double, const cv::Scalar &color = cv::Scalar(200, 200, 200), cv::Ptr<cv::freetype::FreeType2> font = NULL);
    void cvDistanceCircle(cv::Mat &, cv::Point, float, const cv::Scalar &color = cv::Scalar(255));

    void calcHistogram(const cv::Mat &, const cv::Mat &, std::vector<uint> &, const int, const float *&, const bool uniform = true, const bool accumulate = false);
};

// pkg-config --cflags --libs opencv4

#endif // __KATO_FUNCTION_OPENCV_ADDONS_H__