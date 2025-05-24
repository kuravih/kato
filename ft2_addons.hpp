#ifndef __KATO_FUNCTION_FT2_ADDONS_HPP__
#define __KATO_FUNCTION_FT2_ADDONS_HPP__

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
        FreeTypeFont(const char *_pcf, uint _size)
        {
            if (FT_Init_FreeType(&library))
            {
                // std::cerr << "Could not initialize FreeType library.\n";
            }
            else
            {
                if (FT_New_Face(library, _pcf, 0, &face))
                {
                    // std::cerr << "Failed to load font.\n";
                }
                else
                {
                    FT_Set_Pixel_Sizes(face, 0, 0); // Set character height to 16 pixels
                    FT_Set_Char_Size(face, 0, _size, 0, 0);
                }
            }
        }
        ~FreeTypeFont()
        {
            if (face)
                FT_Done_Face(face);
            if (library)
                FT_Done_FreeType(library);
        }
        void drawGlyph(uint16_t *image, uint imgWidth, uint imgHeight, int x, int y, uint16_t intensity)
        {
            FT_Bitmap bitmap = face->glyph->bitmap;
            for (uint row = 0; row < bitmap.rows; ++row)
            {
                for (uint col = 0; col < bitmap.width; ++col)
                {
                    uint imgX = x + col;
                    uint imgY = y + row;
                    if (imgX < imgWidth && imgY < imgHeight) // Check bounds (unsigned no need to check lower limit)
                    {
                        uint16_t pixel = bitmap.buffer[row * bitmap.pitch + col];
                        image[imgY * imgWidth + imgX] = (pixel > 0) ? intensity : 0;
                    }
                }
            }
        }

        void renderText(uint16_t *image, uint imgWidth, uint imgHeight, const std::string &text, int startX, int startY, uint16_t intensity)
        {
            int penX = startX;
            int penY = startY;

            for (const char *p = text.c_str(); *p; ++p)
            {
                if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
                {
                    // std::cerr << "Failed to load character: " << *p << "\n";
                    continue;
                }

                // Draw the glyph's bitmap
                drawGlyph(image, imgWidth, imgHeight, penX + face->glyph->bitmap_left, penY - face->glyph->bitmap_top, intensity);

                // Advance the pen position
                penX += face->glyph->advance.x >> 6; // Convert from 26.6 fixed point
            }
        }
    };
};

namespace kato::function
{
    inline void overlayInfo(kato::FreeTypeFont &font, uint16_t *buffer, const long width, const long height, const std::string &timestamp, const long exposureTime_ms, const float gain, const float framerate, const float temperature_C, const long br_x, const long br_y, const long tl_x, const long tl_y, const long frame_count, const long event_count)
    {
        font.renderText(buffer, width, height, "Time     : " + timestamp, 16, 24, 65535);
        font.renderText(buffer, width, height, "Exp Time : " + std::to_string(exposureTime_ms) + " ms", 16, 38, 65535);
        font.renderText(buffer, width, height, "Gain     : " + std::to_string(gain), 16, 52, 65535);
        font.renderText(buffer, width, height, "Rate     : " + std::to_string(framerate) + " fps", 16, 66, 65535);
        font.renderText(buffer, width, height, "Temp     : " + std::to_string(temperature_C) + " C", 16, 80, 65535);
        font.renderText(buffer, width, height, "ROI", 16, 94, 65535);
        font.renderText(buffer, width, height, "  br     : [" + std::to_string(br_x) + "," + std::to_string(br_y) + "]", 16, 108, 65535);
        font.renderText(buffer, width, height, "  tl     : [" + std::to_string(tl_x) + "," + std::to_string(tl_y) + "]", 16, 122, 65535);
        font.renderText(buffer, width, height, "Frame    : " + std::to_string(frame_count), 16, 136, 65535);
        font.renderText(buffer, width, height, "Event    : " + std::to_string(event_count), 16, 150, 65535);
    }
};

// pkg-config --cflags --libs freetype2

#endif // __KATO_FUNCTION_FT2_ADDONS_HPP__