#include <iostream>
#include <vector>
#include "kato/ft2_addons.h"
#include "kato/function.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h" /* http://nothings.org/stb/stb_image_write.h */

// Image dimensions
const uint IMG_WIDTH = 512;
const uint IMG_HEIGHT = 512;
const uint channels = 1; // Number of channels (e.g., grayscale = 1, RGB = 3)

int main()
{
    kato::FreeTypeFont font("ProggyClean.ttf", 2048);
    std::vector<uint16_t> image(IMG_WIDTH * IMG_HEIGHT);

    // Render text onto the image
    font.renderText(image.data(), IMG_WIDTH, IMG_HEIGHT, "Hello Proggy", 10, 32, 65535);                                 // White text at (10, 32)
    font.renderText(image.data(), IMG_WIDTH, IMG_HEIGHT, kato::function::TimeStampString(3, "%H:%M:%S"), 10, 64, 65535); // White text at (10, 32)

    std::vector<uint8_t> image_8bit(IMG_WIDTH * IMG_HEIGHT);
    for (uint i = 0; i < IMG_WIDTH * IMG_HEIGHT; ++i)
        image_8bit[i] = static_cast<uint8_t>(image[i] >> 8); // Scale to 8-bit by shifting
    stbi_write_png("out.png", IMG_WIDTH, IMG_HEIGHT, channels, image_8bit.data(), IMG_WIDTH);

    return 0;
}