//MonSchedProj
/*
first get info. So ask for mon per 2 weeks.
ask for what you pay for and how often. (for now can do every 2 weeks, except for rent.)
print out the information for every two weeks,(should also be able to do weekly if wanted)

so title * monthly rent or pay date* starting amount, amount plus pay if any, minus the bills, final amount.
(!) still needs to show balance for debts after paying, thus needs debts to be paid and conditions for them.
(!)(!) will it take into account the current week? so minus whatever the bills are for this current week? Should actually.
If it's Thursday, will do the calculations with the information, for the week this Thursday is on.
(!)Doesn't start for today, which it should. 
Debt: School: $1,539.00
		 CC1: $316.00

Current: 987
//(!)Should make prog that makes the best decision for me.
*/

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>

using namespace std;
using namespace System;

#define maxWk 16


void currentify(struct tm *);
int chkRentDay(struct tm * date);
int feb(int month);
int thirty(int month);
int thirtyOne(int month);
void thursdify(struct tm *);// converts to next closest Thursday
void advanceDate(struct tm * date);
void printDebt(float * debt1, float * debt2);


int main(void)
{
	system("color f0");
	time_t currTime = time(NULL);
	struct tm *currTimeA = localtime(&currTime);
	currentify(currTimeA); //make the local time readable to ppl
	char beels[8] = "\0"; //not needed
	char decision = '\0', decision2 = '\0', decision3 = '\0';
	bool nextMonth = false; //not needed
	int currWk = 0, baseWk = 0; //To compare if payday week.

	float current = 0, // current disposable income
		pay = 0,   // pay per 2 weeks
		bills = 0, // bills (gas + food + )
		rent = 0,  // rent 150 min
		payWk = 0, //not needed, pay/wk
		start = 0, //continual var that will hold the fluctuating amount
		misc = 0,
		schoolDebt = 1580.0,
		credDebt = 330.00;
	int freq = 0;
	//>>>>Get information
	//(!)How much disposable income do you have?
	puts("How much disposable income do you currently have? $");
	//scanf("%f", &current);
	current = 717; //-150 rent, - 50 bills. from 500. (!!) - 320 for c.c.. need 400 for phone ! 
	printf("\ncurrent:%.2f", current);
	//How much pay/week?
	puts("\nHow much money do you earn? $");
	//scanf("%f", &pay);
	pay = 370;
	printf("\npay:%.2f", pay);
	// will do 2 week's pay. (473 (50 hrs) or 370 (40 hrs) lol). 
	//In the future will take strings, ex. every: "week", "2 weeks", "month", etc.
	//__for now will take weeks.
	puts("\nEvery how many weeks?"); //might not work? "weeks might be advanced. o/w will use getch, and advance cursor past "weeks".
	//scanf("%d", &freq);
	freq = 2; 

	baseWk = freq; // assigns the space between the weeks as the base factor to determine if a pay week
	//>>>>>>>Get the date of the pay day to use to compare to next weeks that will be processed. 
	//The problem was that I had a pointer to struct w/ no struct really, just its members. So I had to\create a struct\
	yet I didn't have to initialize the struct. Perhaps w/ jsut the pointer it didn't work b/c it was pointing to garbage\
	and creating a struct allocated free memory to the struct. 
	struct tm payDay;
	struct tm *ptrPayDay = &payDay;
	puts("Please enter the date of your next payday(mm/dd/yyyy):");
	//scanf(" %d %*c %d %*c %d", &payDay->tm_mon, &payDay->tm_mday, &payDay->tm_year); //Here gets the first payday to compare.
	//printf("\nDate:%d/%d/%d", payDay->tm_mon, payDay->tm_mday, payDay->tm_year);//since payDay date is already current, don't need to convert it o/w would need to be subtracted. 
	//(!)Will assign next payDay to test out the rest of this prog.
	ptrPayDay->tm_mon = 6; ptrPayDay->tm_mday = 2; ptrPayDay->tm_year = 2016;
	//scanf("%d%*c%d%*c%d", &ptrPayDay->tm_mon, &ptrPayDay->tm_mday, &ptrPayDay->tm_year);
	printf("\nDate: %02d/%02d/%4d", ptrPayDay->tm_mon, ptrPayDay->tm_mday, ptrPayDay->tm_year);

	puts("\n\nEnter the amount of bills you pay per week: $");
	//scanf("%f", &bills);
	bills = 50;
	printf("Bills: %.2f", bills);
	puts("\nHow much monthly rent do you pay?");
	//scanf("%f", &rent);
	rent = 150;
	printf("%.2f", rent);
	puts("\nThis prog will assume you pay rent the last Thursday of the month\
			\nfor that current month.");

	//(!)(!)A)Set start date to the next closest Thursday.
	//thursdify(currTimeA);
	*currTimeA = payDay; 
	printf("\ncurrTime (closestThurs): %2d/%2d/%4d", currTimeA->tm_mon, currTimeA->tm_mday, currTimeA->tm_year);
	//start money is current disposable money
	start = current;
	//>>>>>Print out money schedule as it gets figured out
	//print date
	for (; currWk < maxWk; currWk++) //how many weeks do you want? 3 months. Every week. 
	{
		//chance to modify payment
		if (currWk + 1 > 1 && (currWk % baseWk == 0))
		{
			if (decision2 != 'N')
			{
				printf("\nWould you like to change the pay for the upcoming week?\
					\nPress 'y' for yes, 'n' for no, or 'N' for no to all.");
				decision2 = (char)getch();
				switch (decision2)
				{
				case 'y':
					puts("\nPlease enter new pay: $");
					scanf(" %f", &pay);
					break;
				case 'n':
					break;
				case 'N':
					break;

				}
			}
		}
		//Print date
		printf("\n\n\n\nvv  Week: %d/%d  vv", currWk+1, maxWk);
		printf("\n---------------\
					\n%02d/%02d/%02d", currTimeA->tm_mon, currTimeA->tm_mday, currTimeA->tm_year);

		//(!)A)Check if the current date is a pay day and a rent day. 
		if (currWk % baseWk == 0) // if it is a payday //won't use a bool
		{
			printf(" (P)");
		}
		//(!) Check if the current date is the last Thurs. of The month "Rent Day"
		if (chkRentDay(currTimeA))
		{
			printf(" (R)");
		}
		printf("\n---------------");
		//Print Debt
		printf("\n*Debts*\
			\nC.C:\t$%.2f\
			\nSchool:\t$%.2f\
			\n---------------", credDebt, schoolDebt);

		//Print starting amount
		printf("\nStart:\t  $%.2f", start);
		//Print pay if any
		if (currWk % baseWk == 0)
		{
			printf("\n\t + %.2f (PAY)", pay);
			start += pay;
			printf("\n\t__________\
					\n\t...%.2f", start);
		}
		//Print rent
		if (chkRentDay(currTimeA))
		{
			printf("\n\t  - %.2f (RENT)", rent);
			start -= rent;
			printf("\n\t__________\
					\n\t...%.2f", start);
		}
		//print bills
		printf("\n\t  - %.2f (GAS, FOOD, HCUT?)", bills);
		printf("\n\t__________");
		start -= bills;
		printf("\nLeft:\t  $%.2f", start);
		printf("\nThis money can be used to pay the phone, and your c.c debt, and m.i., pbj debt and the money for the party.");
		if (decision != 'N')
		{
			do
			{
				printf("\nWould you like to enter another billing at this point?\
					\nPress 'y' for yes, 'n' for no, or 'N' for no to all.");
				decision = (char)getch();
				//TEST: putchar(decision);
				switch (decision)
				{
				case 'y':
					puts("\n\t");
					scanf("%f", &misc);
					//misc = (float)atof(gets_s(beels));
					start += misc;
					//
					if(credDebt > 0) //if debt not yet cancelled
					{ 
						//if this becomes true, then the other one won't happen. 
						puts("\nIs this a payment for credit Debt?");
						decision3 = (char)getch();
						if (decision3 == 'y' || decision3 == 'Y')
						{
							credDebt += misc;
							//Print Debt
							printf("\n*Debts*\
			\nC.C:\t$%.2f\
			\nSchool:\t$%.2f\
			\n---------------", credDebt, schoolDebt);

						}

					}
					if (schoolDebt > 0 && (decision3 != 'y' && decision3 != 'Y'))
					{
						puts("\nIs this a payment for School?");
						decision3 = (char)getch();
						if (decision3 == 'y' || decision3 == 'Y')
						{
							schoolDebt += misc;
							//Print Debt
							printf("\n*Debts*\
			\nC.C:\t$%.2f\
			\nSchool:\t$%.2f\
			\n---------------", credDebt, schoolDebt);

						}
					}
					decision3 = '\0';
				
					
					
					puts("\n\t__________");
					printf("\t...%.2f", start);
					break;
				case 'n':
					break;
				case 'N':
					break;

				}
			} while (decision != 'n');
			
		}
		
		//>>>>Advance date by 1 week.
		advanceDate(currTimeA);

	}



	_getch();
	return 0;
}


 
int chkRentDay(struct tm * date)
{
	//one if for every month type
	if (thirtyOne(date->tm_mon))
	{
		if(date->tm_mday + 7 > 31) //if adding a week is greater than the last day of mo. shows that it's the last Thurs of the month
			return 1;
		else
			return 0;

	}
	if (thirty(date->tm_mon))
	{
		if (date->tm_mday + 7 > 30) 
			return 1;
		else
			return 0;
	}
	if (feb(date->tm_mon)) //doesn't take into account leapyear.
	{
		if (date->tm_mday + 7 > 28)
			return 1;
		else 
			return 0;
	}
		
}

int feb(int month) //month and leap year. 
{
	if (month == 2)
		return 1;
	else
		return 0;

}
int thirty(int month) //30 day month
{
	if (month == 4 || month == 6 ||
		month == 9 || month == 11)
		return 1;
	else
		return 0;
}
int thirtyOne(int month)//31 day month
{
	if (month == 1 || month == 3 || month == 5 || month == 7 ||
		month == 8 || month == 10 || month == 12)
		return 1;
	else
		return 0;
}

//makes the dates current
void currentify(struct tm * date)
{
	date->tm_mon += 1;
	date->tm_year += 1900;
	return;
}

void thursdify(struct tm * date) //gets the next closest day. 
{
	for (; date->tm_wday == 4; date->tm_wday++) //advance day
	{
		//check beforehand if the day is the last day of the month b/f adding 
		//one for every type of month. 
		if (thirtyOne(date->tm_mon))
		{
			if (date->tm_mday == 31) //do a different addition if the last day of the month.
			{
				date->tm_mday = 1;
				date->tm_mon++;
				date->tm_wday++;
			}
			else
			{
				date->tm_mday++;
				date->tm_mon++;
				date->tm_wday++;
			}

		}
		if (thirty(date->tm_mon))
		{
			if (date->tm_mday == 30)
			{
				date->tm_mday = 1;
				date->tm_mon++;
				date->tm_wday++;
			}
			else
			{
				date->tm_mday++;
				date->tm_mon++;
				date->tm_wday++;
			}
		}
		if (feb(date->tm_mon)) //doesn't take into account leapyear.
		{
			if (date->tm_mday == 28)
			{
				date->tm_mday = 1;
				date->tm_mon++;
				date->tm_wday++;
			}
			else
			{
				date->tm_mday++;
				date->tm_mon++;
				date->tm_wday++;
			}
		}

	}
}

void advanceDate(struct tm * date)
{
	int extra = 0;
	if (thirtyOne(date->tm_mon))
	{
		if (date->tm_mday + 7 > 31) //do a different addition if the last day of the month.
		{
			extra = 7 - (31 - date->tm_mday);
			date->tm_mday = extra;
			date->tm_mon++;
			return;
		}
		else
		{
			date->tm_mday += 7;
			return;
		}

	}
	if (thirty(date->tm_mon))
	{
		if (date->tm_mday + 7 > 30)
		{
			extra = 7 - (30 - date->tm_mday);
			date->tm_mday = extra;
			date->tm_mon++;
			return;
		}
		else
		{
			date->tm_mday += 7;
			return;
		}
	}
	if (feb(date->tm_mon)) //doesn't take into account leapyear.
	{
		if (date->tm_mday + 7 > 28)
		{
			date->tm_mday = 7 - (30 - date->tm_mday);
			date->tm_mon++;
			return;
		}
		else
		{
			date->tm_mday += 7;
			return;
		}
	}
}

void printDebt(float * debt1, float * debt2)
{
	printf("\n---------------");
	//Print Debt
	printf("\n*Debts*\
			\nC.C:\t$%.2f\
			\nSchool:\t$%.2f\
			\n---------------", debt1, debt2);

}
