#pragma once

#pragma region Forward Declaring
class Image;
class Selection;
#pragma endregion

/**
Performs a Selection in a Image.*/
class RootSelector
{
private:
	/**
	A reference to image´s data pointer element.*/
	unsigned char*& image_data;
	/**
	Selecting image.*/
	const Image* image;
public:
#pragma region Constructors/Destructors
	RootSelector(unsigned char*& imageData, const Image* img);
	~RootSelector();
#pragma endregion
#pragma region Selecting
	/**
	Selects pixels in image with greater RGB than the specified in the parameters.
	
	@param r Selecting RGB Red value.
	@param g Selecting RGB Green value.
	@param b Selecting RGB Blue value.
	@return A Selection.*/
	Selection greaterThanRGB(unsigned char r, unsigned char g, unsigned char b) const;
	/**
	Selects pixels in image with smaller RGB than the specified in the parameters.

	@param r Selecting RGB Red value.
	@param g Selecting RGB Green value.
	@param b Selecting RGB Blue value.
	@return A Selection.*/
	Selection lessThanRGB(unsigned char r, unsigned char g, unsigned char b) const;
	/**
	Selects pixels in image that are not equal to a pixel in the same position in the comparing image.

	@param r Selecting RGB Red value.
	@param g Selecting RGB Green value.
	@param b Selecting RGB Blue value.
	@return A Selection.*/
	Selection notEqualToRGB(const Image* comparing_to) const;
#pragma endregion
};

