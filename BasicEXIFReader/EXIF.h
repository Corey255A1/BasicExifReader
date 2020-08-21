//WunderVision 2020
//Conainer for all the pieces of the EXIF Portion of the Header
#include "IFDEntry.h"
#include "IFDTags.h"

#include <string>
#include <map>

namespace EXIF {
	class EXIF {
	private:
		bool _tiff_is_big_endian;
		unsigned short _length;
		std::string _identifier;
		int _tiff_header_start;
		unsigned short _tiff_endian;
		unsigned short _tiff_id;
		unsigned int _ifd0_offset;
		std::map<IFDTag, std::shared_ptr<IFDEntry>> _tags;

		int SetIFDTags(const char* bytes, int offset, int sectionstart, bool swap);




	public:
		bool TIFFIsBigEndian() { return _tiff_is_big_endian; }
		unsigned short Length() { return _length; }
		const std::string& Identifier() { return _identifier; }

		std::string GetTag(IFDTag tag);
		void DumpAllTags();

		EXIF(const char* bytes, int offset);

		static std::unique_ptr<EXIF> Parse(const char* bytes, int& offset)
		{
			auto exif = std::make_unique<EXIF>(bytes, offset);
			offset = offset + exif->_length + 2;

			return exif;
		}
		static const char UPPER = 0xff;
		static const char LOWER = 0xe1;
		static bool IsType(const char* bytes, int offset) {
			return bytes[offset] == UPPER && bytes[offset + 1] == LOWER;
		}
	};
}