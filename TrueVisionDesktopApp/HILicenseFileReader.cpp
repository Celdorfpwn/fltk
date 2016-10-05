#include "stdafx.h"
#include <boost/algorithm/string.hpp>


using namespace std;
using namespace utility;
using namespace boost;

HILicenseFileReader* HILicenseFileReader::instance;

HILicenseFileReader::HILicenseFileReader()
{
	ifstream file("hilic.file");
	string row;
	getline(file, row);
	file >> row >> row >> this->userInfoId;
	file >> row >> row >> this->key;
	file >> row >> row >> this->hardwareCertificate;
	getline(file, row);
	file >> row;
	file >> this->licenseId >> row >> this->licenseKey;

	this->key = string("r60AjGys7mUn/8oKEJYQiV27FkwjtZJrdyXtYR+x/J/MSkxSIKV1Df5CQEUM+qJCzodpepsifzyKCFg15sfr4JfulR4VpSvGWo90moLpMMrau+T8YsgQLb+SjI7j8kaOSSAQytJL/q8NBr7vap7/EV8PRhN93uUrc1yJw+4ED9s=");
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

string HILicenseFileReader::getHardwareCertificate()
{
	return this->hardwareCertificate;
}
string HILicenseFileReader::getKey()
{
	return this->key;
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