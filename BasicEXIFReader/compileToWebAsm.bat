call emcc EXIFParser.cxx EXIF.cpp APP0Marker.cpp BitUtils.cpp IFDEntry.cpp JPEGEXIFFile.cpp -o jexif.js --bind
copy jexif.js .\webtest\public\jexif.js
copy jexif.wasm .\webtest\public\jexif.wasm
