#include "Selector.h"
#include "Selection.h"

#pragma region Constructors/Destructors
Selector::Selector(Selection* selection) : current_selection(selection){}
Selector::~Selector()
{
}
#pragma endregion
#pragma region Selecting
Selection Selector::greaterThanRGB(unsigned char r, unsigned char g, unsigned char b) const
{
	BitMask mask = *current_selection->getSelectionBitMask();
	const unsigned int mask_size = mask.getSize();
	for (unsigned int i = 0; i < mask_size; i++)
		if (mask[i]) {
			const unsigned char* ptr = mask.getPointerFromIndex(i);
			if (!(*ptr > r) || !(*(ptr + 1) > g) || !(*(ptr + 2) > b))
				mask[i] = false;
		}
	return Selection(mask);
}
Selection Selector::lessThanRGB(unsigned char r, unsigned char g, unsigned char b) const
{
	BitMask mask = *current_selection->getSelectionBitMask();
	const unsigned int mask_size = mask.getSize();
	for (unsigned int i = 0; i < mask_size; i++)
		if (mask[i]) {
			unsigned char* ptr = mask.getPointerFromIndex(i);
			if (!(*ptr < r) || !(*(ptr + 1) < g) || !(*(ptr + 2) < b))
				mask[i] = false;
		}
	return Selection(mask);
}
#pragma endregion