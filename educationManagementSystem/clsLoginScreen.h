#pragma once

#include <iostream>

#include "clsScreen.h"

class clsLoginScreen : protected clsScreen
{
private:

public:

	static void showLoginScreen()
	{
		_DrawScreenHeader("Login Screen");

	}

};

