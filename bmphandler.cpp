#include "bmphandler.h"

bmphandler::bmphandler(){}

unsigned char grayScale(RGBQUAD input) {
    return input.rgbBlue.x*.07+input.rgbRed.x*.21+input.rgbGreen.x*.72;
}

bmphandler::bmphandler(std::string fileName) {
    this -> fileName = fileName;
    is.open(fileName.c_str());
    iter i(is);
    h.bfType.x[0] = *i, i++;
    h.bfType.x[1] = *i, i++;
    h.bfSize.x[0] = *i, i++;
    h.bfSize.x[1] = *i, i++;
    h.bfSize.x[2] = *i, i++;
    h.bfSize.x[3] = *i, i++;
    h.bfReserved1.x[0] = *i, i++;
    h.bfReserved1.x[1] = *i, i++;
    h.bfReserved2.x[0] = *i, i++;
    h.bfReserved2.x[1] = *i, i++;
    h.bfOffBits.x[0] = *i, i++;
    h.bfOffBits.x[1] = *i, i++;
    h.bfOffBits.x[2] = *i, i++;
    h.bfOffBits.x[3] = *i, i++;
    ih.biSize.x[0] = *i, i++;
    ih.biSize.x[1] = *i, i++;
    ih.biSize.x[2] = *i, i++;
    ih.biSize.x[3] = *i, i++;
    ih.biWidth.x[0] = *i, i++;
    ih.biWidth.x[1] = *i, i++;
    ih.biWidth.x[2] = *i, i++;
    ih.biWidth.x[3] = *i, i++;
    ih.biHeight.x[0] = *i, i++;
    ih.biHeight.x[1] = *i, i++;
    ih.biHeight.x[2] = *i, i++;
    ih.biHeight.x[3] = *i, i++;
    ih.biPlanes.x[0] = *i, i++;
    ih.biPlanes.x[1] = *i, i++;
    ih.biBitCount.x[0] = *i, i++;
    ih.biBitCount.x[1] = *i, i++;
    ih.biCompression.x[0] = *i, i++;
    ih.biCompression.x[1] = *i, i++;
    ih.biCompression.x[2] = *i, i++;
    ih.biCompression.x[3] = *i, i++;
    ih.biSizeImage.x[0] = *i, i++;
    ih.biSizeImage.x[1] = *i, i++;
    ih.biSizeImage.x[2] = *i, i++;
    ih.biSizeImage.x[3] = *i, i++;
    ih.biXPelsPerMeter.x[0] = *i, i++;
    ih.biXPelsPerMeter.x[1] = *i, i++;
    ih.biXPelsPerMeter.x[2] = *i, i++;
    ih.biXPelsPerMeter.x[3] = *i, i++;
    ih.biYPelsPerMeter.x[0] = *i, i++;
    ih.biYPelsPerMeter.x[1] = *i, i++;
    ih.biYPelsPerMeter.x[2] = *i, i++;
    ih.biYPelsPerMeter.x[3] = *i, i++;
    ih.biClrUsed.x[0] = *i, i++;
    ih.biClrUsed.x[1] = *i, i++;
    ih.biClrUsed.x[2] = *i, i++;
    ih.biClrUsed.x[3] = *i, i++;
    ih.biClrImportant.x[0] = *i, i++;
    ih.biClrImportant.x[1] = *i, i++;
    ih.biClrImportant.x[2] = *i, i++;
    ih.biClrImportant.x[3] = *i, i++;

    int buff = h.bfOffBits.y - 54;
    for (int j = 0; j < buff; j++)
        i++;
    data.reserve(ih.biHeight.y);
    RGBQUAD temp;
    std::vector<unsigned char> tempo;
    for (int j = 0; j < ih.biWidth.y; j++) {
        data.push_back(tempo);
        data.at(j).reserve(ih.biWidth.y);
        for (int k = 0; k < ih.biHeight.y; k++) {
            temp.rgbBlue.x = *i, i++;
            temp.rgbGreen.x = *i, i++;
            temp.rgbRed.x = *i, i++;
            temp.rgbReserved.x = *i, i++;
            data.at(j).push_back(grayScale(temp));

        }
    }
}

bmphandler::~bmphandler(){};
