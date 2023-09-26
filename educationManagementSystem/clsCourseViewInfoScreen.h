#pragma once

#include <iostream>
#include <string>

#include "clsScreen.h";

#include "clsCourse.h"

class clsCourseViewInfoScreen : protected clsScreen
{
private:

	enum enViewCourseInfo {opUnRegisterFromCourse = 1, opSubmitSolution = 2, opBack = 3};

	static void _BackToMainMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
	}

	static void _PrintCourseInformation(clsCourse& course)
	{
		std::cout << endl << setw(37) << left << "" << "\t Course " + course.courseName + " with Code " + course.getCourseCode() + " - taught by " + course.getCourseInstructor() << endl;
		std::cout << endl << setw(37) << left << "" << "\t Course has 0 assigments" << endl;

		// assigment code will be written here in the future

	}

	static short _ReadOption()
	{
		std::cout << endl << endl << setw(37) << left << "" << "\t\t Enter Choice ? [1 to 3] : ";
		return clsInputValidate::ReadListNumberBetween(1, 3, "\tNumber is out of range, Choose Number between 1 and 3 : ");
	}

	static bool _UnRegisterFromCourse(std::string courseId)
	{
		return currentStudent.unRegisterFromCourse(courseId);
	}

	static bool _PerformCourseOption(enViewCourseInfo option, std::string courseId)
	{
		switch (option)
		{
		case enViewCourseInfo::opUnRegisterFromCourse:
		{
			bool result = _UnRegisterFromCourse(courseId);

			if (result)
			{
				std::cout << endl << setw(37) << left << "" << "\t Course Was Deleted Succussfully. " << endl;
			}
			else
			{
				std::cout << endl << setw(37) << left << "" << "\t Oops, something Course Was Not Deleted Succussfully. " << endl;
			}

			_BackToMainMenu();
			return false;
		}
		case enViewCourseInfo::opSubmitSolution:
		{
			// code for later
			return true;
		}
		case enViewCourseInfo::opBack:
		{
			return false;
		}
		}
	}

public:

	static bool showCourseViewInfoScreen(clsCourse& course)
	{
		system("cls");

		_DrawScreenHeader("View Course Information", course.getCourseCode() + " - " + course.courseName);

		_PrintCourseInformation(course);

		std::cout << endl << endl << endl << setw(37) << left << "" << "\t Please make a choice: " << endl;
		std::cout << endl << setw(37) << left << "" << "\t\t 1 - UnRegister from Course " << endl;
		std::cout << endl << setw(37) << left << "" << "\t\t 2 - Submit solution " << endl;
		std::cout << endl << setw(37) << left << "" << "\t\t 3 - Back " << endl;
		
		return _PerformCourseOption((enViewCourseInfo)_ReadOption(), course.getCourseCode());
	}

};

