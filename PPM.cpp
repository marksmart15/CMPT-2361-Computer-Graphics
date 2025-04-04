#include "PPM.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

PPM::~PPM() {
    pixels.clear();
}

string PPM::getComment() {
    return comment;
}

unsigned int PPM::GetHeight() {
    return height;
}

string PPM::getMagic() {
    return magic;
}

unsigned int PPM::GetMaxColor() {
    return maxColor;
}

unsigned int PPM::GetSize() {
    return pixels.size();
}

unsigned int PPM::GetWidth() {
    return width;
}

const Pixel& PPM::operator[](unsigned int index) const {
    return pixels[index];
}

Pixel& PPM::operator[](unsigned int index) {
    if(index < 0 || index >= 3)
    {
        cout << "> ERROR: Index out of bounds.";
        exit(1);
    }
    return pixels[index];
}
// copy assignment operator
const PPM& PPM::operator=(const PPM& obj) {
    if (this != &obj) {
        width = obj.width;
        height = obj.height;
        maxColor = obj.maxColor;
        comment = obj.comment;
        magic = obj.magic;
        pixels = obj.pixels;
    }
    return *this;
}
// move assignment operator
const PPM& PPM::operator=(PPM&& obj) {
    if(this != &obj) {
        swap(this->width, obj.width);
        swap(this->height, obj.height);
        swap(this->maxColor, obj.maxColor);
        swap(this->comment, obj.comment);
        swap(this->magic, obj.magic);
        swap(this->pixels, obj.pixels);
    }
    return *this;
}

PPM::PPM() : comment(""), height(0), magic(""), maxColor(0), pixels(), width(0)
{}
// copy constructor
PPM::PPM(const PPM& obj) {
    
}
PPM::PPM(ifstream& infile) {
    if(infile)
    {
        getline(infile, magic);
        getline(infile, comment);
        infile >> width >> height;
        infile >> maxColor;
        
        infile >> pixels;
        // construct pixels
        
        for(int row = 0; row < numrows; row++)
        {
            for(int col = 0; col < numcols; col++)
            {
                infile >> board[row][col];
            }
        }
    }
    else
    {
        cout << "> ERROR opening the input file.\n";
    }
}
// move constructor
PPM::PPM(PPM&& obj) {
    
}
void PPM::SaveImageToFile(string input) {
    
}
