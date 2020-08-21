//WunderVision 2020
//For doing byte swapping and things
#include <string>
namespace BitUtils {
	unsigned short Swap(unsigned short val);
	unsigned int Swap(unsigned int val);
	void GetValue(unsigned short& val, const char* bytes, int& offset, bool swap = false);
	void GetValue(unsigned int& val, const char* bytes, int& offset, bool swap = false);
	void GetValue(short& val, const char* bytes, int& offset, bool swap = false);
	void GetValue(int& val, const char* bytes, int& offset, bool swap = false);
	void GetValue(std::string& val, const char* bytes, int& offset, int length);

}