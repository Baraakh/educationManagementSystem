#include <iostream>

#include"clsLoginScreen.h";

#include "clsDoctorMainScreen.h";

#include "clsStudent.h";

#include <vector>;

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

	clsStudent student = clsStudent::find("202210188");

	_PrintStudentInfo(student);

	std::vector <clsCourse> vStudentEnrolledCourses = student.getStudentEnrolledCourses();

	bool result = student.unRegisterFromCourse("CS601");

	if (result)
	{
		cout << "\nthe course had been delete from the student semster succussfully" << endl;
	}
	else
	{
		cout << "\nError" << endl;
	}

	std::vector <clsCourse> vStudentEnrolledCoursesAfterDeleting = student.getStudentEnrolledCourses();

	/*std::vector <clsCourse> vStudentEnrolledCourses = student.getStudentEnrolledCourses();
	std::vector <clsCourse> vStudentNotEnrolledCourses = student.getStudentNotEnrolledCourses();*/

	//bool result = student.isStudentEnrolledInCourse("CS111");
	//

	//if (result)
	//{
	//	cout << "\nYes he is enrolled" << endl;
	//}
	//else
	//{
	//	cout << "\nNo he is not enrolled" << endl;
	//}

	/*bool result = student.registerInCourse("CS111");

	if (result)
	{
		cout << "\nCourse was registerd succussfully" << endl;
	}
	else
	{
		cout << "\nError" << endl;
	}*/

    system("pause>0");
    return 0;
}
