#include <vector>
#include <memory>
#include <string>
namespace EXIF {
	enum class IFDType {
		BYTE = 1, // An 8-bit unsigned integer
		ASCII = 2, // An 8-bit byte containing one 7-bit ASCII code. The final byte is terminated with NULL
		SHORT = 3, // A 16-bit (2-byte) unsigned integer
		LONG = 4, // A 32-bit (4-byte) unsigned integer
		RATIONAL = 5, // Two LONGs. The first LONG is the numerator and the second LONG expresses the denominator
		UNDEFINED = 7, // An 8-bit byte that can take any value depending on the field definition
		SLONG = 9, // A 32-bit (4-byte) signed integer (2's complement notation)
		SRATIONAL = 10 // Two SLONGs. The first SLONG is the numerator and the second SLONG is the denominator
	};


	class IFDEntry {
	private:
		unsigned short _tag;
		unsigned short _type;
		unsigned int _count;
		unsigned int _value_or_offset;
		std::vector<char> _bytes;
		std::string _valstr;

	public:
		unsigned short Tag() { return _tag; }
		unsigned short Type() { return _type; }
		unsigned int Count() { return _count; }
		unsigned int ValueOrOffset() { return _value_or_offset; }
		const std::vector<char>& Bytes() { return _bytes; }

		std::string Value();

		IFDEntry(const char* bytes, int offset, int tiff_offset, bool tiff_is_big_endian);

		static std::unique_ptr<IFDEntry> Parse(const char* bytes, int& offset, int tiff_offset, bool tiff_is_big_endian) {
			auto ifd = std::make_unique<IFDEntry>(bytes, offset, tiff_offset, tiff_is_big_endian);
			offset += 12;
			return ifd;
		}

	};


}