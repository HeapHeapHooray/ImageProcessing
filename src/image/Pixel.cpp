#include "Pixel.h"

#pragma region Constructors/Destructors
Pixel::Pixel(unsigned char* first_value_address) : 
red(*first_value_address),green(*(first_value_address+1)),blue(*(first_value_address+2)),alpha(*(first_value_address+3)),
data_start_address(first_value_address)
{
}
Pixel::~Pixel()
{
}
#pragma endregion
#pragma region Static
float Pixel::getLinearSimiliarityRGB(const Pixel* a, const Pixel* b)
{
	return  100 - ((fabsf(a->getRGBRedPercentage() - b->getRGBRedPercentage())) +
		    (fabsf(a->getRGBGreenPercentage() - b->getRGBGreenPercentage())) +
		    (fabsf(a->getRGBBluePercentage() - b->getRGBBluePercentage())) / 3);
}
#pragma endregion
