#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_APPOINTMENTS 100
#define MAX_LINE_LENGTH 256

#define MAX_LINE 256
#define MAX_PATIENTS 100
#define MAX_ITEMS 100

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

typedef struct {
    char username[50];
    char name[50];
    char specialism[50];
    char startTime[6];
    char endTime[6];
} Appointment;

typedef struct {
    char username[50];
    char password[50];
    char name[50];
    char dob[20];
    char address[100];
    char insurance[50];
    char diagnosticReport[100];
    char allergies[100];
    char medicalHistory[100];
    char pastProcedure[100];
} Patient;

typedef struct {
    char username[50];
    char patientName[50];
    char doctorUsername[50];
    char doctorName[50];
    char doctorSpecialism[50];
    char startTime[6];
    char endTime[6];
} PatientAppointment;

typedef struct {
    char name[50];
    float price;
    int quantity;
} InventoryItem;

typedef struct {
    char patientUsername[50];
    char patientName[50];
    char doctorUsername[50];
    char doctorName[50];
    char doctorSpecialism[50];
    char startTime[6];
    char endTime[6];
    char medication[50];
    int quantity;
    char prescription[100];
    float billing;
} Consultation;

typedef struct {
    char username[50];
    char name[50];
    char specialism[50];
    char startTime[6];
    char endTime[6];
} DoctorAppointment;

typedef struct {
    char username[50];
    char name[50];
    char doctorUsername[50];
    char doctorName[50];
    char doctorSpecialism[50];
    char startTime[6];
    char endTime[6];
    char medication[50];
    int quantity;
    char prescription[100];
    float billing;
} PatientConsultation;

typedef struct {
    char username[50];
    char name[50];
    char specialism[50];
    char startTime[6];
    char endTime[6];
    char observation[256];
    char improvement[256];
    char recommendation[256];
} DoctorReport;

// Define a union for patient and appointment data
typedef union {
    struct {
        char username[100];
        char name[100];
    } patient;
    struct {
        char details[MAX_LINE_LENGTH];
    } appointment;
} Data;

// Define a node for the linked list
typedef struct Node {
    Data data;
    struct Node* next;
} Node;

//CHAPTER 1__________________________ADMIN MENU (START)

//CHAPTER 1.1__________________________USER MENU (START)

//CHAPTER 1.1.1__________________________REGISTER NEW USER (START)

//CHAPTER 1.1.1.1__________________________REGISTER NEW PATIENT (START)
void registerNewPatient() {
    char username[100];
    char password[100];
    char name[100];
    char dob[11];
    char address[200];
    char insurance[50];
    char diagnosticReports[200];
    char allergies[200];
    char medicalHistory[200];
    char pastProcedures[200];

    printf("\n[REGISTER NEW PATIENT]\n\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);
    system("cls");

    printf("\n[REGISTER NEW PATIENT]\n\n");
    printf("Name: ");
    scanf(" %[^\n]", name);

    printf("Date of Birth (DD-MM-YYYY): ");
    scanf("%s", dob);

    printf("Address: ");
    scanf(" %[^\n]", address);

    printf("Insurance (Manulife | Prudential | Allianz): ");
    scanf("%s", insurance);
    system("cls");

    printf("\n[REGISTER NEW PATIENT]\n\n");
    printf("Diagnostic Reports: ");
    scanf(" %[^\n]", diagnosticReports);

    printf("Allergies: ");
    scanf(" %[^\n]", allergies);

    printf("Medical History: ");
    scanf(" %[^\n]", medicalHistory);

    printf("Past Procedures: ");
    scanf(" %[^\n]", pastProcedures);

    // Showing available appointments
    FILE *file = fopen("Appointment.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    char line[256];
    int appointmentCount = 0;
    char appointments[100][256];
    int patientCount[100] = {0};

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        strcpy(appointments[appointmentCount], line);

        // Count the number of patients for each appointment
        FILE *patientFile = fopen("PatientAppointment.txt", "r");
        if (patientFile != NULL) {
            char patientLine[256];
            while (fgets(patientLine, sizeof(patientLine), patientFile)) {
                if (strstr(patientLine, line) != NULL) {
                    patientCount[appointmentCount]++;
                }
            }
            fclose(patientFile);
        }

        appointmentCount++;
    }
    fclose(file);

    if (appointmentCount == 0) {
        printf(RED"No available appointments. Returning to the main menu...\n"RESET);
        return;
    }

    system("cls");

    printf("\n[REGISTER NEW PATIENT]\nSelect available appointment time:\n\n");
    int i;
    for (i = 0; i < appointmentCount; i++) {
        char doctorUsername[100], doctorName[100], specialism[100], startTime[6], endTime[6];
        sscanf(appointments[i], "%[^,],%[^,],%[^,],%[^,],%s", doctorUsername, doctorName, specialism, startTime, endTime);

        printf("%d. %s (%s) [%s - %s]", i + 1, doctorName, specialism, startTime, endTime);
        if (patientCount[i] >= 3) {
            printf(RED" (fully booked)"RESET);
        }
        printf("\n");
    }

    int selectedAppointment;
    printf("\nSelect an appointment (1-%d): ", appointmentCount);
    scanf("%d", &selectedAppointment);

    if (selectedAppointment < 1 || selectedAppointment > appointmentCount) {
        printf(RED"Invalid selection. Press ENTER to return...\n"RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    selectedAppointment--; // Adjust for 0-based index

    if (patientCount[selectedAppointment] >= 3) {
        printf(RED"\nThis appointment slot is fully booked. Press ENTER to return..."RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    // Save patient information
    file = fopen("Patient.txt", "a");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", username, password, name, dob, address, insurance, diagnosticReports, allergies, medicalHistory, pastProcedures);
    fclose(file);

    // Save patient appointment
    file = fopen("PatientAppointment.txt", "a");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    char doctorUsername[100], doctorName[100], specialism[100], startTime[6], endTime[6];
    sscanf(appointments[selectedAppointment], "%[^,],%[^,],%[^,],%[^,],%s", doctorUsername, doctorName, specialism, startTime, endTime);

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", username, name, doctorUsername, doctorName, specialism, startTime, endTime);
    fclose(file);

    printf(GREEN"\nPatient information saved successfully. Press ENTER to return to the main menu..."RESET);
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 1.1.1.1__________________________REGISTER NEW PATIENT (END)

//CHAPTER 1.1.1.2__________________________REGISTER NEW DOCTOR (START)
void registerNewDoctor () {
     char username [100];
     char password [100];
     char name [100];
     char specialism [100];

    printf("\n[REGISTER NEW DOCTOR]\n\n");
    // Prompt the user for input
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    printf("Name: ");
    scanf(" %[^\n]", name); // Modified format specifier %[^\n] for name

    printf("Specialism: ");
    scanf(" %[^\n]", specialism); // Modified format specifier %[^\n] for specialism

    // Open the file in append mode
    FILE *file = fopen("Doctor.txt", "a");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    // Write user information to the file
    fprintf(file, "Username: %s\n", username);
    fprintf(file, "Password: %s\n", password);
    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Specialism: %s\n", specialism);
    fprintf(file, "\n"); // Add a newline for readability between entries

    // Close the file
    fclose(file);

    printf(GREEN"\nNew Doctor has been registered successfully. Press ENTER to return..."RESET);
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 1.1.1.2__________________________REGISTER NEW DOCTOR (END)

//CHAPTER 1.1.1.3__________________________REGISTER NEW NURSE (START)
void registerNewNurse () {
     char username [100];
     char password [100];
     char name [100];

    printf("\n[REGISTER NEW NURSE]\n\n");
    // Prompt the user for input
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    printf("Name: ");
    scanf(" %[^\n]", name); // Modified format specifier %[^\n] for name

    // Open the file in append mode
    FILE *file = fopen("Nurse.txt", "a");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    // Write user information to the file
    fprintf(file, "Username: %s\n", username);
    fprintf(file, "Password: %s\n", password);
    fprintf(file, "Name: %s\n", name);
    fprintf(file, "\n"); // Add a newline for readability between entries

    // Close the file
    fclose(file);

    printf(GREEN"\nNew Nurse has been registered successfully. Press ENTER to return..."RESET);
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 1.1.1.3__________________________REGISTER NEW NURSE (END)


// Function declarations for REGISTER NEW USER MENU options
void registerNewUserMenu() {
    int choice;

    while(1) {
        // Display the registration menu
        printf(" ---------------------------------------\n");
        printf("|        [REGISTER NEW USER MENU]       |\n");
        printf(" ---------------------------------------\n");
        printf("| 1. Register New Patient               |\n");
        printf("| 2. Register New Doctor                |\n");
        printf("| 3. Register New Nurse                 |\n");
        printf("| 4. Return                             |\n");
        printf(" ---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on registration choice
        switch(choice) {
            case 1:
                system("cls");
                registerNewPatient();
                break;
            case 2:
                system("cls");
                registerNewDoctor();
                break;
            case 3:
                system("cls");
                registerNewNurse();
                break;
            case 4:
                system("cls");
                return; // Exit the USER MENU and return to ADMIN MENU
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}


//CHAPTER 1.1.1__________________________REGISTER NEW USER (END)


//CHAPTER 1.1.3__________________________VIEW EXISTING USER (START)

//CHAPTER 1.1.3.1__________________________VIEW EXISTING PATIENT (START)
void viewExistingPatients() {
    FILE *file = fopen("Patient.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    char line[256];
    int patientCount = 0;
    printf("\n[VIEW EXISTING PATIENTS]\n\n");

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        char *username = token;
        token = strtok(NULL, ",");
        char *password = token;
        token = strtok(NULL, ",");
        char *name = token;
        token = strtok(NULL, ",");
        char *dob = token;
        token = strtok(NULL, ",");
        char *address = token;
        token = strtok(NULL, ",");
        char *insurance = token;
        token = strtok(NULL, ",");
        char *diagnosticReport = token;
        token = strtok(NULL, ",");
        char *allergies = token;
        token = strtok(NULL, ",");
        char *medicalHistory = token;
        token = strtok(NULL, ",");
        char *pastProcedure = token;

        // Remove the newline character from pastProcedure
        pastProcedure[strcspn(pastProcedure, "\n")] = '\0';

        // Display patient information
        printf("%d.\n", ++patientCount);
        printf("Username: %s\n", username);
        printf("Password: %s\n", password);
        printf("Name: %s\n", name);
        printf("\n"); // Add an extra blank line for separation
    }
    fclose(file);

    if (patientCount == 0) {
        printf(RED"No patients available.\n"RESET);
    }

    printf("\nPress ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 1.1.3.1__________________________VIEW EXISTING PATIENT (END)

//CHAPTER 1.1.3.2__________________________VIEW EXISTING DOCTOR (START)
// Function to view existing doctors
void viewExistingDoctors() {
    FILE *file = fopen("Doctor.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    char line[256];
    int doctorCount = 0;
    printf("\n[VIEW EXISTING DOCTORS]\n\n");

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Username:") != NULL) {
            printf("%d.\n", ++doctorCount);
            printf("Username: %s", line + strlen("Username: "));
            fgets(line, sizeof(line), file);
            printf("Password: %s", line + strlen("Password: "));
            fgets(line, sizeof(line), file);
            printf("Name: %s", line + strlen("Name: "));
            fgets(line, sizeof(line), file);
            printf("Specialism: %s", line + strlen("Specialism: "));
            fgets(line, sizeof(line), file); // Read the blank line separating doctors
            printf("\n"); // Add an extra blank line for separation
        }
    }
    fclose(file);

    if (doctorCount == 0) {
        printf(RED"No doctors available.\n"RESET);
    }

    printf("\nPress ENTER to return to User Menu...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 1.1.3.2__________________________VIEW EXISTING DOCTOR (END)

//CHAPTER 1.1.3.3__________________________VIEW EXISTING NURSE (START)
// Function to view existing nurses
void viewExistingNurses() {
    FILE *file = fopen("Nurse.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    char line[256];
    int nurseCount = 0;
    printf("\n[VIEW EXISTING NURSES]\n\n");

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Username:") != NULL) {
            printf("%d.\n", ++nurseCount);
            printf("Username: %s", line + strlen("Username: "));
            fgets(line, sizeof(line), file);
            printf("Password: %s", line + strlen("Password: "));
            fgets(line, sizeof(line), file);
            printf("Name: %s", line + strlen("Name: "));
            fgets(line, sizeof(line), file); // Read the blank line separating nurses
            printf("\n"); // Add an extra blank line for separation
        }
    }
    fclose(file);

    if (nurseCount == 0) {
        printf(RED"No nurses available.\n"RESET);
    }

    printf("\nPress ENTER to return to User Menu...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 1.1.3.3__________________________VIEW EXISTING NURSE (END)


// Function to display submenu for viewing existing users
void viewUser() {
    int choice;

    while (1) {
        // Display the view users menu
        printf(" ---------------------------------------\n");
        printf("|          [VIEW EXISTING USERS]        |\n");
        printf(" ---------------------------------------\n");
        printf("| 1. View Existing Patients             |\n");
        printf("| 2. View Existing Doctors              |\n");
        printf("| 3. View Existing Nurses               |\n");
        printf("| 4. Return to User Menu                |\n");
        printf(" ---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on the choice
        switch (choice) {
            case 1:
                system("cls");
                // Function to view existing patients
                viewExistingPatients();
                break;
            case 2:
                system("cls");
                // Function to view existing doctors
                viewExistingDoctors();
                break;
            case 3:
                system("cls");
                // Function to view existing nurses
                viewExistingNurses();
                break;
            case 4:
                system("cls");
                return; // Exit the view users menu and return to USER MENU
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}
//CHAPTER 1.1.3__________________________VIEW EXISTING USER (END)


// Function declarations for USER MENU options
void userMenu() {
    int choice;

    while(1) {
        // Display the registration menu
        printf(" ---------------------------------------\n");
        printf("|               [USER MENU]             |\n");
        printf(" ---------------------------------------\n");
        printf("| 1. Register New User                  |\n");
        printf("| 2. View Existing User                 |\n");
        printf("| 3. Return                             |\n");
        printf(" ---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on registration choice
        switch(choice) {
            case 1:
                system("cls");
                registerNewUserMenu();
                break;
            case 2:
                system("cls");
                viewUser();
                break;
            case 3:
                system("cls");
                return; // Exit the USER MENU and return to ADMIN MENU
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}
//CHAPTER 1.1__________________________USER MENU (END)

//CHAPTER 1.2__________________________APPOINTMENT TREND (START)
void appointmentTrends() {
    // Read appointment data from Appointment.txt
    FILE *appointmentFile = fopen("Appointment.txt", "r");
    if (appointmentFile == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int appointmentCount = 0;
    char appointments[MAX_APPOINTMENTS][MAX_LINE_LENGTH];
    int patientCount[MAX_APPOINTMENTS] = {0};

    // Read appointment data
    while (fgets(line, sizeof(line), appointmentFile)) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        strcpy(appointments[appointmentCount], line);

        // Count the number of patients for each appointment
        FILE *patientFile = fopen("PatientAppointment.txt", "r");
        if (patientFile != NULL) {
            char patientLine[MAX_LINE_LENGTH];
            while (fgets(patientLine, sizeof(patientLine), patientFile)) {
                if (strstr(patientLine, line) != NULL) {
                    patientCount[appointmentCount]++;
                }
            }
            fclose(patientFile);
        }

        appointmentCount++;
    }
    fclose(appointmentFile);

    // Sort appointments based on the number of patients booked
    int i, j;
    for (i = 0; i < appointmentCount - 1; i++) {
        for (j = 0; j < appointmentCount - i - 1; j++) {
            if (patientCount[j] < patientCount[j+1]) {
                int tempCount = patientCount[j];
                patientCount[j] = patientCount[j+1];
                patientCount[j+1] = tempCount;

                char temp[MAX_LINE_LENGTH];
                strcpy(temp, appointments[j]);
                strcpy(appointments[j], appointments[j+1]);
                strcpy(appointments[j+1], temp);
            }
        }
    }

    // Display sorted appointment trend
    int k;
    printf("\n[APPOINTMENT TREND]\n\n");
    for (k = 0; k < appointmentCount; k++) {
        char doctorUsername[MAX_LINE_LENGTH], doctorName[MAX_LINE_LENGTH], specialism[MAX_LINE_LENGTH], startTime[MAX_LINE_LENGTH], endTime[MAX_LINE_LENGTH];
        sscanf(appointments[k], "%[^,],%[^,],%[^,],%[^,],%s", doctorUsername, doctorName, specialism, startTime, endTime);

        printf("%d. %s : %s (%s) [%s - %s] | Booked by: %d\n", k + 1, doctorUsername, doctorName, specialism, startTime, endTime, patientCount[k]);
    }

    printf("\nPress ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 1.2__________________________APPOINTMENT TREND (END)

//CHAPTER 1.3__________________________INVENTORY MENU (START)
void inventoryMenuAdmin() {
    FILE *file = fopen("Inventory.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int itemCount = 0;
    char items[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int i;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        strcpy(items[itemCount], line);
        itemCount++;
    }
    fclose(file);

    if (itemCount == 0) {
        printf(RED "No items available.\n" RESET);
        return;
    }

    printf("\n[DISPLAY ALL PRODUCT RECORDS]\n\n");
    for (i = 0; i < itemCount; i++) {
        char itemName[100];
        int itemQuantity;
        float itemPrice;
        sscanf(items[i], "%[^,],%f,%d", itemName, &itemPrice, &itemQuantity);
        printf("%d. %s | QTY: %d | RM%.2f\n", i + 1, itemName, itemQuantity, itemPrice);
    }
    printf("\nPress ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 1.3__________________________INVENTORY MENU (END)

// Function declarations for ADMIN MENU options
void adminLogin() {
    int choice;

    while(1) {
        // Display the admin menu
        printf(" ---------------------------------------\n");
        printf("|             [ ADMIN MENU]             |\n");
        printf(" ---------------------------------------\n");
        printf("| 1. User Menu                          |\n");
        printf("| 2. Appointment Trend                  |\n");
        printf("| 3. Inventory Menu                     |\n");
        printf("| 4. Logout                             |\n");
        printf(" ---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on admin's choice
        switch(choice) {
            case 1:
                system("cls");
                userMenu();
                break;
            case 2:
                system("cls");
                appointmentTrends();
                break;
            case 3:
                system("cls");
                inventoryMenuAdmin();
                break;
            case 4:
                printf("Logging out... Press ENTER to continue...");
                getchar();
                getchar();
                system("cls");
                return; // Exit the admin menu and return to main menu
            default:
                printf(RED "Invalid choice! Press ENTER to retry..." RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}
//CHAPTER 1__________________________ADMIN MENU (END)


//CHAPTER 2_________________________PATIENT MENU (START)

//CHAPTER 2.1_________________________PATIENT APPOINTMENT MENU (START)

//CHAPTER 2.1.1_________________________PATIENT VIEW APPOINTMENT (START)
void viewAppointment(const char *patientUsername) {
    FILE *file = fopen("PatientAppointment.txt", "r");
    char line[256];
    int found = 0;

    if (file == NULL) {
        printf(RED "Error opening file!\n" RESET);
        return;
    }

    // Read the appointment information from the file
    while (fgets(line, sizeof(line), file)) {
        char tempUsername[100];
        char tempPatientName[100];
        char doctorUsername[100];
        char doctorName[100];
        char doctorSpecialism[100];
        char startTime[100];
        char endTime[100];

        strcpy(tempUsername, strtok(line, ","));
        strcpy(tempPatientName, strtok(NULL, ","));
        strcpy(doctorUsername, strtok(NULL, ","));
        strcpy(doctorName, strtok(NULL, ","));
        strcpy(doctorSpecialism, strtok(NULL, ","));
        strcpy(startTime, strtok(NULL, ","));
        strcpy(endTime, strtok(NULL, "\n"));

        // Check if the appointment belongs to the logged-in patient
        if (strcmp(tempUsername, patientUsername) == 0) {
            found = 1;
            printf("\n[VIEW APPOINTMENT TIME]\n\nYou are assigned to the following appointment time:\n");
            printf("%s | %s (%s) [%s - %s]",
                   doctorUsername, doctorName, doctorSpecialism, startTime, endTime);
        }
    }

    fclose(file);

    if (!found) {
        printf("\n[VIEW APPOINTMENT]\n\n");
        printf(RED"No appointment found for the patient."RESET);
    }

    printf("\n\nPress ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 2.1.1_________________________PATIENT VIEW APPOINTMENT (END)

//CHAPTER 2.1.2_________________________PATIENT RESCHEDULE APPOINTMENT (START)
void rescheduleAppointment(const char *loggedInPatientUsername) {
    FILE *fileAppointments;
    FILE *filePatientAppointments;
    char line[MAX_LINE_LENGTH];
    int found = 0;
    int i;

    fileAppointments = fopen("Appointment.txt", "r");
    filePatientAppointments = fopen("PatientAppointment.txt", "r+");

    if (fileAppointments == NULL || filePatientAppointments == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    // Read and store existing patient appointments
    char patientAppointments[MAX_APPOINTMENTS][MAX_LINE_LENGTH];
    int patientAppointmentsCount = 0;

    while (fgets(line, sizeof(line), filePatientAppointments)) {
        strcpy(patientAppointments[patientAppointmentsCount], line);
        patientAppointmentsCount++;
    }

    // Close the PatientAppointment file to reopen it in write mode later
    fclose(filePatientAppointments);

    // Display available appointments from Appointment.txt
    printf("\n[RESCHEDULE APPOINTMENT TIME]\n\n");
    int availableAppointmentsCount = 0;
    char availableAppointments[MAX_APPOINTMENTS][MAX_LINE_LENGTH];
    int appointmentBookingCounts[MAX_APPOINTMENTS] = {0};

    while (fgets(line, sizeof(line), fileAppointments)) {
        char *appointmentDoctorUsername = strtok(line, ",");
        char *appointmentDoctorName = strtok(NULL, ",");
        char *appointmentDoctorSpecialism = strtok(NULL, ",");
        char *appointmentStartTime = strtok(NULL, ",");
        char *appointmentEndTime = strtok(NULL, "\n");

        // Check if the appointment is already taken by any patient
        int isTaken = 0;
        int bookingCount = 0;

        for (i = 0; i < patientAppointmentsCount; i++) {
            char tempLine[MAX_LINE_LENGTH];
            strcpy(tempLine, patientAppointments[i]);
            char *patientUsername = strtok(tempLine, ",");
            char *patientName = strtok(NULL, ",");
            char *patientDoctorUsername = strtok(NULL, ",");
            char *patientDoctorName = strtok(NULL, ",");
            char *patientDoctorSpecialism = strtok(NULL, ",");
            char *patientStartTime = strtok(NULL, ",");
            char *patientEndTime = strtok(NULL, "\n");

            if (strcmp(appointmentStartTime, patientStartTime) == 0 && strcmp(appointmentEndTime, patientEndTime) == 0) {
                bookingCount++;
                if (bookingCount >= 3 || strcmp(patientUsername, loggedInPatientUsername) == 0) {
                    isTaken = 1;
                    break;
                }
            }
        }

        if (!isTaken) {
            sprintf(availableAppointments[availableAppointmentsCount], "%s,%s,%s,%s,%s", appointmentDoctorUsername, appointmentDoctorName, appointmentDoctorSpecialism, appointmentStartTime, appointmentEndTime);
            appointmentBookingCounts[availableAppointmentsCount] = bookingCount;
            availableAppointmentsCount++;
        }
    }

    fclose(fileAppointments);

    if (availableAppointmentsCount == 0) {
        printf(RED"No available appointments.\n"RESET);
        return;
    }

    for (i = 0; i < availableAppointmentsCount; i++) {
        char tempLine[MAX_LINE_LENGTH];
        strcpy(tempLine, availableAppointments[i]);
        char *appointmentDoctorUsername = strtok(tempLine, ",");
        char *appointmentDoctorName = strtok(NULL, ",");
        char *appointmentDoctorSpecialism = strtok(NULL, ",");
        char *appointmentStartTime = strtok(NULL, ",");
        char *appointmentEndTime = strtok(NULL, "\n");

        // Print the appointment details
        printf("%d. %s | %s (%s) [%s - %s]\n", i + 1, appointmentDoctorUsername, appointmentDoctorName, appointmentDoctorSpecialism, appointmentStartTime, appointmentEndTime);
    }

    printf("\nSelect the available appointment time to reschedule: ");
    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > availableAppointmentsCount || appointmentBookingCounts[choice - 1] >= 3) {
        printf(RED"Invalid choice or appointment fully booked!\n"RESET);
        return;
    }

    // Reopen PatientAppointment.txt in write mode
    filePatientAppointments = fopen("PatientAppointment.txt", "w");

    if (filePatientAppointments == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    // Update the selected appointment time in PatientAppointment.txt
    for (i = 0; i < patientAppointmentsCount; i++) {
        char tempLine[MAX_LINE_LENGTH];
        strcpy(tempLine, patientAppointments[i]);
        char *patientUsername = strtok(tempLine, ",");
        char *patientName = strtok(NULL, ",");
        char *patientDoctorUsername = strtok(NULL, ",");
        char *patientDoctorName = strtok(NULL, ",");
        char *patientDoctorSpecialism = strtok(NULL, ",");
        char *patientStartTime = strtok(NULL, ",");
        char *patientEndTime = strtok(NULL, "\n");

        if (strcmp(patientUsername, loggedInPatientUsername) == 0) {
            fprintf(filePatientAppointments, "%s,%s,%s\n", patientUsername, patientName, availableAppointments[choice - 1]);
        } else {
            fprintf(filePatientAppointments, "%s,%s,%s,%s,%s,%s,%s\n", patientUsername, patientName, patientDoctorUsername, patientDoctorName, patientDoctorSpecialism, patientStartTime, patientEndTime);
        }
    }

    fclose(filePatientAppointments);

    printf(GREEN"\nAppointment rescheduled successfully. Press ENTER to return..."RESET);
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 2.1.2_________________________PATIENT RESCHEDULE APPOINTMENT (END)

//CHAPTER 2.1.3_________________________PATIENT CANCEL APPOINTMENT (START)
// Function to create a new node
Node* createNode(Data data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror(RED "Error allocating memory" RESET);
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to append a node to the linked list
void appendNode(Node** head, Data data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to delete a node from the linked list by username
void deleteNode(Node** head, const char* username) {
    Node* temp = *head;
    Node* prev = NULL;

    while (temp != NULL && strcmp(temp->data.patient.username, username) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
}

// Function to load patients from a file into the linked list
void loadPatients(Node** head) {
    FILE *file = fopen("Patient.txt", "r");
    if (!file) {
        perror(RED "Error opening file" RESET);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        Data data;
        strcpy(data.patient.username, strtok(line, ","));
        strcpy(data.patient.name, strtok(NULL, ","));
        appendNode(head, data);
    }

    fclose(file);
}

// Function to load appointments from a file into the linked list
void loadAppointments(Node** head) {
    FILE *file = fopen("PatientAppointment.txt", "r");
    if (!file) {
        perror(RED "Error opening file" RESET);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        Data data;
        strcpy(data.appointment.details, line); // Store the entire line in details
        appendNode(head, data);
    }

    fclose(file);
}

// Function to save patients from the linked list to a file
void savePatients(Node* head) {
    FILE *file = fopen("PatientTemp.txt", "w");
    if (!file) {
        perror(RED "Error opening file" RESET);
        exit(EXIT_FAILURE);
    }

    Node* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%s\n", temp->data.patient.username, temp->data.patient.name);
        temp = temp->next;
    }

    fclose(file);
}

// Function to save appointments from the linked list to a file
void saveAppointments(Node* head) {
    FILE *file = fopen("AppointmentTemp.txt", "w");
    if (!file) {
        perror(RED "Error opening file" RESET);
        exit(EXIT_FAILURE);
    }

    Node* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s", temp->data.appointment.details); // Write the entire line
        temp = temp->next;
    }

    fclose(file);
}

// Function to free the linked list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void cancelAppointment(const char* patientUsername) {
    char confirmation;
    Node* patientList = NULL;
    Node* appointmentList = NULL;

    // Load data into linked lists
    loadPatients(&patientList);
    loadAppointments(&appointmentList);

    // Ask for user confirmation
    printf("\n[CANCEL APPOINTMENT TIME]\n\n");
    printf("[PS: canceling appointment will result in deletion of this account]\n");
    printf("Are you sure you want to cancel the appointment for %s? (Y/N): ", patientUsername);
    scanf(" %c", &confirmation);

    // If user confirms with 'Y', proceed with cancellation
    if (confirmation == 'Y' || confirmation == 'y') {
        deleteNode(&patientList, patientUsername);
        deleteNode(&appointmentList, patientUsername);
        savePatients(patientList);
        saveAppointments(appointmentList);
        printf("\nAppointment for %s has been canceled successfully. Press ENTER to return to the main menu...", patientUsername);
        getchar(); // Consume the newline character left in the input buffer
        getchar(); // Wait for user to press ENTER
        system("cls");
        main(); // Call the main menu function to return to the main menu
    } else if (confirmation == 'N' || confirmation == 'n') {
        // If user chooses 'N', cancel the function
        printf("\nAppointment cancellation canceled. Press ENTER to return to the main menu...");
        getchar(); // Consume the newline character left in the input buffer
        getchar(); // Wait for user to press ENTER
        system("cls");
    } else {
        // Invalid input, notify user and cancel the function
        printf("\nInvalid input. Appointment cancellation canceled. Press ENTER to return to the main menu...");
        getchar(); // Consume the newline character left in the input buffer
        getchar(); // Wait for user to press ENTER
        system("cls");
    }

    // Free the linked list memory
    freeList(patientList);
    freeList(appointmentList);
}
//CHAPTER 2.1.3_________________________PATIENT CANCEL APPOINTMENT (END)

void appointmentMenu(const char *patientUsername, const char *patientName) {
    int choice;

    while (1) {
        // Display the Appointment Menu
        printf(" -----------------------------------------------\n");
        printf("[APPOINTMENT MENU - Welcome, %s]\n", patientName);
        printf(" -----------------------------------------------\n");
        printf("| 1. View Appointment                           |\n");
        printf("| 2. Reschedule Appointment                     |\n");
        printf("| 3. Cancel Appointment                         |\n");
        printf("| 4. Return to Patient Menu                     |\n");
        printf(" -----------------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on user's choice
        switch(choice) {
            case 1:
                system("cls");
                viewAppointment(patientUsername);
                break;
            case 2:
                system("cls");
                rescheduleAppointment(patientUsername);
                break;
            case 3:
                system("cls");
                cancelAppointment(patientUsername);
                break;
            case 4:
                system("cls");
                return; // Return to Patient Menu
            default:
                printf(RED"Invalid choice! Please try again.\n"RESET);
        }
    }
}
//CHAPTER 2.1_________________________PATIENT APPOINTMENT MENU (END)

//CHAPTER 2.2_________________________EHR RECORD (START)
void ehrRecords(const char *patientUsername) {
    printf("\n[ELECTRONIC HEALTH RECORD]\n\n");

    // Open the PatientConsultation.txt file in read mode
    FILE *file = fopen("PatientConsultation.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int foundRecords = 0;

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Extract patient's username from the line
        char storedUsername[MAX_LINE];
        strcpy(storedUsername, strtok(line, ","));

        // Check if the current line corresponds to the logged-in patient
        if (strcmp(patientUsername, storedUsername) == 0) {
            // Extract relevant fields and display consultation details
            char patientName[MAX_LINE], doctorUsername[MAX_LINE], doctorName[MAX_LINE];
            char specialism[MAX_LINE], startTime[MAX_LINE], endTime[MAX_LINE];
            char medication[MAX_LINE], quantity[MAX_LINE], prescription[MAX_LINE], billing[MAX_LINE];

            strcpy(patientName, strtok(NULL, ","));
            strcpy(doctorUsername, strtok(NULL, ","));
            strcpy(doctorName, strtok(NULL, ","));
            strcpy(specialism, strtok(NULL, ","));
            strcpy(startTime, strtok(NULL, ","));
            strcpy(endTime, strtok(NULL, ","));
            strcpy(medication, strtok(NULL, ","));
            strcpy(quantity, strtok(NULL, ","));
            strcpy(prescription, strtok(NULL, ","));
            strcpy(billing, strtok(NULL, ","));

            // Display the consultation details
            printf("Doctor: %s (%s)\n", doctorName, specialism);
            printf("Appointment Time: %s - %s\n", startTime, endTime);
            printf("Medication: %s\n", medication);
            printf("Quantity: %s\n",quantity);
            printf("Prescription: %s\n", prescription);
            printf("Total Billing: %s\n", billing);

            foundRecords = 1;
        }
    }

    fclose(file);

    if (!foundRecords) {
        printf(RED"No electronic health records found for this patient.\n\n"RESET);
    }

    printf("Press ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 2.2_________________________EHR RECORD (END)

//CHAPTER 2.3_________________________INSURANCE CLAIM (START)
void claimInsurance(const char *patientUsername) {
    // Open the Patient.txt file in read mode
    FILE *file = fopen("Patient.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char line[MAX_LINE_LENGTH];
    char insurance[MAX_LINE_LENGTH];
    int insuranceFound = 0;

    // Read each line from the file to find patient's insurance
    while (fgets(line, sizeof(line), file)) {
        // Extract patient's username
        char *token = strtok(line, ",");
        if (token != NULL && strcmp(token, patientUsername) == 0) {
            // Skip the next 4 tokens
            int i;
            for (i = 0; i < 4; i++) {
                token = strtok(NULL, ",");
            }
            // Extract the insurance token
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(insurance, token);
                // Remove newline character from insurance
                insurance[strcspn(insurance, "\n")] = '\0';
                insuranceFound = 1;
                break;
            }
        }
    }

    fclose(file);

    if (!insuranceFound) {
        printf(RED"Insurance information not found for this patient.\n"RESET);
        return;
    }

    // Open PatientConsultation.txt for reading and writing
    file = fopen("PatientConsultation.txt", "r+");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char tempFile[] = "temp.txt";
    FILE *temp = fopen(tempFile, "w");
    if (temp == NULL) {
        printf(RED "Error creating temp file!\n"RED);
        fclose(file);
        return;
    }

    char consultationLine[MAX_LINE_LENGTH];
    char storedPatientUsername[MAX_LINE_LENGTH];
    char patientName[MAX_LINE_LENGTH];
    char doctorUsername[MAX_LINE_LENGTH];
    char doctorName[MAX_LINE_LENGTH];
    char specialism[MAX_LINE_LENGTH];
    char startTime[MAX_LINE_LENGTH];
    char endTime[MAX_LINE_LENGTH];
    char medication[MAX_LINE_LENGTH];
    char quantity[MAX_LINE_LENGTH];
    char prescription[MAX_LINE_LENGTH];
    char billing[MAX_LINE_LENGTH];
    int consultationFound = 0;
    int insuranceAccepted = 0;

    // Read each line from PatientConsultation.txt
    while (fgets(consultationLine, sizeof(consultationLine), file)) {
        sscanf(consultationLine, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
            storedPatientUsername, patientName, doctorUsername, doctorName, specialism,
            startTime, endTime, medication, quantity, prescription, billing);

        // Check if the current line corresponds to the logged-in patient
        if (strcmp(patientUsername, storedPatientUsername) == 0) {
            consultationFound = 1; // Consultation data found for this patient
            // Apply insurance discounts based on the insurance type
            float currentBilling = atof(billing);
            float discountedBilling = currentBilling;
            if (strcasecmp(insurance, "Manulife") == 0) {
                discountedBilling = currentBilling * 0.7; // 30% discount
                insuranceAccepted = 1;
                printf("\n[INSURANCE CLAIM]\n\n");
                printf("Receipt");
                printf(" -----------------------------------------------\n");
                printf("|                    Receipt                    |\n");
                printf(" -----------------------------------------------\n");
                printf(" Consultation Fee:                  RM 300\n");
                printf(" Medication:                        RM %.2f\n", currentBilling - 300);
                printf(" (%s x %s)\n", medication, quantity);
                printf(" -----------------------------------------------\n");
                printf(" Subtotal:                          RM %.2f\n", currentBilling);
                printf(" Insurance Coverage:                   30%%\n");
                printf(" -----------------------------------------------\n");
                printf(" Total Amount Covered:              RM %.2f\n", discountedBilling);
                printf(" -----------------------------------------------\n");
                printf("\n\nPress ENTER to return...");
                getchar();
                getchar();
                system("cls");
            } else if (strcasecmp(insurance, "Prudential") == 0) {
                discountedBilling = currentBilling * 0.5; // 50% discount
                insuranceAccepted = 1;
                printf("\n[INSURANCE CLAIM]\n\n");
                printf("Receipt");
                printf(" -----------------------------------------------\n");
                printf("|                      Receipt                  |\n");
                printf(" -----------------------------------------------\n");
                printf(" Consultation Fee:                  RM 300\n");
                printf(" Medication:                        RM %.2f\n", currentBilling - 300);
                printf(" (%s x %s)\n", medication, quantity);
                printf(" -----------------------------------------------\n");
                printf(" Subtotal:                          RM %.2f\n", currentBilling);
                printf(" Insurance Coverage:                   50%%\n");
                printf(" -----------------------------------------------\n");
                printf(" Total Amount Covered:              RM %.2f\n", discountedBilling);
                printf(" -----------------------------------------------\n");
                printf("\n\nPress ENTER to return...");
                getchar();
                getchar();
                system("cls");
            } else if (strcasecmp(insurance, "Allianz") == 0) {
                discountedBilling = currentBilling * 0.3; // 70% discount
                insuranceAccepted = 1;
                printf("\n[INSURANCE CLAIM]\n\n");
                printf("Receipt");
                printf(" -----------------------------------------------\n");
                printf("|                      Receipt                  |\n");
                printf(" -----------------------------------------------\n");
                printf(" Consultation Fee:                  RM 300\n");
                printf(" Medication:                        RM %.2f\n", currentBilling - 300);
                printf(" (%s x %s)\n", medication, quantity);
                printf(" -----------------------------------------------\n");
                printf(" Subtotal:                          RM %.2f\n", currentBilling);
                printf(" Insurance Coverage:                   70%%\n");
                printf(" -----------------------------------------------\n");
                printf(" Total Amount Covered:              RM %.2f\n", discountedBilling);
                printf(" -----------------------------------------------\n");
                printf("\n\nPress ENTER to return...");
                getchar();
                getchar();
                system("cls");
            } else {
                printf("\n[INSURANCE CLAIM]\n\n");
                printf(" -----------------------------------------------\n");
                printf("|                      Receipt                  |\n");
                printf(" -----------------------------------------------\n");
                printf(" Consultation Fee:                  RM 300\n");
                printf(" Medication:                        RM %.2f\n", currentBilling - 300);
                printf(" (%s x %s)\n", medication, quantity);
                printf(" -----------------------------------------------\n");
                printf(" Subtotal:                          RM %.2f\n", currentBilling);
                printf(" Insurance Coverage: INSURANCE NOT SUPPORTED\n");
                printf(" -----------------------------------------------\n");
                printf(" Total Amount Covered:              RM 0\n");
                printf(" -----------------------------------------------\n");
                printf("\n\nPress ENTER to return...");
                getchar();
                getchar();
                system("cls");
            }
            sprintf(billing, "%.2f", discountedBilling);
        }

        // Write the updated line (with possibly modified billing) to temp file
        fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            storedPatientUsername, patientName, doctorUsername, doctorName, specialism,
            startTime, endTime, medication, quantity, prescription, billing);
    }
    fclose(file);
    fclose(temp);

    if (!consultationFound) {
        printf("\n[INSURANCE CLAIM]\n\n");
        printf(RED "This patient doesn't have consultation data yet.\n\nPress ENTER to return..." RESET);
        getchar();
        getchar();
        system("cls");
        remove(tempFile); // Delete the temporary file as no updates are needed
        return;
    }

    // Replace PatientConsultation.txt with temp.txt
    remove("PatientConsultation.txt");
    rename(tempFile, "PatientConsultation.txt");

    // Record that the insurance has been claimed in InsuranceClaimed.txt
    FILE *insuranceClaimedFile = fopen("InsuranceClaimed.txt", "a");
    if (insuranceClaimedFile == NULL) {
        printf(RED"Error opening InsuranceClaimed.txt!\n"RESET);
        return;
    }
    fprintf(insuranceClaimedFile, "%s\n", patientUsername);
    fclose(insuranceClaimedFile);
}
//CHAPTER 2.3_________________________INSURANCE CLAIM (END)


void patientMenu(const char *patientUsername, const char *patientName) {
    int choice;
    int insuranceClaimed = 0; // Flag to track if insurance has been claimed

    // Check if insurance has been claimed already
    FILE *insuranceClaimedFile = fopen("InsuranceClaimed.txt", "r");
    if (insuranceClaimedFile != NULL) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), insuranceClaimedFile)) {
            line[strcspn(line, "\n")] = '\0'; // Remove newline character
            if (strcmp(line, patientUsername) == 0) {
                insuranceClaimed = 1;
                break;
            }
        }
        fclose(insuranceClaimedFile);
    }

    while (1) {
        // Display the Patient Menu
        printf(" -----------------------------------------------\n");
        printf("[PATIENT MENU - Welcome, %s]\n", patientName);
        printf(" -----------------------------------------------\n");
        printf("| 1. Appointment Menu                           |\n");
        printf("| 2. Electronic Health Record                   |\n");
        printf("| 3. Insurance Claim                            |\n");
        printf("| 4. Logout                                     |\n");
        printf(" -----------------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on user's choice
        switch(choice) {
            case 1:
                system("cls");
                appointmentMenu(patientUsername, patientName);
                break;
            case 2:
                system("cls");
                ehrRecords(patientUsername);
                break;
            case 3:
                system("cls");
                if (!insuranceClaimed) {
                    claimInsurance(patientUsername);
                    insuranceClaimed = 1;
                } else {
                    system("cls");
                    printf("\n[INSURANCE CLAIM]\n\n");
                    printf(GREEN"Your insurance has already been claimed.\n\nPress ENTER to return..."RESET);
                    getchar();
                    getchar();
                    system("cls");
                }
                break;
            case 4:
                printf("Logging out... Press ENTER to continue...");
                getchar();
                getchar();
                system("cls");
                return; // Logout and return to the main menu
            default:
                printf(RED"Invalid choice! Please try again.\n"RESET);
        }
    }
}

//CHAPTER 2 (INITIALIZER)__________________________LOGIN AS PATIENT (START)
// Function to login to the patient's account
void patientLogin() {
    char username[100];
    char password[100];
    char line[256];
    int attempts = 0;
    int loginSuccess = 0;

    // Allow maximum of 3 login attempts
    while (attempts < 3 && !loginSuccess) {
        printf("\n[PATIENT LOGIN]\n(Type 'RETURN' to go back)\n\n");
        printf("Username: ");
        scanf("%s", username);

        if (strcmp(username, "RETURN") == 0) {
            system("cls");
            return;
        }

        printf("Password: ");

        // Get password input and mask with '*'
        int i = 0;
        char ch;
        while (1) {
            ch = _getch(); // Get character without echoing to the console
            if (ch == 13) { // Enter key is pressed
                password[i] = '\0';
                break;
            } else if (ch == 8) { // Backspace is pressed
                if (i > 0) {
                    i--;
                    printf("\b \b"); // Erase the last '*'
                }
            } else {
                password[i++] = ch;
                printf("*");
            }
        }
        printf("\n");

        // Open the Patient.txt file in read mode
        FILE *file = fopen("Patient.txt", "r");
        if (file == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }

        char storedUsername[100];
        char storedPassword[100];
        char storedName[100];

        // Read the patient information from the file
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, username) != NULL) {
                strcpy(storedUsername, strtok(line, ","));
                strcpy(storedPassword, strtok(NULL, ","));
                strcpy(storedName, strtok(NULL, ","));

                // Remove the newline character from storedName
                storedName[strcspn(storedName, "\n")] = '\0';

                // Check if the entered username and password match
                if (strcmp(password, storedPassword) == 0) {
                    loginSuccess = 1;
                    break;
                }
            }
        }

        fclose(file);

        // If login successful, display Patient Menu
        if (loginSuccess) {
            printf("\nLogin successful! Press ENTER to continue...");
            getchar();
            getchar();
            system("cls");
            patientMenu(storedUsername, storedName);
        } else {
            attempts++;
            if (attempts < 3) {
                printf("\nInvalid username or password. Remaining attempt(s) [%d].", 3 - attempts);
                getchar();
                getchar();
                system("cls");
            } else {
                printf("\nToo many failed attempts. Shutting down the system...");
                getchar();
                getchar();
                system("cls");
                exit(0);
            }
        }
    }
}
//CHAPTER 2 (INITIALIZER)__________________________LOGIN AS PATIENT (END)

//CHAPTER 2_________________________PATIENT MENU (END)












//CHAPTER 3__________________________DOCTOR MENU (START)

//CHAPTER 3.1__________________________DOCTOR MANAGE SCHEDULE MENU (START)

//CHAPTER 3.1.1__________________________INSERT DOCTOR SCHEDULE (START)
// Function to manage doctor's schedule and make appointments
void insertAppointment(const char *doctorUsername, const char *doctorName, const char *specialism) {
    char startTime[6]; // HH:MM format for start time
    char endTime[6];   // HH:MM format for end time

    // Open the file in read mode to count existing appointments
    FILE *file = fopen("Appointment.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    // Check if the doctor has already made 3 appointments
    int countAppointments = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (strcmp(token, doctorUsername) == 0) {
            countAppointments++;
        }
    }

    fclose(file);

    if (countAppointments >= 3) {
        printf(RED"\nYou have already made the maximum number of appointments. Press ENTER to return to the menu..."RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    // Open the file in append mode to add new appointment
    file = fopen("Appointment.txt", "a");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    // Prompt the doctor to enter the appointment details
    system("cls");
    printf("\n[MAKE APPOINTMENT]\n\n");
    printf("Enter Start Time (HH:MM): ");
    scanf("%5s", startTime); // Maximum length is 5 characters for HH:MM

    printf("Enter End Time (HH:MM): ");
    scanf("%5s", endTime); // Maximum length is 5 characters for HH:MM

    // Write appointment information to the file
    fprintf(file, "%s,%s,%s,%s,%s\n", doctorUsername, doctorName, specialism, startTime, endTime);

    // Close the file
    fclose(file);

    printf(GREEN"\nAppointment scheduled successfully. Press ENTER to return to the menu..."RESET);
    getchar();
    getchar();
    system("cls");
}

//CHAPTER 3.1.1__________________________INSERT DOCTOR SCHEDULE (END)

//CHAPTER 3.1.2__________________________VIEW DOCTOR SCHEDULE (START)
void viewDoctorSchedule(const char *doctorName) {
    printf("\n[VIEW SCHEDULE]\n\n");

    // Open the file in read mode
    FILE *file = fopen("Appointment.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char line[256];
    int count = 0;
    int found = 0; // Flag to indicate if any appointments were found for the doctor

    // Read and display each line from the file
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        char *username = token;
        token = strtok(NULL, ",");
        char *name = token;
        token = strtok(NULL, ",");
        char *specialism = token;
        token = strtok(NULL, ",");
        char *startTime = token;
        token = strtok(NULL, ",");
        char *endTime = token;

        // Remove the newline character from endTime
        endTime[strcspn(endTime, "\n")] = '\0';

        // Check if the appointment belongs to the specified doctor
        if (strcmp(name, doctorName) == 0) {
            printf("%d. %s : %s - (%s) [%s - %s]\n", ++count, username, name, specialism, startTime, endTime);
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printf(RED"No appointments available for Dr. %s.\n\nPress ENTER to return ..."RESET, doctorName);
    }
    printf("\nPress ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 3.1.2__________________________VIEW DOCTOR SCHEDULE (END)

//CHAPTER 3.1.3__________________________DELETE DOCTOR SCHEDULE (START)

//CHAPTER 3.1.3.1__________________________RESCHEDULE DOCTOR SCHEDULE (START)
void reschedulePatientOfDeletedAppointment(const char *doctorUsername, const char *doctorName, const char *specialism, const char *startTime, const char *endTime) {
    char availableAppointments[100][256];
    int availableCount = 0;

    // Read all available appointments from Appointment.txt except the deleted one
    FILE *file = fopen("Appointment.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    while (fgets(availableAppointments[availableCount], sizeof(availableAppointments[availableCount]), file)) {
        char storedUsername[100], storedName[100], storedSpecialism[100], storedStartTime[6], storedEndTime[6];
        sscanf(availableAppointments[availableCount], "%[^,],%[^,],%[^,],%[^,],%s", storedUsername, storedName, storedSpecialism, storedStartTime, storedEndTime);

        if (!(strcmp(storedUsername, doctorUsername) == 0 && strcmp(storedName, doctorName) == 0 && strcmp(storedSpecialism, specialism) == 0 && strcmp(storedStartTime, startTime) == 0 && strcmp(storedEndTime, endTime) == 0)) {
            availableCount++;
        }
    }
    fclose(file);

    // Read the PatientAppointment.txt file to get the patients booked for the deleted appointment
    file = fopen("PatientAppointment.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char patientAppointments[100][256];
    int patientCount = 0;

    while (fgets(patientAppointments[patientCount], sizeof(patientAppointments[patientCount]), file)) {
        char patientUsername[100], patientName[100], patientDoctorUsername[100], patientDoctorName[100], patientSpecialism[100], patientStartTime[6], patientEndTime[6];
        sscanf(patientAppointments[patientCount], "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", patientUsername, patientName, patientDoctorUsername, patientDoctorName, patientSpecialism, patientStartTime, patientEndTime);
        if (strcmp(patientDoctorUsername, doctorUsername) == 0 && strcmp(patientDoctorName, doctorName) == 0 && strcmp(patientSpecialism, specialism) == 0 && strcmp(patientStartTime, startTime) == 0 && strcmp(patientEndTime, endTime) == 0) {
            patientCount++;
        }
    }
    fclose(file);

    // For each patient, reschedule their appointment
    int i;
    for (i = 0; i < patientCount; i++) {
        char patientUsername[100], patientName[100], patientDoctorUsername[100], patientDoctorName[100], patientSpecialism[100], patientStartTime[6], patientEndTime[6];
        sscanf(patientAppointments[i], "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", patientUsername, patientName, patientDoctorUsername, patientDoctorName, patientSpecialism, patientStartTime, patientEndTime);

        system("cls");
        printf("\n[DELETE SCHEDULE]\n\n");
        printf("Rescheduling for patient: %s (%s)\n", patientUsername, patientName);
        int j;
        printf("Available appointment times:\n");
        for (j = 0; j < availableCount; j++) {
            char storedUsername[100], storedName[100], storedSpecialism[100], storedStartTime[6], storedEndTime[6];
            sscanf(availableAppointments[j], "%[^,],%[^,],%[^,],%[^,],%s", storedUsername, storedName, storedSpecialism, storedStartTime, storedEndTime);
            printf("%d. %s | %s (%s) [%s - %s]\n", j + 1, storedUsername, storedName, storedSpecialism, storedStartTime, storedEndTime);
        }

        int rescheduleChoice;
        while (1) {




            system("cls");
            printf("\n[DELETE SCHEDULE]\n\n");
            printf("Rescheduling for patient: %s (%s)\n", patientUsername, patientName);
            int j;
            printf("Available appointment times:\n");
            for (j = 0; j < availableCount; j++) {
                char storedUsername[100], storedName[100], storedSpecialism[100], storedStartTime[6], storedEndTime[6];
                sscanf(availableAppointments[j], "%[^,],%[^,],%[^,],%[^,],%s", storedUsername, storedName, storedSpecialism, storedStartTime, storedEndTime);
                printf("%d. %s | %s (%s) [%s - %s]\n", j + 1, storedUsername, storedName, storedSpecialism, storedStartTime, storedEndTime);
            }





            printf("\nEnter the number of the new appointment time: ");
            scanf("%d", &rescheduleChoice);
            rescheduleChoice--;

            if (rescheduleChoice >= 0 && rescheduleChoice < availableCount) {
                break;
            }

            printf(RED"\nInvalid choice, select a valid option. Press ENTER to retry..."RESET);
            getchar();
            getchar();
            //system("cls");
        }

        // Update the patient appointment data
        char newUsername[100], newName[100], newSpecialism[100], newStartTime[6], newEndTime[6];
        sscanf(availableAppointments[rescheduleChoice], "%[^,],%[^,],%[^,],%[^,],%s", newUsername, newName, newSpecialism, newStartTime, newEndTime);

        // Update the PatientAppointment.txt
        file = fopen("PatientAppointment.txt", "r");
        FILE *tempFile = fopen("TempPatientAppointment.txt", "w");
        if (file == NULL || tempFile == NULL) {
            printf(RED"Error opening file!\n"RESET);
            return;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char tempUsername[100], tempName[100], tempDoctorUsername[100], tempDoctorName[100], tempSpecialism[100], tempStartTime[6], tempEndTime[6];
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", tempUsername, tempName, tempDoctorUsername, tempDoctorName, tempSpecialism, tempStartTime, tempEndTime);

            if (strcmp(tempUsername, patientUsername) == 0 && strcmp(tempName, patientName) == 0 && strcmp(tempDoctorUsername, doctorUsername) == 0 && strcmp(tempDoctorName, doctorName) == 0 && strcmp(tempSpecialism, specialism) == 0 && strcmp(tempStartTime, startTime) == 0 && strcmp(tempEndTime, endTime) == 0) {
                fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s\n", patientUsername, patientName, newUsername, newName, newSpecialism, newStartTime, newEndTime);
            } else {
                fputs(line, tempFile);
            }
        }
        fclose(file);
        fclose(tempFile);
        remove("PatientAppointment.txt");
        rename("TempPatientAppointment.txt", "PatientAppointment.txt");
    }

}
//CHAPTER 3.1.3.1__________________________RESCHEDULE DOCTOR SCHEDULE (END)

void deleteDoctorSchedule(const char *doctorUsername, const char *doctorName, const char *specialism) {
    int choice;
    char appointments[100][256];
    int appointmentCount = 0;

    // Read the doctor's appointments from Appointment.txt
    FILE *file = fopen("Appointment.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    while (fgets(appointments[appointmentCount], sizeof(appointments[appointmentCount]), file)) {
        char storedUsername[100], storedName[100], storedSpecialism[100], startTime[6], endTime[6];
        sscanf(appointments[appointmentCount], "%[^,],%[^,],%[^,],%[^,],%s", storedUsername, storedName, storedSpecialism, startTime, endTime);

        if (strcmp(storedUsername, doctorUsername) == 0) {
            appointmentCount++;
        }
    }
    fclose(file);

    // Check if there are no appointments for the doctor
    if (appointmentCount == 0) {
        printf("\n[DELETE SCHEDULE]\n\n");
        printf(RED"No appointments available for Dr. %s. Press ENTER to return..."RESET, doctorName);
        getchar();
        getchar();
        system("cls");
        return;
    }

    printf("\n[DELETE SCHEDULE]\n\n");
    int i;
    for (i = 0; i < appointmentCount; i++) {
        char startTime[6], endTime[6];
        sscanf(appointments[i], "%*[^,],%*[^,],%*[^,],%[^,],%s", startTime, endTime);
        printf("%d. %s | %s (%s) [%s - %s]\n", i + 1, doctorUsername, doctorName, specialism, startTime, endTime);
    }
    int deleteChoice;
    printf("\nEnter the number of the appointment to delete: ");
    scanf("%d", &deleteChoice);
    deleteChoice--;

    if (deleteChoice < 0 || deleteChoice >= appointmentCount) {
        printf(RED"Invalid choice! Press ENTER to retry..."RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    // Extract the selected appointment details
    char selectedStartTime[6], selectedEndTime[6];
    sscanf(appointments[deleteChoice], "%*[^,],%*[^,],%*[^,],%[^,],%s", selectedStartTime, selectedEndTime);

    // Check if the appointment is booked by any patients
    int booked = 0;
    file = fopen("PatientAppointment.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char patientUsername[100], patientName[100], patientDoctorUsername[100], patientDoctorName[100], patientSpecialism[100], patientStartTime[6], patientEndTime[6];
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", patientUsername, patientName, patientDoctorUsername, patientDoctorName, patientSpecialism, patientStartTime, patientEndTime);
            if (strcmp(patientDoctorUsername, doctorUsername) == 0 && strcmp(patientDoctorName, doctorName) == 0 && strcmp(patientSpecialism, specialism) == 0 && strcmp(patientStartTime, selectedStartTime) == 0 && strcmp(patientEndTime, selectedEndTime) == 0) {
                booked = 1;
                break;
            }
        }
        fclose(file);
    }

    if (booked) {
        reschedulePatientOfDeletedAppointment(doctorUsername, doctorName, specialism, selectedStartTime, selectedEndTime);
    }

    // Remove the appointment from Appointment.txt
    file = fopen("Appointment.txt", "r");
    FILE *tempFile = fopen("TempAppointment.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, appointments[deleteChoice]) != 0) {
            fputs(line, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("Appointment.txt");
    rename("TempAppointment.txt", "Appointment.txt");

    printf("\nAppointment deleted successfully.");
    printf("\nPress ENTER to return to the previous menu...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 3.1.3__________________________DELETE DOCTOR SCHEDULE (END)

// Function to manage doctor's schedule menu
void manageSchedule(const char *doctorUsername, const char *doctorName, const char *specialism) {
    int choice;

    while (1) {
        printf(" ---------------------------------------\n");
        printf("|         [MANAGE SCHEDULE MENU]        |\n");
        printf(" ---------------------------------------\n");
        printf("| 1. Insert Schedule                    |\n");
        printf("| 2. View Schedule                      |\n");
        printf("| 3. Delete Schedule                    |\n");
        printf("| 4. Return to Doctor Menu              |\n");
        printf(" ---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on doctor's choice
        switch (choice) {
            case 1:
                insertAppointment(doctorUsername, doctorName, specialism);
                break;
            case 2:
                system("cls");
                viewDoctorSchedule(doctorName);
                break;
            case 3:
                system("cls");
                deleteDoctorSchedule(doctorUsername, doctorName, specialism);
                break;
            case 4:
                system("cls");
                return; // Return to the Doctor Menu
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}
//CHAPTER 3.1__________________________DOCTOR MANAGE SCHEDULE MENU (END)


//CHAPTER 3.2__________________________SECURE EHR ACCESS (START)
void secureEHRAccess(const char *doctorUsername, const char *doctorName) {
    FILE *file = fopen("PatientAppointment.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    char line[256];
    int patientCount = 0;
    printf("\n[SECURE EHR ACCESS]\n\n");

    // Array to store patient usernames and names
    char patientUsernames[100][50];
    char patientNames[100][50];

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        char *patientUsername = token;
        token = strtok(NULL, ",");
        char *patientName = token;
        token = strtok(NULL, ",");
        char *doctorUsernameFile = token;
        token = strtok(NULL, ",");
        char *doctorNameFile = token;
        token = strtok(NULL, ",");
        char *specialism = token;
        token = strtok(NULL, ",");
        char *startTime = token;
        token = strtok(NULL, ",");
        char *endTime = token;

        // Remove the newline character from endTime
        endTime[strcspn(endTime, "\n")] = '\0';

        // Check if the appointment belongs to the logged-in doctor
        if (strcmp(doctorUsername, doctorUsernameFile) == 0 && strcmp(doctorName, doctorNameFile) == 0) {
            printf("%d. %s (%s)\n", ++patientCount, patientName, patientUsername);
            strcpy(patientUsernames[patientCount - 1], patientUsername);
            strcpy(patientNames[patientCount - 1], patientName);
        }
    }
    fclose(file);

    if (patientCount == 0) {
        printf(RED"No patients available for appointment. Press ENTER to return...\n"RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    int selectedPatient;
    printf("\nSelect the patient to check (1-%d): ", patientCount);
    scanf("%d", &selectedPatient);
    system("cls");

    if (selectedPatient < 1 || selectedPatient > patientCount) {
        printf(RED"Invalid selection. Press ENTER to return...\n"RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    selectedPatient--; // Adjust for 0-based index

    // Reopen the file to get the selected patient's information
    file = fopen("Patient.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    // Search for the selected patient's information
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        char *username = token;
        token = strtok(NULL, ",");
        char *password = token;
        token = strtok(NULL, ",");
        char *name = token;
        token = strtok(NULL, ",");
        char *dob = token;
        token = strtok(NULL, ",");
        char *address = token;
        token = strtok(NULL, ",");
        char *insurance = token;
        token = strtok(NULL, ",");
        char *diagnosticReport = token;
        token = strtok(NULL, ",");
        char *allergies = token;
        token = strtok(NULL, ",");
        char *medicalHistory = token;
        token = strtok(NULL, ",");
        char *pastProcedure = token;

        // Remove the newline character from pastProcedure
        pastProcedure[strcspn(pastProcedure, "\n")] = '\0';

        // Check if the current patient is the selected one
        if (strcmp(username, patientUsernames[selectedPatient]) == 0) {
            printf(" -------------------------------------------------\n");
            printf("|          [SELECTED PATIENT INFORMATION]         |\n");
            printf(" -------------------------------------------------\n");
            printf(" Patient Name: %s\n", name);
            printf(" Date of Birth (DD-MM-YYYY): %s\n", dob);
            printf(" Address: %s\n", address);
            printf(" Insurance: %s\n", insurance);
            printf(" Diagnostic Report: %s\n", diagnosticReport);
            printf(" Allergies: %s\n", allergies);
            printf(" Medical History: %s\n", medicalHistory);
            printf(" Past Procedure: %s\n", pastProcedure);
            printf("-------------------------------------------------\n");
            break; // Stop searching after finding the selected patient's information
        }
    }
    fclose(file);

    printf("\nPress ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 3.2__________________________SECURE EHR ACCESS (END)


//CHAPTER 3.3__________________________REPORT MENU (START)

//CHAPTER 3.3.1__________________________GENERATE NEW REPORT (START)
void readAppointments(Appointment appointments[], int *numAppointments) {
    FILE *file = fopen("Appointment.txt", "r");
    if (!file) {
        perror(RED"Unable to open Appointment.txt"RESET);
        exit(1);
    }
    *numAppointments = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%s\n", appointments[*numAppointments].username,
                  appointments[*numAppointments].name, appointments[*numAppointments].specialism,
                  appointments[*numAppointments].startTime, appointments[*numAppointments].endTime) == 5) {
        (*numAppointments)++;
    }
    fclose(file);
}

void readPatients(Patient patients[], int *numPatients) {
    FILE *file = fopen("Patient.txt", "r");
    if (!file) {
        perror(RED"Unable to open Patient.txt"RESET);
        exit(1);
    }
    *numPatients = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", patients[*numPatients].username,
                  patients[*numPatients].password, patients[*numPatients].name, patients[*numPatients].dob,
                  patients[*numPatients].address, patients[*numPatients].insurance, patients[*numPatients].diagnosticReport,
                  patients[*numPatients].allergies, patients[*numPatients].medicalHistory, patients[*numPatients].pastProcedure) == 10) {
        (*numPatients)++;
    }
    fclose(file);
}

void readPatientAppointments(PatientAppointment patientAppointments[], int *numPatientAppointments) {
    FILE *file = fopen("PatientAppointment.txt", "r");
    if (!file) {
        perror(RED"Unable to open PatinetAppointment.txt"RESET);
        exit(1);
    }
    *numPatientAppointments = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", patientAppointments[*numPatientAppointments].username,
                  patientAppointments[*numPatientAppointments].patientName, patientAppointments[*numPatientAppointments].doctorUsername,
                  patientAppointments[*numPatientAppointments].doctorName, patientAppointments[*numPatientAppointments].doctorSpecialism,
                  patientAppointments[*numPatientAppointments].startTime, patientAppointments[*numPatientAppointments].endTime) == 7) {
        (*numPatientAppointments)++;
    }
    fclose(file);
}

void readInventory(InventoryItem inventory[], int *numItems) {
    FILE *file = fopen("Inventory.txt", "r");
    if (!file) {
        perror(RED"Unable to open Inventory.txt"RESET);
        exit(1);
    }
    *numItems = 0;
    while (fscanf(file, "%[^,],%f,%d\n", inventory[*numItems].name, &inventory[*numItems].price, &inventory[*numItems].quantity) == 3) {
        (*numItems)++;
    }
    fclose(file);
}

void writeInventory(InventoryItem inventory[], int numItems) {
    FILE *file = fopen("Inventory.txt", "w");
    if (!file) {
        perror(RED"Unable to open Inventory.txt"RESET);
        exit(1);
    }
    int i;
    for (i = 0; i < numItems; i++) {
        fprintf(file, "%s,%.2f,%d\n", inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    fclose(file);
}

void writeConsultation(Consultation consultation) {
    FILE *file = fopen("PatientConsultation.txt", "a");
    if (!file) {
        perror(RED"Unable to open PatientConsultation.txt"RESET);
        exit(1);
    }
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%.2f\n", consultation.patientUsername, consultation.patientName,
            consultation.doctorUsername, consultation.doctorName, consultation.doctorSpecialism,
            consultation.startTime, consultation.endTime, consultation.medication, consultation.quantity,
            consultation.prescription, consultation.billing);
    fclose(file);
}

void readConsultedPatients(char consultedPatients[][50], int *numConsulted) {
    FILE *file = fopen("PatientConsultation.txt", "r");
    if (!file) {
        perror(RED"Unable to open PatientConsultation.txt"RESET);
        exit(1);
    }
    *numConsulted = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char patientUsername[50];
        sscanf(line, "%[^,],", patientUsername);
        strcpy(consultedPatients[(*numConsulted)++], patientUsername);
    }
    fclose(file);
}

int isConsulted(char consultedPatients[][50], int numConsulted, const char *username) {
    int i;
    for (i = 0; i < numConsulted; i++) {
        if (strcmp(consultedPatients[i], username) == 0) {
            return 1;
        }
    }
    return 0;
}

void generateNewReport(const char *doctorUsername, const char *doctorName) {
    Appointment appointments[MAX_PATIENTS];
    Patient patients[MAX_PATIENTS];
    PatientAppointment patientAppointments[MAX_PATIENTS];
    InventoryItem inventory[MAX_ITEMS];
    int numAppointments, numPatients, numPatientAppointments, numItems;
    char consultedPatients[MAX_PATIENTS][50];
    int numConsulted;

    readAppointments(appointments, &numAppointments);
    readPatients(patients, &numPatients);
    readPatientAppointments(patientAppointments, &numPatientAppointments);
    readInventory(inventory, &numItems);
    readConsultedPatients(consultedPatients, &numConsulted);

    int patientIndices[MAX_PATIENTS], numPatientIndices = 0;

    int i;
    for (i = 0; i < numPatientAppointments; i++) {
        if (strcmp(patientAppointments[i].doctorUsername, doctorUsername) == 0 &&
            !isConsulted(consultedPatients, numConsulted, patientAppointments[i].username)) {
            patientIndices[numPatientIndices++] = i;
        }
    }

    if (numPatientIndices == 0) {
        printf("\n[MANAGE GENERATED REPORTS]\n\n");
        printf(GREEN"All patients had been consulted. Press ENTER to return..."RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    printf("\n[GENERATE NEW PATIENT REPORT]\n\n");
    int j;
    for (j = 0; j < numPatientIndices; j++) {
        int index = patientIndices[j];
        printf("%d. %s - (%s)\n", j + 1, patientAppointments[index].patientName, patientAppointments[index].username);
    }

    int selectedPatientIndex;
    printf("\nSelect a patient to consult: ");
    scanf("%d", &selectedPatientIndex);
    selectedPatientIndex--;  // Adjusting to 0-based index
    system("cls");

    if (selectedPatientIndex < 0 || selectedPatientIndex >= numPatientIndices) {
        printf(RED"Invalid selection. Press ENTER to return..."RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    int patientIndex = patientIndices[selectedPatientIndex];
    PatientAppointment selectedPatient = patientAppointments[patientIndex];

    printf("\n[GENERATE NEW PATIENT REPORT]\n\n");
    int k;
    for (k = 0; k < numItems; k++) {
        printf("%d. %s\n", k + 1, inventory[k].name);
    }

    int selectedItemIndex;
    printf("\nSelect a medication: ");
    scanf("%d", &selectedItemIndex);
    selectedItemIndex--;  // Adjusting to 0-based index
    printf("-----------------------------------");

    if (selectedItemIndex < 0 || selectedItemIndex >= numItems) {
        printf(RED"Invalid selection. Press ENTER to return..."RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    InventoryItem selectedItem = inventory[selectedItemIndex];

    printf("\nAvailable stock [%d]", selectedItem.quantity);
    printf("\nEnter quantity for patient's medication: ");
    int quantity;
    scanf("%d", &quantity);

    if (quantity <= 0 || quantity > selectedItem.quantity) {
        printf(RED"Invalid selection. Press ENTER to return..."RESET);
        getchar();
        getchar();
        system("cls");
        return;
    }

    printf("Enter prescription:\n");
    char prescription[100];
    scanf(" %[^\n]s", prescription);

    selectedItem.quantity -= quantity;
    inventory[selectedItemIndex] = selectedItem;
    writeInventory(inventory, numItems);

    Consultation consultation;
    strcpy(consultation.patientUsername, selectedPatient.username);
    strcpy(consultation.patientName, selectedPatient.patientName);
    strcpy(consultation.doctorUsername, selectedPatient.doctorUsername);
    strcpy(consultation.doctorName, selectedPatient.doctorName);
    strcpy(consultation.doctorSpecialism, selectedPatient.doctorSpecialism);
    strcpy(consultation.startTime, selectedPatient.startTime);
    strcpy(consultation.endTime, selectedPatient.endTime);
    strcpy(consultation.medication, selectedItem.name);
    consultation.quantity = quantity;
    strcpy(consultation.prescription, prescription);
    consultation.billing = 300.0 + (quantity * selectedItem.price);

    writeConsultation(consultation);

    printf("-----------------------------------");
    printf("\nTotal Billing: RM %.2f\n", consultation.billing);
    printf(GREEN"Consultation saved. Press ENTER to return..."RESET);
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 3.3.1__________________________GENERATE NEW REPORT (END)

//CHAPTER 3.3.2__________________________VIEW GENERATED REPORT (START)
void viewGeneratedReport(const char *doctorUsername) {
    FILE *file = fopen("PatientConsultation.txt", "r");
    if (!file) {
        perror(RED"Unable to open PatientConsultation.txt"RESET);
        return;
    }

    char line[256];
    int found = 0;
    int count = 0;

    printf("\n[VIEW GENERATED PATIENT REPORT]\n\n");
    while (fgets(line, sizeof(line), file)) {
        char storedDoctorUsername[50], patientName[50], patientUsername[50];
        if (sscanf(line, "%[^,],%[^,],%[^,],", patientUsername, patientName, storedDoctorUsername) != 3) {
            continue;
        }
        if (strcmp(storedDoctorUsername, doctorUsername) == 0) {
            printf("%d. %s - (%s)\n", ++count, patientName, patientUsername);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf(RED"No patients found for consultation by %s.\n\nPress ENTER to return..."RESET, doctorUsername);
        getchar();
        getchar();
        system("cls");

        return;
    }

    int selectedPatientIndex;
    printf("\nEnter the patient to view their report: ");
    scanf("%d", &selectedPatientIndex);

    file = fopen("PatientConsultation.txt", "r");
    if (!file) {
        perror(RED"Unable to open PatientConsultation.txt"RESET);
        return;
    }

    system("cls");
    printf("\n[VIEW GENERATED PATIENT REPORT]\n\n");
    count = 0;
    while (fgets(line, sizeof(line), file)) {
        char storedPatientUsername[50], storedDoctorUsername[50], patientName[50], doctorName[50], doctorSpecialism[50], startTime[6], endTime[6], medication[50], prescription[100];
        int quantity;
        float billing;
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f", storedPatientUsername, patientName, storedDoctorUsername, doctorName, doctorSpecialism, startTime, endTime, medication, &quantity, prescription, &billing) != 11) {
            continue;
        }
        if (strcmp(storedDoctorUsername, doctorUsername) == 0) {
            count++;
            if (count == selectedPatientIndex) {
                printf("Report for Patient: %s (%s)\n", patientName, storedPatientUsername);
                printf("Doctor: %s (%s)\n", doctorName, storedDoctorUsername);
                printf("Specialism: %s\n", doctorSpecialism);
                printf("Appointment Time: %s - %s\n", startTime, endTime);
                printf("Medication: %s\n", medication);
                printf("Quantity: %d unit\n", quantity);
                printf("Prescription: %s\n", prescription);
                printf("Billing: RM %.2f\n", billing);
                printf("----------------------------------\n");
                fclose(file);

                printf("\nPress ENTER to continue...");
                getchar();
                getchar();
                system("cls");
                return;
            }
        }
    }

    fclose(file);
    printf(RED"Invalid selection.\n"RESET);
}
//CHAPTER 3.3.2__________________________VIEW GENERATED REPORT (END)

//CHAPTER 3.3.3__________________________DELETE GENERATED REPORT (START)
void deleteGeneratedReport(const char *doctorUsername) {
    FILE *file = fopen("PatientConsultation.txt", "r");
    if (!file) {
        perror(RED"Unable to open PatientConsultation.txt"RESET);
        return;
    }

    char line[256];
    int found = 0;
    int count = 0;

    printf("\n[DELETE GENERATED PATIENT REPORT]\n\n");

    while (fgets(line, sizeof(line), file)) {
        char storedPatientUsername[50], storedDoctorUsername[50], patientName[50];
        if (sscanf(line, "%[^,],%[^,],%[^,],", storedPatientUsername, patientName, storedDoctorUsername) != 3) {
            continue;
        }
        if (strcmp(storedDoctorUsername, doctorUsername) == 0) {
            printf("%d. %s - (%s)\n", ++count, patientName, storedPatientUsername);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf(RED"No patients found for consultation by %s.\n\nPress ENTER to return..."RESET, doctorUsername);
        getchar();
        getchar();
        system("cls");
        return;
    }

    int selectedPatientIndex;
    printf("\nEnter the number of the patient to delete their report: ");
    scanf("%d", &selectedPatientIndex);
    system("cls");

    file = fopen("PatientConsultation.txt", "r");
    if (!file) {
        perror(RED"Unable to open PatientConsultation.txt"RESET);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror(RED"Unable to create temp file"RESET);
        fclose(file);
        return;
    }

    count = 0;
    while (fgets(line, sizeof(line), file)) {
        char storedPatientUsername[50], storedDoctorUsername[50], patientName[50];
        if (sscanf(line, "%[^,],%[^,],%[^,],", storedPatientUsername, patientName, storedDoctorUsername) != 3) {
            fprintf(tempFile, "%s", line);
            continue;
        }
        if (strcmp(storedDoctorUsername, doctorUsername) == 0) {
            count++;
            if (count == selectedPatientIndex) {
                printf("\n[DELETE GENERATED PATIENT REPORT]\n\n");
                printf(GREEN"Report for Patient %s (%s) has been deleted.\n\nPress ENTER to return..."RESET, patientName, storedPatientUsername);
                getchar();
                getchar();
                system("cls");
                continue; // Skip writing this line to temp file
            }
        }
        fprintf(tempFile, "%s", line);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with temp file
    remove("PatientConsultation.txt");
    rename("temp.txt", "PatientConsultation.txt");
}
//CHAPTER 3.3.3__________________________DELETE GENERATED REPORT (END)

void reportMenu(const char *doctorUsername, const char *doctorName) {
    int choice;

    while (1) {
        printf(" -----------------------------------------------\n");
        printf("|           [MANAGE GENERATED REPORTS]          |\n");
        printf(" -----------------------------------------------\n");
        printf("| 1. Generate New Report                        |\n");
        printf("| 2. View Generated Report                      |\n");
        printf("| 3. Delete Generated Report                    |\n");
        printf("| 4. Return to Doctor Menu                      |\n");
        printf(" -----------------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                generateNewReport(doctorUsername, doctorName);
                break;
            case 2:
                system("cls");
                viewGeneratedReport(doctorUsername);
                break;
            case 3:
                system("cls");
                deleteGeneratedReport(doctorUsername);
                break;
            case 4:
                system("cls");
                return; // Return to the Doctor Menu
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}
//CHAPTER 3.3__________________________REPORT MENU (END)


// Function to display the doctor's menu
void doctorMenu(const char *doctorUsername, const char *doctorName, const char *specialism) {
    int choice;

    while (1) {
        printf(" -------------------------------------------------\n");
        printf("[DOCTOR MENU - Welcome Dr. %s]\n", doctorName);
        printf(" -------------------------------------------------\n");
        printf("| 1. Manage Schedule                              |\n");
        printf("| 2. Secure EHR Access                            |\n");
        printf("| 3. Patient Report Menu                          |\n");
        printf("| 4. Logout                                       |\n");
        printf(" -------------------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on doctor's choice
        switch (choice) {
            case 1:
                system("cls");
                manageSchedule(doctorUsername, doctorName, specialism);
                break;
            case 2:
                system("cls");
                secureEHRAccess(doctorUsername, doctorName);
                break;
            case 3:
                system("cls");
                reportMenu(doctorUsername, doctorName);
                break;
            case 4:
                printf("Logging out... Press ENTER to continue...");
                getchar();
                getchar();
                system("cls");
                return; // Logout and return to the main menu
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}

//CHAPTER 3 (INITIALIZER)__________________________LOGIN AS DOCTOR (START)
// Function to login as a doctor
void doctorLogin() {
    char username[100];
    char password[100];
    char line[256];
    int attempts = 0;
    int loginSuccess = 0;

    while (attempts < 3 && !loginSuccess) {
        printf("\n[DOCTOR LOGIN]\n(Type 'RETURN' to go back)\n\n");
        printf("Username: ");
        scanf("%s", username);

        if (strcmp(username, "RETURN") == 0) {
            system("cls");
            return;
        }

        printf("Password: ");

        // Get password input and mask with '*'
        int i = 0;
        char ch;
        while (1) {
            ch = _getch(); // Get character without echoing to the console
            if (ch == 13) { // Enter key is pressed
                password[i] = '\0';
                break;
            } else if (ch == 8) { // Backspace is pressed
                if (i > 0) {
                    i--;
                    printf("\b \b"); // Erase the last '*'
                }
            } else {
                password[i++] = ch;
                printf("*");
            }
        }
        printf("\n");

        FILE *file = fopen("Doctor.txt", "r");
        if (file == NULL) {
            printf(RED"Error opening file!\n"RESET);
            exit(1);
        }

        char storedUsername[100];
        char storedPassword[100];
        char storedName[100];
        char storedSpecialism[100];

        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "Username:") != NULL) {
                strcpy(storedUsername, line + strlen("Username: "));
                storedUsername[strcspn(storedUsername, "\n")] = 0; // Remove newline

                fgets(line, sizeof(line), file);
                strcpy(storedPassword, line + strlen("Password: "));
                storedPassword[strcspn(storedPassword, "\n")] = 0; // Remove newline

                fgets(line, sizeof(line), file);
                strcpy(storedName, line + strlen("Name: "));
                storedName[strcspn(storedName, "\n")] = 0; // Remove newline

                fgets(line, sizeof(line), file);
                strcpy(storedSpecialism, line + strlen("Specialism: "));
                storedSpecialism[strcspn(storedSpecialism, "\n")] = 0; // Remove newline

                // Skip the blank line
                fgets(line, sizeof(line), file);

                if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
                    loginSuccess = 1;
                    fclose(file);
                    printf(GREEN"\nLogin successful! Press ENTER to continue..."RESET);
                    getchar();
                    getchar();
                    system("cls");
                    doctorMenu(storedUsername, storedName, storedSpecialism); // Call doctor menu with the doctor's name
                    break;
                }
            }
        }

        if (!loginSuccess) {
            fclose(file);
            attempts++;
            if (attempts < 3) {
                printf(RED"\nInvalid username or password. Remaining attempt(s) [%d]."RESET, 3 - attempts);
                getchar();
                getchar();
                system("cls");
            } else {
                printf(RED"Too many failed attempts. Press ENTER to shut down the system..."RESET);
                getchar();
                getchar();
                system("cls");
                exit(0);
            }
        }
    }
}
//CHAPTER 3 (INITIALIZER)__________________________LOGIN AS DOCTOR (END)

//CHAPTER 3__________________________DOCTOR MENU (END)
















//CHAPTER 4__________________________NURSE MENU (START)

//CHAPTER 4.1__________________________NURSE DOCTOR SCHEDULER (START)
void doctorScheduler() {
    FILE *file = fopen("Appointment.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int appointmentCount = 0;
    char appointments[MAX_APPOINTMENTS][MAX_LINE_LENGTH];
    int patientCount[MAX_APPOINTMENTS] = {0};

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        strcpy(appointments[appointmentCount], line);

        // Count the number of patients for each appointment
        FILE *patientFile = fopen("PatientAppointment.txt", "r");
        if (patientFile != NULL) {
            char patientLine[MAX_LINE_LENGTH];
            while (fgets(patientLine, sizeof(patientLine), patientFile)) {
                if (strstr(patientLine, line) != NULL) {
                    patientCount[appointmentCount]++;
                }
            }
            fclose(patientFile);
        }

        appointmentCount++;
    }
    fclose(file);

    if (appointmentCount == 0) {
        printf(RED"No registered appointments.\n"RESET);
        return;
    }

    printf("\n[DOCTOR SCHEDULER]\n\n");
    int i;
    for (i = 0; i < appointmentCount; i++) {
        char doctorUsername[100], doctorName[100], specialism[100], startTime[6], endTime[6];
        sscanf(appointments[i], "%[^,],%[^,],%[^,],%[^,],%s", doctorUsername, doctorName, specialism, startTime, endTime);

        printf("%d. %s (%s) [%s - %s]", i + 1, doctorName, specialism, startTime, endTime);
        if (patientCount[i] >= 3) {
            if (patientCount[i] > 3) {
                printf(RED" (maximum limit exceeded)"RESET);
            } else {
                printf(RED" (maximum limit of 3 patients reached)"RESET);
            }
        } else {
            int remainingSlots = 3 - patientCount[i];
            printf(GREEN" (%d remaining slot(s) available)"RESET, remainingSlots);
        }
        printf("\n");
    }
    printf("\nPress ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 4.1__________________________NURSE DOCTOR SCHEDULER (END)

//CHAPTER 4.2__________________________NURSE INVENTORY MENU (START)

//CHAPTER 4.2.1__________________________NURSE MANAGE INVENTORY (START)

//CHAPTER 4.2.1.1__________________________INPUT NEW PRODUCT RECORD (START)
void inputNewProductRecord() {
    char itemName[100];
    float itemPrice;
    int itemQuantity;

    system("cls");
    printf("\n[INPUT NEW PRODUCT RECORD]\n\n");
    printf("Enter the item's name: ");
    scanf("%s", itemName);
    printf("Enter the item's price (2 decimal places): RM");
    scanf("%f", &itemPrice);
    printf("Enter the item's quantity: ");
    scanf("%d", &itemQuantity);

    FILE *file = fopen("Inventory.txt", "a");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }
    fprintf(file, "%s,%.2f,%d\n", itemName, itemPrice, itemQuantity);
    fclose(file);

    printf(GREEN"\nNew product record added successfully. Press ENTER to return..."RESET);
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 4.2.1.1__________________________INPUT NEW PRODUCT RECORD (END)

//CHAPTER 4.2.1.2__________________________EDIT PRODUCT QTY (START)
void editProductRecord() {
    FILE *file = fopen("Inventory.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int itemCount = 0;
    char items[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int i;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        strcpy(items[itemCount], line);
        itemCount++;
    }
    fclose(file);

    if (itemCount == 0) {
        printf(RED"No items available.\n");
        return;
    }

    printf("\n[EDIT PRODUCT QUANTITY]\n\n");
    for (i = 0; i < itemCount; i++) {
        char itemName[100];
        int itemQuantity;
        sscanf(items[i], "%[^,],%*f,%d", itemName, &itemQuantity);
        printf("%d. %s | QTY: %d\n", i + 1, itemName, itemQuantity);
    }

    int choice;
    printf("\nSelect an item to edit: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > itemCount) {
        printf(RED"\nInvalid selection. Press ENTER to return..."RESET);
        getchar();
        getchar();
        return;
    }

    char itemName[100];
    float itemPrice;
    int oldQuantity;
    sscanf(items[choice - 1], "%[^,],%f,%d", itemName, &itemPrice, &oldQuantity);

    system("cls");
    printf("\n[EDIT PRODUCT QUANTITY]\n\n");
    printf("Selected Item: %s | QTY: %d\n", itemName, oldQuantity);

    int newQuantity;
    printf("\nEnter the new quantity: ");
    scanf("%d", &newQuantity);

    // Update the selected item
    sprintf(items[choice - 1], "%s,%.2f,%d", itemName, itemPrice, newQuantity);

    // Write the updated list back to the file
    file = fopen("Inventory.txt", "w");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }
    for (i = 0; i < itemCount; i++) {
        fprintf(file, "%s\n", items[i]);
    }
    fclose(file);

    printf(GREEN"\nProduct record updated successfully. Press ENTER to return..."RESET);
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 4.2.1.2__________________________EDIT PRODUCT QTY (END)

//CHAPTER 4.2.1.3__________________________DELETE PRODUCT RECORD (START)
void deleteProductRecord() {
    FILE *file = fopen("Inventory.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int itemCount = 0;
    char items[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int i;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        strcpy(items[itemCount], line);
        itemCount++;
    }
    fclose(file);

    if (itemCount == 0) {
        printf(RED"No items available.\n"RESET);
        return;
    }

    system("cls");
    printf("[DELETE PRODUCT RECORD]\n\n");
    for (i = 0; i < itemCount; i++) {
        char itemName[100];
        int itemQuantity;
        float itemPrice;
        sscanf(items[i], "%[^,],%f,%d", itemName, &itemPrice, &itemQuantity);
        printf("%d. %s | QTY: %d | RM%.2f\n", i + 1, itemName, itemQuantity, itemPrice);
    }

    int choice;
    printf("\nSelect an item to delete: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > itemCount) {
        printf(RED"\nInvalid selection. Press ENTER to return..."RESET);
        getchar();
        getchar();
        return;
    }

    // Remove the selected item from the list
    for (i = choice - 1; i < itemCount - 1; i++) {
        strcpy(items[i], items[i + 1]);
    }
    itemCount--;

    // Write the updated list back to the file
    file = fopen("Inventory.txt", "w");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }
    for (i = 0; i < itemCount; i++) {
        fprintf(file, "%s\n", items[i]);
    }
    fclose(file);

    printf(GREEN"\nProduct record deleted successfully. Press ENTER to return..."RESET);
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 4.2.1.3__________________________DELETE PRODUCT RECORD (END)

void manageInventory() {
    int choice;

    while (1) {
        printf(" ---------------------------------------\n");
        printf("|           [MANAGE INVENTORY]          |\n");
        printf(" ---------------------------------------\n");
        printf("| 1. Input New Product Record           |\n");
        printf("| 2. Edit Product Record                |\n");
        printf("| 3. Delete Product Record              |\n");
        printf("| 4. Return to Inventory Menu           |\n");
        printf(" ---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                inputNewProductRecord();
                break;
            case 2:
                system("cls");
                editProductRecord();
                break;
            case 3:
                system("cls");
                deleteProductRecord();
                break;
            case 4:
                system("cls");
                return; // Return to the Inventory Menu
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}
//CHAPTER 4.2.1__________________________NURSE MANAGE INVENTORY (END)

//CHAPTER 4.2.2__________________________DISPLAY ALL PRODUCT RECORD (START)
void displayAllProductRecord() {
    FILE *file = fopen("Inventory.txt", "r");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int itemCount = 0;
    char items[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int i;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        strcpy(items[itemCount], line);
        itemCount++;
    }
    fclose(file);

    if (itemCount == 0) {
        printf(RED"No items available.\n"RESET);
        return;
    }

    printf("\n[DISPLAY ALL PRODUCT RECORDS]\n\n");
    for (i = 0; i < itemCount; i++) {
        char itemName[100];
        int itemQuantity;
        float itemPrice;
        sscanf(items[i], "%[^,],%f,%d", itemName, &itemPrice, &itemQuantity);
        printf("%d. %s | QTY: %d | RM %.2f\n", i + 1, itemName, itemQuantity, itemPrice);
    }
    printf("\nPress ENTER to return...");
    getchar();
    getchar();
    system("cls");
}
//CHAPTER 4.2.2__________________________DISPLAY ALL PRODUCT RECORD (END)


void inventoryMenu() {
    int choice;

    while (1) {
        printf(" ---------------------------------------\n");
        printf("|             [INVENTORY MENU]          |\n");
        printf(" ---------------------------------------\n");
        printf("| 1. Manage Inventory                   |\n");
        printf("| 2. Display All Product Record         |\n");
        printf("| 3. Return to Nurse Menu               |\n");
        printf(" ---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                manageInventory();
                break;
            case 2:
                system("cls");
                displayAllProductRecord();
                break;
            case 3:
                system("cls");
                return; // Return to the Nurse Menu
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}
//CHAPTER 4.2__________________________NURSE INVENTORY MENU (END)

//CHAPTER 4.3__________________________REPORT MENU (START)

//CHAPTER 4.3.1__________________________GENERATE DOCTOR REPORT (START)
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int readPatientConsultations(PatientConsultation consultations[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(RED"Error opening file %s!\n"RESET, filename);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_ITEMS) {
        trim_newline(line);
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f",
               consultations[count].username,
               consultations[count].name,
               consultations[count].doctorUsername,
               consultations[count].doctorName,
               consultations[count].doctorSpecialism,
               consultations[count].startTime,
               consultations[count].endTime,
               consultations[count].medication,
               &consultations[count].quantity,
               consultations[count].prescription,
               &consultations[count].billing);
        count++;
    }

    fclose(file);
    return count;
}

int readPatientsNurse(Patient patients[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(RED"Error opening file %s!\n"RESET, filename);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_ITEMS) {
        trim_newline(line);
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
               patients[count].username,
               patients[count].password,
               patients[count].name,
               patients[count].dob,
               patients[count].address,
               patients[count].insurance,
               patients[count].diagnosticReport,
               patients[count].allergies,
               patients[count].medicalHistory,
               patients[count].pastProcedure);
        count++;
    }

    fclose(file);
    return count;
}

int isReportGenerated(const char *doctorUsername, const char *startTime, const char *endTime, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        trim_newline(line);
        char storedDoctorUsername[50], storedStartTime[6], storedEndTime[6];
        sscanf(line, "%[^,],%*[^,],%*[^,],%[^,],%[^,]", storedDoctorUsername, storedStartTime, storedEndTime);
        if (strcmp(doctorUsername, storedDoctorUsername) == 0 &&
            strcmp(startTime, storedStartTime) == 0 &&
            strcmp(endTime, storedEndTime) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void displayPatientInfo(const PatientConsultation *consultation, const Patient patients[], int patientCount) {
    int i;
    for (i = 0; i < patientCount; i++) {
        if (strcmp(consultation->username, patients[i].username) == 0) {
            printf(" -------------------------------------------------------------\n");
            printf("|                     (Consulted Patient Data)                |\n");
            printf(" -------------------------------------------------------------\n");
            printf("Patient's Username: %s\n", patients[i].username);
            printf("Patient's Name: %s\n", patients[i].name);
            printf("Patient's Diagnostic Report: %s\n", patients[i].diagnosticReport);
            printf("Patient's Allergy: %s\n", patients[i].allergies);
            printf("Patient's Medical History: %s\n", patients[i].medicalHistory);
            printf("Patient's Past Procedure: %s\n", patients[i].pastProcedure);
            printf("Patient's Medication: %s\n", consultation->medication);
            printf("Patient's Quantity of Medication: %d\n", consultation->quantity);
            printf("Patient's Prescription: %s\n", consultation->prescription);
            printf("Patient's Billing: RM %.2f\n", consultation->billing);
            printf("--------------------------------------------------------------\n\n");
            break;
        }
    }
}

void generateDoctorReport(PatientConsultation consultations[], int consultationCount, Patient patients[], int patientCount) {
    int choice;

    DoctorAppointment doctorAppointments[MAX_ITEMS];
    int doctorCount = 0;

    int i;
    for (i = 0; i < consultationCount; i++) {
        int found = 0;
        int j;
        for (j = 0; j < doctorCount; j++) {
            if (strcmp(consultations[i].doctorUsername, doctorAppointments[j].username) == 0 &&
                strcmp(consultations[i].startTime, doctorAppointments[j].startTime) == 0 &&
                strcmp(consultations[i].endTime, doctorAppointments[j].endTime) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(doctorAppointments[doctorCount].username, consultations[i].doctorUsername);
            strcpy(doctorAppointments[doctorCount].name, consultations[i].doctorName);
            strcpy(doctorAppointments[doctorCount].specialism, consultations[i].doctorSpecialism);
            strcpy(doctorAppointments[doctorCount].startTime, consultations[i].startTime);
            strcpy(doctorAppointments[doctorCount].endTime, consultations[i].endTime);
            doctorCount++;
        }
    }

    while (1) {
        printf("\n[GENERATE NEW DOCTOR REPORT]\n\n");
        int i;
        for (i = 0; i < doctorCount; i++) {
            printf("%d. %s | %s (%s) [%s - %s]",
                   i + 1, doctorAppointments[i].username, doctorAppointments[i].name, doctorAppointments[i].specialism,
                   doctorAppointments[i].startTime, doctorAppointments[i].endTime);
            if (isReportGenerated(doctorAppointments[i].username, doctorAppointments[i].startTime, doctorAppointments[i].endTime, "DoctorConsultation.txt")) {
                printf(" (Report Generated)");
            }
            printf("\n");
        }
        printf("%d. Return to previous menu\n", doctorCount + 1);

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == doctorCount + 1) {
            system("cls");
            return;
        } else if (choice > 0 && choice <= doctorCount) {
            if (isReportGenerated(doctorAppointments[choice - 1].username, doctorAppointments[choice - 1].startTime, doctorAppointments[choice - 1].endTime, "DoctorConsultation.txt")) {
                printf("The selected doctor's report has already been generated. Press ENTER to retry...");
                getchar();
                getchar();
                system("cls");
                continue;
            }

            int allConsulted = 1;
            //int i;
            system("cls");
            printf("\n[GENERATE NEW DOCTOR REPORT]\n\n");
            for (i = 0; i < consultationCount; i++) {
                if (strcmp(consultations[i].doctorUsername, doctorAppointments[choice - 1].username) == 0 &&
                    strcmp(consultations[i].startTime, doctorAppointments[choice - 1].startTime) == 0 &&
                    strcmp(consultations[i].endTime, doctorAppointments[choice - 1].endTime) == 0) {
                    displayPatientInfo(&consultations[i], patients, patientCount);
                }
            }

            if (!allConsulted) {
                printf("Please consult all patients in the selected appointment time before making the report.\n");
                continue;
            }

            char observation[MAX_LINE_LENGTH], improvements[MAX_LINE_LENGTH], recommendations[MAX_LINE_LENGTH];
            getchar(); // Clear the input buffer
            printf("Enter observation: ");
            fgets(observation, sizeof(observation), stdin);
            trim_newline(observation);
            printf("Enter improvements: ");
            fgets(improvements, sizeof(improvements), stdin);
            trim_newline(improvements);
            printf("Enter recommendations: ");
            fgets(recommendations, sizeof(recommendations), stdin);
            trim_newline(recommendations);

            FILE *file = fopen("DoctorConsultation.txt", "a");
            if (file == NULL) {
                printf("Error opening file for writing!\n");
                return;
            }

            fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s\n",
                    doctorAppointments[choice - 1].username,
                    doctorAppointments[choice - 1].name,
                    doctorAppointments[choice - 1].specialism,
                    doctorAppointments[choice - 1].startTime,
                    doctorAppointments[choice - 1].endTime,
                    observation, improvements, recommendations);
            fclose(file);

            printf("\nDoctor report generated successfully! Press ENTER to return...");
            getchar();
            system("cls");
        } else {
            printf("\nInvalid choice! Please try again.Press ENTER to return...");
            getchar();
            system("cls");
        }
    }
}
//CHAPTER 4.3.1__________________________GENERATE DOCTOR REPORT (END)

//CHAPTER 4.3.2__________________________VIEW GENERATED DOCTOR REPORT (START)
int readDoctorReports(DoctorReport reports[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_ITEMS) {
        trim_newline(line);
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
               reports[count].username,
               reports[count].name,
               reports[count].specialism,
               reports[count].startTime,
               reports[count].endTime,
               reports[count].observation,
               reports[count].improvement,
               reports[count].recommendation);
        count++;
    }

    fclose(file);
    return count;
}

void showGeneratedReport(const DoctorReport *report) {
    printf("Doctor's Username: %s\n", report->username);
    printf("Doctor's Name: %s\n", report->name);
    printf("Doctor's Specialism: %s\n", report->specialism);
    printf("Appointment Time: %s - %s\n", report->startTime, report->endTime);
    printf("----------------------------------\n");
    printf("Observation:\n%s\n\n", report->observation);
    printf("Improvement:\n%s\n\n", report->improvement);
    printf("Recommendation:\n%s\n\n", report->recommendation);
}

void showDoctorReport(){
     DoctorReport reports[MAX_ITEMS];
     int reportCount = readDoctorReports(reports, "DoctorConsultation.txt");

     if (reportCount == -1) {
        printf(RED"Error reading generated reports.\n"RESET);
        return;
     }

     printf("\n[VIEW GENERATED DOCTOR REPORTS]\n\n");
     int i;
     for (i = 0; i < reportCount; i++) {
         printf("%d. %s | %s (%s) [%s - %s]\n",
                i + 1, reports[i].username, reports[i].name, reports[i].specialism,
                reports[i].startTime, reports[i].endTime);
     }
     printf("%d. Return to previous menu\n", reportCount + 1);

     int reportChoice;
     printf("\nEnter your choice: ");
     scanf("%d", &reportChoice);

     system("cls");
     printf("\n[VIEW GENERATED DOCTOR REPORT]\n\n");
     if (reportChoice == reportCount + 1) {
         system("cls");
         return;
     } else if (reportChoice > 0 && reportChoice <= reportCount) {
                showGeneratedReport(&reports[reportChoice - 1]);
                printf("Press ENTER to return...");
                getchar();
                getchar();
                system("cls");
     } else {
         printf(RED"Invalid choice! Press ENTER to retry..."RESET);
         getchar();
         getchar();
         system("cls");
     }
}

//CHAPTER 4.3.2__________________________VIEW GENERATED DOCTOR REPORT (END)

//CHAPTER 4.3.3__________________________DELETE GENERATED DOCTOR REPORT (START)
void deleteDoctorReport(const char *filename, int reportIndex) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(RED"Error opening file for reading!\n"RESET);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf(RED"Error opening temporary file for writing!\n"RESET);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int currentIndex = 0;
    while (fgets(line, sizeof(line), file)) {
        if (currentIndex != reportIndex) {
            fputs(line, tempFile);
        }
        currentIndex++;
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);

    printf(GREEN"Report deleted successfully! Press ENTER to return..."RESET);
    getchar();
    getchar();
    system("cls");
}

void dltDoctorReport(){
    DoctorReport reports[MAX_ITEMS];
    int reportCount = readDoctorReports(reports, "DoctorConsultation.txt");

    if (reportCount == -1) {
        printf(RED"Error reading generated reports.\n"RESET);
        return;
    }

    printf("\n[DELETE GENERATED DOCTOR REPORT]\n\n");
    int i;
    for (i = 0; i < reportCount; i++) {
         printf("%d. %s | %s (%s) [%s - %s]\n",
                i + 1, reports[i].username, reports[i].name, reports[i].specialism,
                reports[i].startTime, reports[i].endTime);
    }
    printf("%d. Return to previous menu\n", reportCount + 1);

    int reportChoice;
    printf("\nEnter your choice: ");
    scanf("%d", &reportChoice);

    if (reportChoice == reportCount + 1) {
        system("cls");
        return;
    } else if (reportChoice > 0 && reportChoice <= reportCount) {
        deleteDoctorReport("DoctorConsultation.txt", reportChoice - 1);
    } else {
        printf(RED"Invalid choice! Please try again.\n"RESET);
    }
}
//CHAPTER 4.3.3__________________________DELETE GENERATED DOCTOR REPORT (END)









void reportMenuNurse() {
    Patient patients[MAX_ITEMS];
    PatientConsultation consultations[MAX_ITEMS];
    DoctorAppointment doctorAppointments[MAX_ITEMS];
    int doctorCount = 0;
    int choice;
    int consultationCount = readPatientConsultations(consultations, "PatientConsultation.txt");
    int patientCount = readPatientsNurse(patients, "Patient.txt");

    int i;
    for (i = 0; i < consultationCount; i++) {
        int found = 0;
        int j;
        for (j = 0; j < doctorCount; j++) {
            if (strcmp(consultations[i].doctorUsername, doctorAppointments[j].username) == 0 &&
                strcmp(consultations[i].startTime, doctorAppointments[j].startTime) == 0 &&
                strcmp(consultations[i].endTime, doctorAppointments[j].endTime) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(doctorAppointments[doctorCount].username, consultations[i].doctorUsername);
            strcpy(doctorAppointments[doctorCount].name, consultations[i].doctorName);
            strcpy(doctorAppointments[doctorCount].specialism, consultations[i].doctorSpecialism);
            strcpy(doctorAppointments[doctorCount].startTime, consultations[i].startTime);
            strcpy(doctorAppointments[doctorCount].endTime, consultations[i].endTime);
            doctorCount++;
        }
    }

    if (consultationCount == -1 || patientCount == -1) {
        printf(RED"Error reading data files.\n"RESET);
        return;
    }

    while (1) {
        printf(" ----------------------------------------\n");
        printf("|             [REPORT MENU]              |\n");
        printf(" ----------------------------------------\n");
        printf("| 1. Generate New Doctor Report          |\n");
        printf("| 2. View Generated Doctor Report        |\n");
        printf("| 3. Delete Generated Doctor Report      |\n");
        printf("| 4. Return to Nurse Menu                |\n");
        printf(" ----------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                generateDoctorReport(consultations, consultationCount, patients, patientCount);
                break;
            case 2:
                system("cls");
                showDoctorReport();
                break;
            case 3:
                system("cls");
                dltDoctorReport();
                break;
            case 4:
                system("cls");
                return; // Return to the previous menu
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}
//CHAPTER 4.3__________________________REPORT MENU (END)

void nurseMenu(const char *nurseName) {
    int choice;

    while (1) {
        printf(" ---------------------------------------\n");
        printf("[NURSE MENU - Welcome Nurse %s]\n", nurseName);
        printf(" ---------------------------------------\n");
        printf("| 1. Doctor Scheduler                   |\n");
        printf("| 2. Inventory Menu                     |\n");
        printf("| 3. Report Menu                        |\n");
        printf("| 4. Logout                             |\n");
        printf(" ---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on nurse's choice
        switch (choice) {
            case 1:
                system("cls");
                doctorScheduler();
                break;
            case 2:
                system("cls");
                inventoryMenu();
                break;
            case 3:
                system("cls");
                reportMenuNurse();
                break;
            case 4:
                printf("Logging out... Press ENTER to continue...");
                getchar();
                getchar();
                system("cls");
                return; // Logout and return to the main menu
            default:
                printf(RED"Invalid choice! Press ENTER to retry..."RESET);
                getchar();
                getchar();
                system("cls");
        }
    }
}

//CHAPTER 4 (INITIALIZER)__________________________LOGIN AS NURSE (START)
void nurseLogin() {
    char username[100];
    char password[100];
    char line[256];
    int attempts = 0;
    int loginSuccess = 0;
    int screenWidth = 50;

    while (attempts < 3 && !loginSuccess) {
        printf("\n[NURSE LOGIN]\n(Type 'RETURN' to go back)\n\n");
        printf("Username: ");
        scanf("%s", username);

        if (strcmp(username, "RETURN") == 0) {
            system("cls");
            return;
        }

        printf("Password: ");

        // Get password input and mask with '*'
        int i = 0;
        char ch;
        while (1) {
            ch = _getch(); // Get character without echoing to the console
            if (ch == 13) { // Enter key is pressed
                password[i] = '\0';
                break;
            } else if (ch == 8) { // Backspace is pressed
                if (i > 0) {
                    i--;
                    printf("\b \b"); // Erase the last '*'
                }
            } else {
                password[i++] = ch;
                printf("*");
            }
        }
        printf("\n");

        FILE *file = fopen("Nurse.txt", "r");
        if (file == NULL) {
            printf(RED"Error opening file!\n"RESET);
            exit(1);
        }

        char storedUsername[100];
        char storedPassword[100];
        char storedName[100];

        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "Username:") != NULL) {
                strcpy(storedUsername, line + strlen("Username: "));
                storedUsername[strcspn(storedUsername, "\n")] = 0; // Remove newline

                fgets(line, sizeof(line), file);
                strcpy(storedPassword, line + strlen("Password: "));
                storedPassword[strcspn(storedPassword, "\n")] = 0; // Remove newline

                fgets(line, sizeof(line), file);
                strcpy(storedName, line + strlen("Name: "));
                storedName[strcspn(storedName, "\n")] = 0; // Remove newline

                // Skip the blank line
                fgets(line, sizeof(line), file);

                if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
                    loginSuccess = 1;
                    fclose(file);
                    printf(GREEN"\nLogin successful! Press ENTER to continue..."RESET);
                    getchar();
                    getchar();
                    system("cls");
                    nurseMenu(storedName); // Call nurse menu with the nurse's name
                    break;
                }
            }
        }

        if (!loginSuccess) {
            fclose(file);
            attempts++;
            if (attempts < 3) {
                printf(RED"\nInvalid username or password. Remaining attempt(s) [%d]."RESET, 3 - attempts);
                getchar();
                getchar();
                system("cls");
            } else {
                printf("REDToo many failed attempts. Press ENTER to shut down the system..."RESET);
                getchar();
                getchar();
                system("cls");
                exit(0);
            }
        }
    }
}
//CHAPTER 4 (INITIALIZER)__________________________LOGIN AS NURSE (END)
//CHAPTER 4__________________________NURSE MENU (END)


//FINAL CHAPTER__________________________MAIN PROGRAM (START)
int main() {
    int choice;

    while(1) {
        // Display the menu
        printf(" ----------------------------------------\n");
        printf("|   [Hospital Management System Menu]    |\n");
        printf(" ----------------------------------------\n");
        printf("| 1. Login as Admin                      |\n");
        printf("| 2. Login as Patient                    |\n");
        printf("| 3. Login as Doctor                     |\n");
        printf("| 4. Login as Nurse                      |\n");
        printf("| 5. Terminate Program                   |\n");
        printf(" ----------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on user's choice
        switch(choice) {
            case 1:
                system("cls");
                adminLogin();
                break;
            case 2:
                system("cls");
                patientLogin();
                break;
            case 3:
                system("cls");
                doctorLogin();
                break;
            case 4:
                system("cls");
                nurseLogin();
                break;
            case 5:
                printf(RED"Terminating program...\n" RESET);
                exit(0);
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
        }
    }

    return 0;
}
//FINAL CHAPTER__________________________MAIN PROGRAM (END)
