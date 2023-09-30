#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "clsString.h";
#include "clsCourse.h";

class clsAssigment
{
private:

	enum enMode {EmptyMode = 1, UpdateMode = 2, AddNewMode = 3};
	
	enMode _Mode;
	std::string _AssigmentID, _CourseCode;
	short _AssigmentMark;
	bool _MarkedForDelete = false;

	static clsAssigment _ConvertRecordLineToObject(std::string record)
	{
		std::vector <std::string> vRecordData = clsString::Split(record, "#//#");

		return clsAssigment(enMode::UpdateMode, vRecordData[0], vRecordData[1], stoi(vRecordData[2]));
	}
	static std::string _ConvertObjectToRecordLine(clsAssigment assigment, std::string delim = "#//#")
	{
		std::string recordLine = "";

		recordLine += assigment.assigmentId() + delim;
		recordLine += assigment.courseCode() + delim;
		recordLine += to_string(assigment.assigmentMark);

		return recordLine;
	}

	static std::vector <clsAssigment> _LoadAllAssigmentsFromDB()
	{
		std::vector <clsAssigment> vAssigments;

		std::fstream assigmentsDB;
		assigmentsDB.open("DB/assigments.txt", std::ios::in);

		if (assigmentsDB.is_open())
		{
			std::string line;
			while (getline(assigmentsDB, line))
			{
				clsAssigment assigment = _ConvertRecordLineToObject(line);
				vAssigments.push_back(assigment);
			}

			assigmentsDB.close();
		}

		return vAssigments;
	}
	static bool _AddAssigmentDataLineToDB(std::string stDataLine)
	{
		std::fstream assigmentsDB;
		assigmentsDB.open("DB/assigments.txt", std::ios::out | std::ios::app);

		if (assigmentsDB.is_open())
		{
			assigmentsDB << stDataLine << endl;
			assigmentsDB.close();
			return true;
		}

		return false;
	}

	bool _SaveAssigmentDateToDB(std::vector <clsAssigment>& vAssigment)
	{
		std::fstream assigmentsDB;
		assigmentsDB.open("DB/assigments.txt", std::ios::out);

		if (assigmentsDB.is_open())
		{
			std::string record;
			for (clsAssigment& assigment : vAssigment)
			{
				if (!assigment._MarkedForDelete)
				{
					record = _ConvertObjectToRecordLine(assigment);
					assigmentsDB << record << endl;
				}
			}

			assigmentsDB.close();
			return true;
		}

		return false;
	}

	bool _Update()
	{
		std::vector <clsAssigment> vAssigments = _LoadAllAssigmentsFromDB();

		for (clsAssigment& assigment : vAssigments)
		{
			if (assigment.assigmentId() == _AssigmentID)
			{
				assigment = *this;
				break;
			}
		}

		return _SaveAssigmentDateToDB(vAssigments);
	}

	bool _AddNew()
	{
		return _AddAssigmentDataLineToDB(_ConvertObjectToRecordLine(*this));
	}

	static clsAssigment _GetEmptyAssigmentObject()
	{
		return clsAssigment(enMode::EmptyMode, "", "", 0);
	}

public:

	clsAssigment(enMode mode, std::string assigmentID, std::string courseCode, short assigmentMark)
	{
		_AssigmentID = assigmentID;
		_CourseCode = courseCode;
		_AssigmentMark = assigmentMark;
	}

	// read-only properties

	std::string assigmentId()
	{
		return _AssigmentID;
	}

	std::string courseCode()
	{
		return _CourseCode;
	}

	// read and write

	short getAssigmentMark()
	{
		return _AssigmentMark;
	}

	void setAssigmentMark(short assigmentMark)
	{
		// it's not fully functional

		_AssigmentMark = assigmentMark;
	}

	__declspec(property(get = getAssigmentMark, put = getAssigmentMark)) short assigmentMark;

	// methods 

	//find methods

	static clsAssigment find(std::string assigmentID)
	{
		std::fstream assigmentsDB;
		assigmentsDB.open("DB/assigments.txt", std::ios::in); //read only

		if (assigmentsDB.is_open())
		{
			std::string line;

			while (std::getline(assigmentsDB, line))
			{
				clsAssigment assigment = _ConvertRecordLineToObject(line);

				if (assigment.assigmentId() == assigmentID)
				{
					assigmentsDB.close();
					return assigment;
				}
			}

			assigmentsDB.close();
		}

		return _GetEmptyAssigmentObject();
	}

	// create methods

	static clsAssigment getAddNewAssigmentObject(std::string assigmentID, std::string courseCode, short assigmentMark)
	{
		return clsAssigment(enMode::AddNewMode, assigmentID, courseCode, assigmentMark);
	}

	bool isEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	enum enResults { svFailedEmptyObject = 0, svSucceded = 1, svFailedAssigmentExists = 2, svFaildCourseNotExists = 3 ,svFaildUnableToSave = 4 };

	enResults save()
	{
		switch (_Mode)
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
			if (clsAssigment::isAssigmentExist(_AssigmentID))
			{
				return enResults::svFailedAssigmentExists;
			}
			else
			{
				if (!clsCourse::isCourseExist(_CourseCode))
				{
					return enResults::svFaildCourseNotExists;
				}

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


	// update methods
	static bool isAssigmentExist(std::string assigmentID)
	{
		clsAssigment assigment = clsAssigment::find(assigmentID);

		return (!assigment.isEmpty());
	}

	// delete methods
	// get all assigments
	bool deleteCourse()
	{
		if (isEmpty() || _Mode == enMode::AddNewMode) return false;

		std::vector <clsAssigment> vAssigments = _LoadAllAssigmentsFromDB();

		for (clsAssigment& assigment : vAssigments)
		{
			if (assigment.assigmentId() == _AssigmentID)
			{
				assigment._MarkedForDelete = true;
				break;
			}
		}

		if (_SaveAssigmentDateToDB(vAssigments))
		{
			*this = _GetEmptyAssigmentObject();
			return true;
		}

		return false;
	}

	static std::vector <clsAssigment> getAllAssigmentsFromDB()
	{
		return _LoadAllAssigmentsFromDB();
	}

	static std::vector <clsAssigment> getCourseAllAssigmentsFromDB(std::string courseID)
	{
		std::vector <clsAssigment> vCourseAssigments;

		std::fstream assigmentsDB;
		assigmentsDB.open("DB/assigments.txt", std::ios::in);

		if (assigmentsDB.is_open())
		{
			std::string line;
			while (getline(assigmentsDB, line))
			{
				clsAssigment assigment = _ConvertRecordLineToObject(line);

				if (assigment.courseCode() == courseID)
				{
					vCourseAssigments.push_back(assigment);
				}
			}

			assigmentsDB.close();
		}

		return vCourseAssigments;
	}

	



};

