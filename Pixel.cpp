#include "Pixel.h"
#include <cstring>

Pixel::Pixel() : red(0), green(0), blue(0) {}

Pixel::Pixel(unsigned int red, unsigned int green, unsigned int blue) : red(red), green(green), blue(blue) {}

Pixel::Pixel(const Pixel& other) : red(other.red), green(other.green), blue(other.blue) {}

Pixel::~Pixel() {}

unsigned int& Pixel::operator[](const char* color) {
    if (strcmp(color, "red") == 0) {
        return red;
    }
    else if (strcmp(color, "green") == 0) {
        return green;
    }
    else if (strcmp(color, "blue") == 0) {
        return blue;
    }
    else {
        throw InputOutOfBoundsException("Invalid color index", color);
    }
}

const unsigned int& Pixel::operator[](const char* color) const {
    if (strcmp(color, "red") == 0) {
        return red;
    }
    else if (strcmp(color, "green") == 0) {
        return green;
    }
    else if (strcmp(color, "blue") == 0) {
        return blue;
    }
    else {
        throw InputOutOfBoundsException("Invalid color index", color);
    }
}

Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* errorMessage, const char* offendingIndex)
    : errorMessage(errorMessage), offendingIndex(offendingIndex) {}

const char* Pixel::InputOutOfBoundsException::returnError() const {
    return errorMessage;
}

const char* Pixel::InputOutOfBoundsException::returnOffendingIndex() const {
    return offendingIndex;
}