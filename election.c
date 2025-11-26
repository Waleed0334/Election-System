#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// ADMIN PASSWORD
#define ADMIN_PASS "admin123"
// FUNCTIONS USED IN CODE
int addcandidate(char candidateNames[20][30], int candidateCount);
void viewCandidates(char candidateNames[20][30], int candidateCount);
void showResults(char candidateNames[20][30], int votes[20], int candidateCount);
void deleteCandidate(char candidateNames[20][30], int *candidateCount, int votes[20]);
int isValidName(char *name);
void showVotes(char voterNames[100][20], int voteChoice[100], char candidateNames[20][30], int total_user);
// FILE FUNCTIONS 
void saveCandidateToFile(char *candidate);
void rewriteCandidatesFile(char candidateNames[20][30], int candidateCount);
int loadCandidatesFromFile(char candidateNames[20][30]);

int main() {
    char candidateNames[20][30]; //To Store Candidate Names
    char voterNames[100][20]; // To Store Voters Name
    long long id[100];//To Store Voters ID
    int voteChoice[100];//To Store Voters Choice Of Which Candidates they Voted
    long long userID = 0;//For Temporary storing Current User ID
    int choice = 0;// For Temporary Storing Current User Choice
    int candidateCount = 0;//Number Of Candidates
    int total_user = 0;//Number Of Users
    int votes[20] = {0};// For Storing total Votes of Each Candidates

    // Load candidates from file
    candidateCount = loadCandidatesFromFile(candidateNames);

    while (1) {
        system("cls");// Clear Screen
        // Print Menu
        printf("\n-------------------------------------------------------------\n");
        printf("============= Welcome To the Voting Platform =============\n");
        printf("-------------------------------------------------------------\n");
        printf("1. Add Candidates (ADMIN ONLY)\n");
        printf("2. Delete a Candidate (ADMIN ONLY)\n");
        printf("3. Vote for a Candidate\n");
        printf("4. View Candidates\n");
        printf("5. Show Results\n");
        printf("6. Show Who Voted For Whom\n");
        printf("7. Exit\n");
        printf("-------------------------------------------------------------\n");
        // Ask for Input
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

        case 1:
            // Call Add Candidate Function
            candidateCount = addcandidate(candidateNames, candidateCount);
            break;

        case 2:
            // Call Delete Candidate Function
            deleteCandidate(candidateNames, &candidateCount, votes);
            break;

        case 3:
            // If There are no Candidates stored
            if (candidateCount == 0) {
                printf("No candidates available! Please add candidates first.\n");
                getchar();
                break;
            }
           
            system("cls");
            printf("Enter your name: ");
            fgets(voterNames[total_user], sizeof(voterNames[total_user]), stdin);//input name
            voterNames[total_user][strcspn(voterNames[total_user], "\n")] = '\0';//remove newline
            // Check Voters Name
            if (!isValidName(voterNames[total_user])) {
                printf("Invalid name! Only alphabets and spaces allowed.\n");
                getchar();
                break;
            }
           //ID
            printf("Enter your 13-digit ID: ");
            scanf("%lld", &userID);
            // Check ID
            if (userID > 9999999999999LL || userID < 1000000000000LL) {
                printf("Invalid ID.\n");
                getchar();
                break;
            }

            // Check duplicate ID 
            int duplicate = 0;
            for (int j = 0; j < total_user; j++) {
                //check id array for duplicates
                if (id[j] == userID) {
                    printf("This ID has already voted!\n");
                    duplicate = 1;
                    break;
                }
            }
            //If There are duplicate Break while loop
            if (duplicate) {
                getchar();
                break;
            }
            // Save Current User ID to the Array
            id[total_user] = userID;
            //Print List Of candidates
            printf("\nThese are the list of candidates:\n");
            //Calling  ViewCandidates for printing the list
            viewCandidates(candidateNames, candidateCount);
            //Get Vote from The User
            int vote;
            printf("Enter the candidate number you want to vote for (1 - %d): ", candidateCount);
            scanf("%d", &vote);
            getchar();
            // Check(validate) vote 
            if (vote < 1 || vote > candidateCount) {
                printf("Invalid choice! Vote not recorded.\n");
            } else {
                votes[vote - 1]++;//Increment selected candidate votes
                voteChoice[total_user] = vote - 1;//store users choice in the array
                total_user++;//increment total users
                printf("Vote recorded successfully for %s!\n", candidateNames[vote - 1]);
            }
            getchar();
            break;

        case 4:
            //Clear screen and Call View Candidates Function
            system("cls");
            viewCandidates(candidateNames, candidateCount);
            getchar();
            break;

        case 5:
            //Clear screen and Call Show Results Function
            system("cls");
            showResults(candidateNames, votes, candidateCount);
            getchar();
            break;

        case 6:
            //Clear screen and Call ShowVotes Function
            system("cls");
            showVotes(voterNames, voteChoice, candidateNames, total_user);
            getchar();
            break;

        case 7:
            // Exiting Statement
            system("cls");
            printf("Exiting the program...\n");
            printf("\n\n\n\n\n");
            printf("=====================================================================================================================\n");
            printf("----------------------------------------");
            printf(" THANKYOU FOR VISITING ");
            printf("----------------------------------------");
            printf("\n=====================================================================================================================");

            return 0;

        default:
            printf("Invalid Input\n");
            getchar();
            break;
        }
    }

    return 0;
}
// Validate Names
int isValidName(char *name) {
    int len = strlen(name);
    // No empty name
    if (len == 0){
        printf("NO STRING ENTERED\n");
        return 0;
    } 
    // No leading or trailing spaces
    if (name[0] == ' ' || name[len - 1] == ' '){
        printf("No Leading or trailing Spaces required\n");
        return 0;
    }
    // Only alphabets and single spaces allowed
    for (int i = 0; name[i] != '\0'; i++) {
        if (!(isalpha(name[i]) || name[i] == ' '))
            return 0;
        // Block multiple spaces in a row
        if (name[i] == ' ' && name[i + 1] == ' ')
            return 0;
    }
    return 1;
}
// ============================================================
//              ADD CANDIDATE FUNCTION
// ============================================================

int addcandidate(char candidateNames[20][30], int candidateCount) {
    system("cls");
    char inputPassword[20];
// Password Check For The Admin
    printf("Enter admin password: ");
    scanf("%s", inputPassword);
    getchar();
    if (strcmp(inputPassword, ADMIN_PASS) != 0) {
        printf("Wrong password! Access denied.\n");
        getchar();
        return candidateCount;
    }
    // IF CORECT SHOW MENU
    int choice;
    printf("Welcome to Adding Candidate System\n");
    printf("------------------------------------------------------------\n");
    printf("PRESS 1 : Add New Candidate\n");
    printf("Press any other number to exit program: ");
    scanf("%d", &choice);
    getchar();

    while (choice == 1) {
        system("cls");
        // Stopping Overusage Of Memory
        if (candidateCount == 20) {
            printf("Candidate Limit Reached\n");
            break;
        }
        //Input Candidate Name
        char tempName[30];
        printf("Enter The Name of the Candidate: ");
        fgets(tempName, sizeof(tempName), stdin);
        tempName[strcspn(tempName, "\n")] = '\0';
        // Checks Name
        if (!isValidName(tempName)) {
            printf("Invalid name! Only alphabets and single spaces allowed.\n");
            continue;
        }

        strcpy(candidateNames[candidateCount], tempName);
        printf("Candidate Added: %s\n", candidateNames[candidateCount]);
        // Save To File Candidate.txt
        saveCandidateToFile(tempName);
        candidateCount++;
        // Ask User For Another Addition
        printf("\nPRESS 1 to add another candidate\nPress any other number to EXIT: ");
        scanf("%d", &choice);
        getchar();
    }
    // Clear Screen AND Exit Message
    system("cls");
    printf("Thank You for using the system\n");
    getchar();
    return candidateCount;
}

// ============================================================
//                 VIEW CANDIDATES FUNCTION
// ============================================================

void viewCandidates(char candidateNames[20][30], int candidateCount) {
    // If There Are NO CANDIDATES SAVED
    if (candidateCount == 0) {
        printf("No candidates available.\n");
        return;
    }
    //Prints The List Of Candidates
    printf("\n----- List of Candidates -----\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s\n", i + 1, candidateNames[i]);
    }
    printf("------------------------------\n");
}

// ============================================================
//                     SHOW RESULTS FUNCTION
// ============================================================

void showResults(char candidateNames[20][30], int votes[20], int candidateCount) {
    // If There are no Candidates
    if (candidateCount == 0) {
        printf("No candidates available to show results.\n");
        return;
    }

    printf("\n---------- Voting Results ----------\n");
    // Find for Maximum Vote Index
    int maxVotes = 0;
    for (int i = 0; i < candidateCount; i++) {
        // Print All Candidates with there Name
        printf("%d. %s  %d votes\n", i + 1, candidateNames[i], votes[i]);
        if (votes[i] > maxVotes)
            maxVotes = votes[i];
    }
    // Check for Tie btw Candidates
    int tieCount = 0;
    for (int i = 0; i < candidateCount; i++) {
        if (votes[i] == maxVotes)
            tieCount++;
    }
    printf("\n------------------------------------\n");

    // No Votes Casted Yett
    if (maxVotes == 0) {
        printf("No votes cast yet.\n");
        return;
    }

    if (tieCount == 1) {
        // Normal winner
        for (int i = 0; i < candidateCount; i++) {
            if (votes[i] == maxVotes) {
                printf("Winner: %s with %d votes!\n", candidateNames[i], maxVotes);
                break;
            }
        }
    } else {
        // TIE
        printf("There is a TIE between the following candidates (each has %d votes):\n", maxVotes);
        for (int i = 0; i < candidateCount; i++) {
            // Print All Candidates With A tie
            if (votes[i] == maxVotes) {
                printf("- %s\n", candidateNames[i]);
            }
        }
    }
}

// ============================================================
//                  DELETE CANDIDATE FUNCTION
// ============================================================

void deleteCandidate(char candidateNames[20][30], int *candidateCount, int votes[20]) {
    char inputPassword[20];
    // Clear Screen And Ask for ADMIN Password
    system("cls");
    printf("Enter admin password: ");
    scanf("%s", inputPassword);
    getchar();
    // Check Password
    if (strcmp(inputPassword, ADMIN_PASS) != 0) {
        printf("Wrong password! Access denied.\n");
        getchar();
        return;
    }
    // If There Are No Candidates Saved
    if (*candidateCount == 0) {
        printf("No candidates available to delete.\n");
        getchar();
        return;
    }
    
    printf("\n----- Delete Candidate -----\n");
    // Print Candidate List
    for (int i = 0; i < *candidateCount; i++)
        printf("%d. %s\n", i + 1, candidateNames[i]);
    // Ask User For Index Of Which Candidate To Delete
    int del;
    printf("Enter the candidate number to delete: ");
    scanf("%d", &del);
    getchar();
    // Validate Entered Index
    if (del < 1 || del > *candidateCount) {
        printf("Invalid candidate number.\n");
        getchar();
        return;
    }
    // Decrement to match the array index
    del--;

    printf("Candidate '%s' deleted successfully.\n", candidateNames[del]);
    // Overwrite and shift below elements above by one cell
    for (int i = del; i < *candidateCount - 1; i++) {
        strcpy(candidateNames[i], candidateNames[i + 1]);
        // Update Votes array
        votes[i] = votes[i + 1];
    }
    // Decrement For Deleting a Candidate
    (*candidateCount)--;
    // Update the file
    rewriteCandidatesFile(candidateNames, *candidateCount);
    printf("File updated successfully.\n");
}


// ============================================================
//               SHOW WHO VOTED FOR WHOM
// ============================================================

void showVotes(char voterNames[100][20], int voteChoice[100], char candidateNames[20][30], int total_user) {
    // If Noone Voted
    if (total_user == 0) {
        printf("No votes cast yet.\n");
        return;
    }
    // Print All Data
    printf("\n----- Who Voted For Whom -----\n");
    for (int i = 0; i < total_user; i++) {
        printf("%d. %s voted for  %s\n",i+1, voterNames[i], candidateNames[voteChoice[i]]);
    }
    printf("-------------------------------\n");
}

// ============================================================
//                  CANDIDATE FILE FUNCTIONS
// ============================================================

void saveCandidateToFile(char *candidate) {
    // Open candidate.txt in Append Mode
    FILE *fp = fopen("candidates.txt", "a");
    // If No File found
    if (fp == NULL){
        printf("No File Found\n");
        return;
    } 
    // Save The name in the file
    fprintf(fp, "%s\n", candidate);
    // Close File
    fclose(fp);
}

void rewriteCandidatesFile(char candidateNames[20][30], int candidateCount) {
    // Open File in Write Mode
    FILE *fp = fopen("candidates.txt", "w");
    // If no File Found
    if (fp == NULL) {
        printf("No File Found\n");
        return;
    }
    // Update The File
    for (int i = 0; i < candidateCount; i++) {
        fprintf(fp, "%s\n", candidateNames[i]);
    }
    // Close File
    fclose(fp);
}

int loadCandidatesFromFile(char candidateNames[20][30]) {
    // Open File in Read Mode
    FILE *fp = fopen("candidates.txt", "r");
    // If no File Found
    if (fp == NULL) {
        printf("No File Found\n");
        return 0;
    }

    int count = 0;
    // If The line is Not blank remain in loop
    while (fgets(candidateNames[count], 30, fp) != NULL) {
        // Remove newline And add Null terminator
        candidateNames[count][strcspn(candidateNames[count], "\n")] = '\0';

        if (strlen(candidateNames[count]) == 0)
            continue;

        count++;//Next Candidate
        // Array Limit Reached
        if (count >= 20){
            break;
        } 
    }
    // Close File
    fclose(fp);
    // Return Number Of Candidates
    return count;
}