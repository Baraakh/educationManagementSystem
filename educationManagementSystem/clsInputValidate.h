#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "clsString.h"
#include "clsDate.h"

class clsInputValidate
{

public:

	template <typename T>

	static T IsNumberBetween(T number, T from, T to)
	{
		return (number >= from && number <= to);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if (clsDate::IsDate1AfterDate2(From, To))
		{
			clsDate::SwapDates(From, To);
		}

		return !((clsDate::IsDate1BeforeDate2(Date, From)) || (clsDate::IsDate1AfterDate2(Date, To)));
	}

	template <typename T>

	static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		T Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	template <typename T>

	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		T Number = ReadNumber<T>();

		while (!IsNumberBetween<T>(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>();
		}
		return Number;
	}

	static int ReadListNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadNumber<int>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << setw(37) << left << "" << ErrorMessage;
			Number = ReadNumber<int>();
		}
		return Number;
	}

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}

	static bool ReadYesNoQuestion()
	{
		char answer;

		cin >> answer;

		return (tolower(answer) == 'y');
	}

	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

};

;

