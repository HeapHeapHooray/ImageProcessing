#pragma once
/**
Manages bits array that represents a image selection.*/
class BitMask
{
#pragma region Attributes
private:
	/**
	Address of first element of a Image큦 data.*/
	unsigned char*& initial_data_address;
	unsigned int m_width, m_height;
	unsigned int m_size;
	/**
	Size in bytes of a Image큦 pixel*/
	unsigned int stride;
	/**
	Bits array that represents a image selection.*/
	bool* bitmask;
#pragma endregion

#pragma region Constructors/Destructors
public:
	/**
	A BitMask Constructor.
	
	@param data_address Address of first element of a Image큦 data.
	@param width Image큦 width.
	@param height Image큦 height.
	@param index_stride Size in bytes of a Image큦 pixel.*/
	BitMask(unsigned char*& data_address,unsigned int width,unsigned int height,unsigned int index_stride);
	~BitMask();
#pragma endregion
#pragma region Operations
public:
	/**
	Changes every selected pixel in the bitmask큦 associated image for the specified params.
     
	@param r Red value of RGBA pixel. 0 - 255
	@param g Green value of RGBA pixel. 0 - 255
	@param b Blue value of RGBA pixel. 0 - 255
	@param a Alpha value of RGBA pixel. 0 - 255*/
    void fillColor(unsigned char r, unsigned char g, unsigned char b,unsigned char a);
	/**
	Paints every selected pixel in the bitmask큦 associated image with the params큦 specified color.
	
	@param r Red value of paint color. 0 - 255
	@param g Green value of paint color. 0 - 255
	@param b Blue value of paint color. 0 - 255
	@param alpha Alpha value of paint color. 0 - 255*/
	void paintColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	/**
	Desaturate every selected pixel in the bitmask큦 associated image by the specified percentage.
	
	@param desaturation_percentage The percentage that selected pixels will be desaturated. 0% - 100%*/
	void desaturate(float desaturation_percentage);
	/**
	Inverts the BitMask selection, everything selected will be unselected and everything unselected will be selected.
	
	@return A reference to the BitMask itself.*/
	BitMask& invertBits() {
		for (unsigned int i = 0; i < m_size; i++) bitmask[i] = !bitmask[i];
		return *this;
	}
#pragma endregion
#pragma region Image
public:
	/**
	Gets quantity of elements in bits array.
	NOTE: Quantity of elements in bits array = Quantity of Pixels in Image / stride .
	@return Quantity of elements in bits array.*/
	unsigned int getSize() const { return m_size; }
	/**
	Gets Width of the Image associated with BitMask.
	
	@return Width of the Image associated with BitMask.*/
	unsigned int getWidth() const { return m_width; }
	/**
	Gets Height of the Image associated with BitMask.
			
	@return Height of the Image associated with BitMask.*/
	unsigned int getHeight() const { return m_height; }
	/**
	Returns reference to bitmask큦 nth element.
	
	@param i Index of the desired element.
	@return Reference to the desired element.*/
	bool& operator[] (unsigned int i) { return bitmask[i]; }
	/**
	Returns bitmask큦 nth element.

	@param i Index of the desired element.
	@return Reference to the desired element.*/
	bool operator[] (unsigned int i) const { return bitmask[i]; }
	/**
	Gets Pointer to the first value of the nth pixel.
	
	@param index Index of desired pixel.
	@return Pointer to the First Value of the desired pixel.*/
	unsigned char* getPointerFromIndex(unsigned int index)  { return (&initial_data_address[0] + index*stride); }
	/**
	Gets Const pointer to the first value of the nth pixel.

	@param index Index of desired pixel.
	@return Const pointer to the First Value of the desired pixel.*/
	const unsigned char* getPointerFromIndex(unsigned int index) const { return (&initial_data_address[0] + index*stride); }
	/**
	Gets an Image Data that is the selected pixels of the bitmask큦 associated Image.
	
	@return An Image Data that is the selected pixels of the bitmask큦 associated Image.*/
	unsigned char* getImageData() const;
#pragma endregion
};

