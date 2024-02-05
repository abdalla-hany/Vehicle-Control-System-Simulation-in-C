/*
 * functions.c
 *
 *  This File contains the definitions of function and variables used in Vehicle control system project.
 *
 *  Created on: Dec 26, 2023
 *      Author: abdalla
 */

#include "functions.h" // Including the file that contain the functions prototype

char Status_Input;
enum state{OFF, ON};
enum state Engine_state, AC_state, Engine_Temperature_Controller_State;
const char *state[2] = {"OFF","ON"};

// Setting initial values for sensors reads
int Vehicle_Speed = MID_VEHICLE_SPEED;
int Room_Temperature = MID_ROOM_TEMPERATURE;

// If WITH_ENGINE_TEMP_CONTROLLER = 1 compile and run this code other wise don't compile or run this part of code
#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
int Engine_Temperature = MID_ENGINE_TEMPERATURE;
#endif


/**
 * Main Menu
 *
 * Displays the main menu options for vehicle control and handles user input for the main menu.
 */
void PrintOptionsForVehicle (void)
{
	// Keep asking the user to choose an option until he enters a valid option
	do{
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n\n");
		scanf(" %c" , &Status_Input);
		Status_Input = tolower(Status_Input); // Handle capital letters
	}while( (Status_Input != 'a') && (Status_Input != 'b') && (Status_Input != 'c'));
	TakeActionForVehicle(); // Taking action for the vehicle based on the user input
}

/**
 * Take Action For Vehicle
 *
 * Handles the user input and decide what to do.
 */
void TakeActionForVehicle (void)
{
	// If user chose to turn the vehicle engine ON
	if (Status_Input == 'a')
	{
		printf("Turn on the vehicle engine\n");
		Engine_state = ON;  // Turn on the Engine
		Sensors_Set_Menu(); // Display the sensors menu
	}

	// If user chose to turn the vehicle engine OFF
	else if (Status_Input == 'b')
	{
		printf("b. Turn off the vehicle engine\n\n");
		Engine_state = OFF;  // Turn OFF the Engine
		PrintOptionsForVehicle(); // Return to the main menu
	}

	// If user chose to quit the system
	else
	{
		printf("Quit the system\n");

		// Turn OFF all the systems
		Engine_state = OFF;
		AC_state = OFF;
		Engine_Temperature_Controller_State = OFF;
		return; // Return to the main function and End program
	}
}

/**
 * Sensors Menu
 *
 * Displays the Sensors menu options for Sensors control and handle user input for the Sensors menu.
 */
void Sensors_Set_Menu (void)
{
	// Keep asking the user to chose an option until he enters a valid option
	do{
		printf("\na. Turn off the engine\n");
		printf("b. Set the traffic light color\n");
		printf("c. Set the room temperature (Temperature Sensor)\n");

		// If WITH_ENGINE_TEMP_CONTROLLER = 1 compile and run this code other wise don't compile or run this part of code
		#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
		printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
		#endif

		scanf(" %c" , &Status_Input);
		Status_Input = tolower(Status_Input); // Handle capital letters
	}while( (Status_Input != 'a') && (Status_Input != 'b') && (Status_Input != 'c') && (Status_Input != 'd'));
	TakeActionForSensor();  // Taking action for the sensors based on the user input
}

/**
 * Take Action For Sensors
 *
 * Handles the user input and decide what to do for sensors.
 */
void TakeActionForSensor (void)
{
	char traffic_light;

	// If user chose to turn OFF the Engine
	if (Status_Input == 'a')
	{
		printf("Turn off the engine\n\n");
		Engine_state = OFF;
		PrintOptionsForVehicle(); // Return to the Main menu
	}

	// If user chose to set the traffic light color
	else if(Status_Input == 'b')
	{
		printf("Set the traffic light color\n\n");
		traffic_light = Set_Traffic_light(); // Set the traffic light based on user input
		Set_Vehicle_Speed(traffic_light);    // Set the vehicle speed based on traffic light color
		Vehicle_State();					 // Show the Vehicle state menu
		Sensors_Set_Menu();					 // Display sensors menu
	}

	// If user chose to set the Room Temperature
	else if(Status_Input == 'c')
	{
		printf("Set the Room Temperature\n\n");
		Set_Room_Temperature(); // Set Room Temperature based on user input
		Vehicle_State();		// show Vehicle state menu
		Sensors_Set_Menu();		// Display sensors menu
	}

	// If WITH_ENGINE_TEMP_CONTROLLER = 1 compile and run this code other wise don't compile or run this part of code
	#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
	else if (Status_Input == 'd') // If user chose to Set Engine Temperature
	{
		printf("Set the Engine Temperature\n\n");
		Set_Engine_Temperature(); // Set Room Temperature based on user input
		Vehicle_State();          // show Vehicle state menu
		Sensors_Set_Menu();       // Display sensors menu
	}
	#endif

	// If the user enters d and the Engine temp control is define to zero then return to the Sensor Menu
	else
	{
		Sensors_Set_Menu();
	}
}

/**
 * Set Traffic light
 *
 * Handles the user input and change the color.
 */
char Set_Traffic_light (void)
{
	char traffic_light;

	// Keep asking the user to chose an option until he enters a valid option
	do{
		printf("Enter the required color :");
		scanf(" %c", &traffic_light);
		traffic_light = tolower(traffic_light);
	}while ((traffic_light != 'g') && (traffic_light != 'o') && (traffic_light != 'r') );

	return traffic_light; // return the color that user chose
}

/**
 * Set Vehicle Speed
 *
 * Handles the user input and change the speed of the vehicle.
 */
void Set_Vehicle_Speed(char traffic_light)
{
	switch(traffic_light){

	// If the user chose green light
	case 'g':
		Vehicle_Speed = MAX_VEHICLE_SPEED;
		break;

	// If the user chose orange light
	case 'o':
		Vehicle_Speed = MID_VEHICLE_SPEED;
		AC_state = ON;
		Room_Temperature = (float)Room_Temperature * (5.0/4.0) + 1;

		// If WITH_ENGINE_TEMP_CONTROLLER = 1 compile and run this code other wise don't compile or run this part of code
		#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
		Engine_Temperature_Controller_State = ON;
		Engine_Temperature = (float)Engine_Temperature * (5.0/4.0) + 1;
		#endif

		break;

	// If user chose red light
	default:
		Vehicle_Speed = MIN_VEHICLE_SPEED;
	}
}

/**
 * Set Room Temperature
 *
 * Handles the user input and change the Room Temperature.
 */
void Set_Room_Temperature(void)
{
	printf("Enter the Room Temperature :");
	scanf("%d", &Room_Temperature);
	if (Room_Temperature < MIN_ROOM_TEMPERATURE)
	{
		AC_state = ON;
		Room_Temperature = MID_ROOM_TEMPERATURE;
	}
	else if (Room_Temperature > MAX_ROOM_TEMPERATURE)
	{
		AC_state = ON;
		Room_Temperature = MID_ROOM_TEMPERATURE;
	}
	else
	{
		AC_state = OFF;
	}
}

/**
 * Set Engine Temperature
 *
 * Handles the user input and change the Engine Temperature.
 */
// If WITH_ENGINE_TEMP_CONTROLLER = 1 compile and run this code other wise don't compile or run this part of code
#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
void Set_Engine_Temperature(void)
{
	printf("Enter the Engine Temperature :");
	scanf("%d", &Engine_Temperature);
	if (Engine_Temperature < MIN_ENGINE_TEMPERATURE)
	{
		Engine_Temperature_Controller_State = ON;
		Engine_Temperature = MID_ENGINE_TEMPERATURE;
	}
	else if (Engine_Temperature > MAX_ENGINE_TEMPERATURE)
	{
		Engine_Temperature_Controller_State = ON;
		Engine_Temperature = MID_ENGINE_TEMPERATURE;
	}
	else
	{
		Engine_Temperature_Controller_State = OFF;
	}
}
#endif

/**
 * Vehicle Menu state
 *
 * Displays All Vehicle states.
 */
void Vehicle_State (void)
{
	printf("\nEngine is %s\n", state[Engine_state]);
	printf("AC is %s\n", state[AC_state]);
	printf("Vehicle Speed : %d Km/Hr \n", Vehicle_Speed);
	printf("Room Temperature : %d C\n",Room_Temperature);

	// If WITH_ENGINE_TEMP_CONTROLLER = 1 compile and run this code other wise don't compile or run this part of code
	#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
	printf("Engine Temperature control is %s\n", state[Engine_Temperature_Controller_State]);
	printf("Engine Temperature : %d C\n", Engine_Temperature);
	#endif
}
