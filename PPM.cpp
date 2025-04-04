#include "PPM.h"
#include <iostream>
#include <fstream>
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
    if(index >= pixels.size())
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
    this->magic = obj.magic;
    this->comment = obj.comment;
    this->width = obj.width;
    this->height = obj.height;
    this->maxColor = obj.maxColor;
    this->pixels = obj.pixels;
}

PPM::PPM(ifstream& infile) {
    if (infile) {
        getline(infile, magic);
        getline(infile, comment);
        infile >> width >> height;
        infile >> maxColor;

        Resize(width * height);

        for (int i = 0; i < width * height; ++i) {
            unsigned int r, g, b;
            infile >> r >> g >> b;
            pixels[i] = Pixel{r, g, b};
        }
    }
}
// move constructor
PPM::PPM(PPM&& obj) {
    swap(this->width, obj.width);
    swap(this->height, obj.height);
    swap(this->maxColor, obj.maxColor);
    swap(this->comment, obj.comment);
    swap(this->magic, obj.magic);
    swap(this->pixels, obj.pixels);
}

void PPM::Resize(unsigned int newSize) {
    pixels.resize(newSize);
}

void PPM::SaveImageToFile(string filename) {
    ofstream outfile(filename);
    
    if (!outfile) {
        cout << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    outfile << magic << "\n";
    outfile << comment << "\n";
    outfile << width << " " << height << "\n";
    outfile << maxColor << "\n";
    
    for (int i = 0; i < width * height; i++) {
        outfile << pixels[i]["red"] << " " << pixels[i]["green"] << " " << pixels[i]["blue"] << endl;
    }

    outfile.close();
}

void PPM::SetComment(string newComment) {
    comment = newComment;
}

void PPM::SetHeight(unsigned int newHeight) {
    height = newHeight;
}

void PPM::SetMagic(string newMagic) {
    magic = newMagic;
}

void PPM::SetMaxColor(unsigned int newMaxColor) {
    maxColor = newMaxColor;
}

void PPM::SetWidth(unsigned int newWidth) {
    width = newWidth;
}
