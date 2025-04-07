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
    string inputFilename = "/Users/camer/Documents/winter-douglas-25/computer-graphics/project/repo/Shahriar.ppm";
    string outputPath = "/Users/camer/Documents/winter-douglas-25/computer-graphics/project/repo/outputImages/";
    ifstream inputFile(inputFilename);
    if (!inputFile) {
        cerr << "Failed to open input file: " << inputFilename << endl;
        return 1;
    }

    PPM baseImage(inputFile);
    inputFile.close();

    // Filters
    ProcessAndSave(baseImage, "grayscale", outputPath + "output_grayscale.ppm");
    ProcessAndSave(baseImage, "emboss",  outputPath +"output_emboss.ppm");
    ProcessAndSave(baseImage, "edge",  outputPath +"output_edge.ppm");
    ProcessAndSave(baseImage, "blur",  outputPath +"output_blur.ppm");
    ProcessAndSave(baseImage, "invert",  outputPath +"output_invert.ppm");
    ProcessAndSave(baseImage, "sharpen",  outputPath +"output_sharpen.ppm");

    // Effects
    PPM scaled = baseImage;
    Graphics::ScaleImage(scaled, 0.5);
    scaled.SaveImageToFile("output_scaled.ppm");

    PPM rotated = baseImage;
    Graphics::RotateImage(rotated, 90);
    rotated.SaveImageToFile("output_rotated.ppm");

    PPM translated = baseImage;
    Graphics::TranslateImage(translated, 10, 10);
    translated.SaveImageToFile("output_translated.ppm");

    cout << "All operations completed." << endl;
    return 0;
}
