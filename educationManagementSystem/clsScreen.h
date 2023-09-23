#pragma once

#include <iostream>
#include <string>

#include "clsUtil.h"

class clsScreen
{
protected:

	static void _DrawScreenHeader(std::string title, std::string subTitle = "")
	{
		clsUtil::printCenterText("______________________________________");
		clsUtil::printCenterText(title);
		if (subTitle != "")
		{
			clsUtil::printCenterText(subTitle);
		}
		clsUtil::printCenterText("______________________________________");
	}

};

