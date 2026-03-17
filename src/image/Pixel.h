#pragma once
#include <math.h>
/**
Stores,Manipulates and Abstracts a image큦 RGBA element.*/
class Pixel
{
private:
	/**
	Pointer to pixel큦 first element in a image data.*/
	unsigned char* data_start_address;
public:
	/**
	RGBA element of Pixel.*/
	unsigned char &red, &green, &blue, &alpha;
#pragma region Constructors/Destructors
public:
	/**
	A Constructor of Pixel.
	
	@param first_value_address A pointer to pixel큦 first element in a image data.*/
	Pixel(unsigned char* first_value_address);
	~Pixel();
#pragma endregion
#pragma region Operations
public:
	/**
	Sets Pixel큦 RGB.
	
	@param r Pixel큦 Red value. 0 - 255
	@param g Pixel큦 Green value. 0 - 255
	@param b Pixel큦 Blue value. 0 - 255
	@return A reference to the Pixel itself.*/
	inline Pixel& setRGB(unsigned char r, unsigned char g, unsigned char b) { red = r; green = g; blue = b; return *this; };
	/**
	Sets Pixel큦 RGBA.

	@param r Pixel큦 Red value. 0 - 255
	@param g Pixel큦 Green value. 0 - 255
	@param b Pixel큦 Blue value. 0 - 255
	@param a Pixel큦 Alpha value. 0 - 255
	@return A reference to the Pixel itself.*/
	inline Pixel& setRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { red = r; green = g; blue = b; alpha = a; return *this; };
	/**
	Mixes (paints) Pixel큦 color with color specified in parameters.
	
	@param r Mixing color큦 Red value. 0 - 255
	@param g Mixing color큦 Green value. 0 - 255
	@param b Mixing color큦 Blue value. 0 - 255
	@param a Mixing color큦 Alpha value. 0 - 255*/
	inline void mix(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		float remapped_a = (float)a / 255;
		float remapped_alpha = (float)alpha / 255;
		red =   r*remapped_a +   red*remapped_alpha*(float)(1 - remapped_a);
		green = g*remapped_a + green*remapped_alpha*(float)(1 - remapped_a);
		blue =  b*remapped_a +  blue*remapped_alpha*(float)(1 - remapped_a);
		alpha = (a + remapped_alpha*(float)(1 - remapped_a))*255;
	}
	/**
	Negates (Inverts) Pixel큦 values.
	*/
	inline void negate() {
		red = 255 - red;
		green = 255 - green;
		blue = 255 - blue;
	}
#pragma endregion
#pragma region RGB
public:
	/**
	Gets Sum of Pixel큦 RGB values.
	
	@return Sum of Pixel큦 Red,Green and Blue values.*/
	inline unsigned int getRGBSum() const { return (red + green + blue); }
	/**
	Gets a reference to Pixel큦 Largest RGB element.
	
	@return A reference to Pixel큦 Largest RGB element.*/
	inline unsigned char& getMaxRGB() { return red > green ? (red > blue ? red : blue) : (green > blue ? green : blue); }
	/**
	Gets a reference to Pixel큦 Smallest RGB element.

	@return A reference to Pixel큦 Smallest RGB element.*/
	inline unsigned char& getMinRGB() { return red < green ? (red < blue ? red : blue) : (green < blue ? green : blue); }
	/**
	Gets the percentage Pixel큦 Red value represents of Pixel큦 RGB.
	
	@return The percentage Pixel큦 Red value represents of Pixel큦 RGB.*/
	inline float getRGBRedPercentage()    const { return getRGBSum()==0?100:(100 * red) / (getRGBSum()); }
	/**
	Gets the percentage Pixel큦 Green value represents of Pixel큦 RGB.

	@return The percentage Pixel큦 Green value represents of Pixel큦 RGB.*/
	inline float getRGBGreenPercentage()  const { return getRGBSum()==0?100:(100 * green) / (getRGBSum()); }
	/**
	Gets the percentage Pixel큦 Blue value represents of Pixel큦 RGB.

	@return The percentage Pixel큦 Blue value represents of Pixel큦 RGB.*/
	inline float getRGBBluePercentage()   const { return getRGBSum()==0?100:(100 * blue) / (getRGBSum()); }
#pragma endregion
#pragma region RGBA
public:
	/**
	Gets Sum of Pixel큦 RGBA values.

	@return Sum of Pixel큦 Red,Green,Blue and Alpha values.*/
	inline unsigned int getRGBASum() const { return (red + green + blue + alpha); }
	/**
	Gets a reference to Pixel큦 Largest RGBA element.

	@return A reference to Pixel큦 Largest RGBA element.*/
	inline unsigned char& getMaxRGBA() { red > green ? (red > blue ? (red > alpha ? red : alpha) : (blue > alpha ? blue : alpha)) : 
		                                         (green > blue ? (green > alpha ? green : alpha) : (green > alpha ? green : alpha)); }
	/**
	Gets a reference to Pixel큦 Smallest RGBA element.

	@return A reference to Pixel큦 Smallest RGBA element.*/
	inline unsigned char& getMinRGBA() {
		red < green ? (red < blue ? (red < alpha ? red : alpha) : (blue < alpha ? blue : alpha)) :
			(green < blue ? (green < alpha ? green : alpha) : (green < alpha ? green : alpha));
	}
	/**
	Gets the percentage Pixel큦 Red value represents of Pixel큦 RGBA.

	@return The percentage Pixel큦 Red value represents of Pixel큦 RGBA.*/
	inline float getRGBARedPercentage()   const { return (100 * red) / getRGBASum(); }
	/**
	Gets the percentage Pixel큦 Green value represents of Pixel큦 RGBA.

	@return The percentage Pixel큦 Green value represents of Pixel큦 RGBA.*/
	inline float getRGBAGreenPercentage() const { return (100 * green) / getRGBASum(); }
	/**
	Gets the percentage Pixel큦 Blue value represents of Pixel큦 RGBA.

	@return The percentage Pixel큦 Blue value represents of Pixel큦 RGBA.*/
	inline float getRGBABluePercentage()  const{ return  (100 * blue) / getRGBASum(); }
	/**
	Gets the percentage Pixel큦 Alpha value represents of Pixel큦 RGBA.

	@return The percentage Pixel큦 Alpha value represents of Pixel큦 RGBA.*/
	inline float getRGBAAlphaPercentage() const { return (100 * alpha) / getRGBASum(); }
#pragma endregion
#pragma region Static
public:
	/**
	Gets Similiarity of the values percentages of RGB of two Pixels.
	
	@return Similiarity of the values percentages of RGB of two Pixels.*/
	static float getLinearSimiliarityRGB(const Pixel* a, const Pixel* b);
	/**
	Gets Linear Difference of two Pixel큦 RGBAs.
	
	@return Linear Difference of two Pixel큦 RGBAs.*/
	static unsigned int getDifferenceRGBA(const Pixel* a, const Pixel* b) { return abs(a->red - b->red) + abs(a->green - b->green) + abs(a->blue - b->blue) + abs(a->alpha - b->alpha); }
	/**
	Gets Linear Difference of two Pixel큦 RGBs.

	@return Linear Difference of two Pixel큦 RGBs.*/
	static unsigned int getDifferenceRGB(const Pixel* a, const Pixel* b) { return abs(a->red - b->red) + abs(a->green - b->green) + abs( a->blue - b->blue); } 
	/**
	Swaps data of *p1 and *p2.
	
	@param p1 A pointer to a Pixel to swap data with *p2.
	@param p2 A pointer to a Pixel to swap data with *p1.*/
	inline static void swap(Pixel* p1, Pixel* p2)
	{
		const unsigned char r = p1->red;
		const unsigned char g = p1->green;
		const unsigned char b = p1->blue;
		const unsigned char a = p1->alpha;
		
		p1->red =   p2->red;
		p1->green = p2->green;
		p1->blue =  p2->blue;
		p1->alpha = p2->alpha;

		p2->red	 = r;
		p2->green = g;
		p2->blue = b;
		p2->alpha = a;
	}
#pragma endregion
	//desaturate()
	//getHue(),getHSV(),getHSL(),getColorID() (getColorName()?) 
	//inline void tint(unsigned char r,unsigned char g,unsigned char b);
};

