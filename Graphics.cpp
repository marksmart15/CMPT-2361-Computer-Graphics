#include "Graphics.h"
#include <cstring>
#include "PPM.h"
#include <cmath>

const PPM& Graphics::MakeGrayScale(PPM& image) {
    for (unsigned int i = 0; i < image.GetSize(); ++i) {
        unsigned int r = image[i]["red"];
        unsigned int g = image[i]["green"];
        unsigned int b = image[i]["blue"];
        unsigned int gray = static_cast<unsigned int>((r + g + b) / 3.0);
        image[i]["red"] = gray;
        image[i]["green"] = gray;
        image[i]["blue"] = gray;
    }
    return image;
}

const PPM& Graphics::ScaleImage(PPM& image, double scaleFactor) {
    unsigned int newWidth = static_cast<unsigned int>(image.GetWidth() * scaleFactor);
    unsigned int newHeight = static_cast<unsigned int>(image.GetHeight() * scaleFactor);

    PPM scaledImage;
    scaledImage.SetWidth(newWidth);
    scaledImage.SetHeight(newHeight);
    scaledImage.SetMaxColor(image.GetMaxColor());
    scaledImage.SetMagic(image.getMagic());
    scaledImage.SetComment(image.getComment());
    scaledImage.Resize(newWidth * newHeight);

    for (unsigned int y = 0; y < newHeight; ++y) {
        for (unsigned int x = 0; x < newWidth; ++x) {
            unsigned int origX = static_cast<unsigned int>(x / scaleFactor);
            unsigned int origY = static_cast<unsigned int>(y / scaleFactor);
            scaledImage[y * newWidth + x] = image[origY * image.GetWidth() + origX];
        }
    }

    image = std::move(scaledImage);
    return image;
}

const PPM& Graphics::RotateImage(PPM& image, double angle) {
    double radians = angle * M_PI / 180.0;
    unsigned int width = image.GetWidth();
    unsigned int height = image.GetHeight();
    int centerX = width / 2;
    int centerY = height / 2;

    PPM rotated;
    rotated.SetWidth(width);
    rotated.SetHeight(height);
    rotated.SetMaxColor(image.GetMaxColor());
    rotated.SetMagic(image.getMagic());
    rotated.SetComment(image.getComment());
    rotated.Resize(width * height);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int dx = x - centerX;
            int dy = y - centerY;

            int origX = static_cast<int>(round(centerX + dx * cos(radians) - dy * sin(radians)));
            int origY = static_cast<int>(round(centerY + dx * sin(radians) + dy * cos(radians)));

            if (origX >= 0 && origX < static_cast<int>(width) && origY >= 0 && origY < static_cast<int>(height)) {
                rotated[y * width + x] = image[origY * width + origX];
            }
        }
    }

    image = std::move(rotated);
    return image;
}

const PPM& Graphics::TranslateImage(PPM& image, int dx, int dy) {
    unsigned int width = image.GetWidth();
    unsigned int height = image.GetHeight();

    PPM translated;
    translated.SetWidth(width);
    translated.SetHeight(height);
    translated.SetMaxColor(image.GetMaxColor());
    translated.SetMagic(image.getMagic());
    translated.SetComment(image.getComment());
    translated.Resize(width * height);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int newX = x - dx;
            int newY = y - dy;

            if (newX >= 0 && newX < static_cast<int>(width) && newY >= 0 && newY < static_cast<int>(height)) {
                translated[y * width + x] = image[newY * width + newX];
            }
        }
    }

    image = std::move(translated);
    return image;
}

    void Clamp(unsigned int& value, unsigned int maxColor) {
        if (value > maxColor) value = maxColor;
    }

    void ApplyKernel(PPM& image, const float kernel[3][3], float factor = 1.0f) {
        PPM copy = image;
        int width = image.GetWidth();
        int height = image.GetHeight();

        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                float r = 0, g = 0, b = 0;
                for (int ky = -1; ky <= 1; ++ky) {
                    for (int kx = -1; kx <= 1; ++kx) {
                        int idx = (y + ky) * width + (x + kx);
                        r += copy[idx]["red"] * kernel[ky + 1][kx + 1];
                        g += copy[idx]["green"] * kernel[ky + 1][kx + 1];
                        b += copy[idx]["blue"] * kernel[ky + 1][kx + 1];
                    }
                }
                Pixel& p = image[y * width + x];
                p["red"] = std::min(std::max(int(r * factor), 0), int(image.GetMaxColor()));
                p["green"] = std::min(std::max(int(g * factor), 0), int(image.GetMaxColor()));
                p["blue"] = std::min(std::max(int(b * factor), 0), int(image.GetMaxColor()));
            }
        }
    }

    const PPM& Emboss(PPM& image) {
        float kernel[3][3] = {
            {-2, -1, 0},
            {-1,  1, 1},
            { 0,  1, 2}
        };
        ApplyKernel(image, kernel);
        return image;
    }

    const PPM& EdgeDetect(PPM& image) {
        float kernel[3][3] = {
            { -1, -1, -1 },
            { -1,  8, -1 },
            { -1, -1, -1 }
        };
        ApplyKernel(image, kernel);
        return image;
    }

    const PPM& Blur(PPM& image) {
        float kernel[3][3] = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
        };
        ApplyKernel(image, kernel, 1.0f / 9.0f);
        return image;
    }

    const PPM& Invert(PPM& image) {
        unsigned int maxColor = image.GetMaxColor();
        for (unsigned int i = 0; i < image.GetSize(); ++i) {
            image[i]["red"] = maxColor - image[i]["red"];
            image[i]["green"] = maxColor - image[i]["green"];
            image[i]["blue"] = maxColor - image[i]["blue"];
        }
        return image;
    }

    const PPM& Sharpen(PPM& image) {
        float kernel[3][3] = {
            { 0, -1,  0 },
            {-1,  5, -1 },
            { 0, -1,  0 }
        };
        ApplyKernel(image, kernel);
        return image;
    }

const PPM& Graphics::ApplyFilter(PPM& image, const char* filterName) {
    if (strcmp(filterName, "grayscale") == 0) return MakeGrayScale(image);
    if (strcmp(filterName, "emboss") == 0) return Emboss(image);
    if (strcmp(filterName, "edge") == 0) return EdgeDetect(image);
    if (strcmp(filterName, "blur") == 0) return Blur(image);
    if (strcmp(filterName, "invert") == 0) return Invert(image);
    if (strcmp(filterName, "sharpen") == 0) return Sharpen(image);
    return image;
}
