#include "stdafx.h"
#include "LicenseFileManager.h"

using namespace web;
using namespace utility::conversions;

void writeProperty(string_t name, string_t propertyName, fstream& file,json::value json);

namespace LicenseFileManager
{

	const char *path = "lic.file";


	void writeLicenseFile(json::value  json)
	{
		fstream file;
		file.open(path, fstream::out);

		file << "[" + to_utf8string(json.at(L"productName").as_string()) + "]\n";

		writeProperty(L"UserID", L"userId", file, json);
		writeProperty(L"Key", L"key", file, json);
		writeProperty(L"HW", L"hardwareKey", file, json);

		file << "[License]\n";

		json::array list = json.at(L"licenses").as_array();

		for (size_t index = 0; index < list.size(); index++)
		{
			json::value license = list.at(index);

			file << to_utf8string(license.at(L"licenseId").as_string() + L" = " + license.at(L"licenseKey").as_string()) + "\n";
		}

		file.close();
	}
}

void writeProperty(string_t name, string_t propertyName, fstream& file, json::value  json)
{
	file << to_utf8string(name + L" = " + json.at(propertyName).as_string()) + "\n";
}