#include "stdafx.h"
#include "HILicenseFileReader.h"
#include <boost/algorithm/string.hpp>


using namespace std;
using namespace utility;
using namespace boost;

HILicenseFileReader* HILicenseFileReader::instance;

HILicenseFileReader::HILicenseFileReader()
{
	ifstream file("lic.file");
	string row;
	getline(file, row);
	file >> row >> row >> this->userInfoId;
	file >> row >> row >> this->key;
	file >> row >> row >> this->hardwareCertificate;
	getline(file, row);
	file >> row;
	file >> this->licenseId >> row >> this->licenseKey;
}

string HILicenseFileReader::getUserInfoId()
{
	return this->userInfoId;
}

string HILicenseFileReader::getLicenseId()
{
	return this->licenseId;
}

string HILicenseFileReader::getLicenseKey()
{
	return this->licenseKey;
}

HILicenseFileReader* HILicenseFileReader::Instance()
{
	if (!HILicenseFileReader::instance)
	{
		HILicenseFileReader::instance = new HILicenseFileReader();
	}
	return HILicenseFileReader::instance;
}

HILicenseFileReader::~HILicenseFileReader()
{

}