#include "APP0Marker.h"
#include "BitUtils.h"
#include <memory>
namespace EXIF {
	APP0Marker::APP0Marker(const char* bytes, int offset) {
		offset += 2; //Skip the App0 Marker
		BitUtils::GetValue(_length, bytes, offset, true);
		BitUtils::GetValue(_identifier, bytes, offset, 5);
		BitUtils::GetValue(_jfif_version, bytes, offset, true);
		_density_units = bytes[offset]; offset += 1;
		BitUtils::GetValue(_x_density, bytes, offset, true);
		BitUtils::GetValue(_y_density, bytes, offset, true);
		_x_thumbnail = bytes[offset]; offset += 1;
		_y_thumbnail = bytes[offset]; offset += 1;
		if (_x_thumbnail != 0 && _y_thumbnail != 0) {
			_thumbnail_data.insert(_thumbnail_data.end(), bytes, bytes + 3 * (static_cast<int>(_y_thumbnail) * static_cast<int>(_x_thumbnail)));
		}
	}

}