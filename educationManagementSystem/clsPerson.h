#pragma once

#include <iostream>
#include <string>

class clsPerson
{
private:

	std::string _FirstName, _LastName, _Email, _Phone;

public:

	clsPerson(std::string firstName, std::string lastName, std::string email, std::string phone)
	{
		_FirstName = firstName;
		_LastName = lastName;
		_Email = email;
		_Phone = phone;
	}

	void setFirstName(std::string firstName)
	{
		_FirstName = firstName;
	}

	std::string getFirstName()
	{
		return _FirstName;
	}

	__declspec(property(get = getFirstName, put = setFirstName)) std::string firstName;

	void setLastName(std::string lastName)
	{
		_LastName = lastName;
	}

	std::string getLastName()
	{
		return _LastName;
	}

	__declspec(property(get = getLastName, put = setLastName)) std::string lastName;

	void setEmail(std::string email)
	{
		_Email = email;
	}

	std::string getEmail()
	{
		return _Email;
	}

	__declspec(property(get = getEmail, put = setEmail)) std::string email;

	void setPhone(std::string phone)
	{
		_Phone = phone;
	}

	std::string getPhone()
	{
		return _Phone;
	}

	__declspec(property(get = getPhone, put = setPhone)) std::string phone;

	std::string fullName()
	{
		return _FirstName + " " + _LastName;
	}
 
};

