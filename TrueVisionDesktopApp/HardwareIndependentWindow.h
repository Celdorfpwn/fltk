#pragma once
#include "stdafx.h"

class HardwareIndependentWindow : public Fl_Window
{
public:
	static HardwareIndependentWindow* Instance();
	~HardwareIndependentWindow();

	void addRegistrationForm();

private:
	HardwareIndependentWindow();

	Fl_Button* registrationButton;
	Fl_Button* validationButton;
	Fl_Button* verifyButton;

	static HardwareIndependentWindow* instance;

	void initializeComponent();
};
