#include "FileWriter.h"
#include "file_utils_commons.h"
#include "../../image/Bitmap.h"

#pragma region Constructors/Destructors
FileWriter::FileWriter(const char* file_path)
{
	fopen_s(&m_file_handler, file_path, "ab");
	size_t m_file_path_size = strlen(file_path)+1;
	m_file_path = new char[m_file_path_size];
	strcpy_s(m_file_path,m_file_path_size, file_path);
}
FileWriter::~FileWriter()
{
	fclose(m_file_handler);
	delete[] m_file_path;
}
#pragma endregion
#pragma region File Writing
bool FileWriter::writeData(const unsigned char* data,size_t data_size)
{
	fwrite(data, sizeof(char), data_size,m_file_handler);
	fflush(m_file_handler);
	return true;
}
bool FileWriter::clearData()
{
	freopen_s(&m_file_handler,m_file_path, "w",m_file_handler);
	fflush(m_file_handler);
	freopen_s(&m_file_handler,m_file_path, "ab",m_file_handler);
	return true;
}
#pragma endregion
#pragma region File Creation
bool FileWriter::createFile(const char* file_path)
{
	if (file_exists(file_path)) return true;
	FILE* file_handler;
	fopen_s(&file_handler, file_path, "w");
	if (file_handler != NULL) {
	fflush(file_handler);
	fclose(file_handler);
	return true;
}
	return false;
}
bool FileWriter::createBitmapFile(const char* file_path, const Bitmap* bitmap)
{
	if (!bitmap->getInfoHeader()->type) return false;

	const BitmapFileHeader*  file_header = bitmap->getFileHeader();
	const BitmapInfoHeader*  info_header = bitmap->getInfoHeader();
	unsigned int headers_size = info_header->header_size + 14;
	unsigned char* headers_data = new unsigned char[headers_size];
	memset(headers_data, 0, headers_size);

	//File Header
	write_word_to_address('BM', &headers_data[0]);
	write_dword_to_address(swap_dword_endian(file_header->size), &headers_data[2]);
	write_dword_to_address(swap_dword_endian(file_header->reserved), &headers_data[6]);
	write_dword_to_address(swap_dword_endian(info_header->header_size + 14), &headers_data[10]);

	//Info Header
	write_dword_to_address(swap_dword_endian(info_header->header_size), &headers_data[14]);
	if (info_header->header_size < 40) { //BITMAPCOREHEADER AND OS22XBITMAPHEADER
		write_dword_to_address(swap_word_endian((short)info_header->bitmap_width), &headers_data[18]);
		write_dword_to_address(swap_word_endian((short)info_header->bitmap_height), &headers_data[20]);
		write_word_to_address(swap_word_endian(info_header->number_of_color_planes), &headers_data[22]);
		write_word_to_address(swap_word_endian(info_header->bitsPerPixel), &headers_data[24]);
	}
	else {
		write_dword_to_address(swap_dword_endian(info_header->bitmap_width), &headers_data[18]);
		write_dword_to_address(swap_dword_endian(info_header->bitmap_height), &headers_data[22]);
		write_word_to_address(swap_word_endian(info_header->number_of_color_planes), &headers_data[26]);
		write_word_to_address(swap_word_endian(info_header->bitsPerPixel), &headers_data[28]);
		write_dword_to_address(swap_word_endian(0), &headers_data[30]);
		write_dword_to_address(swap_dword_endian(info_header->rawBitmapDataSize), &headers_data[34]);
		write_dword_to_address(swap_dword_endian(info_header->horizontal_resolution), &headers_data[38]);
		write_dword_to_address(swap_dword_endian(info_header->vertical_resolution), &headers_data[42]);
		write_dword_to_address(swap_dword_endian(info_header->numberOfColors), &headers_data[46]);
		write_dword_to_address(swap_dword_endian(info_header->importantColors), &headers_data[50]);
	}

	FileWriter writer(file_path);
	writer.clearData();
	writer.writeData(headers_data, headers_size);
	delete[] headers_data;

	unsigned int image_size = bitmap->getSizeOfImage();
	if (image_size) writer.writeData(bitmap->getImageData(), image_size);
	return true;
}
#pragma endregion

