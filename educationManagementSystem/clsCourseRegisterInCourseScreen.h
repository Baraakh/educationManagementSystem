#pragma once

#include <iostream>
#include <vector>

#include "Global.h";

#include "clsStudent.h";
#include "clsCourse.h";

#include "clsScreen.h";

class clsCourseRegisterInCourseScreen : protected clsScreen
{
private:

	static short _ReadOption(int numCourses)
	{
		std::cout << endl << endl << setw(37) << left << "" << "\t Choose what course do you want to register in? [1 to " << numCourses << "] : ";
		return clsInputValidate::ReadListNumberBetween(1, numCourses, "Number is out of range, Choose Number between 1 and " + to_string(numCourses) + ": ");
	}

	static void _PrintRecord(clsCourse course, int counter)
	{	
		std::cout << endl << setw(37) << left << "" << "\t " + to_string(counter) + ") Course " + course.courseName + " - Code " + course.getCourseCode();
	}

	static void _PrintAllTheNotEnrolledCourses(std::vector <clsCourse> allNotEnrolledCourses)
	{
		short counter = 1;

		std::cout << endl << setw(37) << left << "" << "\t Courses List: " << endl;

		if (allNotEnrolledCourses.size() == 0)
		{
			cout << endl << setw(37) << left << "" << "\t Sorry, There is no Courses offered for you to take: ";
		}
		else
		{
			for (clsCourse course : allNotEnrolledCourses)
			{
				_PrintRecord(course, counter);
				counter++;
			}
		}
	}

	static void _PrintCourseCard(clsCourse course)
	{
		std::cout << endl << setw(37) << left << "" << "\t Course Card: " << endl;
		std::cout << endl << setw(37) << left << "" << "\t _________________________________________________________ " << endl;
		std::cout << endl << setw(37) << left << "" << "\t Course Code: "  << course.getCourseCode() << endl;
		std::cout << endl << setw(37) << left << "" << "\t Course Name: " << course.courseName << endl;
		std::cout << endl << setw(37) << left << "" << "\t Course Instructor: " << course.getCourseInstructor() << endl;
		std::cout << endl << setw(37) << left << "" << "\t _________________________________________________________ " << endl;
	}

public:
	
	static void showCourseRegisterInCourseScreen()
	{
		
		std::vector <clsCourse> allNotEnrolledCourses = currentStudent.getStudentNotEnrolledCourses();

		string SubTitle = "(" + to_string(allNotEnrolledCourses.size()) + ") Course(s).";

		_DrawScreenHeader("Register In Course", SubTitle);

		_PrintAllTheNotEnrolledCourses(allNotEnrolledCourses);

		short courseNum = _ReadOption(allNotEnrolledCourses.size());

		bool registerResult = currentStudent.registerInCourse((allNotEnrolledCourses[courseNum - 1]).getCourseCode());

		if (registerResult)
		{
			cout << endl << setw(37) << left << "" << "\t Course was registered succussfully: " << endl;
			_PrintCourseCard((allNotEnrolledCourses[courseNum - 1]));
		}
		else
		{
			cout << endl << setw(37) << left << "" << "\t Oops, something went wrong try again: " << endl;
		}
	}

};

