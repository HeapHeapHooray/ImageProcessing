#pragma once
#include <iostream>
#include <math.h>
#undef BI_RGB
#undef BI_RLE8
#undef BI_RLE4
#undef BI_BITFIELDS
#undef BI_JPEG
#undef BI_PNG
class Image;
#pragma region Namespaces
namespace BitmapInfoHeaderTypes {
	/**
	     Represents a Bitmaps큦 Info Header Type*/
		enum InfoHeaderType{BITMAPUNKNOWNTYPE,BITMAPCOREHEADER,BITMAPCOREHEADER2,BITMAPCOREHEADER2v,
			                BITMAPINFOHEADER,BITMAPV2INFOHEADER,BITMAPV3INFOHEADER,BITMAPV4HEADER,BITMAPV5HEADER};
	}
namespace BitmapImageCompressionMethods {
	/**
	    Represents a compression method used by bitmaps.*/
		enum CompressionMethod {BI_RGB,BI_RLE8,BI_RLE4,BI_BITFIELDS,BI_JPEG,
			                    BI_PNG,BI_ALPHABITFIELDS,BI_CMYK,BI_CMYKRLE8,BI_CMYKRLE4};
	}
namespace BitmapFormats {
	/**
	       Represents a Bitmap큦 Format.*/
		enum Format { BITMAP, BITMAP_ARRAY,COLOR_ICON,COLOR_POINTER,ICON,POINTER};
	}
#pragma endregion
#pragma region Headers
/**
A struct that stores Bitmap큦 File Header Data.*/
struct BitmapFileHeader {
	/**
	Stores the Bitmap큦 Format.*/
	BitmapFormats::Format format;
	/**
	Stores the size of the Bitmap File.*/
	unsigned int size;
	/** 
	Stores File Header큦 reserved words as a dword.*/
	unsigned int reserved;
	/**
	Writes a BitmapFileHeader큦 in a std::ostream.
	
	@param stream A reference to the stream to where the BitmapFileHeader큦 will be written.
	@param file_header The file_header that will be written to the ostream.
	@return stream.*/
	friend std::ostream& operator<<(std::ostream& stream, const BitmapFileHeader& file_header);
	/**
	Creates a Bitmap File Header.
	
	@param format a Bitmap Format.
	@param file_size The Size of The Bitmap File.
	@param reserved The reserved File Header큦 words as a dword.
	@return The created BitmapFileHeader.*/
	inline static BitmapFileHeader createBitmapFileHeader(BitmapFormats::Format format, unsigned int file_size,
	unsigned int reserved);
};
/**
A struct that stores Bitmap큦 Info Header Data.*/
struct BitmapInfoHeader {
	/**
	Stores the Bitmap큦 Info Header Type.*/
	BitmapInfoHeaderTypes::InfoHeaderType type;
	/**
	Stores the size of the Info Header.*/
	unsigned int header_size;
	/**
	Stores the Width of the Bitmap Image Data.*/
	int bitmap_width;
	/**
	Stores the Height of the Bitmap Image Data.*/
	int bitmap_height;
	/**
	Stores the Bitmap큦 number of color planes.*/
	unsigned short number_of_color_planes;
	/**
	Stores the Bitmap큦 Color Depth.*/
	unsigned short bitsPerPixel;
	/**
	Stores the Compression method used by the Bitmap.*/
	BitmapImageCompressionMethods::CompressionMethod compressionMethod;
	/**
	Stores the size of the Bitmap큦 Image data without compression (raw data).*/
	unsigned int rawBitmapDataSize;
	/**
	Stores the Bitmap큦 Horizontal Resolution.*/
	int horizontal_resolution;
	/**
	Stores the Bitmap큦 Vertical Resolution.*/
	int vertical_resolution;
	/**
	Stores the Bitmap큦 number of colors.*/
	unsigned int numberOfColors;
	/**
	Stores the Bitmap큦 number of important colors.*/
	unsigned int importantColors;
	/**
	Writes a BitmapInfoHeader to a std::ostream.
	
	@param stream A reference to the stream to where the BitmapInfoHeader will be written.
	@param info_header The BitmapInfoHeader that will be written.
	@return stream.*/
	friend std::ostream& operator<<(std::ostream& stream, const BitmapInfoHeader& info_header);
	/**
	Creates the Application큦 Standard BitmapInfoHeader.
	
	@param image_width The width of the Bitmap Image Data.
	@param image_height The height of the Bitmap Image Data.
	@param bitsPerPixel The Bitmap큦 Color Depth.
	@param compressionMethod The Compression method used by the Bitmap.
	@param image_size The size of the image without compression (raw data).
	@return The created BitmapInfoHeader.*/
	inline static BitmapInfoHeader createStandardBitmapInfoHeader(int image_width, int image_height, unsigned short bitsPerPixel,
	BitmapImageCompressionMethods::CompressionMethod compressionMethod,unsigned int image_size);
};  
#pragma endregion

/**
Class that stores a bitmap file큦 data.*/
class Bitmap
{
private:
	BitmapFileHeader m_fileHeader;
	BitmapInfoHeader m_infoHeader;
	/**
	Stores Bitmap큦 Image Data.*/
	unsigned char* m_data;

#pragma region Constructors/Destructors
public: 
	/**
	A Constructor of Bitmap class.
	
	@param fileHeader The Bitmap큦 BitmapFileHeader.
	@param infoHeader the Bitmap큦 BitmapInfoHeader.
	@param bitmapData the Bitmap큦 Image Data.*/
	Bitmap(const BitmapFileHeader& fileHeader,const BitmapInfoHeader& infoHeader,unsigned char* bitmapData);
	/**
	A Constructor of Bitmap class.
	
	@param image Image that will construct the Bitmap.*/
	Bitmap(const Image* image);
	~Bitmap();
#pragma endregion
#pragma region Headers
public:
	/**
	Gets the Bitmap큦 BitmapFileHeader.
	@return A const pointer to the Bitmap큦 BitmapFileHeader.*/
	inline const BitmapFileHeader* getFileHeader() const { return &m_fileHeader; }
	/**
	Gets the Bitmap큦 BitmapInfoHeader.
	@return A const pointer to the Bitmap큦 BitmapInfoHeader.*/
	inline const BitmapInfoHeader* getInfoHeader() const { return &m_infoHeader; }
#pragma endregion
#pragma region Image Data
public:
	/**
	Gets Bitmap큦 Image Data.
	@return Bitmap큦 Image Data.*/
	inline const unsigned char* getImageData() const { return m_data; }
	/**
	Gets Bitmaps큦 Image Data큦 row size with padding.
	@return Bitmap큦 Image Data큦 row size with padding.*/
	inline unsigned int getRowSize() const { return (((m_infoHeader.bitsPerPixel*m_infoHeader.bitmap_width + 31)&~31)>>3); }
	/**
	Gets Bitmap큦 Image Data큦 Number of Pixels.
	@return Bitmap큦 Image Data큦 Number of Pixels.*/
	inline unsigned int getNumberOfPixels() const { return m_infoHeader.bitmap_width*m_infoHeader.bitmap_height; }
	/**
	Gets Bitmap큦 Image Data큦 size with padding.
	@return Bitmap큦 Image Data큦 size with padding.*/
	inline unsigned int getSizeOfImage() const { return getRowSize()*abs(m_infoHeader.bitmap_height); }
	/**
	Gets Bitmap큦 Image Data큦 Height.
	@return Bitmap큦 Image Data큦 Height*/
	inline int getHeight() const { return m_infoHeader.bitmap_height; }
	/**
	Gets Bitmap큦 Image Data큦 Width.
	@return Bitmap큦 Image Data큦 Width*/
	inline int getWidth() const { return m_infoHeader.bitmap_width; }
#pragma endregion
#pragma region Utils
public:
	/**
	Gets Estimated Bitmap큦 size in disk.
	@return Estimated Bitmap큦 size in disk.
	@todo Create this Method.*/
	unsigned int getEstimatedSizeInDisk();
#pragma endregion
};

