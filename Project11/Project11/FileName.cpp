#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#pragma comment(lib, "urlmon.lib")
using namespace std;

int main()
{
	setlocale(0, "ru");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	// the URL to download from 
	//string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";
	std::cout << "Enter date: ";
	char idate[15];
	std::cin >> idate;
	std::cout << "Enter currency: ";
	char currency[15];
	std::cin >> currency;

	char resurl[1024];

	sprintf_s(resurl, "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode=%s&date=%s&json", currency, idate);
	string srcURL = resurl;
	std::cout << srcURL;
	// the destination file 
	string destFile = "file.txt";
	//URLDownloadToFile returns S_OK on success 
	if (S_OK == URLDownloadToFileA(NULL, srcURL.c_str(), destFile.c_str(), 0, NULL))
	{
		cout << "Saved to " << destFile << "\n";
	}
	else cout << "Fail!\n";

	
	

	string filestring;
	ifstream file(destFile);
	for (int i = 0; i < 3; i++)
	{
		getline(file, filestring);
	}

	int rate = filestring.find("rate");
	int cc = filestring.find("cc");
	int date = filestring.find("exchangedate");
	int IArray[3] = { rate, cc, date };
	wstring Array[3];

	wchar_t* res;

	int temp = 0;
	int c;

	for (int i = 0; i < 3; i++)
	{
		res = new wchar_t[15];
		temp = 0;
		c = 0;
		for (int j = 0; j < 30; j++)
		{
			if (filestring[IArray[i]] == '"' && temp == 0 || filestring[IArray[i]] == ':' && temp == 0)
			{
				temp = 1;
			}
			else if (filestring[IArray[i]] != '"' && filestring[IArray[i]] != ':' && filestring[IArray[i]] != ',' && temp >= 1 && temp <= 2)
			{
				if (filestring[IArray[i]] != '"' && filestring[IArray[i]] != ':' && filestring[IArray[i]] != ',')
				{
					res[c] = filestring[IArray[i]];
					temp = 2;
					c++;
				}
			}
			else if (temp == 2)
			{
				break;
			}

			IArray[i]++;
		}
		res[c] = '\0';
		Array[i] = res;
	}

	std::cout << '\n';
	std::wcout << "Date: " << Array[2] << ", Currency - " << Array[1] << ", 1$ = " << Array[0] << " UAH" << '\n';




	/*
	1. С клавиатуры вводим следующие данные:
	  дата
	  Валюта
	  Вывести актуальную информацию!
	  формат вывода - Дата: 19.03.2024г, Валюта - USD, 1$ = 38.9744 грн.

	*/


}