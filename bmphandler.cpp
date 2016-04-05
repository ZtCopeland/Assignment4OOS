#include "bmphandler.h"
#include <iostream>

bmphandler::bmphandler(){}

unsigned char grayScale(RGBQUAD input) {
    return input.rgbBlue.UCHAR*.07+input.rgbRed.UCHAR*.21+input.rgbGreen.UCHAR*.72;
}

bmphandler::bmphandler(std::string fileName) {
    this -> fileName = fileName;
    is.open(fileName.c_str());
    iter bufIter(is);
    h.bfType.UCHAR[0] = *bufIter, bufIter++;
    h.bfType.UCHAR[1] = *bufIter, bufIter++;
    h.bfSize.UCHAR[0] = *bufIter, bufIter++;
    h.bfSize.UCHAR[1] = *bufIter, bufIter++;
    h.bfSize.UCHAR[2] = *bufIter, bufIter++;
    h.bfSize.UCHAR[3] = *bufIter, bufIter++;
    h.bfReserved1.UCHAR[0] = *bufIter, bufIter++;
    h.bfReserved1.UCHAR[1] = *bufIter, bufIter++;
    h.bfReserved2.UCHAR[0] = *bufIter, bufIter++;
    h.bfReserved2.UCHAR[1] = *bufIter, bufIter++;
    h.bfOffBits.UCHAR[0] = *bufIter, bufIter++;
    h.bfOffBits.UCHAR[1] = *bufIter, bufIter++;
    h.bfOffBits.UCHAR[2] = *bufIter, bufIter++;
    h.bfOffBits.UCHAR[3] = *bufIter, bufIter++;
    ih.biSize.UCHAR[0] = *bufIter, bufIter++;
    ih.biSize.UCHAR[1] = *bufIter, bufIter++;
    ih.biSize.UCHAR[2] = *bufIter, bufIter++;
    ih.biSize.UCHAR[3] = *bufIter, bufIter++;
    ih.biWidth.UCHAR[0] = *bufIter, bufIter++;
    ih.biWidth.UCHAR[1] = *bufIter, bufIter++;
    ih.biWidth.UCHAR[2] = *bufIter, bufIter++;
    ih.biWidth.UCHAR[3] = *bufIter, bufIter++;
    ih.biHeight.UCHAR[0] = *bufIter, bufIter++;
    ih.biHeight.UCHAR[1] = *bufIter, bufIter++;
    ih.biHeight.UCHAR[2] = *bufIter, bufIter++;
    ih.biHeight.UCHAR[3] = *bufIter, bufIter++;
    ih.biPlanes.UCHAR[0] = *bufIter, bufIter++;
    ih.biPlanes.UCHAR[1] = *bufIter, bufIter++;
    ih.biBitCount.UCHAR[0] = *bufIter, bufIter++;
    ih.biBitCount.UCHAR[1] = *bufIter, bufIter++;
    ih.biCompression.UCHAR[0] = *bufIter, bufIter++;
    ih.biCompression.UCHAR[1] = *bufIter, bufIter++;
    ih.biCompression.UCHAR[2] = *bufIter, bufIter++;
    ih.biCompression.UCHAR[3] = *bufIter, bufIter++;
    ih.biSizeImage.UCHAR[0] = *bufIter, bufIter++;
    ih.biSizeImage.UCHAR[1] = *bufIter, bufIter++;
    ih.biSizeImage.UCHAR[2] = *bufIter, bufIter++;
    ih.biSizeImage.UCHAR[3] = *bufIter, bufIter++;
    ih.biXPelsPerMeter.UCHAR[0] = *bufIter, bufIter++;
    ih.biXPelsPerMeter.UCHAR[1] = *bufIter, bufIter++;
    ih.biXPelsPerMeter.UCHAR[2] = *bufIter, bufIter++;
    ih.biXPelsPerMeter.UCHAR[3] = *bufIter, bufIter++;
    ih.biYPelsPerMeter.UCHAR[0] = *bufIter, bufIter++;
    ih.biYPelsPerMeter.UCHAR[1] = *bufIter, bufIter++;
    ih.biYPelsPerMeter.UCHAR[2] = *bufIter, bufIter++;
    ih.biYPelsPerMeter.UCHAR[3] = *bufIter, bufIter++;
    ih.biClrUsed.UCHAR[0] = *bufIter, bufIter++;
    ih.biClrUsed.UCHAR[1] = *bufIter, bufIter++;
    ih.biClrUsed.UCHAR[2] = *bufIter, bufIter++;
    ih.biClrUsed.UCHAR[3] = *bufIter, bufIter++;
    ih.biClrImportant.UCHAR[0] = *bufIter, bufIter++;
    ih.biClrImportant.UCHAR[1] = *bufIter, bufIter++;
    ih.biClrImportant.UCHAR[2] = *bufIter, bufIter++;
    ih.biClrImportant.UCHAR[3] = *bufIter, bufIter++;

    int buff = h.bfOffBits.SINT - 54;
    for (int j = 0; j < buff; j++)
        bufPadding.push_back(*bufIter);
        bufIter++;
    data.reserve(ih.biHeight.SINT);
    RGBQUAD temp;
    std::vector<unsigned char> tempVec;
    for (int j = 0; j < ih.biWidth.SINT; j++) {
        data.push_back(tempVec);
        data.at(j).reserve(ih.biWidth.SINT);
        for (int k = 0; k < ih.biHeight.SINT; k++) {
            temp.rgbBlue.UCHAR = *bufIter, bufIter++;
            temp.rgbGreen.UCHAR = *bufIter, bufIter++;
            temp.rgbRed.UCHAR = *bufIter, bufIter++;
            temp.rgbReserved.UCHAR = *bufIter, bufIter++;
            data.at(j).push_back(grayScale(temp));

        }
    }
}

bmphandler::~bmphandler(){};

void bmphandler::lbpMaker () {
    dataTransformed.reserve(ih.biHeight.SINT/3);
    std::vector<unsigned char> tempVec;
    int widthIter = 0;
    int heightIter = 0;
    for (int i = 1; i < ih.biWidth.SINT; i+=3, widthIter++) {
        dataTransformed.push_back(tempVec);
        dataTransformed.at(widthIter).reserve(ih.biHeight.SINT/3);
        for (int j = 1; j < ih.biHeight.SINT; j+=3, heightIter++) {
            dataTransformed.at(widthIter).push_back((unsigned char)0);

            if (data.at(i-1).at(j-1) < data.at(i).at(j)) {
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            } else {
                dataTransformed.at(widthIter).at(heightIter) += 1;
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            }

            if (data.at(i-1).at(j)   < data.at(i).at(j)) {
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            } else {
                dataTransformed.at(widthIter).at(heightIter) += 1;
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            }

            if (data.at(i-1).at(j+1) < data.at(i).at(j)) {
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            } else {
                dataTransformed.at(widthIter).at(heightIter) += 1;
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            }

            if (data.at(i).at(j+1)   < data.at(i).at(j)) {
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            } else {
                dataTransformed.at(widthIter).at(heightIter) += 1;
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            }

            if (data.at(i+1).at(j+1) < data.at(i).at(j)) {
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            } else {
                dataTransformed.at(widthIter).at(heightIter) += 1;
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            }

            if (data.at(i+1).at(j)   < data.at(i).at(j)) {
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            } else {
                dataTransformed.at(widthIter).at(heightIter) += 1;
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            }

            if (data.at(i+1).at(j-1) < data.at(i).at(j)) {
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            } else {
                dataTransformed.at(widthIter).at(heightIter) += 1;
                dataTransformed.at(widthIter).at(heightIter) <<= 1;
            }

            if (data.at(i).at(j-1)   < data.at(i).at(j)) {
            } else {
                dataTransformed.at(widthIter).at(heightIter) += 1;
            }
        }
        heightIter = 0;
    }
}
