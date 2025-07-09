#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


//function related to the admin
void AdminPanel();
void AdminSignUp();
void AdminLogin();
void AddBusesInfo();
void DisplayAllBuses();
void UpdateBusesInfo();
void DeleteBusesInfo();

//Function Related to the User
void UserPanel();
void UserSignUp();
void UserLogin();
void SearchBuses();

//Function Related to Booking Seats
void BookSeat(int userIndex);
void DisplaySeatsStatus(int busIndex);
void CancelBooking(int userIndex);

//Function to save data
void SaveDataToFile();
void LoadDataFromFile();


//structure for information of the buses
struct Buses {
	char DriverName[25];
	char BusName[50];
	char Routes[70];

	char DepartureTime[10];
	char ArrivalTime[10];
} Buses_Info[10];
int BusesCount=0;

//structure for Booking the Seats of Buses
struct Booking {
	char Seats[50];
	int fare;
	char IsAvailable[4];
	int bookedByUserIndex ;

} Booking_Info[10][50]; // 10 buses, each with 50 seats


//structure for information of Passenger
struct User {
	char UserName[25];
	char UserEmail[30];
	char gender; // 'M' or 'F'
	char UserPassword[15];
} user_Info[2000];
int userCount = 0;

//structure for information of the Admin
struct Admin {
	char AdminName[25];
	char AdminPassword[15];
	int Restriction;
} Admin_Info;

//Files
FILE *busesFile;
FILE *userFile;
FILE *adminFile;

int main() {
	system("color 70");
	// Before LoadDataFromFile()
	for(int bus=0; bus<10; bus++) {
		for(int seat=0; seat<50; seat++) {
			sprintf(Booking_Info[bus][seat].Seats, "Seat #%d", seat+1);
			strcpy(Booking_Info[bus][seat].IsAvailable, "yes");
			Booking_Info[bus][seat].fare = 1000;
			Booking_Info[bus][seat].bookedByUserIndex = -1;
		}
	}
	LoadDataFromFile();


	int choice;
	do {
		printf("\n\t\t\t\t\t=== Bus Reservation System ===\n\n\n");

		printf("1.	Admin Panel.\n");
		printf("2.	User Panel.\n");
		printf("3.	Exit.\n");

		printf("\n\t\t\tChoice: ");
		scanf("%d",&choice);
		getchar(); //buffer control

		switch(choice) {
			case 1:
				AdminPanel();
				break;
			case 2:
				UserPanel();
				break;
			case 3:
				printf("\n\t\t\t\t\t=== Thank You %c ===\n",3);
				exit(0);
				break;

			default:
				printf("Invalid Selection. Plzz Try Again.\n");
		}
	} while(choice != 3);

	return 0;
}

//Admin Panel
void AdminPanel() {
	int choice;

	do {
		printf("\n\t\t\t\t\t=== Admin Panel ===\n\n\n");

		printf("1.	Admin SignUp.\n");
		printf("2.	Admin Login.\n");
		printf("3.	Go Back <----.\n");
		printf("4.	Exit.\n");

		printf("\n\t\t\tChoice: ");
		scanf("%d",&choice);
		getchar(); //buffer control

		switch(choice) {
			case 1:
				AdminSignUp();
				break;
			case 2:
				AdminLogin();
				break;
			case 3:
				return;
				break;
			case 4:
				printf("\n\t\t\t\t\t=== Thank You %c ===\n",3);
				exit(0);
				break;

			default:
				printf("Invalid Selection. Plzz Try Again.\n");
		}

	} while(choice != 4);
}

void AdminSignUp() {

	if(Admin_Info.Restriction == 1) {
		printf("Admin Already Exist.\n");
		return;
	}

	printf("\n\t\t\t\t\t=== Admin SignUp ===\n\n\n");
	printf("Admin Name: ");
	fgets(Admin_Info.AdminName, sizeof(Admin_Info.AdminName), stdin);
	Admin_Info.AdminName[strcspn(Admin_Info.AdminName, "\n")] = 0;

	printf("Admin Password: ");
	fgets(Admin_Info.AdminPassword, sizeof(Admin_Info.AdminPassword), stdin);
	Admin_Info.AdminPassword[strcspn(Admin_Info.AdminPassword, "\n")] = 0;

	Admin_Info.Restriction = 1;
	SaveDataToFile();

}

void AdminLogin() {
	char NameOfAdmin[25];
	char PassOfAdmin[15];

	printf("\n\t\t\t\t\t=== Admin Login ===\n\n\n");
	printf("Admin Name: ");
	fgets(NameOfAdmin, sizeof(NameOfAdmin), stdin);
	NameOfAdmin[strcspn(NameOfAdmin, "\n")] = 0;

	printf("Admin Password: ");
	fgets(PassOfAdmin, sizeof(PassOfAdmin), stdin);
	PassOfAdmin[strcspn(PassOfAdmin, "\n")] = 0;

	if(strcmp(NameOfAdmin,Admin_Info.AdminName)==0 && strcmp(PassOfAdmin,Admin_Info.AdminPassword)==0) {
		printf("\n\t\t\t\t\t=== Successfully Log In ===\n\n\n");

		int choice;
		do {
			printf("1.	Add Buses Info.\n");
			printf("2.	Display All Buses.\n");
			printf("3.	Update Buses Info.\n");
			printf("4.	Delete Buses Info.\n");
			printf("5.	Go Back <----.\n");
			printf("6.	Exit.\n");

			printf("\n\t\t\tChoice: ");
			scanf("%d",&choice);
			getchar(); //buffer control

			switch(choice) {
				case 1:
					AddBusesInfo();
					break;
				case 2:
					DisplayAllBuses();
					break;
				case 3:
					UpdateBusesInfo();
					break;
				case 4:
					DeleteBusesInfo();
					break;
				case 5:
					return;
					break;
				case 6:
					printf("\n\t\t\t\t\t=== Thank You %c ===\n",3);
					exit(0);
					break;
				default:
					printf("Invalid Selection. Plzz Try Again.\n");

			}
		} while(choice != 5);
	} else {
		printf("\n\t\t\t\t\t=== Access Denied ===\n");
		printf("\n\t\t\t\t\t=== Try Again ===\n\n\n");
	}
}

void AddBusesInfo() {

	printf("\n\t\t\t\t\t=== Add Buses information ===\n\n\n");

	if (BusesCount >= 10) {
		printf("Maximum bus limit reached.\n");
		return;
	}

	printf("\nDriver Name: ");
	fgets(Buses_Info[BusesCount].DriverName, sizeof(Buses_Info[BusesCount].DriverName), stdin);
	Buses_Info[BusesCount].DriverName[strcspn(Buses_Info[BusesCount].DriverName, "\n")] = 0;

	printf("\nBus Name: ");
	fgets(Buses_Info[BusesCount].BusName, sizeof(Buses_Info[BusesCount].BusName), stdin);
	Buses_Info[BusesCount].BusName[strcspn(Buses_Info[BusesCount].BusName, "\n")] = 0;

	printf("\nRoutes: ");
	fgets(Buses_Info[BusesCount].Routes, sizeof(Buses_Info[BusesCount].Routes), stdin);
	Buses_Info[BusesCount].Routes[strcspn(Buses_Info[BusesCount].Routes, "\n")] = 0;
	for (int i = 0; Buses_Info[BusesCount].Routes[i] != '\0'; i++) {
		Buses_Info[BusesCount].Routes[i] = toupper(Buses_Info[BusesCount].Routes[i]);
	}


	printf("\nDeparture Time: ");
	fgets(Buses_Info[BusesCount].DepartureTime, sizeof(Buses_Info[BusesCount].DepartureTime), stdin);
	Buses_Info[BusesCount].DepartureTime[strcspn(Buses_Info[BusesCount].DepartureTime, "\n")] = 0;

	printf("\nArrival Time: ");
	fgets(Buses_Info[BusesCount].ArrivalTime, sizeof(Buses_Info[BusesCount].ArrivalTime), stdin);
	Buses_Info[BusesCount].ArrivalTime[strcspn(Buses_Info[BusesCount].ArrivalTime, "\n")] = 0;


	BusesCount++;
	printf("\n\t\t\t\t\t=== Bus information added successfully! ===\n");
	SaveDataToFile();
}

void DisplayAllBuses() {
	printf("\n\t\t\t\t\t=== Display All Buses ===\n\n\n");
	if (BusesCount == 0) {
		printf("\nNo buses available.\n");
		return;
	}

	printf("\n\t\t\t=== All Buses ===\n");
	for (int i = 0; i < BusesCount; i++) {
		printf("\nBus #%d\n", i + 1);
		printf("Driver Name: %s\n", Buses_Info[i].DriverName);
		printf("Bus Name: %s\n", Buses_Info[i].BusName);
		printf("Routes: %s\n", Buses_Info[i].Routes);
		printf("Departure Time: %s\n", Buses_Info[i].DepartureTime);
		printf("Arrival Time: %s\n", Buses_Info[i].ArrivalTime);
	}
}

void UpdateBusesInfo() {
	printf("\n\t\t\t\t\t=== Update Buses information ===\n\n\n");
	DisplayAllBuses();

	if (BusesCount == 0)
		return;

	int index;
	printf("\nEnter the bus number to update (1 to %d): ", BusesCount);
	scanf("%d", &index);
	getchar(); // buffer Control

	if (index < 1 || index > BusesCount) {
		printf("Invalid bus number!\n");
		return;
	}

	index--; // Convert to 0-based index

	printf("\n--- Updating Bus #%d ---\n", index + 1);

	printf("\nDriver Name: ");
	fgets(Buses_Info[index].DriverName, sizeof(Buses_Info[index].DriverName), stdin);
	Buses_Info[index].DriverName[strcspn(Buses_Info[index].DriverName, "\n")] = 0;

	printf("\nBus Name: ");
	fgets(Buses_Info[index].BusName, sizeof(Buses_Info[index].BusName), stdin);
	Buses_Info[index].BusName[strcspn(Buses_Info[index].BusName, "\n")] = 0;

	printf("\nRoutes: ");
	fgets(Buses_Info[index].Routes, sizeof(Buses_Info[index].Routes), stdin);
	Buses_Info[index].Routes[strcspn(Buses_Info[index].Routes, "\n")] = 0;

	printf("\nDeparture Time: ");
	fgets(Buses_Info[index].DepartureTime, sizeof(Buses_Info[index].DepartureTime), stdin);
	Buses_Info[index].DepartureTime[strcspn(Buses_Info[index].DepartureTime, "\n")] = 0;

	printf("\nArrival Time: ");
	fgets(Buses_Info[index].ArrivalTime, sizeof(Buses_Info[index].ArrivalTime), stdin);
	Buses_Info[index].ArrivalTime[strcspn(Buses_Info[index].ArrivalTime, "\n")] = 0;

	printf("\n\t\t\t\t\t=== Bus updated successfully! ===\n\n\n");
	SaveDataToFile();

}

void DeleteBusesInfo() {

	printf("\n\t\t\t\t\t=== Delete Buses information ===\n\n\n");
	DisplayAllBuses();

	if (BusesCount == 0) return;

	int index;
	printf("\nEnter the bus number to delete (1 to %d): ", BusesCount);
	scanf("%d", &index);
	getchar(); //buffer control

	if (index < 1 || index > BusesCount) {
		printf("Invalid bus number!\n");
		return;
	}

	index--; // Convert to 0-based index

	// Shift all buses after the deleted one
	for (int i = index; i < BusesCount - 1; i++) {
		Buses_Info[i] = Buses_Info[i + 1];
	}

	BusesCount--;

	printf("\n\t\t\t\t\t=== Bus deleted successfully! ===\n\n\n");
	SaveDataToFile();

}

//User Panel
void UserPanel() {
	int choice;

	do {
		printf("\n\t\t\t\t\t=== User Panel ===\n\n\n");

		printf("1.	User Sign Up.\n");
		printf("2.	User Login.\n");
		printf("3.	Go Back <----.\n");
		printf("4.	Exit.\n");

		printf("\n\t\t\tChoice: ");
		scanf("%d", &choice);
		getchar(); // buffer control

		switch (choice) {
			case 1:
				UserSignUp();
				break;
			case 2:
				UserLogin();
				break;
			case 3:
				return;
			case 4:
				printf("\n\t\t\t\t\t=== Thank You %c ===\n", 3);
				exit(0);
			default:
				printf("Invalid Selection. Please Try Again.\n");
		}

	} while (choice != 4);
}

void UserSignUp() {
	printf("\n\t\t\t\t\t=== User Sign Up ===\n\n\n");

	if (userCount >= 2000) {
		printf("User limit reached.\n");
		return;
	}

	printf("User Name: ");
	fgets(user_Info[userCount].UserName, sizeof(user_Info[userCount].UserName), stdin);
	user_Info[userCount].UserName[strcspn(user_Info[userCount].UserName, "\n")] = 0;

	while(1) {
	    printf("Enter Email: ");
	    fgets(user_Info[userCount].UserEmail, sizeof(user_Info[userCount].UserEmail), stdin);
	    user_Info[userCount].UserEmail[strcspn(user_Info[userCount].UserEmail, "\n")] = 0;
	    if(strchr(user_Info[userCount].UserEmail, '@') && strchr(user_Info[userCount].UserEmail, '.')) {
	        break;
	    }
	    printf("Invalid Email Try Again with proper Format\n");
	}

	printf("Enter Password: ");
	fgets(user_Info[userCount].UserPassword, sizeof(user_Info[userCount].UserPassword), stdin);
	user_Info[userCount].UserPassword[strcspn(user_Info[userCount].UserPassword, "\n")] = 0;

	printf("Enter Gender (M/F): ");
	scanf(" %c", &user_Info[userCount].gender);
	user_Info[userCount].gender = toupper(user_Info[userCount].gender); //convert lowerCase Character to uperCase like m to M
	getchar(); // clear buffer


	userCount++;
	printf("\n\t\t\t\t=== Sign Up Successful! ===\n");
	
	SaveDataToFile();
}

void UserLogin() {
	char email[30], password[15];
	int found = 0;

	printf("\n\t\t\t\t\t=== User Login ===\n\n\n");

	printf("Enter Email: ");
	fgets(email, sizeof(email), stdin);
	email[strcspn(email, "\n")] = 0;

	printf("Enter Password: ");
	fgets(password, sizeof(password), stdin);
	password[strcspn(password, "\n")] = 0;

	for (int i = 0; i < userCount; i++) {
		if (strcmp(email, user_Info[i].UserEmail) == 0 &&
		        strcmp(password, user_Info[i].UserPassword) == 0) {
			found = 1;
			printf("\n\t\t\t\t=== Login Successful! ===\n");
			printf("\n\t\t\tWelcome %s!\n\n", user_Info[i].UserName);

			// User Menu after successful login
			int userChoice;
			do {
				printf("\n\t\t\t=== User Dashboard ===\n");
				printf("1. View All Buses\n");
				printf("2. Book Seat\n");
				printf("3. Search Buses by Route/Time\n");
				printf("4. Cancel Booking\n"); // <-- Add this line
				printf("5. Logout\n");
				printf("6. Exit\n");



				printf("\n\t\t\tChoice: ");
				scanf("%d", &userChoice);
				getchar(); // buffer control

				switch(userChoice) {
					case 1:
						DisplayAllBuses();
						break;
					case 2:
						BookSeat(i);
						break;
					case 3:
						SearchBuses();
						break;
					case 4:
						CancelBooking(i); // <-- Add this line
						break;
					case 5:
						return;
					case 6:
						printf("\n\t\t\t\t=== Thank You %c ===\n", 3);
						exit(0);
					default:
						printf("Invalid choice. Try again.\n");
				}



			} while(userChoice != 5);

			break;
		}
	}

	if (!found) {
		printf("\n\t\t\t\t=== Invalid Credentials. Try Again ===\n");
	}
}

//Search Buses
void SearchBuses() {
	char keyword[50];
	int found = 0;

	printf("\n\t\t\t\t=== Search Buses ===\n\n");
	printf("Enter Route or Departure Time to search: ");
	fgets(keyword, sizeof(keyword), stdin);
	keyword[strcspn(keyword, "\n")] = 0;
	// In SearchBuses()
	for(int i=0; keyword[i] != '\0'; i++) {
		keyword[i] = toupper(keyword[i]);
	}


	printf("\nSearch Results for \"%s\":\n", keyword);

	for (int i = 0; i < BusesCount; i++) {
		if (strstr(Buses_Info[i].Routes, keyword) != NULL ||
		        strcmp(Buses_Info[i].DepartureTime, keyword) == 0) {

			found = 1;
			printf("\nBus #%d\n", i + 1);
			printf("Driver Name: %s\n", Buses_Info[i].DriverName);
			printf("Bus Name: %s\n", Buses_Info[i].BusName);
			printf("Routes: %s\n", Buses_Info[i].Routes);
			printf("Departure Time: %s\n", Buses_Info[i].DepartureTime);
			printf("Arrival Time: %s\n", Buses_Info[i].ArrivalTime);
		}
	}

	if (!found) {
		printf("\nNo buses found matching \"%s\".\n", keyword);
	}
}

//Booking Seats
void BookSeat(int userIndex) {
	printf("\n\t\t\t\t=== Book a Seat ===\n\n");

	if (BusesCount == 0) {
		printf("No buses available to book.\n");
		return;
	}

	DisplayAllBuses();

	// Get bus selection with validation
	int busChoice;
	while(1) {
		printf("\nSelect a Bus (1 to %d, 0 to cancel): ", BusesCount);
		if(scanf("%d", &busChoice) != 1) {
			printf("Invalid input. Please enter a number.\n");
			while(getchar() != '\n');
			continue;
		}
		getchar();

		if(busChoice == 0) {
			printf("Booking cancelled.\n");
			return;
		}
		if(busChoice < 1 || busChoice > BusesCount) {
			printf("Invalid bus selection. Please try again.\n");
			continue;
		}
		break;
	}

	DisplaySeatsStatus(busChoice-1);

	// Get seat selection with validation
	int seatNumber;
	while(1) {
		printf("\nEnter seat number to book (1-50, 0 to cancel): ");
		if(scanf("%d", &seatNumber) != 1) {
			printf("Invalid input. Please enter a number.\n");
			while(getchar() != '\n');
			continue;
		}
		getchar();

		if(seatNumber == 0) {
			printf("Booking cancelled.\n");
			return;
		}
		if(seatNumber < 1 || seatNumber > 50) {
			printf("Invalid seat number. Please try again.\n");
			continue;
		}
		if(strcmp(Booking_Info[busChoice-1][seatNumber-1].IsAvailable, "no") == 0) {
			printf("Seat already booked! Please choose another.\n");
			continue;
		}
		break;
	}

	// Confirmation
	printf("\nConfirm booking for Seat %d on %s (Y/N)? ",
	       seatNumber, Buses_Info[busChoice-1].BusName);
	char confirm;
	scanf(" %c", &confirm);
	getchar();

	if(toupper(confirm) != 'Y') {
		printf("Booking cancelled.\n");
		return;
	}

	// Complete booking
	sprintf(Booking_Info[busChoice-1][seatNumber-1].Seats, "Seat #%d - %s", seatNumber, Buses_Info[busChoice-1].BusName);
	strcpy(Booking_Info[busChoice-1][seatNumber-1].IsAvailable, "no");
	Booking_Info[busChoice-1][seatNumber-1].bookedByUserIndex = userIndex;

	printf("\n\t\t\t=== Booking Successful! ===\n");
	printf("Passenger: %s\n", user_Info[userIndex].UserName);
	printf("Gender: %c\n", user_Info[userIndex].gender);
	printf("Bus Name: %s\n", Buses_Info[busChoice-1].BusName);
	printf("Route: %s\n", Buses_Info[busChoice-1].Routes);
	printf("Departure: %s\n", Buses_Info[busChoice-1].DepartureTime);
	printf("Arrival: %s\n", Buses_Info[busChoice-1].ArrivalTime);
	printf("Seat Number: %d\n", seatNumber);
	printf("Fare: Rs. %d\n", Booking_Info[busChoice-1][seatNumber-1].fare);

	SaveDataToFile();
}

void DisplaySeatsStatus(int busIndex) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Display bus information
	printf("\n\t\t=== Seat Availability for Bus: %s ===\n", Buses_Info[busIndex].BusName);
	printf("\t\tRoute: %s | Dep: %s | Arr: %s\n\n",
	       Buses_Info[busIndex].Routes,
	       Buses_Info[busIndex].DepartureTime,
	       Buses_Info[busIndex].ArrivalTime);

	// Seat legend
	printf("Legend: ");
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf(" Available ");
	SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf(" Booked(F) ");
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf(" Booked(M) ");
	SetConsoleTextAttribute(hConsole, 0x07);
	printf("\n\n");

	// Display seats in a 5x10 grid
	for (int row = 0; row < 5; row++) {
		printf("\t");
		for (int col = 0; col < 10; col++) {
			int seatNum = row * 10 + col;

			if (strcmp(Booking_Info[busIndex][seatNum].IsAvailable, "yes") == 0) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf(" %2d ", seatNum + 1);
			} else {
				int bookedIndex = Booking_Info[busIndex][seatNum].bookedByUserIndex;
				if (user_Info[bookedIndex].gender == 'F') {
					SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				} else {
					SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				printf(" %2d ", seatNum + 1);
			}
			SetConsoleTextAttribute(hConsole, 0x07);
			printf(" "); // Space between seats
		}
		printf("\n\n");
	}
	printf("\n");
}

//Save Data for Buses
void SaveDataToFile() {
	// Open file for writing
	busesFile = fopen("buses.txt", "w"); // Using text mode for writing
	adminFile = fopen("admin.txt", "w");
	userFile = fopen("user.txt", "w");
	if (busesFile == NULL || adminFile == NULL || userFile == NULL) {
		printf("Error opening file for saving data");
		return;
	}

	// Save admin information first
	fprintf(adminFile, "%d\n", Admin_Info.Restriction);
	if (Admin_Info.Restriction) {
		fprintf(adminFile, "%s\n", Admin_Info.AdminName);
		fprintf(adminFile, "%s\n", Admin_Info.AdminPassword);
	}

	// Save number of buses
	fprintf(busesFile, "%d\n", BusesCount);

	// Save buses information
	for (int i = 0; i < BusesCount; i++) {
		fprintf(busesFile, "%s\n", Buses_Info[i].DriverName);
		fprintf(busesFile, "%s\n", Buses_Info[i].BusName);
		fprintf(busesFile, "%s\n", Buses_Info[i].Routes);
		fprintf(busesFile, "%s\n", Buses_Info[i].DepartureTime);
		fprintf(busesFile, "%s\n", Buses_Info[i].ArrivalTime);
	}

	// Save user information
	fprintf(userFile, "%d\n", userCount);
	for (int i = 0; i < userCount; i++) {
		fprintf(userFile, "%s\n", user_Info[i].UserName);
		fprintf(userFile, "%s\n", user_Info[i].UserEmail);
		fprintf(userFile, "%c\n", user_Info[i].gender);
		fprintf(userFile, "%s\n", user_Info[i].UserPassword);
	}

	// Save booking information per bus
	for (int bus = 0; bus < BusesCount; bus++) {
		for (int seat = 0; seat < 50; seat++) {
			fprintf(busesFile, "%s\n", Booking_Info[bus][seat].Seats);
			fprintf(busesFile, "%s\n", Booking_Info[bus][seat].IsAvailable);
			fprintf(busesFile, "%d\n", Booking_Info[bus][seat].fare);
			fprintf(busesFile, "%d\n", Booking_Info[bus][seat].bookedByUserIndex);
		}
	}

	fclose(busesFile);
	fclose(userFile);
	fclose(adminFile);

	printf("Data saved successfully!\n");
}
//Load Data for Buses
void LoadDataFromFile() {
	busesFile = fopen("buses.txt", "r");  // Using text mode for reading
	adminFile = fopen("admin.txt", "r");
	userFile = fopen("user.txt", "r");

	if (adminFile == NULL || userFile == NULL) {
		printf("No existing data found in admin.txt or user.txt. Starting with fresh system.\n");
		exit(1);
	}


	if (busesFile == NULL) {
		// No existing data file - initialize with default values
		printf("No existing data found. Starting with fresh system.\n");
		return;
	}

	// Load admin information
	fscanf(adminFile, "%d\n", &Admin_Info.Restriction);
	if (Admin_Info.Restriction) {
		fgets(Admin_Info.AdminName, sizeof(Admin_Info.AdminName), adminFile);
		fgets(Admin_Info.AdminPassword, sizeof(Admin_Info.AdminPassword), adminFile);
		// Remove newlines
		Admin_Info.AdminName[strcspn(Admin_Info.AdminName, "\n")] = 0;
		Admin_Info.AdminPassword[strcspn(Admin_Info.AdminPassword, "\n")] = 0;
	}

	// Load buses information
	fscanf(busesFile, "%d\n", &BusesCount);
	if (BusesCount > 10) {  // Ensure we don't exceed array bounds
		printf("Warning: Corrupted data - too many buses. Loading first 10.\n");
		BusesCount = 10;
	}

	for (int i = 0; i < BusesCount; i++) {
		fgets(Buses_Info[i].DriverName, sizeof(Buses_Info[i].DriverName), busesFile);
		fgets(Buses_Info[i].BusName, sizeof(Buses_Info[i].BusName), busesFile);
		fgets(Buses_Info[i].Routes, sizeof(Buses_Info[i].Routes), busesFile);
		fgets(Buses_Info[i].DepartureTime, sizeof(Buses_Info[i].DepartureTime), busesFile);
		fgets(Buses_Info[i].ArrivalTime, sizeof(Buses_Info[i].ArrivalTime), busesFile);

		// Remove trailing newlines
		Buses_Info[i].DriverName[strcspn(Buses_Info[i].DriverName, "\n")] = 0;
		Buses_Info[i].BusName[strcspn(Buses_Info[i].BusName, "\n")] = 0;
		Buses_Info[i].Routes[strcspn(Buses_Info[i].Routes, "\n")] = 0;
		Buses_Info[i].DepartureTime[strcspn(Buses_Info[i].DepartureTime, "\n")] = 0;
		Buses_Info[i].ArrivalTime[strcspn(Buses_Info[i].ArrivalTime, "\n")] = 0;
	}

	// Load user information
	fscanf(userFile, "%d\n", &userCount);
	if (userCount > 2000) {
		printf("Warning: Corrupted data - too many users. Loading first 2000.\n");
		userCount = 2000;
	}

	for (int i = 0; i < userCount; i++) {
		fgets(user_Info[i].UserName, sizeof(user_Info[i].UserName), userFile);
		fgets(user_Info[i].UserEmail, sizeof(user_Info[i].UserEmail), userFile);
		fscanf(userFile, " %c\n", &user_Info[i].gender);  // Space before %c to skip whitespace
		fgets(user_Info[i].UserPassword, sizeof(user_Info[i].UserPassword), userFile);

		// Remove newlines
		user_Info[i].UserName[strcspn(user_Info[i].UserName, "\n")] = 0;
		user_Info[i].UserEmail[strcspn(user_Info[i].UserEmail, "\n")] = 0;
		user_Info[i].UserPassword[strcspn(user_Info[i].UserPassword, "\n")] = 0;
	}

	// Load booking information per bus
	for (int bus = 0; bus < BusesCount; bus++) {
		for (int seat = 0; seat < 50; seat++) {
			fgets(Booking_Info[bus][seat].Seats, sizeof(Booking_Info[bus][seat].Seats), busesFile);
			fgets(Booking_Info[bus][seat].IsAvailable, sizeof(Booking_Info[bus][seat].IsAvailable), busesFile);
			fscanf(busesFile, "%d\n", &Booking_Info[bus][seat].fare);
			fscanf(busesFile, "%d\n", &Booking_Info[bus][seat].bookedByUserIndex);

			// Remove newlines
			Booking_Info[bus][seat].Seats[strcspn(Booking_Info[bus][seat].Seats, "\n")] = 0;
			Booking_Info[bus][seat].IsAvailable[strcspn(Booking_Info[bus][seat].IsAvailable, "\n")] = 0;

			// Validate booking data
			if (strcmp(Booking_Info[bus][seat].IsAvailable, "yes") == 0) {
				Booking_Info[bus][seat].bookedByUserIndex = -1;
			} else if (Booking_Info[bus][seat].bookedByUserIndex >= userCount) {
				printf("Warning: Invalid user reference in booking data. Marking seat as available.\n");
				strcpy(Booking_Info[bus][seat].IsAvailable, "yes");
				Booking_Info[bus][seat].bookedByUserIndex = -1;
			}
		}
	}


	fclose(busesFile);
	fclose(userFile);
	fclose(adminFile);
}

void CancelBooking(int userIndex) {
    printf("\n\t\t\t\t=== Cancel Booking ===\n\n");

    int found = 0;
    // List all bookings for this user
    for (int bus = 0; bus < BusesCount; bus++) {
        for (int seat = 0; seat < 50; seat++) {
            if (Booking_Info[bus][seat].bookedByUserIndex == userIndex &&
                strcmp(Booking_Info[bus][seat].IsAvailable, "no") == 0) {
                printf("Bus #%d: %s | Seat %d | Route: %s | Departure: %s | Arrival: %s\n",
                    bus + 1,
                    Buses_Info[bus].BusName,
                    seat + 1,
                    Buses_Info[bus].Routes,
                    Buses_Info[bus].DepartureTime,
                    Buses_Info[bus].ArrivalTime
                );
                found = 1;
            }
        }
    }

    if (!found) {
        printf("You have no bookings to cancel.\n");
        return;
    }

    int busChoice, seatChoice;
    printf("\nEnter Bus Number to cancel booking (0 to cancel): ");
    scanf("%d", &busChoice);
    getchar();
    if (busChoice == 0) return;
    if (busChoice < 1 || busChoice > BusesCount) {
        printf("Invalid bus number.\n");
        return;
    }

    printf("Enter Seat Number to cancel (1-50): ");
    scanf("%d", &seatChoice);
    getchar();
    if (seatChoice < 1 || seatChoice > 50) {
        printf("Invalid seat number.\n");
        return;
    }

    int busIdx = busChoice - 1;
    int seatIdx = seatChoice - 1;

    if (Booking_Info[busIdx][seatIdx].bookedByUserIndex != userIndex ||
        strcmp(Booking_Info[busIdx][seatIdx].IsAvailable, "yes") == 0) {
        printf("You have not booked this seat.\n");
        return;
    }

    // Cancel booking
    strcpy(Booking_Info[busIdx][seatIdx].IsAvailable, "yes");
    Booking_Info[busIdx][seatIdx].bookedByUserIndex = -1;
    sprintf(Booking_Info[busIdx][seatIdx].Seats, "Seat #%d", seatChoice);

    printf("Booking cancelled successfully!\n");
    SaveDataToFile();
}

