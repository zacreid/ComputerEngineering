/*=========================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *      "Data Structures and Algorithms through C"
 *
 * Assignment:  Flight Lab 1
 *
 * File Name:   flight.c
 *
 * Description: Given a set of distances output the flight times between
 *
 * Authors:     Zac Reid 20470592
 *
 * Date:        03/10/2023
 *
 *=========================================================================*/
#include <stdio.h>
#include <math.h>

const double km_to_miles = 0.621371;
const int avg_velocity_in_miles_hour = 529;
const double avg_velocity_in_km_hour = avg_velocity_in_miles_hour / km_to_miles;

int flight_time_in_minutes(double distance_km) {
    /*
        Returns the flight time rounded to the nearest minute for a given distance
        using the avg_velocity_in_km_hour variable
    */
    const double avg_velocity_in_km_minute = avg_velocity_in_km_hour / 60;
    int flight_minutes = round(distance_km / avg_velocity_in_km_minute);
    return flight_minutes;
}

int main() {
    /* Get our users input to start performing the calculations */
    /* We set our variables to -1 to detect input errors*/
    double lower_limit = -1, upper_limit = -1, step_size = -1;
    printf("Enter the lower limit on distance in km:    ");
    scanf("%lf", &lower_limit);
    printf("Enter the upper limit on distance in km:    ");
    scanf("%lf", &upper_limit);
    printf("Enter the step size in km:                  ");
    scanf("%lf", &step_size);

    /* Check our users input is valid - we print error and exit program if detected*/
    if (lower_limit > upper_limit) {
        printf("\nERROR - lower_limit cannot be larger than upper_limit\n");
        return 0;
    }

    if (step_size <= 0) {
        printf("\nERROR - step_size must > 0\n");
        return 0;
    }

    if (upper_limit <= 0 | lower_limit < 0) {
        printf("\nERROR - lower and upper limit must be greater than 0, and upper must be non-zero\n");
        return 0;
    }

    /* Output our table showing flight distances */
    printf("\n");
    printf("=============================================\n");
    printf("| distance (km) |    hours    |   minutes   |\n");
    printf("=============================================\n");

    for (double step = lower_limit; step <= upper_limit; step += step_size) {
        int flight_minutes = flight_time_in_minutes(step);
        int hours = flight_minutes / 60, minutes = flight_minutes % 60;
        printf("|%-15.2lf|     %2d      |      %2d     |\n", step, hours, minutes);
    }

    printf("=============================================\n");

    return 0;
}