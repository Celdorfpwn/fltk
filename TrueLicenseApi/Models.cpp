#include "stdafx.h"
#include "TrueLicenseApi.h"
#include <string.h>

namespace TrueLicense
{
	ApiException::ApiException(std::string message)
	{
		this->message = message;
	}

	const char* ApiException::getMessage()
	{
		return this->message.c_str();
	}

	ApiException::~ApiException()
	{
	}

	LicensedProductModel::LicensedProductModel(const char* productId, const char* email, const char* username)
	{
		this->productId = productId;
		this->email = email;
		this->username = username;
	}

	LicensedProductModel::~LicensedProductModel()
	{
	}

	ValidateEmailedLicenseModel::ValidateEmailedLicenseModel(const char* productId, const char* hardwarekey, const char* activationkey)
	{
		this->productId = productId;
		this->hardwarekey = hardwarekey;
		this->activationkey = activationkey;
	}

	ValidateEmailedLicenseModel::~ValidateEmailedLicenseModel()
	{
	}
}