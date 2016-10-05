#include "stdafx.h"


using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace pplx;

HIRegistrationGroup::HIRegistrationGroup(int x, int y, const char* t) : BaseGroup(x, y, t)
{
	this->initializeComponent();
}

HIRegistrationGroup::~HIRegistrationGroup()
{
}

void HIRegistrationGroup::initializeComponent()
{

	this->usernameInput = BaseGroup::createInput(NULL, "Username:", true);
	this->emailInput = BaseGroup::createInput(NULL, "Email:", true);
	this->productIdInput = BaseGroup::createInput(Configuration::Instance()->HIProductId().c_str(), "Product Id:", false);

	this->registerButton = BaseGroup::createCenterButton("Register");
	this->registerButton->callback(registerButtonCallback, (void*)this);
	this->end();
}

void HIRegistrationGroup::registerButtonCallback(Fl_Widget *widgent, void* data)
{
	HIRegistrationGroup *group = (HIRegistrationGroup*)data;
	if (group->validateInputs())
	{
		try
		{
			group->getRequestTask().wait();
			group->showMessage();
		}
		catch (const std::exception&)
		{
			fl_alert("Error occured");
		}
	}
}

bool HIRegistrationGroup::validateInputs()
{
	if (this->usernameInput->value() && !this->usernameInput->value()[0])
	{
		fl_alert("Invalid username");
		this->usernameInput->take_focus();
		return false;
	}
	if (this->emailInput->value() && !this->emailInput->value()[0])
	{
		fl_alert("Invalid email");
		this->emailInput->take_focus();
		return false;
	}
	if (this->productIdInput->value() && !this->productIdInput->value()[0])
	{
		fl_alert("Invalid productId");
		this->productIdInput->take_focus();
		return false;
	}

	return true;
}

task<void> HIRegistrationGroup::getRequestTask()
{
	return create_task([&]
	{
		http_client client(conversions::to_string_t(Configuration::Instance()->ServerUrl()));

		uri_builder builder = uri_builder(U("api"));
		builder.append(U("external"));
		builder.append(U("licenseproduct"));
		builder.append_query(U("productId"), conversions::to_string_t(string(this->productIdInput->value())), true);
		builder.append_query(U("username"), conversions::to_string_t(string(this->usernameInput->value())), true);
		builder.append_query(U("email"), conversions::to_string_t(string(this->emailInput->value())), true);
		return client.request(methods::GET, builder.to_string());
	}).then([&](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			this->messageResult = "Email sent";
			this->messageType = Info;
		}
		else if (response.status_code() == status_codes::BadRequest)
		{
			this->messageType = Warning;
			return response.extract_json();
		}
		else
		{
			this->messageResult = "Error occurred";
			this->messageType = Error;
		}

		return create_task([] { return json::value(); });

	}).then([&](json::value jsonValue)
	{
		if (jsonValue.is_null())
			return;

		if (jsonValue.has_field(L"message"))
		{
			this->messageResult = conversions::to_utf8string(jsonValue.at(L"message").serialize());
		}
	});
}

void HIRegistrationGroup::showMessage()
{
	switch (this->messageType)
	{
	case Info: fl_message(this->messageResult.c_str()); break;
	case Warning: fl_alert(this->messageResult.c_str()); break;
	case Error: fl_alert(messageResult.c_str()); break;
	}
}