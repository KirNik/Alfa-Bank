
#include "Core.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::cin;

void GetWords(TCore** /*core*/);
void GetMap(TCore** /*core*/);

int main()
{
	setlocale(LC_ALL, "rus");
	TCore* pCore = new TCore();

	GetWords(&pCore);
	GetMap(&pCore);

	cout << endl;
	cout << "Слова:" << endl;
	cout << pCore->BegWord() << endl;
	cout << pCore->EndWord() << endl;

	cout << endl;
	cout << "Словарь:" << endl;
	TDStringVector StringVct = pCore->GetList();

	for (size_t i = 0; i < StringVct.size(); ++i)
		cout << StringVct[i] << endl;

	cout << endl;
	cout << "Результат:" << endl;
	pCore->Find();

	system("pause");
	return 0;
}

void GetWords(TCore** pCore)
{
	std::ifstream fFile;
	std::string strWordsFileName;

	while (!fFile.is_open())
	{
		static bool bFirstOpen = true;

		system("cls");							
		cout << (bFirstOpen ? "Введите имя файла с начальным и конечным словами: "
							: "Неверное имя файла\nВведите новое имя файла: ");
		bFirstOpen = false;

		getline(cin, strWordsFileName);
		fFile.open(strWordsFileName);
	}

	std::string temp;
	while (getline(fFile, temp))
	{
		static int count = 0;
		switch (count)
		{
			case 0:
				(*pCore)->SetWord(BEGIN, temp);
				break;
			case 1:
				(*pCore)->SetWord(END, temp);
				break;
			default:
				return;
		}

		++count;
	}

}

void GetMap(TCore** pCore)
{
	std::ifstream fFile;
	std::string strMapFileName;
	TDStringVector StringVct;

	while (!fFile.is_open())
	{
		static bool bFirstOpen = true;

		system("cls");							
		cout << (bFirstOpen ? "Введите имя файла, содержащего словарь: "
							: "Неверное имя файла\nВведите новое имя файла: ");
		bFirstOpen = false;

		getline(cin, strMapFileName);
		fFile.open(strMapFileName);
	}

	std::string temp;
	while (getline(fFile, temp))
		StringVct.push_back(temp);

	(*pCore)->SetMap(StringVct);
}
