#include "ImageHandler.h"

ImageHandler::ImageHandler () {}

ImageHandler::~ImageHandler () {};

ImageHandler::ImageHandler (std::string filePath) {
    this->filePath = &filePath;
}
