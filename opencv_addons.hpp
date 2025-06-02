#ifndef __KATO_FUNCTION_OPENCV_ADDONS_HPP__
#define __KATO_FUNCTION_OPENCV_ADDONS_HPP__

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/freetype.hpp> // Include the FreeType module
#include <string>

namespace kato::function
{
    const cv::Mat cvMean(const std::vector<cv::Mat> &_mats)
    {
        cv::Mat ret_meanImage(_mats[0].rows, _mats[0].cols, CV_64FC1, cv::Scalar::all(0));
        cv::Mat temp_doubleImage(_mats[0].rows, _mats[0].cols, CV_64FC1, cv::Scalar::all(0));
        for (const cv::Mat &image : _mats)
        {
            image.convertTo(temp_doubleImage, CV_64FC1, 1.0 / _mats.size());
            cv::accumulate(temp_doubleImage, ret_meanImage);
        }
        return ret_meanImage;
    }
    const cv::Mat cvFuseExposures(const std::vector<cv::Mat> &_exposures, const std::vector<uint> &_expTimes, const float _maxVal, const float threshold = 0.9)
    {
        float peakThreshold = _maxVal * threshold;
        cv::Mat ret_fusedImage(_exposures[0].rows, _exposures[0].cols, CV_64FC1, cv::Scalar::all(0));
        cv::Mat mask;
        cv::Mat denominator(_exposures[0].rows, _exposures[0].cols, CV_64FC1, cv::Scalar::all(0));
        cv::Mat maskedExposure(_exposures[0].rows, _exposures[0].cols, CV_64FC1, cv::Scalar::all(0));
        cv::Mat totalMaskedCounts(_exposures[0].rows, _exposures[0].cols, CV_64FC1, cv::Scalar::all(0));
        for (size_t i = 0; i < _expTimes.size(); i++)
        {
            cv::compare(_exposures[i], peakThreshold, mask, cv::CMP_LT);                               // get mask
            cv::multiply(_exposures[i], mask, maskedExposure, 1.0 / (255.0 * _expTimes[i]), CV_64FC1); // mask exposure
            cv::accumulate(maskedExposure, totalMaskedCounts);
            cv::accumulate(mask, denominator);
        }
        denominator = denominator / 255.0;
        ret_fusedImage = totalMaskedCounts / denominator;
        return ret_fusedImage;
    }
    void cvCopy(const std::vector<cv::Mat> &source, std::vector<cv::Mat> &destination)
    {
        destination.clear();
        for (const cv::Mat &frame : source)
            destination.push_back(frame.clone());
    }

    const std::string cvInfo(const cv::Mat &_mat)
    {
        std::stringstream out;
        out << "[" << cv::typeToString(_mat.type()) << " : ";
        for (int iDim = 0; iDim < _mat.dims; ++iDim)
        {
            if (iDim)
                out << " x ";
            out << _mat.size[iDim];
        }
        out << " : Ch ";
        out << _mat.channels();
        out << "]";
        return out.str();
    }
    const std::string cvInfo(const std::vector<cv::Mat> &_mats)
    {
        std::stringstream out;
        out << "[" << cv::typeToString(_mats[0].type()) << " : ";
        if (_mats.size())
        {
            out << _mats.size();
            out << " x ";
            for (int iDim = 0; iDim < _mats[0].dims; ++iDim)
            {
                if (iDim)
                    out << " x ";
                out << _mats[0].size[iDim];
            }
        }
        out << " : Ch ";
        out << _mats[0].channels();
        out << "]";
        return out.str();
    }
    const std::string cvInfo(const std::vector<std::vector<cv::Mat>> &_mats)
    {
        std::stringstream out;
        out << "[" << cv::typeToString(_mats[0][0].type()) << " : ";
        if (_mats.size())
        {
            out << _mats.size();
            out << " x ";
            if (_mats[0].size())
            {
                out << _mats[0].size();
                out << " x ";
                for (int iDim = 0; iDim < _mats[0][0].dims; ++iDim)
                {
                    if (iDim)
                        out << " x ";
                    out << _mats[0][0].size[iDim];
                }
            }
        }
        out << " : Ch ";
        out << _mats[0][0].channels();
        out << "]";
        return out.str();
    }
    const std::string cvTypeToString(const int _cvType)
    {
        if (_cvType == CV_8UC1)
            return "CV_8UC1";
        else if (_cvType == CV_16UC1)
            return "CV_16UC1";
        else if (_cvType == CV_8UC4) // unsupported by opencv
            return "CV_8UC4";
        else if (_cvType == CV_8UC(8)) // unsupported by opencv
            return "CV_8UC(8)";
        else if (_cvType == CV_32FC1)
            return "CV_32FC1";
        else if (_cvType == CV_64FC1)
            return "CV_64FC1";
        else if (_cvType == CV_8SC1)
            return "CV_8SC1";
        else if (_cvType == CV_16SC1)
            return "CV_16SC1";
        else if (_cvType == CV_32SC1)
            return "CV_32SC1";
        else if (_cvType == CV_8SC(8)) // unsupported by opencv
            return "CV_8SC(8)";
        else
            return "CV_16UC1";
    }
    const float cvTypeMax(const int _cvType)
    {
        if (_cvType == CV_8UC1)
            return 255.0;
        else if (_cvType == CV_16UC1)
            return 65535.0;
        else
            return 1.0;
    }
    const int cvTypeToSize(const int _cvType)
    {
        if (_cvType == CV_8UC1)
            return 8;
        else if (_cvType == CV_16UC1)
            return 16;
        else if (_cvType == CV_8UC4) // unsupported by opencv
            return 32;
        else if (_cvType == CV_8UC(8)) // unsupported by opencv
            return 64;
        else if (_cvType == CV_32FC1)
            return 32;
        else if (_cvType == CV_64FC1)
            return 64;
        else if (_cvType == CV_8SC1)
            return 8;
        else if (_cvType == CV_16SC1)
            return 16;
        else if (_cvType == CV_32SC1)
            return 32;
        else if (_cvType == CV_8SC(8)) // unsupported by opencv
            return 64;
        else
            return 16;
    }
    cv::Ptr<cv::freetype::FreeType2> cvCustomFont(std::string ttf)
    {
        cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
        ft2->loadFontData(ttf, 0);
        return ft2;
    }
    void cvPutText(cv::Mat &_image, std::string _text, cv::Point _origin, double _scale, const cv::Scalar &color = cv::Scalar(200, 200, 200), cv::Ptr<cv::freetype::FreeType2> font = NULL)
    {
        if (font.empty())
            cv::putText(_image, _text, _origin, cv::FONT_HERSHEY_SIMPLEX, _scale, color, 2);
        else
            font->putText(_image, _text, _origin, _scale, color, -1, cv::LINE_AA, true);
    }
    void cvDistanceCircle(cv::Mat &_image, cv::Point _center, float _radius, const cv::Scalar &color = cv::Scalar(255))
    {
        for (int y = 0; y < _image.rows; y++)
        {
            for (int x = 0; x < _image.cols; x++)
            {
                float distance = std::sqrt(std::pow(0.5 + x - _center.x, 2) + std::pow(0.5 + y - _center.y, 2));
                // _image.at<float>(y, x) = 255 * distance / _radius;
                if (distance <= _radius)
                {
                    _image.at<uchar>(y, x) = color[0];
                }
            }
        }
    }

    void calcHistogram(const cv::Mat &_image, const cv::Mat &_mask, std::vector<uint> &_hist, const int _nBins, const float *&_range, const bool uniform = true, const bool accumulate = false)
    {
        cv::Mat hist;
        cv::calcHist(&_image, 1, 0, _mask, hist, 1, &_nBins, &_range, uniform, accumulate);
    }
};

// pkg-config --cflags --libs opencv4

#endif // __KATO_FUNCTION_OPENCV_ADDONS_HPP__