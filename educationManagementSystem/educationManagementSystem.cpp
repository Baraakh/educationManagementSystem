#include <iostream>

#include"clsLoginScreen.h";

#include "clsCourse.h";

int main()
{

    clsCourse course = clsCourse::find("CS11");

    cout << "Course name = " << course.courseName << " Code = " << course.courseCode << " - Taught by Dr: " << course.courseInstructor;

    system("pause>0");
    return 0;
}
