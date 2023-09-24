#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "clsCourse.h";
#include "clsScreen.h";

class clsCourseListScreen : protected clsScreen
{
private:

    static void PrintCourseRecordLine(clsCourse course)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << course.getCourseCode();
        cout << "| " << setw(35) << left << course.courseName;
        cout << "| " << setw(20) << left << course.courseInstructor;
    }

public:

    static void showCourseList()
    {


        vector <clsCourse> vCourse = clsCourse::getAllCoursesFromDB();
        string Title = "Course List Screen";
        string SubTitle = "(" + to_string(vCourse.size()) + ") Course(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Course Code";
        cout << "| " << left << setw(35) << "Course Name";
        cout << "| " << left << setw(12) << "Course Instructor";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCourse.size() == 0)
            cout << "\t\t\t\tNo Courses Available In the System!";
        else

            for (clsCourse& course : vCourse)
            {

                PrintCourseRecordLine(course);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

