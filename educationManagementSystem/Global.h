#pragma once

#include <iostream>
#include "clsStudent.h";
#include "clsDoctor.h";
#include "clsPerson.h";

clsStudent currentStudent = clsStudent::find("", "");
clsDoctor currentDoctor = clsDoctor::find("", "");

// I chose the currentStudent randomly for temporary time
clsPerson* currentPerson = &currentStudent;