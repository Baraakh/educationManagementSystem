#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "clsString.h";

#include "clsDoctor.h";


class clsCourse
{
private:

	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};

	enMode _Mode;
	std::string _CourseCode, _CourseName, _CourseInstructorID, _CourseInstructor;

	bool _MarkedForDelete = false;

	static clsCourse _ConvertRecordLineToObject(std::string record)
	{
		std::vector <std::string> vRecordData = clsString::Split(record, "#//#");

		return clsCourse(enMode::UpdateMode, vRecordData[0], vRecordData[1], vRecordData[2]);
	}
	static std::string _ConvertObjectToRecordLine(clsCourse course, std::string delim = "#//#")
	{
		std::string recordLine = "";

		recordLine += course.getCourseCode() + delim;
		recordLine += course.courseName + delim;
		recordLine += course.courseInstructorID;

		return recordLine;
	}

	static std::vector <clsCourse> _LoadAllCoursesFromDB()
	{
		std::vector <clsCourse> vCourses;

		std::fstream coursesDB;
		coursesDB.open("DB/courses.txt", std::ios::in);

		if (coursesDB.is_open())
		{
			std::string line;
			while (getline(coursesDB, line))
			{
				clsCourse course = _ConvertRecordLineToObject(line);
				vCourses.push_back(course);
			}

			coursesDB.close();
		}

		return vCourses;
	}
	static bool _AddCourseDataLineToDB(std::string stDataLine)
	{
		std::fstream coursesDB;
		coursesDB.open("DB/courses.txt", std::ios::out | std::ios::app);

		if (coursesDB.is_open())
		{
			coursesDB << stDataLine << endl;
			coursesDB.close();
			return true;
		}

		false;
	}

	bool _SaveCourseDateToDB(std::vector <clsCourse>& vCourses)
	{
		std::fstream coursesDB;
		coursesDB.open("DB/courses.txt", std::ios::out);

		if (coursesDB.is_open())
		{
			std::string record;
			for (clsCourse& course : vCourses)
			{
				if (!course._MarkedForDelete)
				{
					record = _ConvertObjectToRecordLine(course);
					coursesDB << record << endl;
				}	
			}

			coursesDB.close();
			return true;
		}

		return false;
	}
		 
	bool _Update()
	{
		std::vector <clsCourse> vCourses = _LoadAllCoursesFromDB();

		for (clsCourse& course : vCourses)
		{
			if (course.getCourseCode() == _CourseCode)
			{
				course = *this;
				break;
			}
		}

		return _SaveCourseDateToDB(vCourses);
	}

	bool _AddNew()
	{
		return _AddCourseDataLineToDB(_ConvertObjectToRecordLine(*this));
	}

	static clsCourse _GetEmptyCourseObject()
	{
		return clsCourse(enMode::EmptyMode, "", "", "");
	}

public:

	clsCourse(enMode mode, std::string courseCode, std::string courseName, std::string courseInstructorID)
	{
		_Mode = mode;
		_CourseCode = courseCode;
		_CourseName = courseName;
		_CourseInstructorID = courseInstructorID;
		_CourseInstructor = (clsDoctor::find(courseInstructorID)).fullName();
	}

	std::string getCourseCode()
	{
		return _CourseCode;
	}

	void setCourseName(std::string courseName)
	{
		_CourseName = courseName;
	}

	std::string getCourseName()
	{
		return _CourseName;
	}

	__declspec(property(get = getCourseName, put = setCourseName)) std::string courseName;

	// == must see them later for (entity integrity) problems====================

	std::string getCourseInstructor()
	{
		return _CourseInstructor;
	}


	// == must see them later for (entity integrity) problems====================

	void setCourseInstructorID(std::string courseInstructorID)
	{
		_CourseInstructorID = courseInstructorID;

		_CourseInstructor = (clsDoctor::find(courseInstructorID)).fullName();
	}

	std::string getCourseInstructorID()
	{
		return _CourseInstructorID;
	}

	__declspec(property(get = getCourseInstructorID, put = setCourseInstructorID)) std::string courseInstructorID;


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

				if (course.getCourseCode() == courseCode)
				{
					coursesDB.close();
					return course;
				}
			}

			coursesDB.close();
		}

		return _GetEmptyCourseObject();
	}

	static clsCourse getAddNewCourseObject(std::string courseCode, std::string courseName ,std::string courseInstructorID)
	{
		return clsCourse(enMode::AddNewMode, courseCode, courseName, courseInstructorID);
	}

	bool isEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	enum enResults {svFailedEmptyObject = 0, svSucceded = 1, svFailedCourseExists = 2, svFaildUnableToSave = 3};

	enResults save()
	{
		switch(_Mode)
		{
		case enMode::EmptyMode:
		{
			return enResults::svFaildUnableToSave;
		}
		case enMode::UpdateMode:
		{
			// write here to update
			if (_Update())
			{
				return enResults::svSucceded;
			}

			return enResults::svFaildUnableToSave;
		}
		case enMode::AddNewMode:
		{
			if (clsCourse::isCourseExist(_CourseCode))
			{
				return enResults::svFailedCourseExists;	
			}
			else
			{
				if (_AddNew())
				{
					_Mode = enMode::UpdateMode;
					return enResults::svSucceded;
				}

				return enResults::svFaildUnableToSave;
			}
		}
		}
	}

	static bool isCourseExist(std::string courseCode)
	{
		clsCourse course = clsCourse::find(courseCode);

		return (!course.isEmpty());
	}
	
	bool deleteCourse()
	{
		if (isEmpty() || _Mode == enMode::AddNewMode) return false;

		std::vector <clsCourse> vCourses = _LoadAllCoursesFromDB();

		for (clsCourse& course : vCourses)
		{
			if (course.getCourseCode() == _CourseCode)
			{
				course._MarkedForDelete = true;
				break;
			}
		}

		if (_SaveCourseDateToDB(vCourses))
		{
			*this = _GetEmptyCourseObject();
			return true;
		}

		return false;
	}

	static std::vector <clsCourse> getAllCoursesFromDB()
	{
		return _LoadAllCoursesFromDB();
	}

	/*static std::vector <clsCourse> getInstructorAllCoursesFromDB(std::string ID)
	{
		std::vector <clsCourse> vInstructorCourses;

		std::fstream coursesDB;
		coursesDB.open("DB/courses.txt", std::ios::in);

		if (coursesDB.is_open())
		{
			std::string line;
			while (getline(coursesDB, line))
			{

				clsCourse course = _ConvertRecordLineToObject(line);

				if (course.courseInstructor)
				{

				}
				vInstructorCourses.push_back(course);
			}

			coursesDB.close();
		}

		return vCourses;

	}*/

};

