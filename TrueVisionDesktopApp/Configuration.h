#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

class Configuration 
{
public:
	~Configuration();
	string ServerUrl();
	string HIProductId();
	string HIHardwareId();
	string HDProductId();
	string HDHardwareId();
	static Configuration* Instance();
private:
	Configuration();
	string server_url;
	string default_productId;
	string default_hardwareId;

	string hd_productId;
	string hd_hardwareKey;

	static Configuration* instance;
};