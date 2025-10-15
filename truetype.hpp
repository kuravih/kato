#ifndef __KATO_TRUETYPE_HPP__
#define __KATO_TRUETYPE_HPP__

#pragma once

#include <string>
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
        stbtt_fontinfo m_font;
        float m_scale = 1.0f;
        int m_baseline = 0;
        std::vector<unsigned char> m_fontBuffer; // keep font data alive

    public:
        TrueTypeFont(const char *_fontpath, const float _scale = 64.0)
        {
            FILE *fontFile = fopen(_fontpath, "rb");
            if (!fontFile)
            {
                fprintf(stderr, "Could not open font file: %s\n", _fontpath);
                return;
            }

            fseek(fontFile, 0, SEEK_END);
            size_t size = ftell(fontFile);
            fseek(fontFile, 0, SEEK_SET);

            m_fontBuffer.resize(size);
            fread(m_fontBuffer.data(), 1, size, fontFile);
            fclose(fontFile);

            if (!stbtt_InitFont(&m_font, m_fontBuffer.data(), stbtt_GetFontOffsetForIndex(m_fontBuffer.data(), 0)))
            {
                fprintf(stderr, "Failed to init font\n");
                return;
            }

            m_scale = stbtt_ScaleForPixelHeight(&m_font, _scale);
            int ascent, descent, lineGap;
            stbtt_GetFontVMetrics(&m_font, &ascent, &descent, &lineGap);
            m_baseline = static_cast<int>(ascent * m_scale);
        }

        template <typename Type>
        void renderText(Type *_image, size_t _width, size_t _height, size_t _pos_x, size_t _pos_y, const std::string &_text, float _color, float _max_color, float _min_color = 0.0f)
        {
            static_assert(std::is_arithmetic_v<Type>, "Pixel type must be numeric");
            if (!_image)
                return; // null safety

            const size_t start_x = _pos_x; // remember left margin

            // --- Compute approximate line height using font metrics ---
            int ascent, descent, lineGap;
            stbtt_GetFontVMetrics(&m_font, &ascent, &descent, &lineGap);
            const float line_height = (ascent - descent + lineGap) * m_scale;

            for (const char &letter : _text)
            {
                // --- Handle newline ---
                if (letter == '\n')
                {
                    _pos_x = start_x; // return to start of line
                    _pos_y += static_cast<size_t>(line_height);
                    continue;
                }

                // --- Get glyph metrics ---
                int ax, lsb;
                stbtt_GetCodepointHMetrics(&m_font, letter, &ax, &lsb);

                int x0, y0, x1, y1;
                stbtt_GetCodepointBitmapBox(&m_font, letter, m_scale, m_scale, &x0, &y0, &x1, &y1);

                const int w = x1 - x0;
                const int h = y1 - y0;

                if (w <= 0 || h <= 0)
                {
                    _pos_x += static_cast<int>(ax * m_scale);
                    continue;
                }

                std::vector<unsigned char> glyph(w * h);
                stbtt_MakeCodepointBitmap(&m_font, glyph.data(), w, h, w, m_scale, m_scale, letter);

                // --- Render the glyph ---
                for (int gy = 0; gy < h; ++gy)
                {
                    for (int gx = 0; gx < w; ++gx)
                    {
                        const size_t ix = _pos_x + gx + x0;
                        const size_t iy = _pos_y + gy + y0 + m_baseline;

                        if (ix >= _width || iy >= _height)
                            continue;

                        const unsigned char val = glyph[gy * w + gx];
                        if (val == 0)
                            continue; // skip empty pixels fast

                        const float alpha = val / 255.0f;

                        // Compute pixel index in continuous memory block
                        Type &pix = _image[iy * _width + ix];
                        const float blended = static_cast<float>(pix) + _color * alpha;
                        pix = static_cast<Type>(std::clamp(blended, _min_color, _max_color));
                    }
                }

                _pos_x += static_cast<int>(ax * m_scale);
            }
        }
    };

} // namespace kato

#endif //__KATO_TRUETYPE_HPP__