#include "Mask.h"
#include <string.h>

#pragma region Constructors/Destructors
Mask::Mask(unsigned int width,unsigned int height) : m_width(width),m_height(height),m_size(width*height)
{
	mask = new float[m_size];
	memset(mask, 0, sizeof(float)*m_size);
}
Mask::Mask(unsigned int width, unsigned int height,float* data) : m_width(width), m_height(height), m_size(width*height),mask(data)
{
}

Mask::~Mask()
{
	delete[] mask;
}
#pragma endregion
