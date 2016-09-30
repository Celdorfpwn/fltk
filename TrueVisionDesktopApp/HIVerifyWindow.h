#pragma once
#include "stdafx.h"
#include "HIVerifyWindow.h"

class HIVerifyWinow : public Fl_Group
{
public:
	HIVerifyWinow(int x, int y, const char* t);
	~HIVerifyWinow ();
private:
	Fl_Box* userInfoIdLabel;
	Fl_Box* hardwareKeyLabel;
	Fl_Box* productIdLabel;
	Fl_Box* licenseIdLabel;
	Fl_Box* licenseKeyLabel;
};
