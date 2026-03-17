#pragma once

#pragma region Forward Declaring
class Image;
class Selection;
#pragma endregion

class Selector
{
private:
	/**
	The Selection associated with the Selector.*/
	Selection* current_selection;

#pragma region Constructors/Destructors
public:
	Selector(Selection* selection);
	~Selector();
#pragma endregion
#pragma region Selecting
public:
	/**
	Selects pixels in Selections´s Selected image pixels with greater RGB than the specified in the parameters.

	@param r Selecting RGB Red value.
	@param g Selecting RGB Green value.
	@param b Selecting RGB Blue value.
	@return A Selection.*/
	Selection greaterThanRGB(unsigned char r, unsigned char g, unsigned char b) const;
	/**
	Selects pixels in Selections´s Selected image pixels with smaller RGB than the specified in the parameters.

	@param r Selecting RGB Red value.
	@param g Selecting RGB Green value.
	@param b Selecting RGB Blue value.
	@return A Selection.*/
	Selection lessThanRGB(unsigned char r, unsigned char g, unsigned char b) const;
#pragma endregion
};
