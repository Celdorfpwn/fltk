#include "stdafx.h"
#include "Configuration.h"

using namespace std;
using namespace utility;

Configuration* Configuration::instance;

Configuration::Configuration()
{
	ifstream file("Configuration.cfg");
	string skip;
	file >> skip >> skip >> this->server_url;
	file >> skip >> skip >> this->default_productId;
	file >> skip >> skip >> this->default_hardwareId;
	file.close();
}

string Configuration::HIProductId()
{
	return this->default_productId;
}

string Configuration::ServerUrl()
{
	return this->server_url;
}


string Configuration::HIHardwareId()
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




