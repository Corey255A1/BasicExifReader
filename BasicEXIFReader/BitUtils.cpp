//WunderVision 2020
//For doing byte swapping and things
#include "BitUtils.h"
namespace BitUtils {

	unsigned short Swap(unsigned short val) {
		return (val << 8) | (val >> 8);
	}
	unsigned int Swap(unsigned int val) {
		return (static_cast<unsigned int>(Swap(static_cast<unsigned short>(val&0xFFFF))) << 16) |
			(static_cast<unsigned int>(Swap(static_cast<unsigned short>(val >> 16))) << 16);
	}
	void GetValue(short& val, const char* bytes, int& offset, bool swap) {
		unsigned short tval = 0;
		GetValue(tval, bytes, offset, swap);
		val = static_cast<short>(tval);
	}
	void GetValue(unsigned short& val, const char* bytes, int& offset, bool swap)
	{
		if (swap) {
			val = (static_cast<unsigned short>(bytes[offset + 1]) & 0xFF) | ((static_cast<unsigned short>(bytes[offset]) & 0xFF) << 8);
		}
		else {
			val = (static_cast<unsigned short>(bytes[offset])&0xFF) | ((static_cast<unsigned short>(bytes[offset + 1])&0xFF)<<8);
		}
		offset += 2;
	}
	void GetValue(int& val, const char* bytes, int& offset, bool swap) {
		unsigned int tval = 0;
		GetValue(tval, bytes, offset, swap);
		val = static_cast<int>(tval);
	}
	void GetValue(unsigned int& val, const char* bytes, int& offset, bool swap)
	{
		if (swap) {
			val = (static_cast<unsigned int>(bytes[offset + 3]) & 0xFF) | 
				((static_cast<unsigned int>(bytes[offset + 2]) & 0xFF) <<8) |
				((static_cast<unsigned int>(bytes[offset + 1]) & 0xFF) <<16) |
				((static_cast<unsigned int>(bytes[offset]) & 0xFF) <<24);
		}
		else {
			val = (static_cast<unsigned int>(bytes[offset]) & 0xFF) |
				((static_cast<unsigned int>(bytes[offset + 1]) & 0xFF) << 8) |
				((static_cast<unsigned int>(bytes[offset + 2]) & 0xFF) << 16) |
				((static_cast<unsigned int>(bytes[offset + 3]) & 0xFF) << 24);
		}
		offset += 4;
	}
	void GetValue(std::string& val, const char* bytes, int& offset, int length)
	{
		val.assign(bytes+offset,length);
		offset += length;

	}

}