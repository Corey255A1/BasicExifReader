//WunderVision 2020
//Main Entry for the test usage of the EXIF code
#include "BasicEXIFReaderMain.h"
#include <iostream>
#include <memory>
#include "JPEGEXIFFile.h"
#include <string>
int main(int argc, char* argv[])
{
	std::cout << "Hello From WunderVision" << std::endl;

	if (argc > 1) {
		auto jpegFile = EXIF::JPEGEXIFFile::Parse(std::string(argv[1]));
		std::cout << "--A Sample of Tags--" << std::endl;
		std::cout << "Description: " << jpegFile->GetTag(EXIF::IFDTag::ImageDescription) << std::endl;
		std::cout << "Camera Model: " << jpegFile->GetTag(EXIF::IFDTag::Model) << std::endl;
		std::cout << "Date/Time: " << jpegFile->GetTag(EXIF::IFDTag::DateTime) << std::endl;
		std::cout << "Image Orienation: " << jpegFile->GetTag(EXIF::IFDTag::Orientation) << std::endl;
		
		std::cout << std::endl << "--Dumping All Tags--" << std::endl;
		jpegFile->DumpAllTags();

	}
	else {
		std::cout << "Please add file path" << std::endl;
	}

	std::string line;
	std::getline(std::cin, line);

	return 0;
}
