#pragma once
#include "Pixel.h"
#include "../selecting/RootSelector.h"
#include "../selecting/Selection.h"

#pragma region Forward Declaring
class Bitmap;
class BitMask;
class Mask;
#pragma endregion

/**
Stores,Manipulates and represents an image data*/
class Image 
{
#pragma region Attributes
private:
/**
Stores image data*/
	unsigned char* m_data;
	unsigned int m_data_size;
	unsigned int m_width;
	unsigned int m_height;
public:
	const RootSelector select;
#pragma endregion
#pragma region Constructors/Destructors
public:
	Image(const Bitmap* bitmap);
	Image(unsigned char* image_data, unsigned int image_width, unsigned int image_height);
	Image(const BitMask* mask);
	Image(const Mask* mask);
	Image(const Mask* mask, float min_difference);
	~Image();
#pragma endregion
#pragma region Image Data
public:
	/**
	Gets Size of Image Data.
	
	@return Size of Image Data.*/
	unsigned int getDataSize() const { return m_data_size; }
	/**
	Gets Image큦 Width
	
	@return Image큦 Width.*/
	unsigned int getWidth() const { return m_width; }
	/**
	Gets Image큦 Height

	@return Image큦 Height.*/
	unsigned int getHeight() const { return m_height; }
	/**
	Gets a nth Pixel from the Image.
	
	@param index Index of the desired pixel.
	@return Desired pixel.*/
	Pixel getPixel(unsigned int index) { return Pixel(&m_data[index*4]); }
	/**
	Gets a nth const Pixel from the Image.

	@param index Index of the desired const pixel.
	@return Desired const pixel.*/
	const Pixel getPixel(unsigned int index) const { return Pixel(&m_data[index * 4]); }
	/**
	Gets Image큦 Data.
	
	@return Image큦 Data.*/
	unsigned char* getData() const { return m_data; }
#pragma endregion
#pragma region Operations
public:
	/**
	Creates a Copy of the Image.
	
	@return a Copy of the Image.*/
	Image copy();
	/**
	Crops Image, keeping only the rectangular area specified by the params.
	
	@param minX Minimum X value of the area that will be cropped.
	@param minY Minimum Y value of the area that will be cropped.
	@param maxX Maximun X value of the area that will be cropped.
	@param minY Maximun Y value of the area that will be cropped.
	@return A reference to the image itself.
	@todo const version.*/
	Image& crop(unsigned int minX, unsigned int minY, unsigned int maxX, unsigned int maxY);
	/**
	Inverts Image Horizontally.
	
	@return A reference to the image itself.*/
	Image& invertHorizontally();
	/**
	Inverts Image Vertically.

	@return A reference to the image itself.*/
	Image& invertVertically();
	/**
	Desaturates every image큦 pixel by the specified percentage.
	
	@param desaturation_percentage The percentage that the pixels will be desaturated. 0%  - 100%
	@return A reference to the image itself.*/
	Image& desaturate(float desaturation_percentage);
	/**
	Changes every pixel큦 color in the image by the color specified in the params.
	
	@param r Red value of RGBA pixel. 0 - 255.
	@param g Green value of RGBA pixel. 0 - 255.
	@param b Blue value of RGBA pixel. 0 - 255.
	@param a Alpha value of RGBA pixel. 0 - 255.
	@return A Reference to the image itself.*/
	Image& fillColor(unsigned char r, unsigned char g, unsigned char b,unsigned char a);
	/**
	Changes every pixel큦 color in the image by the color specified in the params.

	@param r Red value of RGBA pixel. 0 - 255.
	@param g Green value of RGBA pixel. 0 - 255.
	@param b Blue value of RGBA pixel. 0 - 255.
	@return A Reference to the image itself.*/
	Image& fillColor(unsigned char r, unsigned char g, unsigned char b);
	/**
	Paints every pixel in the image with the color specified in the params.
	
	@param r Red value of paint color. 0 - 255.
	@param g Green value of paint color. 0 - 255.
	@param b Blue value of paint color. 0 - 255.
	@param a Alpha value of paint color. 0 - 255.
	@return A Reference to the image itself.*/
	Image& paintColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	/**
	Inserts an image in front of the Image.
	
	@param image The image that will be inserted in front of the Image.
	@param x_pos The x position where the image will be inserted in Image.
	@param y_pos The y position where the image will be inserted in Image.
	@return A Reference to the image itself.*/
	Image& insertImage(const Image* image, unsigned int x_pos, unsigned int y_pos);
	/**
	Shifts the Image n Pixels to the Rigth.
	
	@param number_of_pixels Number of Pixels that the Image will shift right.
	@return A Reference to the image itself.*/
	Image& shiftRigth(unsigned int number_of_pixels);
#pragma endregion
#pragma region Static
public:
	/**
	Gets a Mask that stores the difference of the images큦 pixels as elements.
	
	@param a An Image to Compare.
	@param b An Image to Compare.
	@return A Mask that stores the difference of the images큦 pixels as elements.*/
	static Mask getRGBDifferenceMask(const Image* a, const Image* b);
	//friend void swap_data(Image* img,Image* img2);
	//selector.
	//         selectSimiliarPercentagesRGB(r percentage,g percentage,b percentage,float min_similiarity) <- searchs for pixels with similiar rgb percentages
    static float getLinearSimiliarityRGB(const Image* a,const Image* b);
#pragma endregion
#pragma region Utils
private:

	
	/**
	Mixes Pixels큦 RGBA Values.
	
	@param ptr1 A pointer to the first element of the RGBA that will be changed.
	@param ptr2 A pointer to the first element of the RGBA that will be mixed to the RGBA of ptr1.*/
	inline void mix_rgba_values(unsigned char* ptr1,const unsigned char* ptr2)
	{
		const float a_div_255 = (float)*(ptr2+3) / 255;
		const float alpha_div_255_times_omn_a_div_255 = ((float)*(ptr1 + 3) / 255)*(1 - a_div_255);
		*(ptr1) = *(ptr1)*alpha_div_255_times_omn_a_div_255 + *(ptr2)*a_div_255;
		*(ptr1+1) = *(ptr1+1)*alpha_div_255_times_omn_a_div_255 + *(ptr2+1)*a_div_255;
		*(ptr1+2) = *(ptr1+2)*alpha_div_255_times_omn_a_div_255 + *(ptr2+2)*a_div_255;
		*(ptr1 + 3) = (alpha_div_255_times_omn_a_div_255 + a_div_255) * 255;
	}
#pragma endregion
};

