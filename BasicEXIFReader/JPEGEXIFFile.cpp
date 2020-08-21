//WunderVision 2020

#include "JPEGEXIFFile.h"
#include "BitUtils.h"
#include <fstream>
#include <iostream>
namespace EXIF {

	static const char UPPER = 0xff;
	static const char LOWER = 0xd8;
	bool JPEGEXIFFile::IsJPEGExif(const char* bytes, int offset)
	{
		return bytes[offset] == UPPER && bytes[offset + 1] == LOWER;
	}

	EXIFSections JPEGEXIFFile::GetSectionType(const char* bytes, int offset)
	{
		if (APP0Marker::IsType(bytes, offset)) return EXIFSections::APP0;
		if (EXIF::IsType(bytes, offset)) return EXIFSections::APP1;

		return EXIFSections::Undefined;
	}

	std::unique_ptr<JPEGEXIFFile> JPEGEXIFFile::Parse(const char* data)
	{
		return std::make_unique<JPEGEXIFFile>(data, 0);
	}

	std::unique_ptr<JPEGEXIFFile> JPEGEXIFFile::Parse(const std::string& filepath)
	{
		//start at end of file to get file size
		std::ifstream file(filepath, std::ios::binary | std::ios::in | std::ios::ate);
		if (file.is_open()) {
			int size = file.tellg();
			file.seekg(0, std::ios::beg);
			char* imgFile = new char[size];
			file.read(imgFile, size);
			file.close();

			auto exifData = std::make_unique<JPEGEXIFFile>(imgFile, 0);
			delete[] imgFile;
			
			return exifData;
		}
		else {
			std::cout << "COULD NOT OPEN FILE: " << filepath << std::endl;
		}

		return nullptr;
	}

	JPEGEXIFFile::JPEGEXIFFile(const char* bytes, int offset) 
	{
		BitUtils::GetValue(_soi, bytes, offset);
		bool parse = true;
		while (parse)
		{
			switch (GetSectionType(bytes, offset))
			{
			case EXIFSections::APP0: _app0 = APP0Marker::Parse(bytes, offset); break;
			case EXIFSections::APP1: _exif = EXIF::Parse(bytes, offset); parse = false;  break;
			default: parse = false; break;
			}
		}
	}

	std::string JPEGEXIFFile::GetTag(IFDTag tag)
	{
		return _exif->GetTag(tag);
	}


	void JPEGEXIFFile::DumpAllTags() {
		_exif->DumpAllTags();
	}
}