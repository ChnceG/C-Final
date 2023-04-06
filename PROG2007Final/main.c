#include <stdio.h>
#include <stdbool.h>
#include "functions.h"
// Global variables
int panelResponse;
bool isRunning = true;

// Voter Panel Function
void voterLoginPanel(bool voterRunning) {
    printf("Voter Login Panel\n=================\n");
    if (voterLogin() == true) {
        while (voterRunning) {
            printf("\nVoter Panel (1-2)\n==============\n");
            printf("1. Vote\n");
            printf("2. Change Password\n");
            printf("3. Logout\n");
            scanf("%d", &panelResponse);
            switch (panelResponse) {
                case 1:
                    vote();
                    break;
                case 2:
                    voterChangePassword();
                    break;
                case 3:
                    printf("Logging out...\n");
                    voterRunning = false;
                    break;
                default:
                    printf("Invalid input. Please try again.\n");
                    break;
            }
        }
    }
}
// Admin Panel Function
void adminLoginPanel(bool adminRunning) {
    printf("Administrator Login Panel\n=========================\n");
    if (adminLogin() == true) {
        while(adminRunning) {
            printf("\nAdministrator Panel ()\n===================\n");
            printf("1. Admin Panel\n");
            printf("2. Logout\n");
            scanf("%d", &panelResponse);
            switch (panelResponse) {
                case 1:
                    isRunning = adminPanel();
                    if(isRunning == false) {
                        adminRunning = false;
                    }
                    break;
                case 2:
                    printf("Logging out...\n");
                    adminRunning = false;
                    break;
                default:
                    printf("Invalid input. Please try again.\n");
                    break;
            }
        }
    }
}
// Polling Officer Panel Function
void pollingLoginPanel(bool pollingRunning) {
    printf("Polling Officer\n");
    if (pollingLogin() == true) {
        while(pollingRunning) {
            printf("\nPolling Officer Panel\n=====================\n");
            printf("1. Admin Panel\n");
            printf("2. Poll Panel\n");
            printf("3. Logout\n");
            scanf("%d", &panelResponse);
            switch (panelResponse) {
                case 1:
                    isRunning = adminPanel();
                    if(isRunning == false) {
                        pollingRunning = false;
                    }
                    break;
                case 2:
                    isRunning = pollingPanel();
                    if(isRunning == false) {
                        pollingRunning = false;
                    }
                    break;
                case 3:
                    printf("Logging out...\n");
                    pollingRunning = false;
                    break;
                default:
                    printf("Invalid input. Please try again.\n");
                    break;
            }
        }
    }
}

// Main Function
int main() {
    printf("Welcome to the Polling Station!\n");
    bool adminRunning = true, voterRunning = true, pollingRunning = true;
    int response;
    // Main Menu Loop
    while(isRunning) {
        printf("Please confirm your role. (1-3)\n================================\n");
        printf("1. Voter\n");
        printf("2. Administrator\n");
        printf("3. Polling Officer\n");
        scanf("%d", &response);
        switch(response) {
            case 1:
                // Voter Panel Function
                voterLoginPanel(voterRunning);
                break;
            case 2:
                // Admin Panel Function
                adminLoginPanel(adminRunning);
                break;
            case 3:
                // Polling Officer Panel Function
                pollingLoginPanel(pollingRunning);
                break;
            default:
                printf("Invalid input. Please try again.\n");
                break;
        }
    }

    return 0;
}

