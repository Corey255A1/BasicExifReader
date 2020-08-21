//WunderVision 2020
//The Emscripting Binding code to allow for the creation
//of the class in javascript client code
#include <emscripten/bind.h>
#include "JPEGEXIFFile.h"
#include <iostream>
#include <string>
using namespace emscripten;

class JEXIF {
private:
	std::unique_ptr<EXIF::JPEGEXIFFile> exif;
public:

	JEXIF(std::string path) {
		exif = EXIF::JPEGEXIFFile::Parse(path);
	}

	std::string GetTag(int tagEnum) {
		return exif->GetTag(static_cast<EXIF::IFDTag>(tagEnum));
	}
};


// Binding code
EMSCRIPTEN_BINDINGS(jexif) {
	class_<JEXIF>("EXIF")
		.constructor<std::string>()
		.function("getTag", &JEXIF::GetTag);
}