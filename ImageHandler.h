#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <string.h>
#include <fstream>
#include <vector>
#include "CImg-1.7.0/CImg.h"

class ImageHandler {
private:
    std::string* filePath;
    std::ifstream imageStream;
    std::vector<std::vector<unsigned char>* >* grayImage;
    std::vector<std::vector<unsigned char>* >* processedImage;
public:
    ImageHandler ();
    ~ImageHandler ();
    ImageHandler (std::string);
    std::vector<std::vector<unsigned char>* >* processImage(std::string, std::vector<std::vector<unsigned char>* >*);
};

#endif
