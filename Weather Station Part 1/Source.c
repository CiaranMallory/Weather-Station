#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

struct readings {
	double temperature;
	double wind_direction;
	double wind_speed;
	time_t time;
};


int main(void)
{
	struct readings* readings = NULL;
	int num_readings = 0;
	printf_s("Welcome to Weather Station Program\n");
	printf_s("Please enter the number of readings you wish to log: \n");
	scanf_s("%d", &num_readings);
	readings = malloc(sizeof(struct readings) * num_readings);

	// Declaration for getting time and date 
	time_t t;
	struct tm* tmp;
	char my_time[20];
	time(&t);

	// Receiving values from the User
	for (int i = 0; i < num_readings; i++)
	{
		printf_s("Please enter Temperature in Degress Celcius: \n");
		scanf_s("%lf", &readings[i].temperature);
		printf_s("Please enter Wind Direction in Degrees (0 = North, 90 = East, 180 = South, 270 = West): \n");
		scanf_s("%lf", &readings[i].wind_direction);
		printf_s("Please enter Wind Speed in m/s: \n");
		scanf_s("%lf", &readings[i].wind_speed);
		readings[i].time = time(NULL);
		tmp = localtime(&t);
		// Getting the system time and date
		// localtime() uses the time pointed by t, 
		// to fill a tm structure with the  
		// values that represent the  
		// corresponding local time.
		strftime(my_time, sizeof(my_time), "%x - %I:%M%p", tmp);
		// Using strftime function to display time in a human readable manner
		printf_s("Date & Time: %s\n", my_time);
	}

	// Opening Binary file for writing
	FILE* pFile;
	errno_t error;

	error = fopen_s(&pFile, "Weather.bin", "ab"); // Using ab mode so that the file contents are not destroyed upon start-up
	if (error == 0) // Checking that the file opened successfully
	{
		fwrite(&num_readings, sizeof(int), 1, pFile); // Writing the number of readings entered to the file first
		fwrite(readings, sizeof(struct readings), num_readings, pFile); // Writing the values to the file
		fclose(pFile);
	}
	else
	{
		printf_s("There was an error: %d", error); // If there is an error opening the file it will be displayed
	}

	free(readings); // Clearing allocated memory

	return 0;
}