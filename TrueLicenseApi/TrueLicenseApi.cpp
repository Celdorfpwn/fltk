// TrueLicenseApi.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"
#include "TrueLicenseApi.h"
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
namespace TrueLicense
{
	Concurrency::task<void> EmptyTask();
	Concurrency::task<void> NotFoundTask();
	Concurrency::task<void> BadRequestTask(http_response response);
	void writeProperty(string_t name, string_t propertyName, std::fstream& file, json::value  json);

	void LicenseProduct(LicensedProductModel model, const char* server_url)
	{
		create_task([&] {
			http_client client(to_string_t(server_url));

			uri_builder builder = uri_builder(U("api"));

			builder.append(U("external"));
			builder.append(U("licenseproduct"));

			builder.append_query(U("productId"), model.productId, true);
			builder.append_query(U("email"), model.email, true);
			builder.append_query(U("username"), model.username, true);

			return client.request(methods::GET, builder.to_string());
		}).then([&](http_response response)
		{
			if (response.status_code() == status_codes::BadRequest)
			{
				return BadRequestTask(response);
			}
			else if (response.status_code() == status_codes::OK)
			{
				return EmptyTask();
			}
			else
			{
				return NotFoundTask();
			}
		}).wait();
	}

	void ValidateEmailedLicense(ValidateEmailedLicenseModel model, const char*  licFilePath, const char* server_url)
	{
		create_task([&] {
			http_client client = http_client(to_string_t(server_url));

			uri_builder builder = uri_builder(U("api"));
			builder.append(U("external"));
			builder.append(U("validateemailedlicense"));

			builder.append_query(U("productId"), model.productId, true);
			builder.append_query(U("hardwarekey"), model.hardwarekey, true);
			builder.append_query(U("activationkey"), model.activationkey, true);

			return client.request(methods::GET, builder.to_string());
		}).then([&](http_response response) {

			if (response.status_code() == status_codes::OK)
			{
				return response.extract_json().then([&](json::value result) {
					std::fstream file;
					file.open(licFilePath, std::fstream::out);
					file << "[" + to_utf8string(result.at(L"productName").as_string()) + "]\n";

					writeProperty(L"UserID", L"userId", file, result);
					writeProperty(L"Key", L"key", file, result);
					writeProperty(L"HW", L"hardwareKey", file, result);

					file << "[License]\n";
					file << to_utf8string(result.at(L"licenseId").as_string() + L" = " + result.at(L"licenseKey").as_string()) + "\n";
					file.close();
				});
			}
			else if (response.status_code() == status_codes::BadRequest)
			{
				return BadRequestTask(response);
			}
			else
			{
				return NotFoundTask();
			}
		}).wait();
	}

	void writeProperty(string_t name, string_t propertyName, std::fstream& file, json::value  json)
	{
		file << to_utf8string(name + L" = " + json.at(propertyName).as_string()) + "\n";
	}

	Concurrency::task<void> EmptyTask()
	{
		return create_task([] { return json::value(); }).then([&](json::value result) {
		});
	}

	Concurrency::task<void> NotFoundTask()
	{
		return create_task([] { return json::value(); }).then([&](json::value result)
		{
			throw ApiException("Invalid request");
		});
	}

	Concurrency::task<void> BadRequestTask(http_response response)
	{
		return response.extract_json().then([&](json::value result)
		{
			if (!result.is_null())
			{
				if (result.has_field(L"message"))
				{
					throw ApiException(conversions::to_utf8string(result.at(L"message").serialize()));
				}
				else
				{
					throw ApiException("Invalid request");
				}
			}
		});
	}


}