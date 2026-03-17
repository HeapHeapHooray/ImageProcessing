#pragma once
#include <string>
inline std::string charToBinary(unsigned char c)
{
	std::string result;
	for (unsigned char by = 0; by < 2; by++, result += " ")
		for (unsigned char b = 0; b < 4; b++)
		{
			result += (c % 2 ? "1" : "0");
			c /= 2;
		}
	return result;
}
inline std::string intToBinary(unsigned int i)
{
	std::string result;
	for (unsigned char by = 0; by < 8; by++, result += " ")
		for (unsigned char b = 0; b < 4; b++)
		{
			result += i % 2 ? "1" : "0";
			i /= 2;
		}
	return result;
}
inline std::string shortToBinary(unsigned short s)
{
	std::string result;
	for (unsigned char by = 0; by < 4; by++, result += " ")
		for (unsigned char b = 0; b < 4; b++)
		{
			result += (s % 2 ? "1" : "0");
			s /= 2;
		}
	return result;
}


inline std::string reverse(std::string to_reverse)
{
	std::string result;
	for (const char c : to_reverse) result = c + result;
	return result;
}
