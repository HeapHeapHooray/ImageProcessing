#pragma once
/**
Stores and Manages a floating point array.*/
class Mask
{
private:
	unsigned int m_size;
	unsigned int m_width, m_height;
	/**
	Mask큦 data (floating point array).*/
	float* mask;
#pragma region Constructors/Destructors
public:
	Mask(unsigned int width,unsigned int height);
	Mask(unsigned int width, unsigned int height,float* data);
	~Mask();
#pragma endregion
#pragma region Mask
public:
	/**
	Gets Mask큦 width.
	
	@return Mask큦 width.*/
	inline unsigned int getWidth()  const { return m_width; }
	/**
	Gets Mask큦 height.
	
	@return Mask큦 height.*/
	inline unsigned int getHeight() const { return m_height; }
	/**
	Gets Mask큦 size (number of elements).
	
	@return Mask큦 size (number of elements).*/
	inline unsigned int getSize()   const { return m_size; }
	/**
	Finds Mask큦 largest element.
	
	@return Mask큦 largest element.*/
	float getLargestElement() const {
		float largest = mask[0];
		for (unsigned int i = 1; i < m_size; i++)
			if (mask[i] > largest) largest = mask[i];
		return largest;
	}
#pragma endregion
#pragma region Operations
public:
	/**
	Gets a reference to the Mask큦 nth element.
	
	@param index Index of the desired element.
	@return A reference to the desired element.*/
	float& operator[](const unsigned int index) { return mask[index]; }
	/**
	Gets Mask큦 nth element.

	@param index Index of the desired element.
	@return Mask큦 desired element.*/
	float operator[](const unsigned int index) const { return mask[index]; }
#pragma endregion
};

