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

	static void _ReadCourseInfo(clsCourse& course)
	{
		std::cout << "\nEnter Course Name: ";
		course.courseName = clsInputValidate::ReadString();

		std::string DoctorID = "";

		std::cout << "\nEnter Course Instructor ID: ";
		DoctorID = clsInputValidate::ReadString();

		while (!clsDoctor::isDoctorExist(DoctorID))
		{
			std::cout << "\nTheir is no doctor with this ID, Enter a valid doctor ID: ";
			DoctorID = clsInputValidate::ReadString();
		}

		course.courseInstructor = (clsDoctor::find(DoctorID)).fullName(); // pull the instructor fullname from the DB
	}

	static void _PrintCourseInfo(clsCourse course)
	{
		cout << "\nCourse Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << course.getCourseCode();
		cout << "\nLastName    : " << course.courseName;
		cout << "\nFull Name   : " << course.courseInstructor;
		cout << "\n___________________\n";
	}

public:

	static void showCreateNewCourseScreen()
	{
		_DrawScreenHeader("Create New Course screen");

		std::string courseCode = "";

		std::cout << "\nPlease Enter Course Code : ";
		courseCode = clsInputValidate::ReadString();

		while (clsCourse::isCourseExist(courseCode))
		{
			std::cout << "\nCourse Code is Already Used, Choose another Course Code : ";
			courseCode = clsInputValidate::ReadString();
		}

		clsCourse newCourse = clsCourse::getAddNewCourseObject(courseCode);

		_ReadCourseInfo(newCourse);

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

