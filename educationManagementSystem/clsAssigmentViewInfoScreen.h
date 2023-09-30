#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "clsScreen.h";

#include "clsCourse.h";

#include "clsAssigment.h";

class clsAssigmentViewInfoScreen : protected clsScreen
{
private:

	enum enViewAssigmentInfo { opListAssigments = 1, opCreateAssigment = 2, opViewAssigment = 3, opBack = 4 };

	static void _BackToMainMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
	}

	static void _PrintCourseInformation(clsCourse& course)
	{
		std::cout << endl << setw(37) << left << "" << "\t Course " + course.courseName + " with Code " + course.getCourseCode() + " - taught by " + course.getCourseInstructor() << endl;

	}

	static short _ReadOption()
	{
		std::cout << endl << endl << setw(37) << left << "" << "\t\t Enter Choice ? [1 to 4] : ";
		return clsInputValidate::ReadListNumberBetween(1, 4, "\tNumber is out of range, Choose Number between 1 and 4 : ");
	}

	static void _ListAssigments()
	{
		system("cls");
	}

	static bool _CreateAssigment()
	{
		system("cls");
	}

	static bool _ViewAssigment()
	{
		system("cls");
	}

	static bool _PerformAssigmentOption(enViewAssigmentInfo option, std::string courseId)
	{
		switch (option)
		{
		case enViewAssigmentInfo::opListAssigments:
		{
			_ListAssigments();
			return true;
		}
		case enViewAssigmentInfo::opCreateAssigment:
		{
			// code for later
			return true;
		}
		case enViewAssigmentInfo::opViewAssigment:
		{
			// code for later
			return true;
		}
		case enViewAssigmentInfo::opBack:
		{
			return false;
		}
		}
	}

public:

	static bool showAssigmentViewInfoScreen(clsCourse& course)
	{
		bool keepRunning = true;

		while (keepRunning)
		{
			system("cls");

			_DrawScreenHeader("View Course Information", course.getCourseCode() + " - " + course.courseName);

			_PrintCourseInformation(course);

			std::cout << endl << endl << endl << setw(37) << left << "" << "\t Please make a choice: " << endl;
			std::cout << endl << setw(37) << left << "" << "\t\t 1 - List Assignments " << endl;
			std::cout << endl << setw(37) << left << "" << "\t\t 2 - Create Assignment " << endl;
			std::cout << endl << setw(37) << left << "" << "\t\t 3 - View Assignment " << endl;
			std::cout << endl << setw(37) << left << "" << "\t\t 4 - Back " << endl;

			return _PerformAssigmentOption((enViewAssigmentInfo)_ReadOption(), course.getCourseCode());

		}
	}

};

