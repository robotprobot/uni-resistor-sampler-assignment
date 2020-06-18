/*
	Hardware and computer systems programming in C assignment
	Part B2 - Simple sampling program and data comparison - Source code
	By Steven Wheeler
		w012922i@student.staffs.ac.uk
		Student number: 18012922
	Version 1.0
	
	THIS PROGRAM USES THE ADDENTRY() METHOD FROM PART A2.
	
	Purpose:
		To create a 6 month data log, display data and search tests.
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

int structNumber = 1;
int debug = 0; /* debug off = 0, debug on = 1 */

struct results
{
	char dateFinderSupporter[8];
	char date[12];
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

void main()
{
	int menuChosenOption = 0;
	printf("Resistor sampling and comparison program\r\n");
	printf("By Steven Wheeler\r\n");
	printf("[ASSIGNMENT PART B - FULL PROGRAM]\r\n\n");
	while(1==1) 
	{
		menuChosenOption = menuList();
		switch(menuChosenOption)
		{
			case 1:
				if(0) goto addError;
				{
					structNumber++;
					struct results structure[structNumber];
					addEntry(structure[structNumber]); /* starts the function to get a new sample entry */
					break;
				}
				addError:
				return;
			case 2:
				if(0) goto exportError;
				{
					struct results structure[structNumber];
					export6Month(structure[structNumber]); /* starts the function to export the past 6 months to a txt file */
					break;
				}
				exportError:
				return;
			case 3:
				if(0) goto viewError;
				{
					struct results structure[structNumber];
					displayAllEntries(structure[structNumber]); /* starts the function to display all entries */
					break;
				}
				viewError:
				return;
			case 4:
				if(0) goto displaySupplierError;
				{
					struct results structure[structNumber];
					displaySupplier6Month(structure[structNumber]); /* starts the function to display all entries */
					break;
				}
				displaySupplierError:
				return;
			case 5:
				safeExit();
				break;
			default:
				printf("Invalid menu entry.\r\n\n");
				break;
		}
	}
};

int safeExit()
{
	printf("Exiting...\r\n\n");
	exit(0);
}

int menuList()
{
	int menuChoice;
	printf("1) Add new entry\r\n");
	printf("2) Add data to 6 month data log\r\n");
	printf("3) Display all entries\r\n");
	printf("4) Search 6 month period for supplier\r\n");
	printf("5) Exit\r\n\n");
	printf(" > ");
	scanf("%d",&menuChoice);
	printf("\r\n");
	return menuChoice;
}

int addEntry(struct results structure[structNumber])
{	
	/* get suppliers name from user */
	char supplierNameInput[32];
	printf("Please enter the suppliers name (using _ or - for spaces): ");
	scanf("%s",&structure[structNumber].supplierName);  /* <-- gets the supplier name and stores it into the structure */
	
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
				sprintf(fullDate,"%02d-%02d-%02d",day,month,year);
				strcpy(structure[structNumber].date, fullDate);
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
		structure[structNumber].nominalValue = resistorValue;
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
	structure[structNumber].tolerencePercent = resistors[0][5];
	structure[structNumber].tolerenceLower = resistors[0][7];
	structure[structNumber].tolerenceUpper = resistors[0][8];
	
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
	structure[structNumber].failRate = (float)failRate;
	printf("       FAILURE RATE: %0.f%%\r\n",structure[structNumber].failRate);
	
	/* calculate the mean */
	/* getting the mean of all the measurements entered */
	r = 0;
	double sum;
	structure[structNumber].meanValue = 0;
	for (r=0;r<=resistorAmount-1;r++) 
	{
		sum = sum + resistors[r][9];
	}
	float finalMeanValue = sum / resistorAmount;
	structure[structNumber].meanValue = (double)finalMeanValue;
	printf("               MEAN: %.1f\r\n",structure[structNumber].meanValue);
	
	/* calculate the variance */
	r = 0;
	float squaredResults;
	double mean = structure[structNumber].meanValue;
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
	structure[structNumber].variance = finalVariance;
	printf("           VARIANCE: %.1f\r\n",structure[structNumber].variance);
	
	/* calculate standard deviation */
	structure[structNumber].standardDeviation = sqrt(structure[structNumber].variance);
	printf(" STANDARD DEVIATION: %f\r\n",structure[structNumber].standardDeviation);
	printf("\r\n------------------[END OF RESULTS]------------------\r\n");
	printf("------------[RESULT STORED IN STRUCTURE]------------\r\n\n");

	sprintf(structure[structNumber].dateFinderSupporter,"%d%d",month,year);

	/* debug information */
	if (debug == 1) {
		printf("[DEBUG] Result was stored into the following structure: \r\n");
		printf("DateFinderSupporter: %s\r\n",structure[structNumber].dateFinderSupporter);
		printf("Date: %s\r\n",structure[structNumber].date); /* complete */
		printf("Supplier name: %s\r\n",structure[structNumber].supplierName); /* complete */
		printf("Nominal value: %0.1f\r\n",structure[structNumber].nominalValue); /* complete */
		printf("Tolerence percent: %0.0f\r\n",structure[structNumber].tolerencePercent); /* complete */
		printf("Tolerence lower: %0.0f\r\n",structure[structNumber].tolerenceLower); /* complete */
		printf("Tolerence upper: %0.0f\r\n",structure[structNumber].tolerenceUpper); /* complete */
		printf("Fail rate: %0.1f\r\n",structure[structNumber].failRate); /* complete */
		printf("Mean value: %0.1f\r\n",structure[structNumber].meanValue); /* complete */
		printf("Standard deviation: %f\r\n",structure[structNumber].standardDeviation); /* complete */
		printf("Variance: %0.1f\r\n\n",structure[structNumber].variance);  /* complete */
			
		/*r = 0;
		for (r=0;r<=9;r++)
		{
			printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\r\n",resistors[r][0],resistors[r][1],resistors[r][2],resistors[r][3],resistors[r][4],resistors[r][5],resistors[r][6],resistors[r][7],resistors[r][8],resistors[r][9],resistors[r][10],resistors[r][11]);
		} /* FOR DEBUG USE */
	}
}

int export6Month(struct results structure[structNumber])
{
	int enteredDate, modifiableDate;
	int month, year;
	char fullDate[6];
	int numberOfDigits;
	int monthAccepted = 0;
	while (monthAccepted == 0)
	{
		printf("Please enter the month and year you want the 6 months up to in a 6 digit format (MMYYYY) with no spaces: ");
		scanf("%d",&enteredDate);
		modifiableDate = enteredDate;
		numberOfDigits = 0;
		while (modifiableDate != 0){
			modifiableDate /= 10;
			++numberOfDigits;
		}
		if (numberOfDigits > 6 || numberOfDigits < 4){ /* if date length is too long */
			printf("Length incorrect.\n");
		}
		else{
			year = enteredDate % 10000;
			int month1 = enteredDate % 1000000 - year;
			int month2 = month1 / 10000;
			month = month2;
			printf("month: %d, year: %d\r\n",month,year);
			
			if ((month > 12) || (month < 1))
			{ /* if month does not exist */
				printf("Invalid month entry.\n"); /* reject because of month */
				monthAccepted = 0;
			}		
			else
			{
				sprintf(fullDate,"%d-%d",month,year);
				monthAccepted = 1;
			}
		}
	}
	int m = 0;
	int activeStruct = 1;
	int exportAmount = 0;
	int monthExport[6][2];
	char fileName[32];
	monthExport[0][0] = month;
	monthExport[0][1] = year;
	printf("Exporting all entries that have a date in the following months:\r\n");
	printf("%d-%d  ",monthExport[0][0],monthExport[0][1]);
	for (m=1;m<=5;m++)
	{
		month = month-1;
		if (month == 0){
			month = 12;
			year = year-1;
		}
		monthExport[m][0] = month;
		monthExport[m][1] = year;
		printf("%d-%d  ",monthExport[m][0],monthExport[m][1]);
	}
	printf("\r\nPlease enter a name for the file (using _ or - for spaces): ");
	scanf("%s",&fileName);
	sprintf(fileName,"%s%s",fileName,".txt");
	printf("Saving file: %s\r\n", fileName);
	FILE * outputFile;
	outputFile = fopen(fileName,"a");
	char currentSupplierName[32];
	for (m=0;m<=5;m++) /* for each month selected */
	{
		char monthYear[6];
		sprintf(monthYear,"%d%d",monthExport[m][0],monthExport[m][1]);
		int lookingForMonthYear = atoi(monthYear);
		for (activeStruct=2;activeStruct<=structNumber;activeStruct++) /* search through the structure for matching entries */
		{
			int dateFinder = atoi(structure[activeStruct].dateFinderSupporter);
			sprintf(currentSupplierName,"%s",structure[activeStruct].supplierName);
			if (dateFinder == lookingForMonthYear)
			{
				fprintf(outputFile, "Entry date: %s\nSupplier Name: %s\nNominal Value: %0.1f\nTolerence Percentage: %0.0f%%\nFailure Rate: %0.1f%%\nMean Value: %0.1f\nStandard Deviation: %f\nVariance: %0.1f\n\n",structure[activeStruct].date,currentSupplierName,structure[activeStruct].nominalValue,structure[activeStruct].tolerencePercent,structure[activeStruct].failRate,structure[activeStruct].meanValue,structure[activeStruct].standardDeviation,structure[activeStruct].variance);
				exportAmount++;
			}
		}
	}
	fclose(outputFile);
	if (exportAmount > 0) {
		printf("File successfully exported.\r\n%d entries were exported.\r\nFile is saved next to .exe, called %s\r\n\n",exportAmount,fileName);
	}
	else {
		remove(fileName);
		printf("No entries were found in the export date range.\r\nExport was cancelled.\r\n\n");
	}
}

int displayAllEntries(struct results structure[structNumber])
{
	int activeStruct = 1;
	int displayed = 0;
	printf("Date      |Supplier Name      |Nominal Value    |Tolerence  |Fail Rate  |Mean       |Standard Deviation  |Variance    \r\n-----------------------------------------------------------------------------------------------------------------------\r\n");
	for (activeStruct=2;activeStruct<=structNumber;activeStruct++)
	{
		displayed++;
		printf("%-11s%-20s%-18.1f%-12.0f%-12.0f%-12.1f%-21f%0.1f% \r\n",structure[activeStruct].date,structure[activeStruct].supplierName,structure[activeStruct].nominalValue,structure[activeStruct].tolerencePercent,structure[activeStruct].failRate,structure[activeStruct].meanValue,structure[activeStruct].standardDeviation,structure[activeStruct].variance);
	}
	if (displayed == 0)
	{
		printf("There are no entries.\r\n");
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\r\n\n");
}

int displaySupplier6Month(struct results structure[structNumber])
{
	int enteredDate, modifiableDate;
	int month, year;
	char fullDate[6];
	int numberOfDigits;
	int monthAccepted = 0;
	char searchSupplierName[32];
	printf("Please enter the suppliers name (using _ or - for spaces): ");
	scanf("%s",searchSupplierName);
	while (monthAccepted == 0)
	{
		printf("Please enter the month and year you want the 6 months up to in a 6 digit format (MMYYYY) with no spaces: ");
		scanf("%d",&enteredDate);
		modifiableDate = enteredDate;
		numberOfDigits = 0;
		while (modifiableDate != 0){
			modifiableDate /= 10;
			++numberOfDigits;
		}
		if (numberOfDigits > 6 || numberOfDigits < 4){ /* if date length is too long */
			printf("Length incorrect.\n");
		}
		else{
			year = enteredDate % 10000;
			int month1 = enteredDate % 1000000 - year;
			int month2 = month1 / 10000;
			month = month2;
			printf("month: %d, year: %d\r\n",month,year);
			
			if ((month > 12) || (month < 1))
			{ /* if month does not exist */
				printf("Invalid month entry.\n"); /* reject because of month */
				monthAccepted = 0;
			}		
			else
			{
				sprintf(fullDate,"%d-%d",month,year);
				monthAccepted = 1;
			}
		}
	}
	int m = 0;
	int displayed = 0;
	int activeStruct = 1;
	int foundAmount = 0;
	float failureRateCount = 0;
	float meanValueCount = 0;
	float standardDeviationCount = 0;
	float varianceCount = 0;
	int monthSearch[6][2];
	monthSearch[0][0] = month;
	monthSearch[0][1] = year;
	printf("Finding all entries for '%s' that have a date in the following months:\r\n", searchSupplierName);
	printf("%d-%d  ",monthSearch[0][0],monthSearch[0][1]);
	for (m=1;m<=5;m++)
	{
		month = month-1;
		if (month == 0){
			month = 12;
			year = year-1;
		}
		monthSearch[m][0] = month;
		monthSearch[m][1] = year;
		printf("%d-%d  ",monthSearch[m][0],monthSearch[m][1]);
	}
	printf("\r\n\nDate      |Supplier Name      |Nominal Value    |Tolerence  |Fail Rate  |Mean       |Standard Deviation  |Variance    \r\n-----------------------------------------------------------------------------------------------------------------------\r\n");
	for (activeStruct=2;activeStruct<=structNumber;activeStruct++)
	{
		for (m=0;m<=5;m++) /* for each month selected */
		{
			char monthYear[6];
			char currentSupplierName[32];
			int difference;
			sprintf(monthYear,"%d%d",monthSearch[m][0],monthSearch[m][1]);
			int lookingForMonthYear = atoi(monthYear);
			for (activeStruct=2;activeStruct<=structNumber;activeStruct++) /* search through the structure for matching entries */
			{
				int dateFinder = atoi(structure[activeStruct].dateFinderSupporter);
				if (dateFinder == lookingForMonthYear) /* if date matches */
				{
					if (debug == 1)
					{
						printf("[DEBUG] Found a entry, the month looking for is %d, the month of entry is %d.\r\n",lookingForMonthYear,dateFinder);
					}
					char foundSupplierName[32];
					sprintf(foundSupplierName,"%s",structure[activeStruct].supplierName);
					char needSupplierName[32];
					sprintf(needSupplierName,"%s",searchSupplierName);
					if (debug == 1)
					{
						printf("[DEBUG] In that entry, the found supplier name is %s, the supplier name needed is %s.\r\n",foundSupplierName,needSupplierName);
					}
					difference = strncmp(foundSupplierName,needSupplierName,32); /* compare the two strings */
					if (difference == 0) /* if there is no difference */
					{
						printf("%-11s%-20s%-18.1f%-12.0f%-12.0f%-12.1f%-21f%0.1f% \r\n",structure[activeStruct].date,structure[activeStruct].supplierName,structure[activeStruct].nominalValue,structure[activeStruct].tolerencePercent,structure[activeStruct].failRate,structure[activeStruct].meanValue,structure[activeStruct].standardDeviation,structure[activeStruct].variance);
						displayed++;
						failureRateCount = failureRateCount + structure[activeStruct].failRate;
						meanValueCount = meanValueCount + structure[activeStruct].meanValue;
						standardDeviationCount = standardDeviationCount + structure[activeStruct].standardDeviation;
						varianceCount = varianceCount + structure[activeStruct].variance;
					}
				}
			}
		}
	}
	if (displayed == 0)
	{
		printf("No matching entries.\r\n");
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\r\n");
	if (displayed > 0)
	{
		float failureRateAverage = failureRateCount/displayed; /* calculate the average fail rate */
		float meanValueAverage = meanValueCount/displayed; /* calculate the average mean value */
		float standardDeviationAverage = standardDeviationCount/displayed; /* calculate the average standard deviation */
		float varianceAverage = varianceCount/displayed; /* calculate the average variance */
		printf("--- AVERAGE OVER THE SIX MONTHS ---------------------------- %-12.2f%-12.1f%-21.6f%.1f",failureRateAverage,meanValueAverage,standardDeviationAverage,varianceAverage);
		printf("\r\n-----------------------------------------------------------------------------------------------------------------------\r\n");
	}
	printf("\r\n");
}
