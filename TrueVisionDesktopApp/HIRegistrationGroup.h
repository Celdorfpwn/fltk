#pragma once
#include "stdafx.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "Enums.h"

using namespace utility;
using namespace pplx;
using namespace std;


class HIRegistrationGroup : public Fl_Group
{
public:
	HIRegistrationGroup(int x, int y, const char* t);
	~HIRegistrationGroup();

private:
	Fl_Box* usernameLabel;
	Fl_Box* emailLabel;
	Fl_Box* productIdLabel;

	Fl_Input* usernameInput;
	Fl_Input* emailInput;
	Fl_Input* productIdInput;

	Fl_Button* registerButton;

	string messageResult;
	MessageType messageType;

	static void registerButtonCallback(Fl_Widget *widgent, void* data);

	void initializeComponent();
	bool validateInputs();
	task<void> getRequestTask();
	void showMessage();
};

