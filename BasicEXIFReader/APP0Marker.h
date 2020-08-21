#include <string>
#include <memory>
#include <vector>
namespace EXIF {
	
	class APP0Marker {
	private:
		unsigned short _length;
		std::string _identifier;
		unsigned short _jfif_version;
		unsigned char _density_units;
		unsigned short _x_density;
		unsigned short _y_density;
		unsigned char _x_thumbnail;
		unsigned char _y_thumbnail;
		std::vector<char> _thumbnail_data;		

	public:
		APP0Marker(const char* bytes, int offset);
		unsigned short Length() { return _length; }
		const std::string& Identifier() { return _identifier; }

		static const char UPPER = 0xff;
		static const char LOWER = 0xe0;		
		static bool IsType(const char* bytes, int offset) { 
			return bytes[offset] == UPPER && bytes[offset + 1] == LOWER;
		}

		static std::unique_ptr<APP0Marker> Parse(const char* bytes, int& offset) {
			auto app0 = std::make_unique<APP0Marker>(bytes, offset);
			offset += app0->_length;
			return app0;
		}

	};

}