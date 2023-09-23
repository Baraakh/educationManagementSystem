#include <iostream>

#include"clsLoginScreen.h";

#include "clsCourse.h";

int main()
{
    
    clsCourse newCourse = clsCourse::getAddNewCourseObject("CS112");
    newCourse.courseName = "Prog 2";
    newCourse.courseInstructor = "Morad";

    if (newCourse.save() == clsCourse::enResults::svSucceded)
    {
        cout << "The course had been created successfully thank you :-)" << endl;
    }
    else
    {
        cout << "Sorry :-(" << endl;
    }

    system("pause>0");
    return 0;
}
