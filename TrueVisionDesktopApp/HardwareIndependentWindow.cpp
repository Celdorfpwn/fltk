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
	this->registrationButton = new Fl_Button(10, 10, 150, 30, "Registration");
	this->registrationButton->callback(HardwareIndependentWindow::registrationButtonCallback, (void*)this);
	this->validationButton = new Fl_Button(170, 10, 150, 30, "Validation");
	this->validationButton->callback(HardwareIndependentWindow::validationButtonCallback, (void*)this);
	this->verifyButton = new Fl_Button(330, 10, 150, 30, "Verify");
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