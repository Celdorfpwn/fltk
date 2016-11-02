// TestConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TrueLicenseApi.h"
#include <iostream>

using namespace std;
using namespace TrueLicense;

void LicenseProduct();
void ValidateEmailedLicense();

const char* server_url = "http://localhost:28652/";

int main()
{
	ValidateEmailedLicense();
	return 0;
}


void LicenseProduct() 
{
	LicensedProductModel model = LicensedProductModel("iasd", "ionut.apostol@sofvision.ro", "username");
	try
	{
		LicenseProduct(model, server_url);
		cout << "email sent" << "\n";
	}
	catch (ApiException apiException)
	{
		cout << apiException.getMessage() << "\n";
	}
	catch (const std::exception&)
	{
		cout << "error" << "\n";
	}
}

void ValidateEmailedLicense()
{
	ValidateEmailedLicenseModel model = ValidateEmailedLicenseModel("productId", "hwkey", "1234-5432-1234");
	try
	{
		const char* file = "license.file";
		ValidateEmailedLicense(model,file , server_url);
		cout << "file Wrote" << "\n";
	}
	catch (ApiException apiException)
	{
		cout << apiException.getMessage() << "\n";
	}
	catch (const std::exception&)
	{
		cout << "error" << "\n";
	}
}

