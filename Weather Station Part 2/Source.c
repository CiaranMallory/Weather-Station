#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#pragma warning(disable : 4996)

struct readings {
	double temperature;
	double wind_direction;
	double wind_speed;
	time_t time;
};

// Sorting Functions
// Descending Orders
int Descend1(const void* p, const void* q) {
	struct readings* a = (struct readings*)p;
	struct readings* b = (struct readings*)q;

	if (b->temperature > a->temperature)
		return 1;
	else if (b->temperature < a->temperature)
		return -1;
	else
		return 0;
}


int Descend2(const void* p, const void* q) {
	struct readings* a = (struct readings*)p;
	struct readings* b = (struct readings*)q;

	if (b->wind_direction > a->wind_direction)
		return 1;
	else if (b->wind_direction < a->wind_direction)
		return -1;
	else
		return 0;
}

int Descend3(const void* p, const void* q) {
	struct readings* a = (struct readings*)p;
	struct readings* b = (struct readings*)q;

	if (b->wind_speed > a->wind_speed)
		return 1;
	else if (b->wind_speed < a->wind_speed)
		return -1;
	else
		return 0;
}

// Ascending Orders
int Ascend1(const void* p, const void* q) {
	struct readings* a = (struct readings*)p;
	struct readings* b = (struct readings*)q;

	if (b->temperature > a->temperature)
		return -1;
	else if (b->temperature < a->temperature)
		return 1;
	else
		return 0;
}

int Ascend2(const void* p, const void* q) {
	struct readings* a = (struct readings*)p;
	struct readings* b = (struct readings*)q;

	if (b->wind_direction > a->wind_direction)
		return -1;
	else if (b->wind_direction < a->wind_direction)
		return 1;
	else
		return 0;
}

int Ascend3(const void* p, const void* q) {
	struct readings* a = (struct readings*)p;
	struct readings* b = (struct readings*)q;

	if (b->wind_speed > a->wind_speed)
		return -1;
	else if (b->wind_speed < a->wind_speed)
		return 1;
	else
		return 0;
}


int main(void)
{
	struct readings* readings = NULL;
	int option = 0;
	printf_s("\nWelcome to Data Acquisition Program\n");

	while (option != 5)
	{
		printf_s("\nOptions are as follows:\n 1:Load File\n 2:Search Weather by date\n 3:View Monthly Data\n 4:Export to Excel\n 5:Exit\n");
		printf_s("Enter an option: ");
		scanf_s("%d", &option);

		// Loading File into program
		FILE* pFile;
		errno_t error;
		int num_readings = 0;

		time_t t;
		struct tm* tmp;
		char my_time[20];
		time(&t);

		error = fopen_s(&pFile, "Weather.bin", "rb"); // Opening Binary file for reading

		if (error == 0)
		{
			fread(&num_readings, sizeof(int), 1, pFile);
			readings = malloc(sizeof(struct readings) * num_readings);
			fread(readings, sizeof(struct readings), num_readings, pFile);
			fclose(pFile);
		}
		else { printf_s("Error: %d", error); }
		

		if (option == 1)
		{
			// Displaying contents of binary file created in the other program to the user

				for (int i = 0; i < num_readings; i++)
				{
					printf_s("Temperature: %lf\n", readings[i].temperature);
					printf_s("Wind Direction: %lf\n", readings[i].wind_direction);
					printf_s("Wind Speed: %lf\n", readings[i].wind_speed);
					tmp = localtime(&readings[i].time);
					strftime(my_time, sizeof(my_time), "%x - %I:%M%p", tmp);
					printf_s("Date & Time: %s\n", my_time);
				}	
		}



		if (option == 2)
		{
			// Searching by date in file

			char date[10];

			if (readings != NULL) // Checking that readings is not empty
			{
					tmp = localtime(&readings[0].time); 
					// Extracting date from binary file
					// Only the first date is needed as searching will be done by when the readings started being taken
					strftime(my_time, sizeof(my_time), "%x", tmp);

				getchar();
				printf_s("Enter the Date you wish to search for in the form Month/Day/Year: \n"); // Include "/" when entering date
				fgets(date, sizeof(date), stdin);
				date[strcspn(date, "\n")] = 0; // Removes trailing \n from char date

				int result = 0;

				result = strcmp(date, my_time);
				// Compares two strings,
				// returns 0 if strings are equal
				// returns -1 or 1 depending on whether the first
				// character is less than or greater than the other string character

				if (result == 0)
				{
					printf_s("Date found!\n %s\n", date);
					for (int i = 0; i < num_readings; i++)
					{
						printf_s("Temperature is: %lf\n", readings[i].temperature);
						printf_s("Wind Direction is: %lf\n", readings[i].wind_direction);
						printf_s("Wind Speed is: %lf\n", readings[i].wind_speed);
					}
				}
				else
				{
					printf_s("Date not found!\n");
				}
			}
			else
			{
				printf_s("Error!!, File is Empty\n");
			}

		}


		if (option == 3)
		{
		
				// Extracting time stamp from binary file
				tmp = localtime(&readings[0].time);
				printf_s("\n");

				if (tmp->tm_mon == 0) { // tmp->tm_mon returns the number of months since Janurary
					printf_s("Janurary Data\n");
				}
				if (tmp->tm_mon == 1) {
					printf_s("Feburary Data\n");
				}
				if (tmp->tm_mon == 2) {
					printf_s("March Data\n");
				}
				if (tmp->tm_mon == 3) {
					printf_s("April Data\n");
				}
				if (tmp->tm_mon == 4) {
					printf_s("May Data\n");
				}
				if (tmp->tm_mon == 5) {
					printf_s("June Data\n");
				}
				if (tmp->tm_mon == 6) {
					printf_s("July Data\n");
				}
				if (tmp->tm_mon == 7) {
					printf_s("August Data\n");
				}
				if (tmp->tm_mon == 8) {
					printf_s("September Data\n");
				}
				if (tmp->tm_mon == 9) {
					printf_s("October Data\n");
				}
				if (tmp->tm_mon == 10) {
					printf_s("November Data\n");
				}
				if (tmp->tm_mon == 11) {
					printf_s("December Data\n");
				}

			printf_s("-------------------------------\n");


			// Calculating Average

			double total1 = 0, total2 = 0, total3 = 0;	// Variable declaration

			for (int i = 0; i < num_readings; i++) {

				total1 = total1 + readings[i].temperature;	// Loop for calculating total
				total2 = total2 + readings[i].wind_direction;
				total3 = total3 + readings[i].wind_speed;
			}
			double avg1 = total1 / num_readings;	// Calculating average
			double avg2 = total2 / num_readings;
			double avg3 = total3 / num_readings;

			printf_s("Average Temperature: %lf\n", avg1);
			printf_s("Average Wind Direction: %lf\n", avg2);
			printf_s("Average Wind Speed: %lf\n", avg3);

			printf_s("-------------------------------\n");

			// Calculating Higest and Lowest

			double h1 = 0, l1 = 0, h2 = 0, l2 = 0, h3 = 0, l3 = 0;

			l1 = readings[0].temperature;
			h1 = readings[0].temperature;
			l2 = readings[0].wind_direction;
			h2 = readings[0].wind_direction;
			l3 = readings[0].wind_speed;
			h3 = readings[0].wind_speed;

			// Temperature
			for (int i = 0; i < num_readings; i++)
			{
				if (readings[i].temperature > h1)
					h1 = readings[i].temperature;
				else
				{
					if (readings[i].temperature < l1)
						l1 = readings[i].temperature;
				}
			}
			// Wind Direction
			for (int i = 0; i < num_readings; i++)
			{
				if (readings[i].wind_direction > h2)
					h2 = readings[i].wind_direction;
				else
				{
					if (readings[i].wind_direction < l2)
						l2 = readings[i].wind_direction;
				}
			}
			// Wind Speed
			for (int i = 0; i < num_readings; i++)
			{
				if (readings[i].wind_speed > h3)
					h3 = readings[i].wind_speed;
				else
				{
					if (readings[i].wind_speed < l3)
						l3 = readings[i].wind_speed;
				}
			}
			printf_s("Highest Temperature of the month: %lf\n", h1);
			printf_s("Lowest Temperature of the month: %lf\n", l1);
			printf_s("-------------------------------\n");
			printf_s("Highest Wind Direction of the month: %lf\n", h2);
			printf_s("Lowest Wind Direction of the month: %lf\n", l2);
			printf_s("-------------------------------\n");
			printf_s("Highest Wind Speed of the month: %lf\n", h3);
			printf_s("Lowest Wind Speed of the month: %lf\n", l3);

		}


		if (option == 4)
		{
			// Writing data from binary file to excel file

			FILE* aFile; // Declaration for csv file
			errno_t error;

			int order = 0;
			printf_s("Would you like to export in desending or ascending order? (1 = Descending, 2 = Ascending): \n");
			scanf_s("%d", &order);

			error = fopen_s(&aFile, "Weather.csv", "w"); // Opening csv file in writing mode

			if (error == 0) // Checking File Opened Correctly
			{
				if (order == 1)
				{
					// Sorting Data in Descending mode

						fprintf_s(aFile, "%d readings were saved\n", num_readings); // Writing number of readings to file
				
						qsort(readings, num_readings, sizeof(struct readings), Descend1); // Sorting Temperature
						printf_s("Temperature: \n");
						fprintf_s(aFile, "Temperature: \n");
						for (int i = 0; i < num_readings; i++) {
							printf_s("%lf\n", readings[i].temperature); // Displaying Sort to the User
							fprintf_s(aFile, "%lf\n", readings[i].temperature); // Writing Sort to File
						}
						qsort(readings, num_readings, sizeof(struct readings), Descend2); // Sorting Wind Direction
						printf_s("Wind Direction: \n");
						fprintf_s(aFile, "Wind Direction: \n");
						for (int i = 0; i < num_readings; i++) {
							printf_s("%lf\n", readings[i].wind_direction);
							fprintf_s(aFile, "%lf\n", readings[i].wind_direction);
						}
						qsort(readings, num_readings, sizeof(struct readings), Descend3); // Sorting Wind Speed
						printf_s("Wind Speed: \n");
						fprintf_s(aFile, "Wind Speed: \n");
						for (int i = 0; i < num_readings; i++) {
							printf_s("%lf\n", readings[i].wind_speed);
							fprintf_s(aFile, "%lf\n", readings[i].wind_speed);
						}
						
						tmp = localtime(&readings[0].time); 
						// I use readings[0].time as I only want the time when the user started entering readings for neatness
						strftime(my_time, sizeof(my_time), "%x - %I:%M%p", tmp);
						printf_s("Date & Time: %s\n", my_time);
						fprintf_s(aFile, "Date & Time: %s\n", my_time); // Writing time from binary file to csv file
						fclose(aFile);

				}
				else if (order == 2)
				{
					// Sorting Data in Ascending mode

						fprintf_s(aFile, "%d readings were saved\n", num_readings);

						qsort(readings, num_readings, sizeof(struct readings), Ascend1);
						printf_s("Temperature: \n");
						fprintf_s(aFile, "Temperature: \n");
						for (int i = 0; i < num_readings; i++) {
							printf_s("%lf\n", readings[i].temperature);
							fprintf_s(aFile, "%lf\n", readings[i].temperature);
						}
						qsort(readings, num_readings, sizeof(struct readings), Ascend2);
						printf_s("Wind Direction: \n");
						fprintf_s(aFile, "Wind Direction: \n");
						for (int i = 0; i < num_readings; i++) {
							printf_s("%lf\n", readings[i].wind_direction);
							fprintf_s(aFile, "%lf\n", readings[i].wind_direction);
						}
						qsort(readings, num_readings, sizeof(struct readings), Ascend3);
						printf_s("Wind Speed: \n");
						fprintf_s(aFile, "Wind Speed: \n");
						for (int i = 0; i < num_readings; i++) {
							printf_s("%lf\n", readings[i].wind_speed);
							fprintf_s(aFile, "%lf\n", readings[i].wind_speed);
						}

						tmp = localtime(&readings[0].time);
						strftime(my_time, sizeof(my_time), "%x - %I:%M%p", tmp);
						printf_s("Date & Time: %s\n", my_time);
						fprintf_s(aFile, "Date & Time: %s\n", my_time);
						fclose(aFile);
				}

			}
			else { printf_s("Error: %d", error); }


		}

	}

		if (option == 5)
		{
			free(readings); // Clearing allocated memory
			exit(0); // Exiting Program
		}
	
	free(readings); // Clears allocated memory incase user exits program but doesnt select option 5
	return 0;
}