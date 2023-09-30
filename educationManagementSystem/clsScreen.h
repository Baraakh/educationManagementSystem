#pragma once

#include <iostream>
#include <string>

#include "clsUtil.h";
#include "clsDate.h";
#include "Global.h";

class clsScreen
{
protected:

	static void _DrawScreenHeader(std::string title, std::string subTitle = "")
	{
		clsUtil::printCenterText("--------------------------------------");
		clsUtil::printCenterText(title);
		if (subTitle != "")
		{
			clsUtil::printCenterText(subTitle);
		}
		clsUtil::printCenterText("--------------------------------------");
		clsUtil::printCenterText("Name: " + currentPerson->fullName() + "\t\tDate: " + clsDate::DateToString(clsDate()));
		clsUtil::printCenterText("--------------------------------------");
	}

};

