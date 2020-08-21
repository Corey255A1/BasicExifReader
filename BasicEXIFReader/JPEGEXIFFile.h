#include "APP0Marker.h"
#include "EXIF.h"
namespace EXIF {
	enum class EXIFSections
	{
		Undefined,
		APP0,
		APP0Ex,
		APP1
	};

	class JPEGEXIFFile {
	private:
		unsigned short _soi;
		std::unique_ptr<APP0Marker> _app0;
		std::unique_ptr<EXIF> _exif;

		static EXIFSections GetSectionType(const char* bytes, int offset);

	public:
		JPEGEXIFFile(const char* bytes, int offset);

		std::string GetTag(IFDTag tag);
		void DumpAllTags();

		static bool IsJPEGExif(const char* bytes, int offset);


		static std::unique_ptr<JPEGEXIFFile> Parse(const std::string& filepath);
		static std::unique_ptr<JPEGEXIFFile> Parse(const char* bytes);
	};


}