#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h";

#include "clsDoctor.h";
#include "clsStudent.h";

#include "clsInputValidate.h";

#include "clsDoctorMainScreen.h";
#include "clsStudentMainScreen.h";

#include"Global.h";

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		bool loginFaild = false;
		std::string userName, password;
		char userNamePrefix;
		short numberOfTrials = 3;

		do
		{
			
			if (loginFaild) 
			{
				numberOfTrials--;

				if (numberOfTrials == 0)
				{
					cout << "\nYour are Locked after 3 faild Trials\n";
					return false;
				}

				cout << "\nInvlaid Username/Password!\n";
				cout << "\nYou have " << numberOfTrials << " Trial(s) to login.\n\n";
			}

			cout << "Enter UserName? ";
			cin >> userName;

			cout << "Enter Password? ";
			cin >> password;

			userNamePrefix = userName[0];

			if (userNamePrefix == 'd')
			{
				currentDoctor = clsDoctor::find(userName, password);

				loginFaild = currentDoctor.isEmpty();
			}
			else if (userNamePrefix == 's')
			{
				currentStudent = clsStudent::find(userName, password);

				loginFaild = currentStudent.isEmpty();
			}
			else
			{
				loginFaild = true;
			}



		} while (loginFaild);

		

		if (userNamePrefix == 'd')
		{
			currentPerson = &currentDoctor;
			clsDoctorMainScreen::showDoctorMainScreen();
		}
		else if (userNamePrefix == 's')
		{
			currentPerson = &currentStudent;
			clsStudentMainScreen::showStudentMainScreen();
		}

		return true;
	}

public:

	static void showLoginScreen()
	{
		while (true)
		{
			system("cls");
			_DrawScreenHeader("Login Screen");

			if (!_Login())
			{
				break;
			}

		}

		

	}

};

