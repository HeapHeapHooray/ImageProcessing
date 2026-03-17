#include "Bitmap.h"
#include "Image.h" 

#pragma region Constructors/Destructors
Bitmap::Bitmap(const BitmapFileHeader& fileHeader, const BitmapInfoHeader& infoHeader, unsigned char* bitmapData) 
     : m_fileHeader(fileHeader),m_infoHeader(infoHeader),m_data(bitmapData)
{
}
Bitmap::Bitmap(const Image* image)
{
	const unsigned int image_size = image->getDataSize();
	const unsigned char* image_data = image->getData();
	m_data = new unsigned char[image_size];

	for (unsigned int i = 0; i < image_size; i += 4) {
		m_data[i] = image_data[i + 2]; // Blue
		m_data[i + 1] = image_data[i + 1]; // Green
		m_data[i + 2] = image_data[i]; //Red
		m_data[i + 3] = image_data[i+3]; // Alpha 
		//BGRA
	}

	m_infoHeader = BitmapInfoHeader::createStandardBitmapInfoHeader(image->getWidth(),
	image->getHeight(),32,BitmapImageCompressionMethods::BI_RGB,image_size);
	m_fileHeader = BitmapFileHeader::createBitmapFileHeader(BitmapFormats::BITMAP,
	14+40+image_size,0);
}
Bitmap::~Bitmap()
{
	delete[] m_data;
}
#pragma endregion
#pragma region Headers Creation
inline BitmapInfoHeader BitmapInfoHeader::createStandardBitmapInfoHeader(int image_width, int image_height,
unsigned short bitsPerPixel,
BitmapImageCompressionMethods::CompressionMethod compressionMethod,unsigned int image_size)
{
	return{ BitmapInfoHeaderTypes::BITMAPINFOHEADER, 40,image_width,image_height, 1, 32,compressionMethod, image_size,
		(int)1000, (int)1000, 0, 0 };
}

inline BitmapFileHeader BitmapFileHeader::createBitmapFileHeader(BitmapFormats::Format format, 
unsigned int file_size,unsigned int reserved)
{
	return{ format,file_size,reserved };
}
#pragma endregion
#pragma region Utils
std::ostream& operator<<(std::ostream& stream, const BitmapFileHeader& file_header)
{
	return stream << "Bitmap File Format: " << file_header.format << std::endl
		          << "Bitmap File Size: " << file_header.size << " bytes" << std::endl
		          << "Bitmap Reserved Bits: " << file_header.reserved << std::endl;       
}
std::ostream& operator<<(std::ostream& stream, const BitmapInfoHeader& info_header)
{
	return stream << "Info Header Type: " << info_header.type << std::endl
		          << "Info Header Size: " << info_header.header_size << " bytes" << std::endl
		          << "Bitmap Width: " << info_header.bitmap_width << " px" << std::endl
		          << "Bitmap Height: " << info_header.bitmap_height << " px" << std::endl
		          << "Number of Color Planes: " << info_header.number_of_color_planes << std::endl
		          << "Bitmap Color Depth(Pixel Density): " << info_header.bitsPerPixel << " bpp" << std::endl
		          << "Bitmap Compression Method: " << info_header.compressionMethod << std::endl
		          << "Raw Bitmap(Uncompressed) Data Size: " << info_header.rawBitmapDataSize << " bytes" << std::endl
		          << "Bitmap Horizontal Resolution: " << info_header.horizontal_resolution << " ppm" << std::endl
		          << "Bitmap Vertical Resolution: " << info_header.vertical_resolution << " ppm" << std::endl
		          << "Bitmap Number of Colors: " << info_header.numberOfColors << std::endl
		          << "Bitmap Important Colors: " << info_header.importantColors << std::endl;
}
#pragma endregion