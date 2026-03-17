#include "BitMask.h"
#include <string.h>

#pragma region Constructors/Destructors
BitMask::BitMask(unsigned char*& data_address,unsigned int width,unsigned int height,unsigned int index_stride) : 
initial_data_address(data_address),m_size(height*width),stride(index_stride),m_width(width),
m_height(height)
{
	bitmask = new bool[m_size];
	memset(bitmask, 0, sizeof(bool)*m_size);
}


BitMask::~BitMask()
{
}
#pragma endregion
#pragma region Operations
void BitMask::fillColor(unsigned char r, unsigned char g, unsigned char b,unsigned char a)
{
	for (unsigned int i = 0; i < m_size; i++)
		if (bitmask[i])
		{
			unsigned char* ptr = initial_data_address + i*stride;
			*(ptr) = r;
			*(ptr + 1) = g;
			*(ptr + 2) = b;
			*(ptr + 3) = a;
		}
}

void BitMask::paintColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	const float a_div_255 = (float)a / 255;
	const float omn_a_div_255 = 1 - a_div_255;
	for (unsigned int i = 0; i < m_size; i++)
	{
		if (bitmask[i])
		{
			unsigned char* ptr = initial_data_address + i*stride;
			const float alpha_div_255_times_omn_a_div_255 = ((float)*(ptr + 3) / 255)*omn_a_div_255;
			*(ptr) =   *(ptr)*alpha_div_255_times_omn_a_div_255 + r*a_div_255;
			*(ptr+1) = *(ptr+1)*alpha_div_255_times_omn_a_div_255 + g*a_div_255;
			*(ptr+2) = *(ptr+2)*alpha_div_255_times_omn_a_div_255 + b*a_div_255;
			*(ptr+3) = (alpha_div_255_times_omn_a_div_255 + a_div_255)*255;
		}
	}
}
void BitMask::desaturate(float desaturation_percentage)
{
	if (desaturation_percentage > 100) desaturation_percentage = 100;
	else if (desaturation_percentage < 0) desaturation_percentage = 0;
	desaturation_percentage /= 100;
	const float desaturation_percentage_divided_by_3 = desaturation_percentage / 3;
	const float one_minus_desaturation_percentage = 1 - desaturation_percentage;
	for (unsigned int i = 0; i < m_size; i++)
	{
		if (bitmask[i])
		{
			unsigned char* ptr = initial_data_address + i*stride;
			const unsigned char rgb_average = (*(ptr)+*(ptr + 1) + *(ptr + 2))*desaturation_percentage_divided_by_3;
			*(ptr) = *(ptr)*one_minus_desaturation_percentage + rgb_average;
			*(ptr + 1) = *(ptr + 1)*one_minus_desaturation_percentage + rgb_average;
			*(ptr + 2) = *(ptr + 2)*one_minus_desaturation_percentage + rgb_average;
		}
	}
}
#pragma endregion
#pragma region Image
unsigned char* BitMask::getImageData() const {
	unsigned char* image_data = new unsigned char[m_size * 4];
	for (unsigned int i = 0, y = 0; i < m_size; i++, y += 4)
		if (bitmask[i])
		{
			const unsigned char* i_ptr = initial_data_address + i*stride;
			image_data[y] = *(i_ptr);
			image_data[y + 1] = *(i_ptr + 1);
			image_data[y + 2] = *(i_ptr + 2);
			image_data[y + 3] = *(i_ptr + 3);
		}
		else {
			image_data[y] = 0;
			image_data[y + 1] = 0;
			image_data[y + 2] = 0;
			image_data[y + 3] = 0;
		}
	return image_data;
}
#pragma endregion