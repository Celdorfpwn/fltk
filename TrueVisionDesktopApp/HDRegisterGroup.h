#pragma once
#include "stdafx.h"

class HDRegisterGroup : public BaseGroup
{
public:
	HDRegisterGroup(int x,int y,const char* t);
	~HDRegisterGroup();

private:
	Fl_Input* serialInput;
	Fl_Input* emailInput;
	Fl_Input* usernameInput;
	Fl_Input* affiliationInput;
	Fl_Input* otherInput;
	Fl_Input* productIdInput;
	Fl_Input* hardwareKey;

	Fl_Button* registerButton;


	void initializeComponent();
};