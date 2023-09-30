#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsAssigment.h";

#include "clsScreen.h";

class clsListDoctorAssigmentScreen : protected clsScreen
{
private:

    static void _PrintAssigmentRecordLine(clsAssigment assigment)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << assigment.assigmentId();
        cout << "| " << setw(12) << left << assigment.courseCode();
        cout << "| " << setw(8) << left << assigment.assigmentMark;
    }

public:

	static void showListDoctorAssigmentScreen(std::string courseId)
	{
        vector <clsAssigment> vAssigment = clsAssigment::getCourseAllAssigmentsFromDB(courseId);
        string Title = "Assignments List Screen";
        string SubTitle = "(" + to_string(vAssigment.size()) + ") Assignment(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Assignment Id";
        cout << "| " << left << setw(12) << "Course Code";
        cout << "| " << left << setw(8) << "Assigment mark";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vAssigment.size() == 0)
            cout << "\t\t\t\t There is no Assignments.";
        else

            for (clsAssigment& assigment : vAssigment)
            {

                _PrintAssigmentRecordLine(assigment);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

