#include "stdafx.h"

HDRegisterGroup::HDRegisterGroup(int x, int y, const char* t) : BaseGroup(x, y, t)
{
	this->initializeComponent();
}

HDRegisterGroup::~HDRegisterGroup()
{
}

void HDRegisterGroup::initializeComponent()
{
	this->serialInput = BaseGroup::createInput(NULL, "Serial:",true);
	this->emailInput = BaseGroup::createInput(NULL, "Email:", true);
	this->usernameInput = BaseGroup::createInput(NULL, "Username:", true);
	this->affiliationInput = BaseGroup::createInput(NULL, "Affiliation:", true);
	this->otherInput = BaseGroup::createInput(NULL, "Other:", true);

	this->productIdInput = BaseGroup::createInput(Configuration::Instance()->HDProductId().c_str(), "Product Id:", false);
	this->hardwareKey = BaseGroup::createInput(Configuration::Instance()->HDHardwareId().c_str(), "Hardware Key:", false);

	this->registerButton = BaseGroup::createCenterButton("Register");

	this->end();
}