#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

class HILicenseFileReader
{
public:
	~HILicenseFileReader();
	string getUserInfoId();
	string getLicenseId();
	string getLicenseKey();
	string getHardwareCertificate();
	string getKey();
	static HILicenseFileReader* Instance();
private:
	HILicenseFileReader();
	string userInfoId;
	string licenseId;
	string licenseKey;
	string hardwareCertificate;
	string key;
	static HILicenseFileReader* instance;
};