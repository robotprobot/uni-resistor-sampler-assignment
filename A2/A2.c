/*
	Hardware and computer systems programming in C assignment
	Part A2 - Simple sampling program and data comparison - Source code
	By Steven Wheeler
		w012922i@student.staffs.ac.uk
		Student number: 18012922
	Version 2.0
	
	Purpose:
		To determine the values, mean, standard deviation and variance of a sample of resistors.
*/

	/* ARRAY REFERENCE SHEET 
	resistors[r]     <-- r is the resistor number
	resistors[r][0]  <-- 0 is the first band
	resistors[r][1]  <-- 1 is the second band
	resistors[r][2]  <-- 2 is the third band (if band is 4, this is 0)
	resistors[r][3]  <-- 3 is the fourth band (if band is 5, this and previous is 0)
	resistors[r][4]  <-- 4 is the multiplier
	resistors[r][5]  <-- 5 is the tolerence
	resistors[r][6]  <-- 6 is the expected value for the resistor
	resistors[r][7]  <-- 7 is the tolerence lower value
	resistors[r][8]  <-- 8 is the tolerence upper value
	resistors[r][9]  <-- 9 is the taken measurement
	resistors[r][10] <-- 10 is the pass or fail boolean (0 if fail, 1 if pass, it passes if tolerence within lower and upper value)
	resistors[r][11] <-- 11 is the variance
	*/
	
	/* STRUCTURE REFERENCE SHEET
	date 			   <-- char
	supplierName       <-- char
	nominalValue	   <-- double
	tolerencePercent   <-- float
	tolerenceLower     <-- double
	tolerenceUpper     <-- double
	failRate           <-- float
	meanValue		   <-- double
	standardDeviation  <-- float
	variance		   <-- float
	*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int structNumber = 0;
struct results
{
	char date[10];
	char supplierName[32];
	double nominalValue;
	float tolerencePercent;
	double tolerenceLower;
	double tolerenceUpper;
	float failRate;
	double meanValue;
	float standardDeviation;
	float variance;
};

void main() /* Viewing entries are not setup */
{
	int menuChosenOption = 0;
	printf("Resistor sampling and comparison program\r\n");
	printf("By Steven Wheeler\r\n");
	printf("[ASSIGNMENT PART A - DATA INSERTION AND STORAGE ONLY]\r\n\n");
	while(1==1) 
	{
		menuChosenOption = menuListAndGet();
		switch(menuChosenOption)
		{
			case 1:
				addEntry(structNumber+1);
				break;
			case 2:
				printf("Exiting...\r\n\n");
				exit(0);
				break;
			default:
				printf("Invalid menu entry.\r\n\n");
				break;
		}
	}
};

int menuListAndGet()
{
	int menuChoice;
	printf("1) Add new entry\r\n");
	printf("2) Exit\r\n\n");
	printf(" > ");
	scanf("%d",&menuChoice);
	printf("\r\n");
	return menuChoice;
}

int addEntry()
{
	/* preparing a instance of the structure to store results */
	struct results structNumber;
	
	/* get suppliers name from user */
	char supplierNameInput[16];
	printf("Please enter the suppliers name: ");
	scanf("%s",&structNumber.supplierName);  /* <-- gets the supplier name and stores it into the structure */
	
	/* get user to enter date */
	int enteredDate, modifiableDate;
	int day, month, year;
	char fullDate[8];
	int numberOfDigits;
	int maxDateForMonth;
	int dayAccepted, monthAccepted, dateAccepted = 0;
	while (dateAccepted == 0){
		printf("Please enter the date in an 8 digit format (DDMMYYYY) with no spaces: ");
		scanf("%d",&enteredDate);
		modifiableDate = enteredDate;
		numberOfDigits = 0;
		while (modifiableDate != 0){
			modifiableDate /= 10;
			++numberOfDigits;
		}
		if (numberOfDigits > 8 || numberOfDigits < 6){ /* if date length is too long */
			printf("Length incorrect.\n");
		}
		else{
			year = enteredDate % 10000;
			int month1 = enteredDate % 1000000 - year;
			int month2 = month1 / 10000;
			month = month2;
			day = enteredDate / 1000000;
			printf("date: %d, month: %d, year: %d\r\n",day,month,year);
			
			if ((month > 12) || (month < 1))
			{ /* if month does not exist */
				printf("Invalid month entry.\n"); /* reject because of month */
				monthAccepted = 0;
			}
			else if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)){ /* if month is Jan, Mar, May, July, Aug, Oct or Dec */
				monthAccepted = 1;
				maxDateForMonth = 31; /* Set maximum date to 31 */
			}
			else if ((month == 4) || (month == 6) || (month == 9) || (month == 11)){ /* else if month is Apr, June, Sep or Nov */
				monthAccepted = 1;
				maxDateForMonth = 30; /* Set maximum date to 30 */
			}
			else if (month == 2){ /* else if month is Feb */
				monthAccepted = 1;
				maxDateForMonth = 28; /* Set maximum date to 28 */
			}
			
			if ((day > maxDateForMonth) || (day < 1)){ /* if the date exceeds the max for the month or is under 1 */
				printf("Invalid date entry.\n"); /* reject because of date */
				dayAccepted = 0;
			}
			else {
				dayAccepted = 1;
			}
			
			if (dayAccepted == 1 & monthAccepted == 1){
				dateAccepted = 1;
				sprintf(fullDate,"%d-%d-%d",day,month,year);
				strcpy(structNumber.date, fullDate);
			}
		}
	}
	
	/* get resistor band amount */
	int resistorBandChosen = 0;
	int resistorBandNumber;
	while (resistorBandChosen == 0)
	{
		printf("How many bands do the resistors have? (4, 5 or 6): ");
		scanf("%d",&resistorBandNumber);
		if((resistorBandNumber == 4) || (resistorBandNumber == 5) || (resistorBandNumber == 6))
		{
			resistorBandChosen = 1;
		}
		else
		{
			printf("Invalid band entry.\r\n");
			resistorBandChosen = 0;
		}
	}
	
	/* get resistor band colors */	
	double resistors[11][13];
	int b = 0, r = 0;
	for (b=0;b<=resistorBandNumber-3;b++)
	{
		printf("\r\n");
		printf("Please enter the number for the colour of band %d on the resistors:\r\n", b+1);
		int chosenResistorBand = 0;
		int result;
		while (chosenResistorBand == 0)
		{
			printf("1) White\r\n2) Grey\r\n3) Violet\r\n4) Blue\r\n5) Green\r\n6) Yellow\r\n7) Orange\r\n8) Red\r\n9) Brown\r\n10) Black\r\n\n");
			printf(" > ");
			scanf("%d",&chosenResistorBand);
			result = 10 - chosenResistorBand;
			if ((result > 9) || (result < 0))
			{
				printf("INVALID BAND ENTRY. Please re-enter the band %d of resistor.\r\n",b);
				chosenResistorBand = 0;
			}
		}
	printf("");
	resistors[0][b] = result;
	}
	
	/* get resistor multiplier */
	printf("\r\n");
	printf("Please enter the number for the colour of band %d on the resistors:\r\n", resistorBandNumber-1);
	int chosenResistorMultiplierBand = 0;
	int resultOfMultiplierChoice;
	while (chosenResistorMultiplierBand == 0)
	{
		printf("1) Blue\r\n2) Green\r\n3) Yellow\r\n4) Orange\r\n5) Red\r\n6) Brown\r\n7) Black\r\n8) Gold\r\n9) Silver\r\n\n");
		printf(" > ");
		scanf("%d",&chosenResistorMultiplierBand);
		switch(chosenResistorMultiplierBand)
		{
			case 1:
				resultOfMultiplierChoice = 1000000;
				break;
			case 2:
				resultOfMultiplierChoice = 100000;
				break;
			case 3:
				resultOfMultiplierChoice = 10000;
				break;
			case 4:
				resultOfMultiplierChoice = 1000;
				break;
			case 5:
				resultOfMultiplierChoice = 100;
				break;
			case 6:
				resultOfMultiplierChoice = 10;
				break;
			case 7:
				resultOfMultiplierChoice = 1;
				break;
			case 8:
				resultOfMultiplierChoice = -10; /* NUMBER IS MINUS TO INDICATED THAT IT IS TO BE DIVIDED INSTEAD OF MULTIPLIED */
				break;
			case 9:
				resultOfMultiplierChoice = -100; /* NUMBER IS MINUS TO INDICATED THAT IT IS TO BE DIVIDED INSTEAD OF MULTIPLIED */
				break;
			default:
				printf("INVALID BAND ENTRY. Please re-enter the band %d of resistor.\r\n",b);
				chosenResistorMultiplierBand = 0;
		}
	}
	resistors[0][4] = resultOfMultiplierChoice;
	
	/* get resistor tolerence */
	printf("\r\n");
	printf("Please enter the number for the colour of band %d on the resistors:\r\n", resistorBandNumber);
	int chosenResistorTolerenceBand = 0;
	int resultOfTolerenceChoice;
	while (chosenResistorTolerenceBand == 0)
	{
		printf("1) Red\r\n2) Brown\r\n3) Gold\r\n4) Silver\r\n\n");
		printf(" > ");
		scanf("%d",&chosenResistorTolerenceBand);
		switch(chosenResistorTolerenceBand)
		{
			case 1:
				resultOfTolerenceChoice = 2;
				break;
			case 2:
				resultOfTolerenceChoice = 1;
				break;
			case 3:
				resultOfTolerenceChoice = 5;
				break;
			case 4:
				resultOfTolerenceChoice = 10;
				break;
			default:
				printf("INVALID BAND ENTRY. Please re-enter the band %d of resistor.\r\n",b);
				chosenResistorTolerenceBand = 0;
		}
	}
	resistors[0][5] = resultOfTolerenceChoice;
	if (resistorBandNumber == 5)
	{
		resistors[0][3] = 0;
	}
	if (resistorBandNumber == 4)
	{
		resistors[0][2] = 0; resistors[0][3] = 0;
	}
	for (r=1;r<=10;r++)
	{
		resistors[r][0] = resistors[0][0];
		resistors[r][1] = resistors[0][1];
		resistors[r][2] = resistors[0][2];
		resistors[r][3] = resistors[0][3];
		resistors[r][4] = resistors[0][4];
		resistors[r][5] = resistors[0][5];
	}
	
	/* calculate resistor values */
	r = 0;
	int resistorAmount = 10;
	for (r=0;r<=resistorAmount-1;r++)
	{
		double resistorValue;
		double value;
		switch(resistorBandNumber)
		{
			case 6:
				value = ((resistors[r][0])*1000+(resistors[r][1])*100+(resistors[r][2])*10+(resistors[r][3]));
				if (resistors[r][4] > 0)
				{
					resistorValue = ((value)*(resistors[r][4])); /* Multiplying by the multiplier */
				}
				else if (resistors[r][4] < 0)
				{
					int signRemoved = resistors[r][4] =- resistors[r][4];
					int resistorValue = ((value)/(signRemoved)); /* Dividing by the multiplier */
				}
				break;
			case 5:
				value = ((resistors[r][0])*100+(resistors[r][1])*10+(resistors[r][2]));
				if (resistors[r][4] > 0)
				{
					resistorValue = ((value)*(resistors[r][4])); /* Multiplying by the multiplier */
				}
				else if (resistors[r][4] < 0)
				{
					int signRemoved = resistors[r][4] =- resistors[r][4];
					int resistorValue = ((value)/(signRemoved)); /* Dividing by the multiplier */
				}
				break;
			case 4:
				value = ((resistors[r][0])*10+(resistors[r][1]));
				if (resistors[r][4] > 0)
				{
					resistorValue = (value*(resistors[r][4])); /* Multiplying by the multiplier */
				}
				else if (resistors[r][4] < 0)
				{
					int signRemoved = resistors[r][4] =- resistors[r][4];
					int resistorValue = (value/(signRemoved)); /* Dividing by the multiplier */
				}
				break;
		}
		resistors[r][6] = resistorValue;
		structNumber.nominalValue = resistorValue;
	}
	
	/* calculate tolerence values */
	r = 0; 
	for (r=0;r<=resistorAmount-1;r++)
	{
		int resistorExpectedValue = resistors[r][6];
		int resistorTolerenceValue = resistors[r][5];
		int resistorTolerenceMeasured = resistorExpectedValue * resistorTolerenceValue / 100;
		int resistorTolerenceLowerValue = resistorExpectedValue - resistorTolerenceMeasured;
		int resistorTolerenceUpperValue = resistorExpectedValue + resistorTolerenceMeasured;
		resistors[r][7] = resistorTolerenceLowerValue;
		resistors[r][8] = resistorTolerenceUpperValue;
	}
	printf("\r\n");
	printf("Value of resistors is %.0f ohms with a %.0f%% tolerence, tolerence range: %.0f to %.0f ohms\r\n",resistors[0][6],resistors[0][5],resistors[0][7],resistors[0][8]);
	printf("\r\n");
	structNumber.tolerencePercent = resistors[0][5];
	structNumber.tolerenceLower = resistors[0][7];
	structNumber.tolerenceUpper = resistors[0][8];
	
	/* enter resistor measurements */
	r = 0;
	int measurement;
	for (r=0;r<=resistorAmount-1;r++)
	{
		printf("Please enter the measurement taken for resistor %d in ohms: ",r+1);
		scanf("%d",&measurement);
		resistors[r][9] = measurement;
	}
	
	/* check resistor measurements against expected */
	r = 0;
	int failedResistorTotal = 0;
	printf("\r\n------------------[SAMPLE RESULTS]------------------\r\n\n");
	for (r=0;r<=resistorAmount-1;r++)
	{
		if (resistors[r][9] > resistors[r][8] || resistors[r][9] < resistors[r][7])
		{
			resistors[r][10] = 0;
			failedResistorTotal++;
			printf(" (!) Resistor %d FAILED\r\n",r+1);
		}
		else
		{
			resistors[r][10] = 1;
			printf(" ( ) Resistor %d PASSED \r\n",r+1);
		}
	}
	printf("\r\n");
	int percentageValue = 100/resistorAmount;
	int failRate = percentageValue*failedResistorTotal;
	structNumber.failRate = (float)failRate;
	printf("       FAILURE RATE: %0.f%%\r\n",structNumber.failRate);
	
	/* calculate the mean */
	/* getting the mean of all the measurements entered */
	r = 0;
	double sum;
	structNumber.meanValue = 0;
	for (r=0;r<=resistorAmount-1;r++) 
	{
		sum = sum + resistors[r][9];
	}
	float finalMeanValue = sum / resistorAmount;
	structNumber.meanValue = (double)finalMeanValue;
	printf("               MEAN: %.1f\r\n",structNumber.meanValue);
	
	/* calculate the variance */
	r = 0;
	float squaredResults;
	double mean = structNumber.meanValue;
	/* taking the difference from the mean */
	for (r=0;r<=resistorAmount-1;r++) 
	{
		resistors[r][11] = resistors[r][9]-mean; /* STRUCTNUMBER.MEANVALUE CANT BE READ */
	}
	/* squaring the differences */
	for (r=0;r<=resistorAmount-1;r++) 
	{
		resistors[r][11] = resistors[r][11]*resistors[r][11];
	}
	/* adding the squares together */
	for (r=0;r<=resistorAmount-1;r++) 
	{
		squaredResults = squaredResults + resistors[r][11];
	}
	/* dividing the squares by the amount of resistors for result */
	float finalVariance = squaredResults / resistorAmount;
	structNumber.variance = finalVariance;
	printf("           VARIANCE: %.1f\r\n",structNumber.variance);
	
	/* calculate standard deviation */
	structNumber.standardDeviation = sqrt(structNumber.variance);
	printf(" STANDARD DEVIATION: %f\r\n",structNumber.standardDeviation);
	printf("\r\n------------------[END OF RESULTS]------------------\r\n\n");
	printf("------------------[RESULT STORED!]------------------\r\n\n");
		
	/* debug information */
	printf("[DEBUG] Result was stored into the following structure: \r\n");
	printf("Date: %s\r\n",structNumber.date); /* complete */
	printf("Supplier name: %s\r\n",structNumber.supplierName); /* complete */
	printf("Nominal value: %0.1f\r\n",structNumber.nominalValue); /* complete */
	printf("Tolerence percent: %0.0f\r\n",structNumber.tolerencePercent); /* complete */
	printf("Tolerence lower: %0.0f\r\n",structNumber.tolerenceLower); /* complete */
	printf("Tolerence upper: %0.0f\r\n",structNumber.tolerenceUpper); /* complete */
	printf("Fail rate: %0.1f\r\n",structNumber.failRate); /* complete */
	printf("Mean value: %0.1f\r\n",structNumber.meanValue); /* complete */
	printf("Standard deviation: %f\r\n",structNumber.standardDeviation); /* complete */
	printf("Variance: %0.1f\r\n\n",structNumber.variance);  /* complete */
	
	/*r = 0;
	for (r=0;r<=9;r++)
	{
		printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\r\n",resistors[r][0],resistors[r][1],resistors[r][2],resistors[r][3],resistors[r][4],resistors[r][5],resistors[r][6],resistors[r][7],resistors[r][8],resistors[r][9],resistors[r][10],resistors[r][11]);
	} /* FOR DEBUG USE */
	
}
