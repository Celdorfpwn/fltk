#include "stdafx.h"
#include "HIValidationGroup.h"


using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace pplx;

HIValidationGroup::HIValidationGroup(int x, int y, const char* t): Fl_Group(x, y, 400, 300, t)
{
	this->initializeComponent();
}

HIValidationGroup::~HIValidationGroup()
{
}

void HIValidationGroup::initializeComponent()
{
	this->activationKeyLabel = new Fl_Box(this->x() + 10, this->y() + 20, 50, 30, "Activation Key:");
	this->activationKeyLabel->align(FL_ALIGN_POSITION_MASK);
	this->activationKeyInput = new Fl_Input(this->x() + 10, this->y() + 20, this->w(), 30);

	this->hardwareKeyLabel = new Fl_Box(this->x() + 10, this->y() + 140, 50, 30, "Hardware Key:");
	this->hardwareKeyLabel->align(FL_ALIGN_POSITION_MASK);
	this->hardwareKeyInput = new Fl_Input(this->x() + 10, this->y() + 80, this->w(), 30);

	this->productIdLabel = new Fl_Box(this->x() + 10, this->y() + 260, 50, 30, "Product Id:");
	this->productIdLabel->align(FL_ALIGN_POSITION_MASK);
	this->productIdInput = new Fl_Input(this->x() + 10, this->y() + 140, this->w(), 30);

	this->validateButton = new Fl_Button(this->x() + 150, this->y() + 190, 100, 30, "Validate");
	this->validateButton->callback(HIValidationGroup::validateButtonCallback, (void*)this);
	this->end();

}

void HIValidationGroup::validateButtonCallback(Fl_Widget* widget, void* data)
{
	HIValidationGroup *group = (HIValidationGroup*)data;
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

task<void> HIValidationGroup::getRequestTask()
{
	return create_task([&]
	{
		http_client client(SERVER_BASE_URL);
		uri_builder builder = uri_builder(U("api"));
		builder.append(U("external"));
		builder.append(U("validateemailedlicense"));

		builder.append_query(U("activationKey"), conversions::to_string_t(string(this->activationKeyInput->value())), true);
		builder.append_query(U("hardwareKey"), conversions::to_string_t(string(this->hardwareKeyInput->value())), true);
		builder.append_query(U("productId"), conversions::to_string_t(string(this->productIdInput->value())), true);
		
		return client.request(methods::GET, builder.to_string());
	}).then([&](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			this->messageType = Info;
			return response.extract_json();
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
			return create_task([] { return json::value(); });
		}

	}).then([&](json::value jsonValue)
	{
		if (jsonValue.is_null())
			return;
		if (this->messageType == Warning)
		{
			if (jsonValue.has_field(L"message"))
			{
				this->messageResult = conversions::to_utf8string(jsonValue.at(L"message").serialize());
			}
		}
		else if(this->messageType == Info)
		{
			LicenseFileManager::writeLicenseFile(jsonValue);
			this->messageResult = "Validation Key is valid";
		}
	});
}

bool HIValidationGroup::validateInputs()
{
	if (this->activationKeyInput->value() && !this->activationKeyInput->value()[0])
	{
		fl_alert("Invalid activation key");
		this->activationKeyInput->take_focus();
		return false;
	}
	if (this->hardwareKeyInput->value() && !this->hardwareKeyInput->value()[0])
	{
		fl_alert("Invalid hardware key");
		this->hardwareKeyInput->take_focus();
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

void HIValidationGroup::showMessage()
{
	switch (this->messageType)
	{
	case Info: fl_message(this->messageResult.c_str()); break;
	case Warning: fl_alert(this->messageResult.c_str()); break;
	case Error: fl_alert(messageResult.c_str()); break;
	}
}