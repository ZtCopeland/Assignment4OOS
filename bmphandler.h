#ifndef BMPHANDLER_H
#define BMPHANDLER_H
#include <fstream>
#include <string.h>
#include <vector>

#pragma pack(2)

typedef std::istreambuf_iterator<char> iter;

typedef union WORD {
    unsigned char UCHAR;
} WORD;

typedef union DWORD {
    unsigned char UCHAR[2];
    short SSHORT;
    unsigned short USHORT;
} DWORD;

typedef union LONG {
    unsigned char UCHAR[4];
    int SINT;
    unsigned int UINT;
} LONG;

typedef struct BITMAPFILEHEADER{
    DWORD  bfType;           /* Magic number for file */
    LONG   bfSize;           /* Size of file */
    DWORD  bfReserved1;      /* Reserved */
    DWORD  bfReserved2;      /* ... */
    LONG   bfOffBits;        /* Offset to bitmap data */
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER                      /**** BMP file info structure ****/
{
    LONG           biSize;           /* Size of info header */
    LONG           biWidth;          /* Width of image, signed */
    LONG           biHeight;         /* Height of image, signed */
    DWORD          biPlanes;         /* Number of color planes */
    DWORD          biBitCount;       /* Number of bits per pixel */
    LONG           biCompression;    /* Type of compression to use */
    LONG           biSizeImage;      /* Size of image data */
    LONG           biXPelsPerMeter;  /* X pixels per meter, signed */
    LONG           biYPelsPerMeter;  /* Y pixels per meter, signed */
    LONG           biClrUsed;        /* Number of colors used */
    LONG           biClrImportant;   /* Number of important colors */
} BITMAPINFOHEADER;

typedef struct RGBQUAD                       /**** Colormap entry structure ****/
{
    WORD  rgbBlue;          /* Blue value */
    WORD  rgbGreen;         /* Green value */
    WORD  rgbRed;           /* Red value */
    WORD  rgbReserved;      /* Reserved */
} RGBQUAD;

#pragma pack()

class bmphandler {
private:
    std::ifstream is;
    std::string fileName;
    std::vector<std::vector<unsigned char> > data;
    std::vector<std::vector<unsigned char> > dataTransformed;
    std::vector<unsigned char> bufPadding;
    BITMAPFILEHEADER h;
    BITMAPINFOHEADER ih;
public:
    bmphandler();
    bmphandler(std::string);
    ~bmphandler();
    void lbpMaker();
    void updateDB();
};

#endif
