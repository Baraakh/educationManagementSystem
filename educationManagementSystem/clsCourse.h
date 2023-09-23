#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "clsString.h";

class clsCourse
{
private:

	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};

	enMode _Mode;
	std::string _CourseCode, _CourseName, _CourseInstructor;

	static clsCourse _ConvertRecordLineToObject(std::string record)
	{
		std::vector <std::string> vRecordData = clsString::Split(record, "#//#");

		return clsCourse(enMode::UpdateMode, vRecordData[0], vRecordData[1], vRecordData[2]);
	}

	static clsCourse _GetEmptyCourseObject()
	{
		return clsCourse(enMode::EmptyMode, "", "", "");
	}

public:

	clsCourse(enMode mode, std::string courseCode, std::string courseName, std::string courseInstructor)
	{
		_Mode = mode;
		_CourseCode = courseCode;
		_CourseName = courseName;
		_CourseInstructor = courseInstructor;
	}

	void setCourseCode(std::string courseCode)
	{
		_CourseCode = courseCode;
	}

	std::string getCourseCode()
	{
		return _CourseCode;
	}

	__declspec(property(get = getCourseCode, put = putCourseCode)) std::string courseCode;

	void setCourseName(std::string courseName)
	{
		_CourseName = courseName;
	}

	std::string getCourseName()
	{
		return _CourseName;
	}

	__declspec(property(get = getCourseName, put = setCourseName)) std::string courseName;

	void setCourseInstructor(std::string courseInstructor)
	{
		_CourseInstructor = courseInstructor;
	}

	std::string getCourseInstructor()
	{
		return _CourseInstructor;
	}

	__declspec(property(get = getCourseInstructor, put = putCourseInstructor)) std::string courseInstructor;

	static clsCourse find(std::string courseCode)
	{
		std::fstream coursesDB;
		coursesDB.open("DB/courses.txt", std::ios::in); //read only

		if (coursesDB.is_open())
		{
			std::string line;

			while (std::getline(coursesDB, line))
			{
				clsCourse course = _ConvertRecordLineToObject(line);

				if (course.courseCode == courseCode)
				{
					coursesDB.close();
					return course;
				}
			}

			coursesDB.close();
		}

		return _GetEmptyCourseObject();
	}

};

