#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>

struct Birthday
{
	std::string name;
	std::tm date;
};

void enterBirthday(std::string& name);
int convertToDays(std::tm& tm);
void printBirthdays(std::vector<Birthday>& vec);
bool isLeap(int year);

std::vector <Birthday> Notebook;

int main()
{
  std::string name;
  do
  {
    system ("cls");
    std::cout << "Enter name: ";
    std::cin >> name;
    if (name != "end") 
      enterBirthday (name);
  }
  while (name != "end");
  
  system ("cls");
  std::time_t time = std::time (nullptr);
  std::tm local = *std::localtime (&time);

  std::vector <Birthday> nearestBirthdays;
  std::vector <Birthday> todayBirthdays;

  int currentDay = convertToDays (local);

  for (int i = 0;i < Notebook.size();++i)
  { 
	 int differenceDays;
	 if (isLeap(Notebook[i].date.tm_year + 1900) && Notebook[i].date.tm_mon > 1)
	 {
		 differenceDays = convertToDays(Notebook[i].date) - currentDay - 1;
	 }
	 else
	 {
		 differenceDays = convertToDays(Notebook[i].date) - currentDay; 
	 }
	 if (differenceDays == 0)
	 {
		 todayBirthdays.push_back(Notebook[i]);
	 }
	 else if (differenceDays > 0)
	 {
		 nearestBirthdays.push_back(Notebook[i]);
	 }
  }
  if (!todayBirthdays.empty())
  {
    std::cout << "Today birthdays:" << std::endl;
    printBirthdays (todayBirthdays);
    std::cout << std::endl;
  }

  if (!nearestBirthdays.empty())
  {
    std::cout << "Nearest birthdays:" << std::endl;
    printBirthdays (nearestBirthdays);
  }
}

void enterBirthday(std::string& name)
{
	Birthday person;
	std::time_t time = std::time(nullptr);
	std::tm local = *std::localtime(&time);
	person.date = local;

	person.name = name;
	std::cout << "Enter birthday on format YYYY/MM/DD: ";
	std::cin >> std::get_time(&person.date, "%Y/%m/%d");

	Notebook.push_back(person);
}

void printBirthdays(std::vector<Birthday>& vec)
{
	for (int i = 0;i < vec.size();++i)
	{
		std::cout << vec[i].name << " " << std::put_time(&vec[i].date, "%m/%d") << std::endl;
	}
}

int convertToDays(std::tm& tm)
{
	int allDays = 0;
	int day = tm.tm_mday;
	int mon = tm.tm_mon;
	int year = tm.tm_year + 1900;

	for (int i = 0; i < mon; ++i)
	{
		if (i == 3 || i == 5 || i == 8 || i == 10)
		{
			allDays += 30;
		}
		else
		{
			if (i == 1)
			{
				if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
				{
					allDays += 29;
				}
				else
				{
					allDays += 28;
				}
			}
			else
			{
				allDays += 31;
			}
		}
	}

	allDays += day;

	return allDays;
}

bool isLeap(int year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}