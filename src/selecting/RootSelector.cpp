#include "RootSelector.h"
#include "../image/Image.h"
#include "Selection.h"

#pragma region Constructors/Destructors
RootSelector::RootSelector(unsigned char*& imageData, const Image* img) : image_data(imageData), image(img) {}
RootSelector::~RootSelector(){}
#pragma endregion
#pragma region Selecting
Selection RootSelector::greaterThanRGB(unsigned char r, unsigned char g, unsigned char b) const
{
	BitMask* mask_ = new BitMask(image_data, image->getWidth(), image->getHeight(), 4);
	BitMask& mask = *mask_;
	const unsigned int data_size = image->getDataSize();
	for (unsigned int i = 0, y = 0; i < data_size; i += 4, y++)
		if ((image_data[i] > r) && (image_data[i + 1] > g) && (image_data[i + 2] > b))
			mask[y] = true;
	return Selection(mask_);
}
Selection RootSelector::greaterSimiliarityRGB(const Image* comparing_to, float min_similiarity) const
{
	const unsigned char* comparing_to_data = comparing_to->getData();
	BitMask* mask_ = new BitMask(image_data, image->getWidth(), image->getHeight(), 4);
	BitMask& mask = *mask_;
	if (comparing_to->getWidth() == image->getWidth() && comparing_to->getHeight() == image->getHeight())
	{
		bool* bm = mask_->bitmask;
		const unsigned int data_size = image->getDataSize();
		for (unsigned int y = 0, i = 0; y < data_size; y += 4, i++)
			if (100-get_rgba_distance(&image_data[y], &comparing_to_data[y])>=min_similiarity)
				bm[i] = true;
		return mask_;
	}
	const unsigned int comp_width = image->getWidth();
	const unsigned int comp_height = image->getHeight();
	const unsigned int comp_to_width = comparing_to->getWidth();
	const unsigned int comp_to_height = comparing_to->getHeight();
	const unsigned int min_height = comp_height < comp_to_height ? comp_height : comp_to_height;
	const unsigned int min_width = comp_width < comp_to_width ? comp_width : comp_to_width;
	for (unsigned int y = 0; y < min_height; y++)
	{
		register const unsigned int y_times_comp_width = y*comp_width;
		register const unsigned int y_times_comp_to_width = y*comp_to_width;
		for (unsigned int x = 0; x < min_width; x++) {
			if (100-get_rgba_distance(&image_data[(x + y_times_comp_to_width) * 4],
				&comparing_to_data[(x + y_times_comp_to_width) * 4]) >= min_similiarity)
				mask[x + y_times_comp_width] = true;
		}
	}
	return Selection(mask_);
}
Selection RootSelector::lessThanRGB(unsigned char r, unsigned char g, unsigned char b) const
{
	BitMask* mask_ = new BitMask(image_data, image->getWidth(), image->getHeight(), 4);
	BitMask& mask = *mask_;
	const unsigned int data_size = image->getDataSize();
	for (unsigned int i = 0; i < data_size; i += 4)
		if ((image_data[i] < r) && (image_data[i + 1] < g) && (image_data[i + 2] < b))
			mask[i / 4] = true;
	return Selection(mask_);
}
Selection RootSelector::equalToRGB(const Image* comparing_to) const
{
	const unsigned char* comparing_to_data = comparing_to->getData();
	BitMask* mask_ = new BitMask(image_data, image->getWidth(), image->getHeight(), 4);
	BitMask& mask = *mask_;
	if (comparing_to->getWidth() == image->getWidth() && comparing_to->getHeight() == image->getHeight())
	{
		bool* bm = mask_->bitmask;
		const unsigned int data_size = image->getDataSize();
		for (unsigned int y = 0, i = 0; y < data_size; y += 4, i++)
			if (image_data[y] == comparing_to_data[y] && image_data[y + 1] == comparing_to_data[y + 1]
				&& image_data[y + 2] == comparing_to_data[y + 2])
				bm[i] = true;
		return mask_;
	}
	const unsigned int comp_width = image->getWidth();
	const unsigned int comp_height = image->getHeight();
	const unsigned int comp_to_width = comparing_to->getWidth();
	const unsigned int comp_to_height = comparing_to->getHeight();
	const unsigned int min_height = comp_height < comp_to_height ? comp_height : comp_to_height;
	const unsigned int min_width = comp_width < comp_to_width ? comp_width : comp_to_width;
	for (unsigned int y = 0; y < min_height; y++)
	{
		register const unsigned int y_times_comp_width = y*comp_width;
		register const unsigned int y_times_comp_to_width = y*comp_to_width;
		for (unsigned int x = 0; x < min_width; x++) {
			if (image_data[(x + y_times_comp_width) * 4] == comparing_to_data[(x + y_times_comp_to_width) * 4]
				&& image_data[(x + y_times_comp_width) * 4 + 1] == comparing_to_data[(x + y_times_comp_to_width) * 4 + 1]
				&& image_data[(x + y_times_comp_width) * 4 + 2] == comparing_to_data[(x + y_times_comp_to_width) * 4 + 2])
				mask[x + y_times_comp_width] = true;
		}
	}
	return Selection(mask_);
}

Selection RootSelector::notEqualToRGB(const Image* comparing_to) const
{
		const unsigned char* comparing_to_data = comparing_to->getData();
	BitMask* mask_ = new BitMask(image_data, image->getWidth(), image->getHeight(), 4);
	BitMask& mask = *mask_;
	if (comparing_to->getWidth() == image->getWidth() && comparing_to->getHeight() == image->getHeight())
	{
	   bool* bm = mask_->bitmask;
		const unsigned int data_size = image->getDataSize();
		for (unsigned int y = 0, i = 0; y < data_size; y += 4, i++)
			if (image_data[y] != comparing_to_data[y] || image_data[y + 1] != comparing_to_data[y + 1]
				|| image_data[y + 2] != comparing_to_data[y + 2])
				bm[i] = true;
		return mask_;
	}
	const unsigned int comp_width = image->getWidth();
	const unsigned int comp_height = image->getHeight();
	const unsigned int comp_to_width = comparing_to->getWidth();
	const unsigned int comp_to_height = comparing_to->getHeight();
	const unsigned int min_height = comp_height < comp_to_height ? comp_height : comp_to_height;
	const unsigned int min_width = comp_width < comp_to_width ? comp_width : comp_to_width;
	for (unsigned int y = 0; y < min_height; y++) 
	{
	register const unsigned int y_times_comp_width = y*comp_width;
	register const unsigned int y_times_comp_to_width = y*comp_to_width;
	for (unsigned int x = 0; x < min_width; x++) {
		if (image_data[(x + y_times_comp_width) * 4] != comparing_to_data[(x + y_times_comp_to_width) * 4]
			|| image_data[(x + y_times_comp_width) * 4 + 1] != comparing_to_data[(x + y_times_comp_to_width) * 4 + 1]
			|| image_data[(x + y_times_comp_width) * 4 + 2] != comparing_to_data[(x + y_times_comp_to_width) * 4 + 2])
			mask[x + y_times_comp_width] = true;
	}
}
	return Selection(mask_);
}
#pragma endregion
