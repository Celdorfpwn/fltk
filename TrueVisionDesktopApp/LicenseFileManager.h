#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace web::json;

namespace LicenseFileManager
{
	void writeHiLicenseFile(value json);
}