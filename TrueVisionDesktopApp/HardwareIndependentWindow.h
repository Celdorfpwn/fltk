#pragma once
#include "stdafx.h"

class HardwareIndependentWindow : public Fl_Window
{
public:
	static HardwareIndependentWindow* Instance();
	~HardwareIndependentWindow();

private:
	HardwareIndependentWindow();

	Fl_Button* registrationButton;
	Fl_Button* validationButton;
	Fl_Button* verifyButton;
	Fl_Button* offlineButton;

	Fl_Group* currentGroup;

	static HardwareIndependentWindow* instance;

	void initializeComponent();
	void clearGroups();

	void addRegistrationGroup();
	void addValidationGroup();
	void addVerifyGroup();

	static void registrationButtonCallback(Fl_Widget *widgent, void* data);
	static void validationButtonCallback(Fl_Widget *widget, void* data);
	static void verifyButtonCallack(Fl_Widget *widget, void * data);
};
