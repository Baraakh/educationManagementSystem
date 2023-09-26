#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "clsUtil.h";
#include "clsInputValidate.h";

#include "clsScreen.h";

#include "clsCourseListScreen.h";
#include "clsCreateNewCourseScreen.h";
#include "clsViewCourseMenue.h";

class clsDoctorMainScreen : protected clsScreen
{
private:

	enum enDoctorMainMenuOptions { opListCourses = 1, opCreateCourses = 2, opViewCourse = 3, Logout = 4 };

	static short _ReadOption()
	{
		cout << endl << setw(37) << left << "" << "\t Choose what do you want to do? [1 to 4] : ";
		return clsInputValidate::ReadListNumberBetween(1, 4, "Number is out of range, Choose Number between 1 and 4: ");
	}

	static void _GoBackToMainMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
	}

	static void _ShowAllCourses()
	{
		system("cls");
		clsCourseListScreen::showCourseList();
	}

	static void _ShowCreateCourse()
	{
		system("cls");
		clsCreateNewCourseScreen::showCreateNewCourseScreen();
	}

	static void _ShowViewCourseMenu()
	{
		system("cls");
		clsViewCourseMenue::showCourseMenu();
	}

	static bool _PerformDoctorMainMenuOptions(enDoctorMainMenuOptions option)
	{
		switch (option)
		{
		case enDoctorMainMenuOptions::opListCourses:
		{
			_ShowAllCourses();
			_GoBackToMainMenu();
			return true;
		}
		case enDoctorMainMenuOptions::opCreateCourses:
		{
			_ShowCreateCourse();
			_GoBackToMainMenu();
			return true;
		}
		case enDoctorMainMenuOptions::opViewCourse:
		{
			_ShowViewCourseMenu();
			_GoBackToMainMenu();
			return true;
		}
		case enDoctorMainMenuOptions::Logout:
		{
			return false;
		}
		}
	}

	static void _PrintMenuList()
	{
		_DrawScreenHeader("Doctor Main");
			
		cout << setw(37) << left << "" << "\t [1] List Courses.\n";
		cout << setw(37) << left << "" << "\t [2] Create course.\n";
		cout << setw(37) << left << "" << "\t [3] View Course.\n";
		cout << setw(37) << left << "" << "\t [4] Logout.";
		clsUtil::printCenterText("______________________________________");
	}

public:

	static void showDoctorMainScreen()
	{
		bool keepRunning = true;

		while (keepRunning)
		{
			system("cls");

			_PrintMenuList();

			keepRunning = _PerformDoctorMainMenuOptions((enDoctorMainMenuOptions) _ReadOption());
		}

		


	}

};

