#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

class Configuration 
{
public:
	~Configuration();
	string getServerUrl();
	string getDefaultProductId();
	string getDefaultHardwareId();
	static Configuration* Instance();
private:
	Configuration();
	string server_url;
	string default_productId;
	string default_hardwareId;
	static Configuration* instance;
};