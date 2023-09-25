#include <iostream>

#include"clsLoginScreen.h";

#include "clsDoctorMainScreen.h";

#include "clsStudent.h";

static void _PrintStudentInfo(clsStudent student)
{
	cout << "\nStudent Card:";
	cout << "\n___________________";
	cout << "\nstudent id   : " << student.getId();
	cout << "\nFirstName   : " << student.firstName;
	cout << "\nLastName    : " << student.lastName;
	cout << "\nFull Name   : " << student.fullName();
	cout << "\nEmail   : " << student.email;
	cout << "\nPhone   : " << student.phone;
	cout << "\nUserName   : " << student.userName;
	cout << "\nPassword   : " << student.password;
	cout << "\n___________________\n";
}

int main()
{

    system("pause>0");
    return 0;
}
