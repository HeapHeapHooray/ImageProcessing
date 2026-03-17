#include <iostream>
#include "utils/fileutils.h"
#include "image/Bitmap.h"
#include "image/Image.h"
#include <string.h>

int main()
{  
	Bitmap* bitmap = FileReader::readFromBitmapFile("test_resources/rws.bmp");
	Bitmap* bitmap2 = FileReader::readFromBitmapFile("test_resources/rws.bmp");

	Image img(bitmap);
	Image img2(bitmap2);

	delete bitmap;
	delete bitmap2;
	
	Bitmap output(&img2); 

	FileWriter::createBitmapFile("bitmap-output.bmp", &output);

	system("bitmap-output.bmp");

	return 0;
}