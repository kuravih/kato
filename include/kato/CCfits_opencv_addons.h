#ifndef __KATO_FUNCTION_CCFITS_OPENCV_ADDONS_H__
#define __KATO_FUNCTION_CCFITS_OPENCV_ADDONS_H__

#pragma once

#include <CCfits/CCfits>
#include <opencv2/opencv.hpp>
#include <string>

namespace kato::function
{
    const int cvTypeToCCfitsBitPix(const int);
    const int CCfitsBitPixTocvType(const int);
};

// pkg-config --cflags --libs CCfits opencv4

#endif //__KATO_FUNCTION_CCFITS_OPENCV_ADDONS_H__