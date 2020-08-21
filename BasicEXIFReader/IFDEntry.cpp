#include "IFDEntry.h"
#include "BitUtils.h"
#include <sstream>
namespace EXIF {
	IFDEntry::IFDEntry(const char* bytes, int offset, int tiff_offset, bool tiff_is_big_endian):
		_valstr("")
	{
		BitUtils::GetValue(_tag, bytes, offset, tiff_is_big_endian);
		BitUtils::GetValue(_type, bytes, offset, tiff_is_big_endian);
		BitUtils::GetValue(_count, bytes, offset, tiff_is_big_endian);

		switch (static_cast<IFDType>(_type)) {
		
		case IFDType::UNDEFINED:
		case IFDType::BYTE:
		{
			_value_or_offset = bytes[offset];
			offset += 4;
		}break;
		
		case IFDType::ASCII:
		{
			BitUtils::GetValue(_value_or_offset, bytes, offset, tiff_is_big_endian);
			unsigned long val_offset = (static_cast<unsigned long>(tiff_offset) + static_cast<unsigned long>(_value_or_offset));
			if (_count > 2) {
				//Getting a warning about 64bit ptrs ...
				_bytes.insert(_bytes.end(), bytes + val_offset, bytes + (val_offset + static_cast<unsigned long>(_count)));
			}
			else
			{
				_value_or_offset = ((_value_or_offset >> 24) & 0xFF);
				_bytes.push_back(static_cast<char>(_value_or_offset));
			}
		}break;

		case IFDType::SHORT:
		{
			unsigned short val = 0;
			BitUtils::GetValue(val, bytes, offset, tiff_is_big_endian);
			_value_or_offset = val;
		}break;

		case IFDType::RATIONAL:
		case IFDType::SRATIONAL:
		{
			BitUtils::GetValue(_value_or_offset, bytes, offset, tiff_is_big_endian);
			unsigned long val_offset = (static_cast<unsigned long>(tiff_offset) + static_cast<unsigned long>(_value_or_offset));
			//Getting a warning about 64bit ptrs ...
			_bytes.insert(_bytes.end(), bytes + val_offset, bytes + (val_offset + 8L));

		}break;

		default: {
			BitUtils::GetValue(_value_or_offset, bytes, offset, tiff_is_big_endian);
		}break;

		}
	}

	std::string IFDEntry::Value() 
	{
		if (_valstr == "")
		{
			std::stringstream ss;
			if (_bytes.size() > 0) {
				switch (static_cast<IFDType>(_type)) {
				case IFDType::RATIONAL:
				{
					//Swapping the Original C# .. wondering if its dependent on the tiff_is_big_endian.
					unsigned int a = 
						(static_cast<unsigned int>(_bytes[3]) & 0xFF) | 
						(static_cast<unsigned int>(_bytes[2]) & 0xFF) << 8 |
						(static_cast<unsigned int>(_bytes[1]) & 0xFF) << 16 |
						(static_cast<unsigned int>(_bytes[0]) & 0xFF) << 24;
					unsigned int b = 
						(static_cast<unsigned int>(_bytes[7]) & 0xFF) |
						(static_cast<unsigned int>(_bytes[6]) & 0xFF) << 8 |
						(static_cast<unsigned int>(_bytes[5]) & 0xFF) << 16 |
						(static_cast<unsigned int>(_bytes[4]) & 0xFF) << 24;
					double f = static_cast<double>(a) / static_cast<double>(b);
					ss << f;
					_valstr = ss.str();
				}break;
				case IFDType::SRATIONAL:
				{
					//Swapping the Original C# .. wondering if its dependent on the tiff_is_big_endian.
					int a = 
						(static_cast<int>(_bytes[3]) & 0xFF) |
						(static_cast<int>(_bytes[2]) & 0xFF) << 8 |
						(static_cast<int>(_bytes[1]) & 0xFF) << 16 |
						(static_cast<int>(_bytes[0]) & 0xFF) << 24;
					int b = 
						(static_cast<int>(_bytes[7]) & 0xFF) |
						(static_cast<int>(_bytes[6]) & 0xFF) << 8 |
						(static_cast<int>(_bytes[5]) & 0xFF) << 16 |
						(static_cast<int>(_bytes[4]) & 0xFF) << 24;
					double f = static_cast<double>(a) / static_cast<double>(b);
					ss << f;
					_valstr = ss.str();
				}break;
				default:
				{
					for (auto itr = _bytes.begin(); itr != _bytes.end(); ++itr) {
						ss << (*itr);
					}
					_valstr = ss.str();
				}break;

				}
			}
			else {
				ss << _value_or_offset;
				_valstr = ss.str();
			}
		}

		return _valstr;
	}

}