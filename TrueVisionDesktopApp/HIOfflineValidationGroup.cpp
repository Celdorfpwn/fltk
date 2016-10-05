#include "stdafx.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/sha.h>



HIOfflineValidationGroup::HIOfflineValidationGroup(int x, int y, const char* t) : Fl_Group(x, y, 400, 300, t)
{
	this->offlineButton = new Fl_Button(this->x() + 100, this->y() + 10, 200, 30, "Validate offline");
	this->offlineButton->callback(HIOfflineValidationGroup::offlineButtonCallback, (void*)this);
}

bool HIOfflineValidationGroup::areValuesValid()
{
	RSA* publicKey = RSA_new();
	HILicenseFileReader::Instance()->getKey();
	

	FILE* fp = fopen("public.key", "r");

	PEM_read_RSA_PUBKEY(fp, &publicKey, NULL, NULL);
	int resutl;
	unsigned char* value = reinterpret_cast<unsigned char *>("18900fdb-66ed-4cc5-a0fb-5285977077e7");
	unsigned char* signature = reinterpret_cast<unsigned char *>("c0fRX4uee1T/Ag/XHPH7f4ca1R9sv84k25gOrjLQjDObEwcgRBS36FKM3yOsUvPxIUnPY3YHx3YCDBLzxeK83zzZ0qSsel9q1ktGfXT4T+GmQOOrkXflCbmnps2JGdjv5kyF09smLJjRS2NTboVnAaJC3/cCvR4dT4yCKPPezzk=");

	try
	{
		resutl = RSA_verify(NID_sha1, value,
			string("18900fdb-66ed-4cc5-a0fb-5285977077e7").length(),
			signature,
			string("c0fRX4uee1T/Ag/XHPH7f4ca1R9sv84k25gOrjLQjDObEwcgRBS36FKM3yOsUvPxIUnPY3YHx3YCDBLzxeK83zzZ0qSsel9q1ktGfXT4T+GmQOOrkXflCbmnps2JGdjv5kyF09smLJjRS2NTboVnAaJC3/cCvR4dT4yCKPPezzk=").length(),
			publicKey);
	}
	catch (const std::exception &e)
	{
		fl_alert(e.what());
	}

		

	return true;
}

void HIOfflineValidationGroup::offlineButtonCallback(Fl_Widget* widget, void* data)
{
	HIOfflineValidationGroup *group = (HIOfflineValidationGroup*)data;
	if (group->areValuesValid())
	{
		fl_message("Valid license");
	}
	else
	{
		fl_alert("Invalid license");
	}
}


HIOfflineValidationGroup::~HIOfflineValidationGroup()
{
}
