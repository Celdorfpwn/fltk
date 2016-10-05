#pragma once
#include "stdafx.h"
#include "HIVerifyGroup.h"
#include "HILicenseFileReader.h"
#include "Configuration.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "Enums.h"

class HIVerifyGroup : public BaseGroup
{
public:
	HIVerifyGroup(int x, int y, const char* t);
	~HIVerifyGroup ();
private:

	Fl_Input* userInfoInput;
	Fl_Input* hardwareKeyInput;
	Fl_Input* productIdInput;
	Fl_Input* licenseIdInput;
	Fl_Input* licenseKeyInput;

	Fl_Button* verifyButton;

	MessageType messageType;
	string messageResult;

	static void verifyButtonCallback(Fl_Widget *widget, void* data);

	void initializeComponent();
	task<void> getRequestTask();
	void showMessage();
};
