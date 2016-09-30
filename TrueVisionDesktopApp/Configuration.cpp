#include "stdafx.h"
#include "Configuration.h"

using namespace std;
using namespace utility;

Configuration* Configuration::instance;

Configuration::Configuration()
{
	ifstream file("Configuration.cfg");
	file >> this->server_url;
	file >> this->default_productId;
	file >> this->default_hardwareId;
	file.close();
}

string Configuration::getDefaultProductId()
{
	return this->default_productId;
}

string Configuration::getServerUrl()
{
	return this->server_url;
}

string Configuration::getDefaultHardwareId()
{
	return this->default_hardwareId;
}


Configuration* Configuration::Instance()
{
	if (!Configuration::instance)
	{
		Configuration::instance = new Configuration();
	}
	return Configuration::instance;
}

Configuration::~Configuration()
{

}


