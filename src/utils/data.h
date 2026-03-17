#pragma once
/**
Gets a dword from a byte array.

@param address The address of the first byte of the dword in the array.
@return a dword.*/
inline unsigned int get_dword_from_byte_array(const unsigned char* address) {
	return ((unsigned int)address[0]) << 24  | ((unsigned int)address[1]) << 16 |
		   ((unsigned int)address[2]) << 8   | (address[3]);
}
/**
Writes a dword to a data address.

@param dword The dword to be written.
@param address The address to where the dword will be written.*/
inline void write_dword_to_address(const unsigned int dword, unsigned char* address)
{
	address[3] = (dword & 0x000000ff);
	address[2] = (dword & 0x0000ff00) >> 8;
	address[1] = (dword & 0x00ff0000) >> 16;
	address[0] = (dword & 0xff000000) >> 24;
}
/**
Writes a word to a data address.

@param word The word to be written.
@param address The address to where the word will be written.*/
inline void write_word_to_address(const unsigned long dword, unsigned char* address)
{
	address[1] = (dword & 0x00ff);
	address[0] = (dword & 0xff00) >> 8;
}
inline unsigned short get_word_from_little_endian(const unsigned char* address) {
	return ((unsigned short)address[1]) << 8 | (address[0]);
}
inline unsigned int get_dword_from_little_endian(const unsigned char* address) {
	return ((unsigned int)address[3]) << 24  | ((unsigned int)address[2]) << 16 |
		   ((unsigned int)address[1]) << 8   | (address[0]);
}
inline unsigned int swap_dword_endian(const unsigned int dword) {
	return ((dword & 0x000000ff)<<24) | ((dword & 0x0000ff00) << 8) | ((dword & 0x00ff0000) >> 8) | ((dword & 0xff000000) >> 24);
}
inline unsigned int swap_word_endian(const unsigned short word) {
	return ((word & 0x00ff) << 8)| ((word & 0xff00) >> 8);
}