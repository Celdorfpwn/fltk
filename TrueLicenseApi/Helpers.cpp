#include "stdafx.h"
#include "Helpers.h"


namespace Helpers
{
	LicenseFileWriter::LicenseFileWriter(string filePath)
	{
		this->filePath = filePath;
	}

	Concurrency::task<void> LicenseFileWriter::WriteHILicenseFile(http_response response)
	{
		return response.extract_json().then([&](json::value result) {
			std::fstream file;
			file.open(this->filePath, std::fstream::out);
			file << "[" + to_utf8string(result.at(L"productName").as_string()) + "]\n";

			writeProperty(L"UserID", L"userId", file, result);
			writeProperty(L"Key", L"key", file, result);
			writeProperty(L"HW", L"hardwareKey", file, result);

			file << "[License]\n";
			file << to_utf8string(result.at(L"licenseId").as_string() + L" = " + result.at(L"licenseKey").as_string()) + "\n";
			file.close();
		});
	}

	void LicenseFileWriter::writeProperty(string_t name, string_t propertyName, std::fstream& file, json::value  json)
	{
		file << to_utf8string(name + L" = " + json.at(propertyName).as_string()) + "\n";
	}

	LicenseFileWriter::~LicenseFileWriter()
	{

	}
}