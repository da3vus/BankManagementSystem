//Author: Davis Nguyen
//Project: Bank Management System

//Project Description:
//Multiple users with ID and password. Only those with correct ID and password can login.
//The person should be able to withdraw/deposit cash and view/edit profile.
//ID and passwords are saved by reading/writing in files.


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void menu(char *ID, char *pass);
void load(int j);
int check_login(char *ID, char *pass);
int check_ID(char *ID);
void sign_up(char *ID, char *pass);
void deposit(char *ID, char *pass);
void withdraw(char *ID, char *pass);
void view_profile(char *ID, char *pass);
void delete_account(char *ID, char *pass);


struct profile{
    char ID[100];
    char password[100];
    double balance;
} user;


int main()
{
    char username[500];
    char password[500];
    int select;
    char status_login[100];
    char status_signup[100];
    int check_id;
    int check_user;

    system("cls");
    system("color 5");


    printf("\n\n\t\t\t*******************************************\n");
    printf("\t\t\t** WELCOME TO THE BANK MANAGEMENT SYSTEM **\n");
    printf("\t\t\t*******************************************\n");
    printf("\t\t\t            MADE BY DAVIS NGUYEN\n");
    printf("\t\t\t*******************************************\n");
    printf("\t\t\t\t1: LOGIN\n");
    printf("\t\t\t\t2: SIGN UP\n");
    printf("\t\t\t     PRESS ANY OTHER KEY TO END PROGRAM\n");
    printf("\n\t\t\t*******************************************\n\n\n");

    printf("\nEnter your option: ");
    scanf("%d", &select);


    if(select == 2)
    {
        while (strcmp("0", status_signup) != 0)
        {
            printf("\nPlease enter ID: ");
            scanf("%s", username);

            check_id = check_ID(username);

            if (check_id == 0)
            {
                printf("Please enter password: ");
                scanf("%s", password);
                sign_up(username, password);
                system("cls");
                system("color 2");
                printf("\n\nLOADING ");
                for(int i=0;i <= 10;i++)
                {
                    load(100000000);
                    printf(".");
                }
                system("cls");
                printf("\n\t\t\t\t      Welcome %s!", username);
                menu(username, password);
                break;
            }
            else
            {
                invalid_choice:
                printf("\nThe ID has been taken. Enter 1 to try again or 0 to end the program: ");
                scanf("%s", &status_signup);

                if (strcmp("0", status_signup) == 0)
                {
                    end_screen();
                    break;
                }
                else if (strcmp("1", status_signup) == 0)
                {
                    system("cls");
                    continue;
                }
                else
                {
                    system("cls");
                    printf("\nInvalid Input.");
                    goto invalid_choice;
                }
            }
        }
    }

    if(select == 1)
    {
        while (strcmp("0", status_login) != 0)
        {
            printf("\nPlease enter ID: ");
            scanf("%s", username);
            printf("Please enter password: ");
            scanf("%s", password);

            check_user = check_login(username, password);

            if (check_user == 1)
            {
                system("cls");
                system("color 2");
                printf("\n\nLOADING ");
                for(int i=0;i <= 10;i++)
                {
                    load(100000000);
                    printf(".");
                }
                system("cls");
                printf("\n\t\t\t\t    Welcome Back %s!", username);
                menu(username, password);
                break;
            }
            else
            {
                wrong_choice:
                printf("\nIncorrect ID or password. Enter 1 to try again or 0 to end the program: ");
                scanf("%s", &status_login);
                if (strcmp("0", status_login) == 0)
                {
                    end_screen();
                    break;
                }
                else if (strcmp("1", status_login) == 0)
                {
                    system("cls");
                    continue;
                }
                else
                {
                    system("cls");
                    printf("\nInvalid Input.");
                    goto wrong_choice;
                }
            }
        }
    }
}

//Function that checks if user input ID and password is correct to login.
int check_login(char *ID, char *pass)
{
    FILE *userFile;
    userFile = fopen("userInfo.txt", "r");
    char line[500];
    int count = 0;
    int check = 0;


    if (userFile == NULL){
        puts("A file can not be opened.");
    }
    while (fgets(line, 500, userFile) != NULL){
        count = 0;
        char *token = strtok(line, " ");
        while (token != NULL){
           if (count == 0){
                strcpy(user.ID, token);
           }
           else if (count == 1){
                strcpy(user.password, token);
           }
           token = strtok(NULL, " ");
           count++;
        }
        if ((strcmp(user.ID, ID) == 0) && (strcmp(user.password, pass) == 0)){
            check++;
        }

    }
    fclose(userFile);
    if (check != 0){
        return 1;
    }
    return 0;
}

//Function that checks if input ID is found in files.
int check_ID(char *ID)
{
    FILE *userFile;
    userFile = fopen("userInfo.txt", "r");
    char line[500];
    int count = 0;
    int check = 0;

    if (userFile == NULL){
        puts("A file can not be opened.");
    }
    while (fgets(line, 500, userFile) != NULL){
        count = 0;
        char *token = strtok(line, " ");
        while (token != NULL){
            if (count == 0){
                strcpy(user.ID, token);
            }
            token = strtok(NULL, " ");
            count++;
        }
        if (strcmp(user.ID, ID) == 0){
            check++;
        }
    }
    fclose(userFile);
    if (check != 0){
        return 1;
    }
    return 0;
}

//Function that writes into file a new account that has signed up.
void sign_up(char *ID, char *pass)
{
    FILE *userFile;
    userFile = fopen("userInfo.txt", "a+");
    fprintf(userFile,"%s %s 0.00\n", ID, pass);
    fclose(userFile);
}

//Function to deposit money from account.
void deposit(char *ID, char *pass)
{
    FILE *oldFile;
    FILE *newFile;
    oldFile = fopen("userInfo.txt", "r");
    newFile = fopen("updatedInfo.txt", "w");
    char line[500];
    int count = 0;
    int select;
    double deposit_amount;

    if ((oldFile == NULL) || (newFile == NULL)){
        puts("A file can not be opened.");
    }

    while (fgets(line, 500, oldFile) != NULL){
        count = 0;
        char *token = strtok(line, " ");
        while (token != NULL){
           if (count == 0){
                strcpy(user.ID, token);
           }
           else if (count == 1){
                strcpy(user.password, token);
           }
           else if (count == 2){
                user.balance = strtod(token, &*token);
           }
           token = strtok(NULL, " ");
           count++;
        }
        if ((strcmp(user.ID, ID) == 0) && (strcmp(user.password, pass) == 0)){
            printf("Your current balance is %.2lf\n", user.balance);
            printf("\nEnter the amount you want to deposit: ");
            scanf("%lf",&deposit_amount);
            user.balance += deposit_amount;
            fprintf(newFile,"%s %s %.2lf\n", user.ID, user.password, user.balance);
            printf("The deposit was completed! Your new balance is %.2lf", user.balance);
        }
        else{
            fprintf(newFile,"%s %s %.2lf\n", user.ID, user.password, user.balance);
        }

   }

   fclose(oldFile);
   fclose(newFile);
   remove("userInfo.txt");
   rename("updatedInfo.txt", "userInfo.txt");

   printf("\n\n\nEnter 1 to return to main menu and any other key to end the program: ");
   scanf("%d", &select);

   if (select == 1){
        system("cls");
        menu(ID, pass);
   }
   else{
        system("cls");
        puts("\nThank you for using the program. Goodbye!");
   }
}


//Function to withdraw money from account.
void withdraw(char *ID, char *pass)
{
    FILE *oldFile;
    FILE *newFile;
    oldFile = fopen("userInfo.txt", "r");
    newFile = fopen("updatedInfo.txt", "w");
    char line[500];
    int count = 0;
    int select;
    double withdraw_amount;

    if ((oldFile == NULL) || (newFile == NULL)){
        puts("A file can not be opened.");
    }

    while (fgets(line, 500, oldFile) != NULL){
        count = 0;
        char *token = strtok(line, " ");
        while (token != NULL){
           if (count == 0){
                strcpy(user.ID, token);
           }
           else if (count == 1){
                strcpy(user.password, token);
           }
           else if (count == 2){
                user.balance = strtod(token, &*token);
           }
           token = strtok(NULL, " ");
           count++;
        }
        if ((strcmp(user.ID, ID) == 0) && (strcmp(user.password, pass) == 0)){
            printf("Your current balance is %.2lf\n", user.balance);
            printf("\nEnter the amount you want to withdraw: ");
            scanf("%lf", &withdraw_amount);
            user.balance -= withdraw_amount;
            fprintf(newFile, "%s %s %.2lf\n", user.ID, user.password, user.balance);
            printf("The withdraw was completed! Your new balance is %.2lf", user.balance);
        }
        else{
            fprintf(newFile, "%s %s %.2lf\n", user.ID, user.password, user.balance);
        }
   }

   fclose(oldFile);
   fclose(newFile);
   remove("userInfo.txt");
   rename("updatedInfo.txt", "userInfo.txt");

   printf("\n\n\nEnter 1 to return to main menu and any other key to end the program: ");
   scanf("%d", &select);

   if (select == 1){
        system("cls");
        menu(ID, pass);
   }
   else{
        system("cls");
        puts("\nThank you for using the program. Goodbye!");
   }
}

//Function that displays profile information of user logged in.
void view_profile(char *ID, char *pass)
{
    FILE *userFile;
    userFile = fopen("userInfo.txt","r");
    char line[500];
    int count = 0;
    int select;


    if (userFile == NULL){
        puts("A file can not be opened.");
    }

    printf("\n\nHere is all the info in your profile.\n");
    puts("-------------------------------------");
    while (fgets(line, 500, userFile) != NULL){
        count = 0;
        char *token = strtok(line, " ");
        while (token != NULL){
           if (count == 0){
                strcpy(user.ID, token);
           }
           else if (count == 1){
                strcpy(user.password, token);
           }
           else if (count == 2){
                user.balance = strtod(token, &*token);
           }
           token = strtok(NULL, " ");
           count++;
        }
        if ((strcmp(user.ID, ID) == 0) && (strcmp(user.password, pass) == 0)){
            printf("ID: %s\nPASSWORD: %s\nBALANCE: %.2lf\n", user.ID, user.password, user.balance);
            puts("-------------------------------------");
        }
   }

   fclose(userFile);

   printf("\nEnter 1 to return to main menu and any other key to end the program: ");
   scanf("%d", &select);

   if (select == 1){
        system("cls");
        menu(ID, pass);
   }
   else{
        end_screen();
   }

}

//Function that can edit account ID and password logged in.
void edit(char *ID, char *pass)
{
    FILE *oldFile;
    FILE *newFile;
    oldFile = fopen("userInfo.txt", "r");
    newFile = fopen("updatedInfo.txt", "w");
    char line[500];
    int count = 0;
    int select;
    int check_id;
    char status_id[100];
    char edit_choice[100];
    char new_ID[500];
    char new_pass[500];



    if ((oldFile == NULL) || (newFile == NULL)){
        puts("A file can not be opened.");
    }

    while (fgets(line, 500, oldFile) != NULL){
        count = 0;
        char *token = strtok(line, " ");
        while (token != NULL){
           if (count == 0){
                strcpy(user.ID, token);
           }
           else if (count == 1){
                strcpy(user.password, token);
           }
           else if (count == 2){
                user.balance = strtod(token, &*token);
           }
           token = strtok(NULL, " ");
           count++;
        }
        if ((strcmp(user.ID, ID) == 0) && (strcmp(user.password, pass) == 0)){
            printf("What would you like to change?\nEnter 1 to edit ID and enter 2 to edit password: ");
            scanf("%s", edit_choice);

            if (strcmp("1", edit_choice) == 0){
                reEnterID:
                printf("\nEnter your new ID: ");
                scanf("%s", new_ID);

                check_id = check_ID(new_ID);

                if (check_id == 0)
                {
                    fprintf(newFile, "%s %s %.2lf\n", new_ID, user.password, user.balance);
                    printf("\nYour ID has now been changed.");
                    strcpy(ID, new_ID);
                    //break;
                }
                else
                {
                    printf("\nThe ID has been taken. Enter 1 to try again or 2 to go back to the main menu: ");
                    scanf("%s", &status_id);

                    if (strcmp("1", status_id) == 0)
                    {
                        system("cls");
                        goto reEnterID;
                    }
                    else if (strcmp("2", status_id) == 0)
                    {
                        system("cls");
                        menu(ID, pass);
                        //break;
                    }
                }
            }
            if (strcmp("2", edit_choice) == 0){
                system("cls");
                printf("Enter your new password: ");
                scanf("%s", new_pass);

                fprintf(newFile, "%s %s %.2lf\n", user.ID, new_pass, user.balance);
                printf("\nYour password has now been changed.");
                strcpy(pass, new_pass);

            }
        }
        else{
            fprintf(newFile, "%s %s %.2lf\n", user.ID, user.password, user.balance);
        }
   }

   fclose(oldFile);
   fclose(newFile);
   remove("userInfo.txt");
   rename("updatedInfo.txt", "userInfo.txt");

   printf("\n\n\nEnter 1 to return to main menu and any other key to end the program: ");
   scanf("%d", &select);

   if (select == 1){
        system("cls");
        menu(ID, pass);
   }
   else{
        system("cls");
        puts("\nThank you for using the program. Goodbye!");
   }
}

//Function that deletes the account logged in.
void delete_account(char *ID, char *pass)
{

    int ask_delete;
    char line[500];
    int count = 0;
    int select;

    printf("Are you sure you want to delete your account? Enter 1 for yes and 2 to return to main menu: ");
    scanf("%d", &ask_delete);

    if (ask_delete == 2) {
        system("cls");
        menu(ID, pass);
    }

    if (ask_delete == 1){


        FILE *oldFile;
        FILE *newFile;
        oldFile = fopen("userInfo.txt", "r");
        newFile = fopen("updatedInfo.txt", "w");

        if ((oldFile == NULL) || (newFile == NULL)){
        puts("A file can not be opened.");
        }

        while (fgets(line, 500, oldFile) != NULL){
            count = 0;
            char *token = strtok(line, " ");
            while (token != NULL){
                if (count == 0){
                    strcpy(user.ID, token);
                }
                else if (count == 1){
                    strcpy(user.password, token);
                }
                else if (count == 2){
                    user.balance = strtod(token, &*token);
                }
                token = strtok(NULL, " ");
                count++;
            }
            if ((strcmp(user.ID, ID) != 0)){
                fprintf(newFile, "%s %s %.2lf\n", user.ID, user.password, user.balance);
            }
        }

        fclose(oldFile);
        fclose(newFile);
        remove("userInfo.txt");
        rename("updatedInfo.txt", "userInfo.txt");
    }


    printf("\n\n\nAccount deleted successfully. Enter 1 to return to login and any other key to end the program: ");
    scanf("%d", &select);

    if (select == 1){
        system("cls");
        main();
    }
    else{
        system("cls");
        puts("\nThank you for using the program. Goodbye!");
    }
}

//For loading screen when logging in.
void load(int j)
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}

//For goodbye screen when user ends program.
void end_screen(void)
{
    system("cls");
    puts("\nThank you for using the program. Goodbye!");
}

//Main menu when a user is logged in.
void menu(char *ID, char *pass)
{
    int select;
    printf("\n\n\t\t\t*******************************************\n");
    printf("\t\t\t**** BANK MANAGEMENT SYSTEM  MAIN MENU ****\n");
    printf("\t\t\t*******************************************\n");
    printf("\t\t\t           MADE BY DAVIS NGUYEN\n");
    printf("\t\t\t*******************************************\n");
    printf("\t\t\t\t1: DEPOSIT\n");
    printf("\t\t\t\t2: WITHDRAW\n");
    printf("\t\t\t\t3: VIEW PROFILE\n");
    printf("\t\t\t\t4: BACK TO LOGIN\n");
    printf("\t\t\t\t5: EDIT PROFILE\n");
    printf("\t\t\t\t6: DELETE ACCOUNT\n");
    printf("\t\t\t     PRESS ANY OTHER KEY TO END PROGRAM\n");
    printf("\n\t\t\t*******************************************\n\n\n");


    printf("\nEnter your option: ");
    scanf("%d", &select);

    switch(select){
        case 1:
            system("cls");
            deposit(ID, pass);
            break;
        case 2:
            system("cls");
            withdraw(ID, pass);
            break;
        case 3:
            system("cls");
            view_profile(ID, pass);
            break;
        case 4:
            system("cls");
            printf("\n");
            main();
            break;
        case 5:
            system("cls");
            edit(ID, pass);
            break;
        case 6:
            system("cls");
            delete_account(ID, pass);
            break;
        default:
            end_screen();
    }
}
