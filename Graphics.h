// ImageProcessor.h

#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

// Forward declaration of the PPM class/struct
class PPM;

class Graphics {
public:
    static const PPM& ApplyFilter(PPM& image, const char* filterName);
    static const PPM& MakeGrayScale(PPM& image);
    static const PPM& RotateImage(PPM& image, double angle);
    static const PPM& ScaleImage(PPM& image, double scaleFactor);
    static const PPM& TranslateImage(PPM& image, int dx, int dy);
};

#endif // IMAGE_PROCESSOR_H
