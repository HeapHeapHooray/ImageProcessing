#pragma once
#include "../Image.h"
namespace Transform
{
	static void applyLinearTransformation(unsigned char* image_data,const unsigned char image_data_size, 
	const unsigned char transformation_input)
	{
		for (unsigned int i = 0; i < image_data_size; i++)
			if (image_data[i] + transformation_input>255) image_data[i] = 255;
			else
			image_data[i] += transformation_input;
	}
	static void applyInverseTransformation(unsigned char* image_data, const unsigned char image_data_size)
	{
		for (unsigned int i = 0; i < image_data_size; i++) image_data[i] = 255 - image_data[i];
	}
}
