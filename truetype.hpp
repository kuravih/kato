#ifndef __KATO_TRUETYPE_HPP__
#define __KATO_TRUETYPE_HPP__

#pragma once

#include <vector>
#include <cstdio>
#include <algorithm>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"

namespace kato
{

    class TrueTypeFont
    {
    private:
        stbtt_fontinfo font;
        float scale = 1.0f;
        int baseline = 0;
        std::vector<unsigned char> fontBuffer; // keep font data alive

    public:
        TrueTypeFont(const char *fontPath)
        {
            FILE *fontFile = fopen(fontPath, "rb");
            if (!fontFile)
            {
                fprintf(stderr, "Could not open font file: %s\n", fontPath);
                return;
            }

            fseek(fontFile, 0, SEEK_END);
            size_t size = ftell(fontFile);
            fseek(fontFile, 0, SEEK_SET);

            fontBuffer.resize(size);
            fread(fontBuffer.data(), 1, size, fontFile);
            fclose(fontFile);

            if (!stbtt_InitFont(&font, fontBuffer.data(), stbtt_GetFontOffsetForIndex(fontBuffer.data(), 0)))
            {
                fprintf(stderr, "Failed to init font\n");
                return;
            }

            scale = stbtt_ScaleForPixelHeight(&font, 64.0f);
            int ascent, descent, lineGap;
            stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
            baseline = static_cast<int>(ascent * scale);
        }

        template <typename T>
        void renderText(std::vector<T> &_image, size_t _width, size_t _height, size_t _pos_x, size_t _pos_y, const char *_text, const float _color, const float _max_color, const float _min_color = 0)
        {
            for (const char *p = _text; *p; ++p)
            {
                int ax, lsb;
                stbtt_GetCodepointHMetrics(&font, *p, &ax, &lsb);

                int x0, y0, x1, y1;
                stbtt_GetCodepointBitmapBox(&font, *p, scale, scale, &x0, &y0, &x1, &y1);

                int w = x1 - x0;
                int h = y1 - y0;

                std::vector<unsigned char> glyph(w * h);
                stbtt_MakeCodepointBitmap(&font, glyph.data(), w, h, w, scale, scale, *p);

                for (int gy = 0; gy < h; ++gy)
                {
                    for (int gx = 0; gx < w; ++gx)
                    {
                        size_t ix = _pos_x + gx + x0;
                        size_t iy = _pos_y + gy + y0 + baseline;
                        if (ix >= _width || iy >= _height)
                            continue;

                        unsigned char val = glyph[gy * w + gx];
                        T &pix = _image[iy * _width + ix];

                        float alpha = val / 255.0f;

                        pix = std::clamp<T>(pix + _color * alpha, _min_color, _max_color);
                    }
                }

                _pos_x += static_cast<int>(ax * scale);
            }
        }
    };

} // namespace kato

#endif //__KATO_TRUETYPE_HPP__