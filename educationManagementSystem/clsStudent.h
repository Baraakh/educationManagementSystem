#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "clsString.h";

#include "clsPerson.h";

#include "clsCourse.h";

class clsStudent : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1};

	enMode _Mode;
	std::string _Id, _UserName, _Password;

	static clsStudent _ConvertRecordLineToObject(std::string record)
	{
		std::vector <std::string> vRecordData = clsString::Split(record, "#//#");

		return clsStudent(enMode::UpdateMode, vRecordData[0], vRecordData[1], vRecordData[2], vRecordData[3], vRecordData[4], vRecordData[5], vRecordData[6]);
	}

	bool _AddNewCourseForStudent(std::string newStudentCourse)
	{
		std::fstream DBStudentsAndCourses;
		DBStudentsAndCourses.open("DB/studentsAndCourses.txt", std::ios::out | std::ios::app);

		if (DBStudentsAndCourses.is_open())
		{
			DBStudentsAndCourses << newStudentCourse << endl;
			DBStudentsAndCourses.close();
			return true;
		}

		return false;
	}

	struct stStudentAndCourse
	{
		bool markedForDelete = false;
		std::string studentId, courseCode;
	};

	stStudentAndCourse _ConvertStudentAndCourseRecordToStruct(std::string record)
	{
		std::vector <string> vStudentAndCourse = clsString::Split(record, "#//#");

		stStudentAndCourse studentAndCourse;
		
		studentAndCourse.studentId = vStudentAndCourse[0];
		studentAndCourse.courseCode = vStudentAndCourse[1];

		return studentAndCourse;
	}
	
	std::string _ConvertStudentAndCourseStructToRecordLine(stStudentAndCourse& vStudentsCoursesRelations)
	{
		std::string recordLine = "";

		recordLine += vStudentsCoursesRelations.studentId + "#//#";
		recordLine += vStudentsCoursesRelations.courseCode;

		return recordLine;
	}

	std::vector <clsCourse> _getAllCoursesStudentIsEnrolledWith()
	{
		
		std::vector <clsCourse> vStudentEnrolledCourses;

		std::fstream DBStudentsAndCourses;
		DBStudentsAndCourses.open("DB/studentsAndCourses.txt", std::ios::in);
		
		if (DBStudentsAndCourses.is_open())
		{
			std::string line;
			while (getline(DBStudentsAndCourses, line))
			{
				stStudentAndCourse studentAndCourse = _ConvertStudentAndCourseRecordToStruct(line);

				if (studentAndCourse.studentId == _Id)
				{
					vStudentEnrolledCourses.push_back(clsCourse::find(studentAndCourse.courseCode));
				}
			}

			DBStudentsAndCourses.close();
		}

		return vStudentEnrolledCourses;

	}

	std::vector <stStudentAndCourse> _LoadAllStudentCoursesRelationsFromDB()
	{
		std::vector <stStudentAndCourse> vStudentsCoursesRelations;

		std::fstream DBStudentsAndCourses;
		DBStudentsAndCourses.open("DB/studentsAndCourses.txt", std::ios::in);

		if (DBStudentsAndCourses.is_open())
		{
			std::string line;
			while (getline(DBStudentsAndCourses, line))
			{
				 stStudentAndCourse studentAndCourseRelation = _ConvertStudentAndCourseRecordToStruct(line);
				 vStudentsCoursesRelations.push_back(studentAndCourseRelation);
			}

			DBStudentsAndCourses.close();
		}

		return vStudentsCoursesRelations;
	}

	bool _MarkTheStudentCourseRelationFromDeleting(std::vector <stStudentAndCourse>& vStudentCoursesRelations, std::string courseCode)
	{
		for (stStudentAndCourse& studentCourseRelation : vStudentCoursesRelations)
		{
			if (studentCourseRelation.studentId == _Id && studentCourseRelation.courseCode == courseCode)
			{
				studentCourseRelation.markedForDelete = true;
				return true;
			}
		}

		return false;
	}

	bool _SaveStudentsAndCoursesRelationDateToDB(std::vector <stStudentAndCourse>& vStudentsCoursesRelations)
	{
		std::fstream DBStudentsAndCourses;
		DBStudentsAndCourses.open("DB/studentsAndCourses.txt", std::ios::out);

		if (DBStudentsAndCourses.is_open())
		{
			std::string record;
			for (stStudentAndCourse& studentAndCourseRelation : vStudentsCoursesRelations)
			{
				if (!studentAndCourseRelation.markedForDelete)
				{
					record = _ConvertStudentAndCourseStructToRecordLine(studentAndCourseRelation);
					DBStudentsAndCourses << record << endl;
				}
			}

			DBStudentsAndCourses.close();
			return true;
		}

		return false;
	}

	static clsStudent _GetEmptyDoctorObject()
	{
		return clsStudent(enMode::EmptyMode, "", "", "", "", "", "", "");
	}

public:

	clsStudent(enMode mode, std::string id, std::string firstName, std::string lastName, std::string email, std::string phone, std::string userName, std::string password) :
		clsPerson(firstName, lastName, email, phone)
	{
		_Mode = mode;
		_Id = id;
		_UserName = userName;
		_Password = password;
	}

	// read only
	std::string getId()
	{
		return _Id;
	}

	void setUserName(std::string userName)
	{
		_UserName = userName;
	}

	std::string getUserName()
	{
		return _UserName;
	}

	__declspec(property(get = getUserName, put = setUserName)) std::string userName;

	void setPassword(std::string password)
	{
		_Password = password;
	}

	std::string getPassword()
	{
		return _Password;
	}

	__declspec(property(get = getPassword, put = setPassword)) std::string password;

	static clsStudent find(std::string id)
	{
		std::fstream studentsDB;

		studentsDB.open("DB/students.txt", std::ios::in); //read mode

		if (studentsDB.is_open())
		{
			std::string line;
			while (std::getline(studentsDB, line))
			{
				clsStudent student = _ConvertRecordLineToObject(line);

				if (student.getId() == id)
				{
					studentsDB.close();
					return student;
				}
			}

			studentsDB.close();
		}

		return _GetEmptyDoctorObject();

	}

	static clsStudent find(std::string userName, std::string password)
	{
		std::fstream studentsDB;

		studentsDB.open("DB/students.txt", std::ios::in); //read mode

		if (studentsDB.is_open())
		{
			std::string line;
			while (std::getline(studentsDB, line))
			{
				clsStudent student = _ConvertRecordLineToObject(line);

				if (student.userName == userName && student.password == password)
				{
					studentsDB.close();
					return student;
				}
			}

			studentsDB.close();
		}

		return _GetEmptyDoctorObject();

	}

	bool isEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static bool isDoctorExist(std::string id)
	{
		clsStudent doctor = clsStudent::find(id);
		return (!doctor.isEmpty());
	}

	// =========== student courses =============

	bool registerInCourse(std::string courseCode)
	{
		// == Note. must check if the student is not already enrolled in the course.
		if (_Mode == enMode::EmptyMode || !(clsCourse::isCourseExist(courseCode) || isStudentEnrolledInCourse(courseCode))) return false;

		clsCourse course = clsCourse::find(courseCode);

		std::string studentNewCourseRecord = "";
		studentNewCourseRecord += _Id + "#//#";
		studentNewCourseRecord += course.getCourseCode();

		return _AddNewCourseForStudent(studentNewCourseRecord);

	}

	// == last task 
	bool unRegisterFromCourse(std::string courseCode)
	{
		// == Note. must check if the student is already enrolled in the course.
		if (_Mode == enMode::EmptyMode || !(clsCourse::isCourseExist(courseCode) || !(isStudentEnrolledInCourse(courseCode)))) return false;

		// pull all the data 
		std::vector <stStudentAndCourse> vStudentCoursesRelations = _LoadAllStudentCoursesRelationsFromDB();
		
		// find the course 
		// markForDelete = true

		if (!_MarkTheStudentCourseRelationFromDeleting(vStudentCoursesRelations, courseCode)) return false;

		// save the new data

		return _SaveStudentsAndCoursesRelationDateToDB(vStudentCoursesRelations);

	}

	std::vector <clsCourse> getStudentEnrolledCourses()
	{
		std::vector <clsCourse> studentCourses;

		if (_Mode == enMode::EmptyMode) return studentCourses;

		studentCourses = _getAllCoursesStudentIsEnrolledWith();

		return studentCourses;
	}

	std::vector <clsCourse> getStudentNotEnrolledCourses()
	{
		std::vector <clsCourse> vNotStudentCourses;
		std::vector <clsCourse> vAllCourses;

		if (_Mode == enMode::EmptyMode) return vNotStudentCourses;

		vAllCourses = clsCourse::getAllCoursesFromDB();

		for (clsCourse& course : vAllCourses)
		{
			if (!(isStudentEnrolledInCourse(course.getCourseCode())))
			{
				vNotStudentCourses.push_back(course);
			}
		}

		return vNotStudentCourses;
	}
	
	bool isStudentEnrolledInCourse(std::string courseCode)
	{
		if (_Mode == enMode::EmptyMode || !(clsCourse::isCourseExist(courseCode))) return false;

		std::vector <clsCourse> vStudentCourses = getStudentEnrolledCourses();

		for (clsCourse& course : vStudentCourses)
		{
			if (course.getCourseCode() == courseCode) return true;	
		}

		return false;
	}

};

