#pragma once

#include <iostream>
#include <string>
#include "clsInputValidate.h";

#include "clsAssigment.h";
#include "clsCourse.h";

#include "clsScreen.h";


class clsCreateAssigmentScreen : protected clsScreen
{
private:
	 
	static clsAssigment _ReadAssigmentInfoAndCreate(std::string& courseId)
	{
		std::string assigmentId = "";

		std::cout << "\nPlease Enter Assigment Code : ";
		assigmentId = clsInputValidate::ReadString();

		while (clsAssigment::isAssigmentExist(assigmentId))
		{
			std::cout << "\nAssigment Id is Already Used, Choose another Course Code : ";
			assigmentId = clsInputValidate::ReadString();
		}

		short assigmentMark = 0;

		std::cout << "\nEnter Assigment : ";
		assigmentMark = clsInputValidate::ReadNumber<short>();

		while (assigmentMark == 5 || assigmentMark == 10 || assigmentMark == 15)
		{
			std::cout << "\nYou only able to 5, 10, 15 for assignment: ";
			assigmentMark = clsInputValidate::ReadNumber<short>();
		}

		return clsAssigment::getAddNewAssigmentObject(assigmentId, courseId, assigmentMark);

	}

	static void _PrintAssigmentInfo(clsAssigment assigment)
	{
		cout << "\nAssigment Card:";
		cout << "\n___________________";
		cout << "\nAssignment ID   : " << assigment.assigmentId();
		cout << "\nCourse ID	   : " << assigment.courseCode();
		cout << "\nAssignment Mark : " << assigment.assigmentMark;
		cout << "\n___________________\n";
	}

public:

	static void showCreateAssigmentScreen(std::string& courseId)
	{
		_DrawScreenHeader("Create New Assignment screen");

		clsAssigment newAssigment = _ReadAssigmentInfoAndCreate(courseId);

		clsAssigment::enResults saveResult = newAssigment.save();

		switch (saveResult)
		{
		case clsAssigment::enResults::svSucceded:
		{
			cout << "\nAssignment had been Added successfully :-)\n";
			_PrintAssigmentInfo(newAssigment);
			break;
		}
		case clsAssigment::enResults::svFailedEmptyObject:
		{
			cout << "\nError assignment was not saved because it's Empty\n";
			break;
		}
		case clsAssigment::enResults::svFaildUnableToSave:
		{
			cout << "\nError Assignment was not saved because course code number is used!\n";
			break;
		}
		default:
		{
			cout << "\nError in the Assignment inputs!\n";
			break;
		}
		}
	}

};

