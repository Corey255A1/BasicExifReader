//WunderVision 2020
#include "EXIF.h"
#include "BitUtils.h"
#include <iostream>

namespace EXIF {
	EXIF::EXIF(const char* bytes, int offset)
	{
		offset += 2; //Skip the App1 Marker;

		BitUtils::GetValue(_length, bytes, offset, true);
		BitUtils::GetValue(_identifier, bytes, offset, 6);
		_tiff_header_start = offset;
		BitUtils::GetValue(_tiff_endian, bytes, offset, true);
		_tiff_is_big_endian = (_tiff_endian == 0x4D4D);
		BitUtils::GetValue(_tiff_id, bytes, offset, _tiff_is_big_endian);
		BitUtils::GetValue(_ifd0_offset, bytes, offset, _tiff_is_big_endian);

		int byte_count = SetIFDTags(bytes, offset, _tiff_header_start, _tiff_is_big_endian);
		offset += byte_count;
		if (_tags.find(IFDTag::ExifIFD) != _tags.end()) {
			int section_offset = _tiff_header_start + static_cast<int>(_tags[IFDTag::ExifIFD]->ValueOrOffset());
			SetIFDTags(bytes, section_offset, _tiff_header_start, _tiff_is_big_endian);
		}


	}


	int EXIF::SetIFDTags(const char* bytes, int offset, int sectionstart, bool swap) 
	{
		unsigned short tag_count = 0;
		int start = offset;
		BitUtils::GetValue(tag_count, bytes, offset, swap);
		for (int dIdx = 0; dIdx < tag_count; ++dIdx) {
			std::shared_ptr<IFDEntry> ifd = IFDEntry::Parse(bytes, offset, sectionstart, swap);
			//C# Would check that the enum is valid ..
			//std::cout << "Enum:" << ifd->Tag() << " - Value:" << ifd->Value() << std::endl;
			_tags.insert(std::make_pair(static_cast<IFDTag>(ifd->Tag()),ifd));
		}

		return offset - start;
	}

	void EXIF::DumpAllTags() {

		for (auto itr = _tags.begin(); itr != _tags.end(); ++itr) {
			std::cout << "Enum: " << itr->second->Tag() << " - Value:" << itr->second->Value() << std::endl;
		}

	}

	std::string EXIF::GetTag(IFDTag tag) {

		if (_tags.find(tag) != _tags.end()) {
			//std::cout << "Found Tag " << (int)tag << std::endl;
			return _tags[tag]->Value();
		}
		else {
			std::cout << "Not Found " << (int)tag << std::endl;
			return std::string("");
		}

	}
}