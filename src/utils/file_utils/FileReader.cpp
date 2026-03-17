#include "FileReader.h"
#include "../data.h"
#include "../../image/Bitmap.h"
#include <sys/stat.h>

#pragma region Constructors/Destructors
FileReader::FileReader(const char* file_path)
{
	file_size = getSizeOfFile(file_path);
	fopen_s(&m_file_handler, file_path, "rb");
}
FileReader::~FileReader()
{
	fclose(m_file_handler);
}
#pragma endregion
#pragma region File Reading
const char* FileReader::readFromTextFile(const char* file_path)
{
	long file_size = getSizeOfFile(file_path);
	FILE* file_handler;
	fopen_s(&file_handler, file_path, "rb");
	char* dataBuffer = new char[file_size+1];
	memset(dataBuffer, 0, file_size + 1);
	fread_s(dataBuffer, sizeof(char)*file_size, sizeof(char), file_size, file_handler);
	return dataBuffer;
	/*
#ifdef WIN32 || WIN64
	int file_handler;
	long file_size;
	_sopen_s(&file_handler, file_path, _O_BINARY | _O_RDONLY,_SH_DENYRW,_S_IREAD);
	file_size = _filelength(file_handler);
	char* dataBuffer = new char[file_size+1];
	memset(dataBuffer, 0,file_size);
	_read(file_handler, dataBuffer, file_size);
	_close(file_handler);
	dataBuffer[file_size] = '\0';
	return dataBuffer;
#endif
*/
}

#pragma region Bitmap
Bitmap* FileReader::readFromBitmapFile(const char* file_path)  
{
	FileReader reader(file_path);
	unsigned char* data_buffer = new unsigned char[14];
	reader.readNextBytes(14, data_buffer);

	BitmapFileHeader file_header = create_file_header_from_data_buffer(data_buffer);
	unsigned int info_header_size = get_dword_from_little_endian(&data_buffer[10])-14;
	delete[] data_buffer;

	data_buffer = new unsigned char[info_header_size]; 
	reader.readNextBytes(info_header_size, data_buffer);
	BitmapInfoHeader info_header = create_info_header_from_data_buffer(data_buffer, info_header_size);
	delete[] data_buffer;
	if (!info_header.type) return new Bitmap(file_header, info_header, NULL);

	unsigned int bitmap_data_size = abs(info_header.bitmap_height) *  
   (((info_header.bitmap_width*info_header.bitsPerPixel + 31)&~31) >> 3);
	unsigned char* bitmap_data = new unsigned char[bitmap_data_size];
    reader.readNextBytes(bitmap_data_size, bitmap_data);

	return new Bitmap(file_header, info_header, bitmap_data);
}
BitmapFileHeader FileReader::create_file_header_from_data_buffer(const unsigned char* data_buffer) {
	BitmapFileHeader file_header;
	file_header.format = (BitmapFormats::Format)get_word_from_little_endian(&data_buffer[0]);
	file_header.size = get_dword_from_little_endian(&data_buffer[2]);
	file_header.reserved = get_dword_from_little_endian(&data_buffer[6]);
	return file_header;
}
BitmapInfoHeader FileReader::create_info_header_from_data_buffer(const unsigned char* data_buffer, size_t buffer_size) {
	BitmapInfoHeader info_header;
	switch (buffer_size) {
	case 40: info_header.type = BitmapInfoHeaderTypes::BITMAPINFOHEADER; break;
	case 12: info_header.type = BitmapInfoHeaderTypes::BITMAPCOREHEADER; break;
	case 52: info_header.type = BitmapInfoHeaderTypes::BITMAPV2INFOHEADER; break;
	case 124: info_header.type = BitmapInfoHeaderTypes::BITMAPV5HEADER; break;
	default: info_header.type = BitmapInfoHeaderTypes::BITMAPUNKNOWNTYPE; break;
	}
	if (!info_header.type) return info_header; //Returns if Header Type is Unknown
	info_header.header_size = get_dword_from_little_endian(&data_buffer[0]); //Also equals to buffer_size !
	if (info_header.header_size < 40) { //BITMAPCOREHEADER and OS22XBITMAPHEADER
		info_header.bitmap_width = get_word_from_little_endian(&data_buffer[4]);
		info_header.bitmap_height = get_word_from_little_endian(&data_buffer[6]);
		info_header.number_of_color_planes = get_word_from_little_endian(&data_buffer[8]);
		info_header.bitsPerPixel = get_word_from_little_endian(&data_buffer[10]);
		return info_header;
	}
	info_header.bitmap_width = get_dword_from_little_endian(&data_buffer[4]);
	info_header.bitmap_height = get_dword_from_little_endian(&data_buffer[8]);
	info_header.number_of_color_planes = get_word_from_little_endian(&data_buffer[12]);
	info_header.bitsPerPixel = get_word_from_little_endian(&data_buffer[14]);
	info_header.compressionMethod = (BitmapImageCompressionMethods::CompressionMethod)
	get_dword_from_little_endian(&data_buffer[16]);
	info_header.rawBitmapDataSize = get_dword_from_little_endian(&data_buffer[20]);
	info_header.horizontal_resolution = get_dword_from_little_endian(&data_buffer[24]);
	info_header.vertical_resolution = get_dword_from_little_endian(&data_buffer[28]);
	info_header.numberOfColors = get_dword_from_little_endian(&data_buffer[32]);
	info_header.importantColors = get_dword_from_little_endian(&data_buffer[36]);
	return info_header;
}
#pragma endregion
#pragma endregion
#pragma region Sequential Reading
bool FileReader::nextLine()
{
	if (feof(m_file_handler)) return false;
	line_data = "";
	char c;
	while (!feof(m_file_handler) && (c = fgetc(m_file_handler)) != '\0') line_data += c;
	return true;
}
inline size_t FileReader::readNextBytes(size_t num_of_bytes,unsigned char* buffer) const 
{
	memset(buffer, 0, num_of_bytes);
	return fread_s(buffer, sizeof(char)*num_of_bytes, sizeof(char), num_of_bytes, m_file_handler);
}
#pragma endregion
#pragma region Utils
inline long FileReader::getSizeOfFile(const char* file_path) 
{
  struct stat stat_buffer;
  return !stat(file_path, &stat_buffer) ? stat_buffer.st_size : -1;
}
#pragma endregion

