#pragma once

class Pixel {
private:
    unsigned int red;
    unsigned int green;
    unsigned int blue;

public:

    Pixel();
    Pixel(unsigned int red, unsigned int green, unsigned int blue);
    Pixel(const Pixel& other);

    ~Pixel();

    unsigned int& operator[](const char* color);
    const unsigned int& operator[](const char* color) const;

    class InputOutOfBoundsException {
    private:
        const char* errorMessage;
        const char* offendingIndex;

    public:
        InputOutOfBoundsException(const char* errorMessage, const char* offendingIndex);
        const char* returnError() const;
        const char* returnOffendingIndex() const;
    };
};


