/*=========================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *      "Data Structures and Algorithms through C"
 *
 * Assignment:  Find root of a cubic function - Lab 2
 *
 * File Name:   root.c
 *
 * Description: find one root of the cubic using an efficient search
 *              method called “the bisection method”
 *
 * Authors:     Zac Reid 20470592
 *
 * Date:        24/10/2023
 *
 *=========================================================================*/

/*==================================================================
 * Systems header files
 *==================================================================*/
#include <stdio.h>
#include <math.h>

/*==================================================================
 * Constant definitions
 *==================================================================*/
#define TOLERANCE 0.000001
#define STARTING_N 1000.0

/*==================================================================
 * Function definitions
 *==================================================================*/

double cubic_function(double a, double b, double c, double d, double x) {
    /*
        Simple cubic function calculates f(x)=ax^3+bx^2+cx+d
    */
    return a * x * x * x + b * x * x + c * x + d;
}

double bisection_method(double a, double b, double c, double d, double l, double u, double tolerance) {
    /*
        Estimates and finds a root of a cubic function using the bisection method
        Takes the parameters for a cubic function (a, b, c, d)
        Takes a search interval (l, u)
        and takes a tolerance to which we reduce our search area to if root is not found
        returns the midpoint of the search interval or the exact root
    */
    double midpoint;
    while ((u - l) >= tolerance) {
        midpoint = (l + u) / 2;

        double cubic_func_mid = cubic_function(a, b, c, d, midpoint);

        if (cubic_func_mid == 0) {
            return midpoint;
        }

        /* We get our function at point l and multiply by our function on the
           midpoint of our interval to get if is negative. If negative we have
           two different signs and can move our interval u to midpoint else we
           can move interval l to m and try again.
        */
        if (cubic_function(a, b, c, d, l) * cubic_func_mid < 0) {
            u = midpoint;
        } else {
            l = midpoint;
        }
    }

    return (l + u) / 2;
}

int main() {
    /*
        Our main function gives a welcome banner to user at start of program.
        Run the inital run of our program, and then prompt user if they wish
        to run a calculation again. If user inputs y or Y we run it again.
        (without the welcome banner)
    */
    printf("************************************************\n");
    printf("Welcome to the cubic root estimator.\n");
    printf("This estimates the value of one root of\n");
    printf("f(x)=ax^3+bx^2+cx+d\n");
    printf("************************************************\n\n");
    
    char to_continue;

    do {
        double a, b, c, d;
        double l, u;

        printf("Enter the coefficients (a, b, c, d): ");
        scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

        /*
            Using our STARTING_N as defined at the head of our program we can
            start the search for a interval sufficiantly big enough so that we
            can ensure we can always find a root.

            If we can evalucate our function at both intervals to check if the
            multiple of the two are positive or negative, if positive we know
            that both signs are the same and the interval does not change sign
            in the interval, therfore we can double the interval size and try
            again to find a suitable interval
        */
        double N = STARTING_N;
        do {
            l = -N;
            u = N;
            N *= 2;
        } while (cubic_function(a, b, c, d, l) * cubic_function(a, b, c, d, u) > 0);

        double root = bisection_method(a, b, c, d, l, u, TOLERANCE);

        printf("\nThere is a root at: x = %.3lf\n", root);

        printf("Do you wish to try another cublic [y/n]: ");
        scanf(" %c", &to_continue);
    } while (to_continue == 'y' || to_continue == 'Y');

    return 0;
}