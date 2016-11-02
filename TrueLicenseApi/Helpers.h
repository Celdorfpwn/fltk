#pragma once

#include "stdafx.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace pplx;
using namespace conversions;
namespace Helpers
{
	class LicenseFileWriter
	{
	public:
		LicenseFileWriter(string  filePath);
		~LicenseFileWriter();
		Concurrency::task<void> WriteHILicenseFile(http_response response);
	private:
		string filePath;
		void writeProperty(string_t name, string_t propertyName, std::fstream& file, json::value  json);
	};
}