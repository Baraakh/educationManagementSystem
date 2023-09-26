#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "clsUtil.h";
#include "clsInputValidate.h";

#include "clsScreen.h";

#include "clsCourseRegisterInCourseScreen.h";
#include "clsListStudentCoursesScreen.h";
#include "clsViewCourse.h";
#include "clsGradeReport.h";

class clsStudentMainScreen : protected clsScreen
{
private:
	
	enum enStudentMainMenuOptions {opRegisterInCourse = 1, opListMyCourses = 2, opViewACourse = 3, opGradesReport = 4, opLogout = 5};

	static void _BackToMainMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
	}

	static short _ReadOption()
	{
		cout << endl << setw(37) << left << "" << "\t Choose what do you want to do? [1 to 5] : ";
		return clsInputValidate::ReadListNumberBetween(1, 5, "Number is out of range, Choose Number between 1 and 5: ");
	}

	static void _PrintMenuList()
	{
		_DrawScreenHeader("Student Main");

		cout << setw(37) << left << "" << "\t [1] Register in course.\n";
		cout << setw(37) << left << "" << "\t [2] List my courses.\n";
		cout << setw(37) << left << "" << "\t [3] View a course.\n";
		cout << setw(37) << left << "" << "\t [4] Grades report.\n";
		cout << setw(37) << left << "" << "\t [5] Logout.";
		clsUtil::printCenterText("______________________________________");
	}

	static void _RegisterInCourse()
	{	
		system("cls");
		clsCourseRegisterInCourseScreen::showCourseRegisterInCourseScreen();
	}

	static void _ListMyCourses()
	{
		system("cls");
		clsListStudentCoursesScreen::showListStudentCoursesScreen();
	}

	static void _ViewACourse()
	{
		system("cls");
		clsViewCourse::showViewCourse();
	}

	static void _GradeReport()
	{
		system("cls");
		
	}

	static bool _PerformStudentMainMenuOptions(enStudentMainMenuOptions option)
	{
		switch (option)
		{
		case enStudentMainMenuOptions::opRegisterInCourse:
		{
			_RegisterInCourse();
			_BackToMainMenu();
			return true;
		}
		case enStudentMainMenuOptions::opListMyCourses:
		{
			_ListMyCourses();
			_BackToMainMenu();
			return true;
		}
		case enStudentMainMenuOptions::opViewACourse:
		{
			_ViewACourse();
			return true;
		}
		case enStudentMainMenuOptions::opGradesReport:
		{
			_GradeReport();
			_BackToMainMenu();
			return true;
		}
		case enStudentMainMenuOptions::opLogout:
		{
			return false;
		}
		}
	}

public:

	static void showStudentMainScreen()
	{
		bool keepRunning = true;

		while (keepRunning)
		{
			system("cls");

			_PrintMenuList();

			keepRunning = _PerformStudentMainMenuOptions((enStudentMainMenuOptions) _ReadOption());
		}
	}

};

