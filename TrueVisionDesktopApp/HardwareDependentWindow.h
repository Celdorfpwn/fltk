#pragma once
#include "stdafx.h"

class HardwareDependentWindow : public Fl_Window
{
public:
	static HardwareDependentWindow* Instance();
	~HardwareDependentWindow();

private:
	HardwareDependentWindow();

	Fl_Button* registerButton;
	Fl_Button* checkButton;

	Fl_Group* currentGroup;

	void initializeComponents();
	void clearGroups();
	
	void addRegistrationGroup();
	void addCheckGroup();

	static HardwareDependentWindow* instance;

	static void registerButtonCallback(Fl_Widget *widget, void* data);
	static void checkButtonCallback(Fl_Widget * widget, void* data);
};
