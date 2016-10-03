#pragma once
#include "stdafx.h"

class HIOfflineValidationGroup: public Fl_Group
{
public:
	HIOfflineValidationGroup(int x, int y, const char* t);
	~HIOfflineValidationGroup();

private:
	Fl_Button* offlineButton;

	string hardwareKey;
	string hardwareCertificate;
	string licenseId;
	string licenseKey;

	static void offlineButtonCallback(Fl_Widget* widget, void* data);
};

