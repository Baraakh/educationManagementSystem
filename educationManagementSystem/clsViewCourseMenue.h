#pragma once

#include <iostream>
#include <vector>

#include "Global.h";
#include "clsCourse.h";
#include "clsScreen.h";

#include "clsAssigmentViewInfoScreen.h";

class clsViewCourseMenue : public clsScreen
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

	static void _PrintAllTheCourses(std::vector <clsCourse> allDoctorCourses)
	{
		short counter = 1;

		cout << endl << setw(37) << left << "" << "\t My Courses List: " << endl;

		if (allDoctorCourses.size() == 0)
		{
			cout << endl << setw(37) << left << "" << "\t Sorry, There is no Courses you are responsible for: ";
		}
		else
		{
			for (clsCourse course : allDoctorCourses)
			{
				_PrintRecord(course, counter);
				counter++;
			}
		}
	}

public:

	static void showCourseMenu()
	{
		bool keepRunning = true;

		while (keepRunning)
		{
			system("cls");
			
			std::vector <clsCourse> vDoctorCourses = currentDoctor.getDoctorCourses();

			string SubTitle = "(" + to_string(vDoctorCourses.size()) + ") Course(s).";

			_DrawScreenHeader("View course", SubTitle);

			_PrintAllTheCourses(vDoctorCourses);

			short courseNum = _ReadOption(vDoctorCourses.size());

			keepRunning = clsAssigmentViewInfoScreen::showAssigmentViewInfoScreen(vDoctorCourses[courseNum - 1]);

		}
	}

};

