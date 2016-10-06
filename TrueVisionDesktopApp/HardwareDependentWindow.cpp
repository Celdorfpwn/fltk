#include "stdafx.h"


HardwareDependentWindow* HardwareDependentWindow::instance;

HardwareDependentWindow::HardwareDependentWindow(): Fl_Window(490, 600, "Hardware Dependent Product")
{
	this->initializeComponents();
}

HardwareDependentWindow* HardwareDependentWindow::Instance()
{
	if (!HardwareDependentWindow::instance)
	{
		HardwareDependentWindow::instance = new HardwareDependentWindow();
	}
	
	return HardwareDependentWindow::instance;
}

HardwareDependentWindow::~HardwareDependentWindow()
{
}

void HardwareDependentWindow::initializeComponents()
{
	this->registerButton = new Fl_Button(30, 10, 210, 30, "Register");
	this->registerButton->callback(HardwareDependentWindow::registerButtonCallback,(void*)this);

	this->checkButton =  new Fl_Button(250, 10, 210, 30, "Check");
	this->checkButton->callback(HardwareDependentWindow::checkButtonCallback, (void*)this);

	this->end();
}

void HardwareDependentWindow::clearGroups()
{
	if (this->currentGroup)
	{
		this->remove(this->currentGroup);
		this->currentGroup->~Fl_Group();
		this->redraw();
	}
}

void HardwareDependentWindow::addRegistrationGroup()
{
	this->begin();
	this->currentGroup = new HDRegisterGroup(50, 100, "Registration Form");
	this->end();
	this->redraw();
}

void HardwareDependentWindow::addCheckGroup()
{

}

void HardwareDependentWindow::registerButtonCallback(Fl_Widget* widget, void* data)
{
	HardwareDependentWindow *window = (HardwareDependentWindow*)data;
	window->addRegistrationGroup();
}

void HardwareDependentWindow::checkButtonCallback(Fl_Widget* widget, void* data)
{

}

