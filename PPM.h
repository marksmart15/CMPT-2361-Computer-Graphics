#ifndef PPM_h
#define PPM_h
#include "Pixel.h"
#include <vector>
#include <string>

using namespace std;

class PPM {
private:
    string comment;
    unsigned int height;
    string magic;
    unsigned int maxColor;
    vector<Pixel> pixels;
    unsigned int width;
public:
    ~PPM();
    
    string getComment();
    unsigned int GetHeight();
    string getMagic();
    unsigned int GetMaxColor();
    unsigned int GetSize();
    unsigned int GetWidth();
    
    const Pixel& operator[](unsigned int) const;
    Pixel& operator[](unsigned int);
    const PPM& operator=(const PPM&);
    const PPM& operator=(PPM&&);
    
    PPM();
    PPM(const PPM&);
    PPM(ifstream&);
    PPM(PPM&&);
    
    void Resize(unsigned int);
    void SaveImageToFile(string);
    
    void SetComment(string);
    void SetHeight(unsigned int);
    void SetMagic(string);
    void SetMaxColor(unsigned int);
    void SetWidth(unsigned int);
};

#endif /* PPM_h */
