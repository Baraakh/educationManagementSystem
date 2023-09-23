#include <iostream>

#include"clsLoginScreen.h";

#include "clsCourse.h";

int main()
{
    

    clsCourse newCourse = clsCourse::getAddNewCourseObject("CS112");

    if (newCourse.deleteCourse())
    {
        cout << "The course had been deleted successfully thank you :-)" << endl;
    }
    else
    {
        cout << "Sorry :-(" << endl;
    }

    system("pause>0");
    return 0;
}
