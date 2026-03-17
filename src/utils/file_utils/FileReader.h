#pragma once
#include <cstdio>
#include <string>

#pragma region Forward Declaring
class Bitmap;
struct BitmapFileHeader;
struct BitmapInfoHeader;
#pragma endregion

/**
Reads data from files.*/
class FileReader {
private:
	FILE* m_file_handler;
	std::string line_data;
	long file_size;

#pragma region File Reading
public:
	/**
	Reads from a Text File.

	@param file_path The Path/Location of the file.
	@return The data of the file.
	*/
	static const char* readFromTextFile(const char* file_path);


#pragma region Bitmap
public:

/**
	Reads from a Bitmap File.

	@param file_path The Path/Location of the file.
	@return A Bitmap.
	*/
static Bitmap* readFromBitmapFile(const char* file_path);


#pragma region Headers Creation
private:
/**
Creates a bitmap file header.

@param data_buffer The buffer where the header큦 data is.
@return a BitmapFileHeader.
*/
static BitmapFileHeader create_file_header_from_data_buffer(const unsigned char* data_buffer);
/**
Creates a bitmap info header.

@param data_buffer The buffer where the header큦 data is.
@param buffer_size The size of the header큦 data.
@return a BitmapInfoHeader.
*/
static BitmapInfoHeader create_info_header_from_data_buffer(const unsigned char* data_buffer, size_t buffer_size);
//--END OF HEADERS CREATION--//
#pragma endregion
//--END OF BITMAP--//
#pragma endregion
//--END OF FILE READING--//
#pragma endregion
#pragma region Constructors/Destructors
public:

	FileReader(const char* file_path);
	~FileReader();
#pragma endregion
#pragma region Sequential Reading
public:

	/**
	Tries to read the next line in the file, if in end of file it returns false.

	@return If in end of file it returns false, if not it return true and writes the data of the next file큦 line in
	line_data.
	*/
	bool nextLine();


	/**
	Returns the data that has been read from the method nextLine().
	
	@return The line data stored in the FileReader by the function nextLine().*/
	inline const char* getLineData() const { return &line_data[0]; };


	/**
	Reads the next N bytes of the file and writes it to buffer and returns how many bytes could be read.

	@param num_of_bytes The number of bytes to be read.
	@param buffer The buffer where the data will written.
	@return The number of bytes that could be read.
	*/
	inline size_t readNextBytes(size_t num_of_bytes,unsigned char* buffer) const;
#pragma endregion
#pragma region Utils
public:
	/**
	Returns the size of the file opened in the FileReader.

	@return The size of the file.
	*/
	long getFileSize() const { return file_size; }
	

	/**
	Returns the size of a file.

	@param file_path The Path/Location of the file.
	@return The size of the file.
	*/
	inline static long getSizeOfFile(const char* file_path);
#pragma endregion
};

