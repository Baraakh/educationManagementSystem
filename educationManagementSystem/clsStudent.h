#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "clsString.h";

#include "clsPerson.h";


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


};

