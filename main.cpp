#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>
#include "bmphandler.h"

int main () {
    bmphandler thing("the_sandman_comics_neil_gaiman_98470_3840x2160.bmp");
    thing.lbpMaker();
    return 0;
}

