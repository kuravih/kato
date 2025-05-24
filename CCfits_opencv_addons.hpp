#ifndef __KATO_FUNCTION_CCFITS_OPENCV_ADDONS_HPP__
#define __KATO_FUNCTION_CCFITS_OPENCV_ADDONS_HPP__

#pragma once

#include <CCfits/CCfits>
#include <opencv2/opencv.hpp>
#include <string>

namespace kato::function
{
    const int cvTypeToCCfitsBitPix(const int _cvType)
    {
        if (_cvType == CV_8UC1)
            return BYTE_IMG;
        else if (_cvType == CV_16UC1)
            return USHORT_IMG;
        else if (_cvType == CV_8UC4) // unsupported by opencv
            return ULONG_IMG;
        else if (_cvType == CV_8UC(8)) // unsupported by opencv
            return ULONGLONG_IMG;
        else if (_cvType == CV_32FC1)
            return FLOAT_IMG;
        else if (_cvType == CV_64FC1)
            return DOUBLE_IMG;
        else if (_cvType == CV_8SC1)
            return SBYTE_IMG;
        else if (_cvType == CV_16SC1)
            return SHORT_IMG;
        else if (_cvType == CV_32SC1)
            return LONG_IMG;
        else if (_cvType == CV_8SC(8)) // unsupported by opencv
            return LONGLONG_IMG;
        else
            return USHORT_IMG;
    }
    const int CCfitsBitPixTocvType(const int _bitPix)
    {
        if (_bitPix == BYTE_IMG)
            return CV_8UC1;
        else if (_bitPix == USHORT_IMG)
            return CV_16UC1;
        else if (_bitPix == ULONG_IMG) // unsupported by opencv
            return CV_8UC4;
        else if (_bitPix == ULONGLONG_IMG) // unsupported by opencv
            return CV_8UC(8);
        else if (_bitPix == FLOAT_IMG)
            return CV_32FC1;
        else if (_bitPix == DOUBLE_IMG)
            return CV_64FC1;
        else if (_bitPix == SBYTE_IMG)
            return CV_8SC1;
        else if (_bitPix == SHORT_IMG)
            return CV_16SC1;
        else if (_bitPix == LONG_IMG)
            return CV_32SC1;
        else if (_bitPix == LONGLONG_IMG) // unsupported by opencv
            return CV_8SC(8);
        else
            return CV_16UC1;
    }
};

// pkg-config --cflags --libs CCfits opencv4

#endif //__KATO_FUNCTION_CCFITS_OPENCV_ADDONS_HPP__