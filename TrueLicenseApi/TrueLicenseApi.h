#pragma once

#define TRUELICENSE_API __declspec(dllexport) 

#include "stdafx.h"
#include <string>

namespace TrueLicense
{
	class ApiException
	{
	public:
		ApiException(std::string message);
		TRUELICENSE_API ~ApiException();
		TRUELICENSE_API const char* getMessage();
	private:
		std::string message;
	};

	class LicensedProductModel
	{
	public:
		TRUELICENSE_API LicensedProductModel(const char* productId, const char* email, const char* username);
		TRUELICENSE_API ~LicensedProductModel();
		const char* productId;
		const char* email;
		const char* username;
	private:

	};

	class ValidateEmailedLicenseModel
	{
	public:
		TRUELICENSE_API ValidateEmailedLicenseModel(const char* productId, const char* hardwarekey, const char* activationkey);
		TRUELICENSE_API ~ValidateEmailedLicenseModel();
		const char* productId;
		const char* hardwarekey;
		const char* activationkey;
	private:

	};

	TRUELICENSE_API void LicenseProduct(LicensedProductModel model, const char* server_url);

	TRUELICENSE_API void ValidateEmailedLicense(ValidateEmailedLicenseModel model, const char*  licFilePath, const char* server_url);

}