/*
 * functions.h
 *
 *  This File contains the declarations of function used in Vehicle control system project.
 *
 *  Created on: Dec 26, 2023
 *      Author: abdalla
 */

#ifndef SRC_FUNCTIONS_H_
#define SRC_FUNCTIONS_H_

#include <stdio.h>
#include <ctype.h>     // for Tolower function to Implement error handling for user inputs

#define MAX_VEHICLE_SPEED 100		// Maximum Vehicle Speed
#define MID_VEHICLE_SPEED 30		// Medium Vehicle Speed
#define MIN_VEHICLE_SPEED 0			// Minimum Vehicle Speed

#define MAX_ROOM_TEMPERATURE 30		// Maximum Room Temperature
#define MID_ROOM_TEMPERATURE 20		// Medium Room Temperature
#define MIN_ROOM_TEMPERATURE 10		// Minimum Room Temperature

#define MAX_ENGINE_TEMPERATURE 150  // Maximum Engine Temperature
#define MID_ENGINE_TEMPERATURE 125	// Medium Engine Temperature
#define MIN_ENGINE_TEMPERATURE 100	// Minimum Engine Temperature

// if the #define set to 1 (All functions that has Engine Temperature control will compile and run)
// if the #define set to 0 (All functions that has Engine Temperature control won't compile and run)
#define WITH_ENGINE_TEMP_CONTROLLER 1

// Functions Prototype
void PrintOptionsForVehicle (void);   		// Print the start menu for the vehicle
void TakeActionForVehicle (void);			// Take action for Vehicle control based on user input
void Sensors_Set_Menu (void);				// print the sensors set menu
void TakeActionForSensor (void);			// Take action for sensors control based on user input
char Set_Traffic_light (void);				// Set the Traffic light based on the user input
void Set_Vehicle_Speed(char traffic_light); // Set the vehicle speed based on the traffic light
void Set_Room_Temperature(void);			// Set the Room Temperature based on the user input
void Set_Engine_Temperature(void);			// Set the Engine Temperature based on the user input
void Vehicle_State (void);					// Display the states of the vehicle


#endif /* SRC_FUNCTIONS_H_ */
