#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "clsPerson.h";

#include "clsString.h";

class clsDoctor : public clsPerson
{
private:
	
	enum enMode {EmptyMode = 0, UpdateMode = 1};

	enMode _Mode;
	std::string _Id, _UserName, _Password;

	static clsDoctor _ConvertRecordLineToObject(std::string record)
	{
		std::vector <std::string> vRecordData = clsString::Split(record, "#//#");

		return clsDoctor(enMode::UpdateMode, vRecordData[0], vRecordData[1], vRecordData[2], vRecordData[3], vRecordData[4], vRecordData[5], vRecordData[6]);
	}

	static clsDoctor _GetEmptyDoctorObject()
	{
		return clsDoctor(enMode::EmptyMode, "", "", "", "", "", "", "");
	}

public:

	clsDoctor(enMode mode, std::string id, std::string firstName, std::string lastName, std::string email, std::string phone, std::string userName, std::string password) : 
		clsPerson (firstName, lastName, email, phone)
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

	static clsDoctor find(std::string id)
	{
		std::fstream doctorsDB;

		doctorsDB.open("DB/doctors.txt", std::ios::in); //read mode

		if (doctorsDB.is_open())
		{
			std::string line;
			while (std::getline(doctorsDB, line))
			{
				clsDoctor doctor = _ConvertRecordLineToObject(line);

				if (doctor.getId() == id)
				{
					doctorsDB.close();
					return doctor;
				}
			}

			doctorsDB.close();
		}

		return _GetEmptyDoctorObject();

	}

	static clsDoctor find(std::string userName, std::string password)
	{
		std::fstream doctorsDB;

		doctorsDB.open("DB/doctors.txt", std::ios::in); //read mode

		if (doctorsDB.is_open())
		{
			std::string line;
			while (std::getline(doctorsDB, line))
			{
				clsDoctor doctor = _ConvertRecordLineToObject(line);

				if (doctor.userName == userName && doctor.password == password)
				{
					doctorsDB.close();
					return doctor;
				}
			}

			doctorsDB.close();
		}

		return _GetEmptyDoctorObject();

	}

	// ================= creat isDoctorExist method later ======================== 

};

