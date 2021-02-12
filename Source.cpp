/* 
Name: Christine Pavlik
Date: May 1,2020
Discription: This program tracks how much water the users drinks over the course of time up to a year. 
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;
//the functions in this program. The first two are overloaded
double usersInfo(double [100][365], int);
double usersInfo();
int enterWater(double [100][365], int, int);
void waterChart(double[100][365], int);
int newDay(int);
void information();
int main()
{
	
	int choice;
	int k = 0;
	int day = 0;
	int sum = 0;
	double userWeightVar = 0;
	double foundTodaysGoals = 0;
	//here is the required 2D array
	double goalsArray[100][365];
	cout << "Type in 1 to figure out how much water to drink today";
	cout << "\nType in 2 to adjust how much you weigh";
	cout << "\nType in 3 to add to your total water consumption for today";
	cout << "\nType in 4 to start a new day";
	cout << "\nType in 5 see all the water you drank so far ";
	cout << "\nType in 6 get see the URL for the source of this information.";
	cout << "\nType anything else to end the program: ";
	cin >> choice;
	do
	{
		switch (choice)
		{
		case 1:
			if (userWeightVar == 0)
			{
				userWeightVar = usersInfo();
				foundTodaysGoals = usersInfo(goalsArray, day);
			}
			else {
				foundTodaysGoals = usersInfo(goalsArray, day);
			}
			break;
		case 2: userWeightVar = usersInfo();
			break;
		case 3:
			//this includes the required nested if statements
			//makeing sure the user has found todays goals and weight
			if (foundTodaysGoals == 0)
		{
			if (userWeightVar == 0)
			{
				userWeightVar = usersInfo();
				foundTodaysGoals = usersInfo(goalsArray, day);
			}
			else {
				foundTodaysGoals = usersInfo(goalsArray, day);
			}
		}
			//the sum is the water drunken for the day
			sum = enterWater(goalsArray, day, sum);
			break;
		case 4:
			//making sure the user entered in the right data
			if (sum == 0)
			{
				if (foundTodaysGoals == 0)
				{
					if (userWeightVar == 0)
					{
						userWeightVar = usersInfo();
						foundTodaysGoals = usersInfo(goalsArray, day);
					}
					else {
						foundTodaysGoals = usersInfo(goalsArray, day);
					}
				}
				sum = enterWater(goalsArray, day, sum);
			}
			day = newDay(day);
			foundTodaysGoals = 0;
			sum = 0;
			break;
		case 5:
			//the if statment is so we have all the data
			if (foundTodaysGoals == 0)
			{
				if (userWeightVar == 0)
				{
					userWeightVar = usersInfo();
					foundTodaysGoals = usersInfo(goalsArray, day);
				}
				else {
					foundTodaysGoals = usersInfo(goalsArray, day);
				}
			}
			if (sum == 0)
			{
				goalsArray[1][day] = 0;
			}
			waterChart(goalsArray, day);
			break;
		case 6: information();
			break;
		default: exit(0);
		}
		cout << "\n\nType in 1 to figure out how much water to drink today";
		cout << "\nType in 2 to adjust how much you weigh";
		cout << "\nType in 3 to add to your total water consumption for today";
		cout << "\nType in 4 to start a new day";
		cout << "\nType in 5 see all the water you drank so far";
		cout << "\nType in 6 get see the URL for the source for this information.";
		cout << "\nType anything else to end the program: ";
		cin >> choice;
	}while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6);

	
	return 0;
}
// this function inputs the users weight and outputs the water they should be drinking
double usersInfo(double goalsArray [100][365], int day)
{
	double userWeightVar = 0;
	//here I am reading the users weight from a file
	ifstream readingWeight;
	readingWeight.open("usersData.txt");
	readingWeight >> userWeightVar;
	readingWeight.close();
	double minutes;
	cout << "\nHow many minutes of exercise are you going to be doing today (for day number " << (day + 1) << ")?";
	 cin >> minutes;
	 //here are the math operations reqiured
	 double amountToDrink = (userWeightVar * .67) + (.4 * minutes);
	 double amountToDrinkCups = amountToDrink / 8;
	 cout << "\nYou should be drinking about " << amountToDrink << " ounces of water which is between " <<  floor(amountToDrinkCups) << " and " << ceil(amountToDrinkCups) << " cups.\n";
	 goalsArray[0][day]= amountToDrink;
	 return 1;
}
//this function outputs the users weight and returns the weight (so the weight can be a number other than 0)
double usersInfo()
{
	//here I am saving the users weight to a file
		ofstream usersWeight;
		usersWeight.open("usersData.txt");
		double usersWeightVar;
		cout << "\nHow much do you weigh (in pounds)?";
		cin >> usersWeightVar;
		//this validates the users input
		while (usersWeightVar < 0)
		{
			cout << "Please enter a valid weight: ";
			cin >> usersWeightVar;
		}
		usersWeight << usersWeightVar;
		usersWeight.close();
		return usersWeightVar;
	
}
//this allows the user to enter the water they have dranker for the day
int enterWater(double goalsArray[100][365], int day, static int sum)
{
	static int counter = 0;
	int ounces;
	if (counter == 100)
	{
		"I am sorry you are unable to add more water drinkage the maximum nmber is 100. To enter more water you have to start a new day.";
	}
	cout << "\nEnter the ounces of water you drank for day " << day + 1 << ": ";
	cin >> ounces;
	sum = sum + ounces;
	goalsArray[1][day] = sum;
	counter++;
	return sum;
}
//this adds another day to the program
int newDay(int day)
{
	int exit1;
	if (day == 365)
	{
		cout << "You can only have 365 days. Press 1 to go back to the menu. Press 2 to exit the program.";
			cin >> exit1;
		if (exit1 == 2)
		{
			exit(0);
		}
		else 
		{
			return day;
		}
	}
	cout << "\nGood morning!";
	day++;
	return day;
}
//this shows the water the user drank throughout the year along with their goals
void waterChart(double goalsArray[100][365], int day)
{
	for (int j = 0; j < day + 1; j++)
	{
		if (j == 0)
		{
			cout << "                ";
		}
		cout << "Day " << j + 1 << "\t";
	}
	cout << endl;
	//this contains the required nested loops
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			cout << "Goal:           ";
		}
		if (i == 1) {
			cout << "What you drank: ";
		}
		for (int k = 0; k < (day + 1); k++)
		{
		cout << goalsArray[i][k] << "\t";
		}
		cout << endl;
	}

}
//the is the source I got my information from
void information()
{
	cout << "\nThe information in this program came from this website: https://www.slenderkitchen.com/article/how-to-calculate-how-much-water-you-should-drink-a-day";
	cout << "\nThe website also includes benifits of drinking more water and tips and trick to do so.";
}