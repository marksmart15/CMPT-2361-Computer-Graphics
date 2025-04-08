#include <iostream>
#include <fstream>
#include "PPM.h"
#include "graphics.h"

using namespace std;

void ProcessAndSave(PPM original, const char* filterName, const string& outputFilename) {
    Graphics::ApplyFilter(original, filterName);
    original.SaveImageToFile(outputFilename);
    cout << "Saved: " << outputFilename << endl;
}

int main() {
    ifstream inputFile("input.ppm");
    if (!inputFile) {
        cerr << "Failed to open input file: input.ppm" << endl;
        return 1;
    }

    PPM baseImage(inputFile);
    inputFile.close();

    // Filters
    ProcessAndSave(baseImage, "grayscale", "output_grayscale.ppm");
    ProcessAndSave(baseImage, "emboss", "output_emboss.ppm");
    ProcessAndSave(baseImage, "edge", "output_edge.ppm");
    ProcessAndSave(baseImage, "blur", "output_blur.ppm");
    ProcessAndSave(baseImage, "invert", "output_invert.ppm");
    ProcessAndSave(baseImage, "sharpen", "output_sharpen.ppm");

    // Effects
    PPM scaled = baseImage;
    Graphics::ScaleImage(scaled, 0.5);
    scaled.SaveImageToFile("output_scaled.ppm");
    cout << "Saved: " << "output_scaled.ppm" << endl;

    PPM rotated = baseImage;
    Graphics::RotateImage(rotated, 90);
    rotated.SaveImageToFile("output_rotated.ppm");
    cout << "Saved: " << "output_rotated.ppm" << endl;

    PPM translated = baseImage;
    Graphics::TranslateImage(translated, 100, 100);
    translated.SaveImageToFile("output_translated.ppm");
    cout << "Saved: " << "output_translated.ppm" << endl;


    cout << "All operations completed." << endl;
    return 0;
}
