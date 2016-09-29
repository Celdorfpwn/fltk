#pragma once
#include "stdafx.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "Enums.h"
#include "LicenseFileManager.h"


class HIValidationGroup : public Fl_Group
{
public:
	HIValidationGroup(int x, int y, const char* t);
	~HIValidationGroup();

private:

	Fl_Box* activationKeyLabel;
	Fl_Box* hardwareKeyLabel;
	Fl_Box* productIdLabel;

	Fl_Input* activationKeyInput;
	Fl_Input* hardwareKeyInput;
	Fl_Input* productIdInput;

	Fl_Button* validateButton;

	string messageResult;
	MessageType messageType;

	static void validateButtonCallback(Fl_Widget *widget, void* data);

	void initializeComponent();
	bool validateInputs();
	task<void> getRequestTask();
	void showMessage();
};