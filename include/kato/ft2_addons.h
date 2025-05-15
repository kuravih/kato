#ifndef __KATO_FUNCTION_FT2_ADDONS_H__
#define __KATO_FUNCTION_FT2_ADDONS_H__

#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <stdint.h>

namespace kato
{
    struct FreeTypeFont
    {
        FT_Library library;
        FT_Face face;
        FreeTypeFont(const char *_pcf, uint _pxh);
        ~FreeTypeFont();
        void drawGlyph(uint16_t *, uint, uint, int, int, uint16_t);
        void renderText(uint16_t *, uint, uint, const std::string &, int, int, uint16_t);
    };
};
namespace kato::function
{
    void overlayInfo(kato::FreeTypeFont &font, uint16_t *buffer, const long width, const long height, const std::string &timestamp, const long exposureTime_ms, const float gain, const float framerate, const float temperature_C, const long br_x, const long br_y, const long tl_x, const long tl_y, const long frame_count, const long event_count);
};

// pkg-config --cflags --libs freetype2

#endif // __KATO_FUNCTION_FT2_ADDONS_H__