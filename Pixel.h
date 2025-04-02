#pragma once

class Pixel {
public:

    Pixel();
    Pixel(unsigned int red, unsigned int green, unsigned int blue);
    Pixel(const Pixel& other);

    ~Pixel();

    unsigned int& operator[](const char* color);
    const unsigned int& operator[](const char* color) const;

    class InputOutOfBoundsException {
    public:
        InputOutOfBoundsException(const char* errorMessage, const char* offendingIndex);
        const char* returnError() const;
        const char* returnOffendingIndex() const;

    private:
        const char* errorMessage;
        const char* offendingIndex;
    };

private:
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};


