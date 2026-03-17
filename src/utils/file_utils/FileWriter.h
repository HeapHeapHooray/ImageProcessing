#pragma once
#include <cstdio>

class Bitmap;
/**
File Writing and Creation.*/
class FileWriter
{
	FILE* m_file_handler;
	char* m_file_path;

#pragma region Constructors/Destructors
public:
	FileWriter(const char* file_path);
	~FileWriter();
#pragma endregion
#pragma region File Writing
public:
	/**
	Appends data to FileWriter´s file.
	
	@param data The data to be Written/Appended.
	@param data_size The size of the data param.
	@return True if successful or false otherwise.*/
	bool writeData(const unsigned char* data,size_t data_size);
	/**
	Clears the data in the FileWriter´s file.
	
	@return True if successful or false otherwise.*/
	bool clearData();
#pragma endregion
#pragma region File Creation
public:
	/**
	Creates a Bitmap File.
	
	@param file_path The Path/Location where the file will be created.
	@param bitmap The Bitmap that will be written to a file.
	@return True if successful or false otherwise.*/
	static bool FileWriter::createBitmapFile(const char* file_path,const Bitmap* bitmap);
	/**
	Creates an empty file.
	
	@param file_path The Path/Location where the file will be created.
	@return True if successful or false otherwise.*/
	static bool createFile(const char* file_path);
#pragma endregion
};

