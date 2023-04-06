//
// Created by cbgra on 2023-03-28.
//
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

//Setting username, password, and name for voters, polling officers, and administrators
struct Voter voters[] = {
        {"Andrew", "ajones1", "111", false},
        {"Steve", "sjobs1", "222", false},
        {"Bill", "blawrence1", "333", false},
};
struct PollingOfficer pollingOfficers[] = {
        {"Gary", "gsmith1", "1"},
};
struct Administrator administrators[] = {
        {"Paul", "pwhite1", "1"},
};
struct candidate candidates[] = {
        {"Bob", "Republican", 0},
        {"Andrew", "Democrat", 0},
        {"Steve", "Green", 0},
};

//Class variables
int voterCount = sizeof(voters) / sizeof(struct Voter);
int indexVoter;
int pollingOfficerCount = sizeof(pollingOfficers) / sizeof(struct PollingOfficer);
int administratorCount = sizeof(administrators) / sizeof(struct Administrator);
int candidateCount = sizeof(candidates) / sizeof(struct candidate);

// Function to get username and password
void getLogin(char *username, char *password) {
    printf("Please log in to confirm your identity.\n");
    printf("Username:");
    scanf("%s", username);
    printf("Password:");
    scanf("%s", password);
}
// Function to check if voter login is correct
bool voterLogin() {
    char username[20];
    char password[20];
    getLogin(username, password);
    for(int i = 0; i < voterCount; i++) {
        if(strcmp(username, voters[i].username) == 0 && strcmp(password, voters[i].password) == 0) {
            printf("Welcome, %s!\n", voters[i].name);
            indexVoter = i;
            return true;
        }
    }
    printf("Incorrect username or password. Please try again.\n");
    return false;
}
// Function to check if admin login is correct
bool adminLogin() {
    char username[20];
    char password[20];
    getLogin(username, password);
    for(int i = 0; i < administratorCount; i++) {
        if(strcmp(username, administrators[i].username) == 0 && strcmp(password, administrators[i].password) == 0) {
            printf("Welcome, %s!\n", administrators[i].name);
            return true;
        }
    }
    printf("Incorrect username or password. Please try again.\n");
    return false;
}
// Function to check if polling officer login is correct
bool pollingLogin() {
    char username[20];
    char password[20];
    getLogin(username, password);
    for(int i = 0; i < pollingOfficerCount; i++) {
        if(strcmp(username, pollingOfficers[i].username) == 0 && strcmp(password, pollingOfficers[i].password) == 0) {
            printf("Welcome, %s!\n", pollingOfficers[i].name);
            return true;
        }
    }
    printf("Incorrect username or password. Please try again.\n");
    return false;
}
// Function to check if voter has already voted
bool checkVote() {
    return voters[indexVoter].hasVoted;
}
// Function to vote and set hasVoted to true
void vote() {
    if(!checkVote()) {
        int voteResponse;
        printf("Voting Panel\n=================\n");
        // Loops through candidates and prints them
        for (int i = 0; i < candidateCount; i++) {
            printf("%d. %s, %s\n", i + 1, candidates[i].name, candidates[i].party);
        }
        printf("Please select a candidate to vote for. (1-%d)\n", candidateCount);
        scanf("%d", &voteResponse);
        // Adds vote to candidate if valid input, sets hasVoted to true
        if (voteResponse > 0 && voteResponse <= candidateCount) {
            candidates[voteResponse - 1].votes++;
            voters[indexVoter].hasVoted = true;
        } else {
            printf("Invalid input. Please try again.\n");
        }
        printf("You have voted for %s, %s.\n", candidates[voteResponse - 1].name, candidates[voteResponse - 1].party);
        printf("Thank you for voting!\n\n");
    }
    else {
        printf("You've already voted!\n");
    }
}
// Function to print results of the election, if there are enough candidates
bool printResults() {
    if(candidateCount <= 1) {
        printf("Not enough candidates have been added yet!\n");
        return false;
    }
    else {
        printf("The results are...\n=================\n");
        for(int i = 0; i < candidateCount; i++) {
            printf("%s, %s: %d votes\n", candidates[i].name, candidates[i].party, candidates[i].votes);
        }
        return true;
    }
}
// Function to add candidates
void addCandidate() {
    printf("Add Candidate\n========================\n");
    printf("Please enter the candidate's name: ");
    char name[20];
    scanf("%s", name);
    printf("Please enter the candidate's party: ");
    char party[20];
    scanf("%s", party);
    strcpy(candidates[candidateCount].name, name);
    strcpy(candidates[candidateCount].party, party);
    candidates[candidateCount].votes = 0;
    candidateCount++;
    printf("Candidate added successfully!\n");
}
// Function to add voters
void addVoter() {
    printf("Add Voter\n========================\n");
    printf("Please enter the voter's name: ");
    char name[20];
    scanf("%s", name);
    printf("Please enter the voter's username: ");
    char username[20];
    scanf("%s", username);
    printf("Please enter the voter's password: ");
    char password[20];
    scanf("%s", password);
    strcpy(voters[voterCount].name, name);
    strcpy(voters[voterCount].username, username);
    strcpy(voters[voterCount].password, password);
    voters[voterCount].hasVoted = false;
    voterCount++;
    printf("Voter added successfully!\n");
}
// Function to check if there are votes for any candidates to prevent clearing
void indexCandidateVotes() {
    for(int i = 0; i < candidateCount; i++) {
        if(candidates[i].votes > 0) {
            printf("There are votes for some candidates. Please publish the results or restart the program before clearing.\n");
            return;
        }
    }
}
//Function to clear all current candidates, if there are no votes
void clearCandidates() {
    if(candidateCount == 0) {
        printf("There are no candidates to clear!\n");
        return;
    }
    // if there are votes for any candidates, don't clear
    indexCandidateVotes();
    for(int i = 0; i < candidateCount; i++) {
        strcpy(candidates[i].name, "");
        strcpy(candidates[i].party, "");
        candidates[i].votes = 0;
    }
    candidateCount = 0;
    printf("All candidates have been cleared!\nPlease add new candidates.\n");
}
// Function to open the Polling Officer's Panel
bool pollingPanel() {
    int pollingResponse;
    char publishResponse;
    printf("Polling Panel\n");
    printf("========================\n");
    printf("1. View results\n");
    printf("2. Add Users\n");
    printf("3. Add Candidates\n");
    printf("4. Clear all current Candidates\n");
    printf("5. Exit\n");
    printf("Please select an option. (1-2)\n");
    scanf("%d", &pollingResponse);
    if(pollingResponse == 1) {
        if(printResults()) {
            printf("Would you like to publish the results? (y/n)\n");
            scanf(" %c", &publishResponse);
            // If publishResponse is y, publish the results and end the program
            if (publishResponse == 'y') {
                printf("The results have been published!\n");
                printResults();
                return false;
            }
                // If publishResponse is n, return to the Polling Officer Panel
            else if (publishResponse == 'n') {
                printf("Results have not been published.\n");
                return true;
            }
                // If publishResponse is anything else, return to the Polling Officer Panel
            else {
                printf("Invalid input. Please try again.\n");
                return true;

            }
        }
        else {
            return true;
        }
    }
    else if(pollingResponse == 2) {
        addVoter();
        return true;
    }
    else if(pollingResponse == 3) {
        addCandidate();
        return true;
    }
    else if(pollingResponse == 4) {
        clearCandidates();
        return true;
    }
    else if(pollingResponse == 5) {
        printf("Exiting...\n");
        return true;
    }
    else {
        printf("Invalid input. Please try again.\n");
        return true;
    }
}
// Function for voter to change their own password
void voterChangePassword() {
    printf("Change your password\n========================\n");
    //ask for current password before allowing change
    printf("Please enter your current password: ");
    char currentPassword[20];
    scanf("%s", currentPassword);
    //if current password is incorrect, return to landing page
    if(strcmp(currentPassword, voters[indexVoter].password) != 0) {
        printf("Incorrect password, returning to the landing page.\n");
        return;
    }
    printf("Please enter the new password: ");
    char password[20];
    scanf("%s", password);
    strcpy(voters[indexVoter].password, password);
    printf("Password changed successfully!\n");
}
// Function for Admins to change voter password
void adminChangePassword() {
    printf("Change user password\n========================\n");
    printf("Please enter the username of the user:");
    char username[20];
    scanf("%s", username);
    printf("Please enter the new password: ");
    char password[20];
    scanf("%s", password);
    for(int i = 0; i < voterCount; i++) {
        if(strcmp(username, voters[i].username) == 0) {
            strcpy(voters[i].password, password);
            printf("Password changed successfully!\n");
        }
        else if (strcmp(username, voters[i].username) != 0) {
            printf("User not found, try again\n");
        }
    }
}
// Function to open the Admin Panel
bool adminPanel() {
    int adminResponse;
    printf("Admin Panel (1-2)\n");
    printf("========================\n");
    printf("1. Cancel Poll\n");
    printf("2. Change User password\n");
    printf("3. Exit\n");
    printf("Please select an option. (1-2)\n");
    scanf("%d", &adminResponse);
    if(adminResponse == 1) {
        printf("The poll has been cancelled.\n");
        return false;
    }
    else if (adminResponse == 2) {
        adminChangePassword();
        return true;
    }
    else if(adminResponse == 3) {
        printf("Exiting...\n");
        return true;
    }
    else {
        printf("Invalid input. Please try again.\n");
        return true;
    }
}