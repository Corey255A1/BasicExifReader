# WUNDERVISION 2020
# CMakeList.txt : CMake project for CppProj, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (BasicEXIFReader "BasicEXIFReaderMain.cpp" "BasicEXIFReaderMain.h" 
	"APP0Marker.cpp" "APP0Marker.h" 
	"BitUtils.h" "BitUtils.cpp" 
	"IFDEntry.h" "IFDEntry.cpp"
	"EXIF.h" "EXIF.cpp"
	"JPEGEXIFFile.h" "JPEGEXIFFile.cpp"
	)

# TODO: Add tests and install targets if needed.
