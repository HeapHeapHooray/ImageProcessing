#pragma once
#include <vector>
#include "Selector.h"
#include "BitMask.h"

class Image;
/**
Interface of a Selection BitMask and a Selector.*/
class Selection
{
private:
	BitMask m_selection_mask;
public:
	Selector select;
#pragma region Constructors/Destructors
public:
	Selection(BitMask selection_mask);
	~Selection();
#pragma endregion
#pragma region Operations
public:
	/**
	Changes every selected pixel in the selection bitmask큦 associated image for the specified params.

	@param r Red value of RGBA pixel. 0 - 255
	@param g Green value of RGBA pixel. 0 - 255
	@param b Blue value of RGBA pixel. 0 - 255
	@param a Alpha value of RGBA pixel. 0 - 255
	@return A reference to the Selection itself.*/
	inline Selection& fillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { m_selection_mask.fillColor(r, g, b, a); return *this; };
	/**
	Changes every selected pixel in the selection bitmask큦 associated image for the specified params.

	@param r Red value of RGBA pixel. 0 - 255
	@param g Green value of RGBA pixel. 0 - 255
	@param b Blue value of RGBA pixel. 0 - 255
	@return A reference to the Selection itself.*/
	inline Selection& fillColor(unsigned char r, unsigned char g, unsigned char b) { m_selection_mask.fillColor(r, g, b, 255); return *this; }
	/**
	Paints every selected pixel in the selection bitmask큦 associated image with the params큦 specified color.

	@param r Red value of paint color. 0 - 255
	@param g Green value of paint color. 0 - 255
	@param b Blue value of paint color. 0 - 255
	@param alpha Alpha value of paint color. 0 - 255
	@return A reference to the Selection itself. */
	inline Selection& paintColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { m_selection_mask.paintColor(r, g, b, a); return *this; }
	/**
	Inverts the Selection, everything selected will be unselected and everything unselected will be selected.

	@return A reference to the Selection itself.*/
	inline Selection& invertSelection() { m_selection_mask.invertBits(); return *this; }
	/**
	Desaturate every selected pixel in the selection bitmask큦 associated image by the specified percentage.

	@param desaturation_percentage The percentage that selected pixels will be desaturated. 0% - 100%
	@return A reference to the Selection itself.*/
	inline Selection& desaturate(float desaturation_percentage) { m_selection_mask.desaturate(desaturation_percentage); return *this; }
#pragma endregion
#pragma region Selection
public:
	/**
	Gets Selection BitMask.

	@return A pointer to Selection큦 Selection BitMask.*/
	BitMask* getSelectionBitMask() { return &m_selection_mask; }
	/**
	Gets an Image that its data is the selected pixels of the selection bitmask큦 associated Image.

	@return An Image that its data is the selected pixels of the selection bitmask큦 associated Image.*/
	Image getImageFromSelection() const;
#pragma endregion
};

