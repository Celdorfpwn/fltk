#include "stdafx.h"
#include "HardwareIndependentWindow.h"

HardwareIndependentWindow* HardwareIndependentWindow::instance;

HardwareIndependentWindow::HardwareIndependentWindow() : Fl_Window(490, 500, "Hardware Independent Product")
{
	this->initializeComponent();
}

HardwareIndependentWindow::~HardwareIndependentWindow()
{
}

HardwareIndependentWindow* HardwareIndependentWindow::Instance()
{
	if (!HardwareIndependentWindow::instance)
	{
		HardwareIndependentWindow::instance = new HardwareIndependentWindow();
	}

	return HardwareIndependentWindow::instance;
}

void HardwareIndependentWindow::initializeComponent()
{
	this->registrationButton = new Fl_Button(30, 10, 100, 30, "Register");
	this->registrationButton->callback(HardwareIndependentWindow::registrationButtonCallback, (void*)this);
	this->validationButton = new Fl_Button(140, 10, 100, 30, "Validate");
	this->validationButton->callback(HardwareIndependentWindow::validationButtonCallback, (void*)this);
	this->verifyButton = new Fl_Button(250, 10, 100, 30, "Verify");
	this->verifyButton->callback(HardwareIndependentWindow::verifyButtonCallack, (void*)this);
	this->offlineButton = new Fl_Button(360, 10, 100, 30, "Offline");
	this->end();
}

void HardwareIndependentWindow::clearGroups()
{
	if (this->currentGroup)
	{
		this->remove(this->currentGroup);
		this->currentGroup->~Fl_Group();
		this->redraw();
	}
}

void HardwareIndependentWindow::addRegistrationGroup()
{
	this->clearGroups();
	this->begin();
	this->currentGroup = new HIRegistrationGroup(50, 100, "Registration Form");
	this->end();
	this->redraw();
}

void HardwareIndependentWindow::addValidationGroup()
{
	this->clearGroups();
	this->begin();
	this->currentGroup = new HIValidationGroup(50, 100, "Validation Form");
	this->end();
	this->redraw();
}

void HardwareIndependentWindow::addVerifyGroup()
{
	this->clearGroups();
	this->begin();
	this->currentGroup = new HIVerifyGroup(50, 100, "Verify Form");
	this->end();
	this->redraw();
}


void HardwareIndependentWindow::registrationButtonCallback(Fl_Widget *widgent, void* data)
{
	HardwareIndependentWindow* window = (HardwareIndependentWindow*)data;
	window->addRegistrationGroup();
}

void HardwareIndependentWindow::validationButtonCallback(Fl_Widget *widget, void* data)
{
	HardwareIndependentWindow* window = (HardwareIndependentWindow*)data;
	window->addValidationGroup();
}

void HardwareIndependentWindow::verifyButtonCallack(Fl_Widget *widget, void* data)
{
	HardwareIndependentWindow* window = (HardwareIndependentWindow*)data;
	window->addVerifyGroup();
}