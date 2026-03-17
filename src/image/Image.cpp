#include "Image.h"
#include "Bitmap.h"
#include "../selecting/BitMask.h"
#include "../Mask.h"

#pragma region Constructors/Destructors
Image::Image(const Bitmap* bitmap) : select(m_data,this)//TODO: Modify This!
{
	unsigned char valuesPerPixel = (bitmap->getInfoHeader()->bitsPerPixel)>>3;
	if (valuesPerPixel < 3||valuesPerPixel>4) return;

	unsigned int image_size = bitmap->getSizeOfImage();
	const unsigned char* image_data = bitmap->getImageData();
	m_height = bitmap->getHeight();
	m_width = bitmap->getWidth();

	unsigned int new_image_size = (((32 * m_width) + 31) / 32) * 4 * m_height;
	m_data = new unsigned char[new_image_size];
	m_data_size = new_image_size;

	unsigned int rowSize = ((bitmap->getWidth()*bitmap->getInfoHeader()->bitsPerPixel + 31) / 32) * 4;
	unsigned int valuesPerRow = m_width*valuesPerPixel;
	const unsigned int width_times_4 = m_width * 4;

	for (unsigned int y = 0; y < m_height; y++) 
	{
	 register const unsigned int y_times_wtms4 = y * width_times_4;
	 register const unsigned int y_times_rowSize = y * rowSize;
	 for (unsigned int x = 0, i = 0; x < valuesPerRow; x += valuesPerPixel, i += 4)
	 {
	   const unsigned int ytw_plus_i = y_times_wtms4 + i;
	   const unsigned int ytr_plus_x = y_times_rowSize + x;
	   m_data[ytw_plus_i]     = image_data[ytr_plus_x + 2]; //Red
	   m_data[ytw_plus_i + 1] = image_data[ytr_plus_x + 1]; //Green 
	   m_data[ytw_plus_i + 2] = image_data[ytr_plus_x]; //Blue
	   m_data[ytw_plus_i + 3] = 255; //Alpha
	   //RGBA
	 }
	}
	/*for (unsigned int i = 0; i < data_size; i += 4) {
		if (m_data[i] + m_data[i + 1] + m_data[i + 2]>500) m_data[i] = m_data[i + 1] = m_data[i + 2] = 255;
		else if (m_data[i] + m_data[i + 1] + m_data[i + 2] < 300) m_data[i] = m_data[i + 1] = m_data[i + 2] = 0;
	}8?
	/*for (unsigned int i=0,y=0; y < new_image_size; i+=valuesPerPixel,y+=4) {
		m_data[y] = image_data[i + 2]; // Red
		m_data[y+1] = image_data[i+1]; // Green
		m_data[y+2] = image_data[i]; //Blue 
		m_data[y + 3] = 255;// image_data[i]; // Alpha
		//RGBA
	}*/
}
Image::Image(const BitMask* mask) : select(m_data, this),
m_width(mask->getWidth()),m_height(mask->getHeight())
{
	unsigned int size = mask->getSize();
	m_data_size = size * 4;
	m_data = new unsigned char[m_data_size];
	for (unsigned int i = 0, y = 0; i < size; i++, y += 4)
		if ((*mask)[i]) m_data[y] = m_data[y + 1] = m_data[y + 2] = m_data[y + 3] = 255;
		else m_data[y] = m_data[y + 1] = m_data[y + 2] = m_data[y + 3] = 0;
}
Image::Image(const Mask* mask):select(m_data, this),
m_width(mask->getWidth()), m_height(mask->getHeight())
{
	float largest_element = mask->getLargestElement();
	unsigned int mask_size = mask->getSize();

	m_data_size = mask_size * 4;
	m_data = new unsigned char[m_data_size];

	for (unsigned int i = 0, y = 0; i < mask_size; i++, y += 4) {
		m_data[y]  = m_data[y+1] = m_data[y+2] = (255 * (*mask)[i]) / largest_element;
		m_data[y + 3] = 255;
	}
}
Image::Image(const Mask* mask,float min_difference) :select(m_data, this),
m_width(mask->getWidth()), m_height(mask->getHeight())
{
	float largest_element = mask->getLargestElement();
	unsigned int mask_size = mask->getSize();

	m_data_size = mask_size * 4;
	m_data = new unsigned char[m_data_size];

	for (unsigned int i = 0, y = 0; i < mask_size; i++, y += 4) 
	m_data[y] = m_data[y + 1] = m_data[y + 2] = m_data[y + 3] = (*mask)[i]>=min_difference?255:0;
}
Image::Image(unsigned char* image_data, unsigned int width, unsigned int height):m_data(image_data),m_width(width),
m_height(height),select(m_data,this),m_data_size(width*height*4)
{}
Image::~Image()
{
	delete[] m_data;
}
#pragma endregion
#pragma region Operations
Image Image::copy()
{
	unsigned char* new_image_data = new unsigned char[m_data_size];
	for (unsigned int i = 0; i < m_data_size; i++)
		new_image_data[i] = m_data[i];
	return Image(new_image_data, m_width, m_height);
}
Image& Image::crop(unsigned int minX, unsigned int minY, unsigned int maxX, unsigned int maxY)
{
	if (minX > m_width)  minX = m_width;
	if (minY > m_height) minY = m_height;
	if (maxX > m_width)  maxX = m_width;
	if (maxY > m_height) maxY = m_height;
	if (minX > maxX)
	{
		const unsigned int aux = maxX;
		maxX = minX;
		minX = aux;
	}
	if (minY > maxY)
	{
		const unsigned int aux = maxY;
		maxY = minY;
		minY = aux;
	}

	const unsigned int croppedHeight = (maxY - minY);
	const unsigned int croppedWidth = (maxX - minX);
    const unsigned int croppedDataSize = croppedHeight*croppedWidth * 4;

	unsigned char* croppedImageData = new unsigned char[croppedDataSize];
	for (unsigned int y = 0; y < croppedHeight;y++)
	for (unsigned int x = 0; x < croppedWidth*4; x++)
	croppedImageData[x + y*croppedWidth*4] = m_data[(minX*4 + x) + (minY*m_width*4) + y*m_width * 4];

	delete[] m_data;
	m_width = croppedWidth;
	m_height = croppedHeight;
	m_data_size = croppedDataSize;
	m_data = croppedImageData;
	return *this;
}
Image& Image::invertHorizontally()
{
	for (unsigned int y = 0; y < m_height; y++)
		for (unsigned int x = 0; x < m_width/2; x++) {
			Pixel::swap(&getPixel(x + y*m_width),&getPixel(m_width - x - 1 + y*m_width));
			/*unsigned char  *pixel_addr = &m_data[(x * 4 + y*m_width * 4)],
				           *pixel_addr2 = &m_data[((m_width-x) * 4 + y*m_width * 4)-4];
			unsigned char r = *pixel_addr, g = *(pixel_addr + 1), b = *(pixel_addr + 2), a = *(pixel_addr + 3);

			*pixel_addr = *pixel_addr2;
			*(pixel_addr+1) = *(pixel_addr2+1);
			*(pixel_addr+2) = *(pixel_addr2+2);
			*(pixel_addr+3) = *(pixel_addr2+3);

			*pixel_addr2 = r;
			*(pixel_addr2 + 1) = g;
			*(pixel_addr2 + 2) = b;
			*(pixel_addr2 + 3) = a;*/
		}
	return *this;
}
Image& Image::invertVertically()
{
	for (unsigned int x = 0; x < m_width-1; x++)
		for (unsigned int y = 0; y < m_height / 2; y++) {
			Pixel::swap(&getPixel(x + y*m_width), &getPixel(x + (m_height-y-1)*m_width));
			/*unsigned char  *pixel_addr = &m_data[(x * 4 + y*m_width * 4)],
			*pixel_addr2 = &m_data[((m_width-x) * 4 + y*m_width * 4)-4];
			unsigned char r = *pixel_addr, g = *(pixel_addr + 1), b = *(pixel_addr + 2), a = *(pixel_addr + 3);

			*pixel_addr = *pixel_addr2;
			*(pixel_addr+1) = *(pixel_addr2+1);
			*(pixel_addr+2) = *(pixel_addr2+2);
			*(pixel_addr+3) = *(pixel_addr2+3);

			*pixel_addr2 = r;
			*(pixel_addr2 + 1) = g;
			*(pixel_addr2 + 2) = b;
			*(pixel_addr2 + 3) = a;*/
		}
	return *this;
}
Image& Image::desaturate(float desaturation_percentage)
{
	if (desaturation_percentage > 100) desaturation_percentage = 100;
	else if (desaturation_percentage < 0) desaturation_percentage = 0;
	desaturation_percentage /= 100;
	const float desaturation_percentage_divided_by_3 = desaturation_percentage / 3;
	const float one_minus_desaturation_percentage = 1 - desaturation_percentage;
	for (unsigned char *ptr = m_data; ptr != (&m_data[m_data_size]); ptr += 4)
	{
		const unsigned char rgb_average = (*(ptr)+*(ptr + 1) + *(ptr + 2))*desaturation_percentage_divided_by_3;
		*(ptr) = *(ptr)*one_minus_desaturation_percentage + rgb_average;
		*(ptr+1) = *(ptr+1)*one_minus_desaturation_percentage + rgb_average;
		*(ptr+2) = *(ptr+2)*one_minus_desaturation_percentage + rgb_average;
	}
	return *this;
}
Image& Image::fillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	for (unsigned char* ptr=m_data;ptr!=(&m_data[m_data_size]); ptr += 4) {
		*(ptr) = r;
		*(ptr+1) = g;
		*(ptr+2) = b;
		*(ptr+3) = a;
	}
	return *this;
}
Image& Image::fillColor(unsigned char r, unsigned char g, unsigned char b)
{
	return fillColor(r, g, b, 255);
}
Image& Image::paintColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	const float a_div_255 = (float)a / 255;
	const float omn_a_div_255 = 1 - a_div_255;
	for (unsigned char* ptr = m_data; ptr != (&m_data[m_data_size]); ptr += 4) {
		const float alpha_div_255_times_omn_a_div_255 = ((float)*(ptr + 3) / 255)*omn_a_div_255;
	   *(ptr) =     *(ptr)*alpha_div_255_times_omn_a_div_255 + r*a_div_255;
	   *(ptr + 1) = *(ptr+1)*alpha_div_255_times_omn_a_div_255 + g*a_div_255;
	   *(ptr + 2) = *(ptr+2)*alpha_div_255_times_omn_a_div_255 + b*a_div_255;
	   *(ptr + 3) =  (alpha_div_255_times_omn_a_div_255 + a_div_255)*255;
	}
	return *this;
}
Image& Image::insertImage(const Image* image, unsigned int x_pos, unsigned int y_pos)
{
	const unsigned int image_width = image->getWidth();
	const unsigned int min_x = image_width / 2 > x_pos ? 0 : (x_pos - image_width / 2);
	if (min_x > m_width) return *this;

	const unsigned int image_height = image->getHeight();
	const unsigned int min_y = image_height / 2 > y_pos ? 0 : (y_pos - image_height / 2);
	if (min_y > m_height) return *this;
	const unsigned int max_x = x_pos + image_width / 2 > m_width ? m_width : x_pos + image_width / 2;
	const unsigned int max_y = y_pos + image_height / 2 > m_height ? m_height : y_pos + image_height / 2;

	const unsigned int width = max_x - min_x;
	const unsigned int height = max_y - min_y;

	const unsigned char* image_data = image->getData();

	for (unsigned int y = 0; y < height; y++)
	for (unsigned int x = 0; x < width; x++)
		mix_rgba_values(&m_data[(min_x + x) * 4 + (min_y + y)*m_width * 4], 
				        &image_data[(x)* 4 + (y)*image_width * 4]);

	return *this;
}
#pragma endregion
#pragma region Static
float Image::getLinearSimiliarityRGB(const Image* a,const Image* b) //TODO: Recreate This!
{
	/*const unsigned int min_width = a->getWidth() < b->getWidth() ? a->getWidth() : b->getWidth();
	const unsigned int min_height = a->getHeight() < b->getHeight() ? a->getHeight() : b->getHeight();
	double differences_sum=0;
	for (unsigned int y = 0; y < min_height; y++)
		for (unsigned int x = 0; x < min_width; x++)
		{
			Pixel pa = a->getPixel(x + y*a->getWidth());
			Pixel pb = b->getPixel(x + y*b->getWidth());
			differences_sum += (fabsf(pa.getRGBRedPercentage() - pb.getRGBRedPercentage())
				+ fabsf(pa.getRGBGreenPercentage() - pb.getRGBGreenPercentage())
				+ fabsf(pa.getRGBBluePercentage() - pb.getRGBBluePercentage())) / 3;
		}
	*/
	return 0;// 100 - 2 * differences_sum / (min_width*min_height);
}
Mask Image::getRGBDifferenceMask(const Image* a, const Image* b)
{
	const unsigned int min_width = a->getWidth() < b->getWidth() ? a->getWidth() : b->getWidth();
	const unsigned int min_height = a->getHeight() < b->getHeight() ? a->getHeight() : b->getHeight();
	float* mask = new float[min_width*min_height];
	const unsigned char* data_a = a->getData();
	const unsigned char* data_b = b->getData();
	for (unsigned int y = 0; y < min_height; y++) {
		const unsigned int y_times_a_width = y*a->getWidth();
		const unsigned int y_times_b_width = y*b->getWidth();
		const unsigned int y_times_min_width = y*min_width;
		for (unsigned int x = 0; x < min_width; x++)
		{
			const unsigned char* ra = data_a+((x + y_times_a_width) * 4);
			const unsigned char* rb = data_b+((x + y_times_b_width) * 4);
			mask[x + y_times_min_width] = (100 * (abs(ra[0] - rb[0])+ abs(ra[1] - rb[1]) + 
				abs(ra[2] - rb[2]))) / 765;

		}
	}
	return Mask(min_width,min_height,mask);
}
#pragma endregion