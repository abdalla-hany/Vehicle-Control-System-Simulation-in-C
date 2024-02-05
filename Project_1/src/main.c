/*
 * main.c
 *
 *	Vehicle control system project.
 *
 *  Created on: Dec 26, 2023
 *      Author: abdalla
 */

#include "functions.h" // Including the file that contain the functions prototype

int main (void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	PrintOptionsForVehicle(); // Display the start menu

	return 0; // Return 0 to indicate successful program execution
}
