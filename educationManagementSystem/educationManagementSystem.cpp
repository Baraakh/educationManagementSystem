#include <iostream>

#include"clsLoginScreen.h";

#include"clsDoctor.h";

void print(clsDoctor doctor)
{
	cout << "\nInfo:";
	cout << "\n___________________";
	cout << "\nFirstName: " << doctor.getId();
	cout << "\nEmail    : " << doctor.userName;
	cout << "\nPhone    : " << doctor.password;
	cout << "\nFirstName: " << doctor.firstName;
	cout << "\nLastName : " << doctor.lastName;
	cout << "\nFull Name: " << doctor.fullName();
	cout << "\nEmail    : " << doctor.email;
	cout << "\nPhone    : " << doctor.phone;
	cout << "\n___________________\n";
}

int main()
{

    //clsLoginScreen::showLoginScreen();

    clsDoctor doctor = clsDoctor::find("d001", "d001");

	print(doctor);

    return 0;
}
