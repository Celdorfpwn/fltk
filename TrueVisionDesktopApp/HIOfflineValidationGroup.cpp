#include "stdafx.h"
#include "HIOfflineValidationGroup.h"
#include <openssl/rsa.h>

HIOfflineValidationGroup::HIOfflineValidationGroup(int x, int y, const char* t) : Fl_Group(x, y, 400, 300, t)
{
	this->offlineButton = new Fl_Button(this->x() + 100, this->y() + 10, 200, 30, "Validate offline");
	this->offlineButton->callback(HIOfflineValidationGroup::offlineButtonCallback, (void*)this);
}

HIOfflineValidationGroup::~HIOfflineValidationGroup()
{
}

void HIOfflineValidationGroup::offlineButtonCallback(Fl_Widget* widget, void* data)
{

}