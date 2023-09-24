#pragma once

#include <iostream>
#include <string>
#include "clsUtil.h";
#include "clsInputValidate.h";

#include "clsCourse.h";
#include "clsDoctor.h";

#include "clsScreen.h";

class clsCreateNewCourseScreen : protected clsScreen
{
private:

	static clsCourse _ReadCourseInfoAndCreate()
	{
		std::string courseCode = "";

		std::cout << "\nPlease Enter Course Code : ";
		courseCode = clsInputValidate::ReadString();

		while (clsCourse::isCourseExist(courseCode))
		{
			std::cout << "\nCourse Code is Already Used, Choose another Course Code : ";
			courseCode = clsInputValidate::ReadString();
		}

		std::string courseName = "";

		std::cout << "\nEnter Course Name: ";
		courseName = clsInputValidate::ReadString();

		std::string InstructorID = "";

		std::cout << "\nEnter Course Instructor ID: ";
		InstructorID = clsInputValidate::ReadString();

		while (!clsDoctor::isDoctorExist(InstructorID))
		{
			std::cout << "\nTheir is no doctor with this ID, Enter a valid doctor ID: ";
			InstructorID = clsInputValidate::ReadString();
		}

		return clsCourse::getAddNewCourseObject(courseCode, courseName, InstructorID);	
		
	}

	static void _PrintCourseInfo(clsCourse course)
	{
		cout << "\nCourse Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << course.getCourseCode();
		cout << "\nLastName    : " << course.courseName;
		cout << "\nFull Name   : " << course.getCourseInstructor();
		cout << "\n___________________\n";
	}

public:

	static void showCreateNewCourseScreen()
	{
		_DrawScreenHeader("Create New Course screen");
		
		clsCourse newCourse = _ReadCourseInfoAndCreate();

		clsCourse::enResults saveResult = newCourse.save();

		switch (saveResult)
		{
		case clsCourse::enResults::svSucceded:
		{
			cout << "\nCourse had been Added successfully :-)\n";
			_PrintCourseInfo(newCourse);
			break;
		}
		case clsCourse::enResults::svFailedEmptyObject:
		{
			cout << "\nError course was not saved because it's Empty\n";
			break;
		}
		case clsCourse::enResults::svFailedCourseExists:
		{
			cout << "\nError course was not saved because course code number is used!\n";
			break;
		}
		}

	}

};

