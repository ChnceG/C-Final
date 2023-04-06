//
// Created by cbgra on 2023-03-28.
//

#ifndef PROG2007FINAL_FUNCTIONS_H
#define PROG2007FINAL_FUNCTIONS_H

#include <stdbool.h>

// Global structs
struct Voter {
    char name[20];
    char username[20];
    char password[20];
    bool hasVoted;
};
struct PollingOfficer {
    char name[20];
    char username[20];
    char password[20];
};
struct Administrator {
    char name[20];
    char username[20];
    char password[20];
};
struct candidate {
    char name[20];
    char party[20];
    int votes;
};

// Function calls
bool voterLogin();
bool adminLogin();
bool pollingLogin();
void vote();
bool pollingPanel();
bool adminPanel();
void voterChangePassword();

#endif //PROG2007FINAL_FUNCTIONS_H
