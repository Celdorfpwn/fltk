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
	static HILicenseFileReader* Instance();
private:
	HILicenseFileReader();
	string userInfoId;
	string licenseId;
	string licenseKey;
	static HILicenseFileReader* instance;
};