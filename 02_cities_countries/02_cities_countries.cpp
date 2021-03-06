/*
Завдання  2.
Есть файл с данными о названиях стран и городов. Реализуйте программу, которая позволит
загружать данные из файла,+
сохранять данные в файл,+
искать города конкретной  страны,+
заменять название города,+
добавлять города и страны,+
удалять города и страны,+
подсчитывать количество городов,+
отображать список стран.+
 При программировании  приложения обязательно используйте механизм лямбд.

*/

//#include "stdafx.h"
#include "pch.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>

	using namespace std;


	class Directory
	{
	private:

		multimap<string, string> geo;

	public:

		// добавлять города и страны
		void add()
		{
			string country, city;
			cout << "\tAdd\nEnter country: ";
			cin >> country;
			cout << "Enter City: ";
			cin >> city;
			
			geo.insert({ country, city });
			save();
		}
		
		// удалять города и страны,
		void del()
		{
			//видаляє лише країни
			string delElem;
			cout << "\nEnter country or city for delete:\t";
			cin >> delElem;
			geo.erase(delElem);

			//проходиться по містам
			for (auto it = geo.begin(); it != geo.end();)
				if (it->second == delElem)
				{
					it = geo.erase(it);
				}
				else
					++it;
			save();
		}
		
		// сохранять данные в файл
		void save()
		{
			ofstream file("geo.txt");
			if (!file)
				return;
			for (auto it = geo.begin(); it != geo.end(); ++it)
				file << it->first << endl << it->second << endl;
			file.close();
		}
		
		// загружать данные из файла
		void load()
		{
			ifstream file("geo.txt");
			if (!file)
				return;
			string country, city;
			while (file >> country >> city, !file.eof())
			{
			
				geo.insert({ country, city });
			}
			file.close();
		}

		// отображать весь справочник
		void printAll()
		{
			cout << "Country\t\t-\tCity\n- - - - - - - - - - - - - - - - - -\n";
			for (auto it = geo.begin(); it != geo.end(); ++it)
				cout << it->first << "\t\t-\t" << it->second << endl;
		}

		// отображать список стран
		void printCountry()
		{
			for (auto it = geo.begin(); it != geo.end(); ++it)
				cout << it->first << endl;
		}

		// подсчитывать количество городов
		int getCount()
		{
			int count = 0;
			for (auto it = geo.begin(); it != geo.end(); ++it)
				++count;
			return count;
		}

		 // искать города конкретной  страны
		void findCountry(string country)
		{
			int count = 0;
			cout << "\n\tFinding " << country << endl;

			/* виводить лише перший шуканий запис
			auto it = geo.find(country);
			if (it != geo.end())
			{
				cout << it->second << endl;
			}
			*/

			for (auto it = geo.begin(); it != geo.end(); ++it)
				if (it->first == country)
				{
					cout << it->first << "\t\t-\t" << it->second << endl;
					++count;
				}
			if (count == 0)
				cout << "\nDon't find cities of counrty " << country << endl;
				
		}

		// заменять название города
		void replaceCity()
		{
			string oldName, newName;
			cout << "\n\tReplace name of city\nEnter name of city which you want replace:\t";
			cin >> oldName;
			for (auto it = geo.begin(); it != geo.end(); ++it)
				if (it->second == oldName)
				{
					cout << it->first << "\t\t-\t" << it->second << endl;
					cout << "Enter new name for city:\t";
					cin >> newName;
					it->second = newName;
					cout << it->first << "\t\t-\t" << it->second << endl;
					save();
					geo.emplace(oldName, newName);
					return;
				}
			cout << "Not found city " << oldName << endl;
		}

	};

int main()
{
	Directory d;
	d.load();
	d.printAll();
	//d.printCountry();
	//d.add();
	//d.printAll();
	cout << "\nQ-ty cities:\t" << d.getCount() << endl << endl;
	d.findCountry("Ukraine");
	//d.replaceCity();
	//d.del();


	cout << endl;
	system("pause");
	return 0;
}