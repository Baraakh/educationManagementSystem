#pragma once

#include <iostream>
#include <vector>

#include "Global.h";
#include "clsCourse.h";
#include "clsScreen.h";
#include "clsCourseViewInfoScreen.h";

class clsViewCourse : protected clsScreen
{
private:

	static short _ReadOption(int numCourses)
	{
		std::cout << endl << endl << setw(37) << left << "" << "\t Choose what course do you want see ? [1 to " << numCourses << "] : ";
		return clsInputValidate::ReadListNumberBetween(1, numCourses, "Number is out of range, Choose Number between 1 and " + to_string(numCourses) + ": ");
	}

	static void _PrintRecord(clsCourse course, int counter)
	{
		std::cout << endl << setw(37) << left << "" << "\t " + to_string(counter) + ") Course " + course.courseName + " - Code " + course.getCourseCode();
	}

	static void _PrintAllTheEnrolledCourses(std::vector <clsCourse> allEnrolledCourses)
	{
		short counter = 1;

		cout << endl << setw(37) << left << "" << "\t My Courses List: " << endl;

		if (allEnrolledCourses.size() == 0)
		{
			cout << endl << setw(37) << left << "" << "\t Sorry, There is no Courses offered for you to take: ";
		}
		else
		{
			for (clsCourse course : allEnrolledCourses)
			{
				_PrintRecord(course, counter);
				counter++;
			}
		}
	}

public:

	static void showViewCourse()
	{
		bool keepRunning = true;

		while (keepRunning)
		{
			system("cls");

			std::vector <clsCourse> allEnrolledCourses = currentStudent.getStudentEnrolledCourses();

			string SubTitle = "(" + to_string(allEnrolledCourses.size()) + ") Course(s).";

			_DrawScreenHeader("View course", SubTitle);

			_PrintAllTheEnrolledCourses(allEnrolledCourses);

			short courseNum = _ReadOption(allEnrolledCourses.size());

			keepRunning = clsCourseViewInfoScreen::showCourseViewInfoScreen(allEnrolledCourses[courseNum - 1]);

		}

	}

};

