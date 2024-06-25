#include <stdio.h>
#include <stdlib.h>

void CreateBankAccount()
{
    FILE *file = fopen("accounts.txt", "a");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    char name[31];
    char email[31];
    char password1[21];
    char password2[21];
    printf("Please enter your name: ");
    scanf("%s", name);
    getchar();
    printf("Please enter an email: ");
    scanf("%s", email);
    getchar();
    printf("Please enter a password: ");
    scanf("%s", password1);
    getchar();
    printf("Please enter the password again: ");
    scanf("%s", password2);
    getchar();
    if(strcmp(password1, password2) == 0)
    {
        fprintf(file, "%s; %s; %s;\n", name, email, password2);
        printf("Account created successfully");
    }
    fclose(file);
}

void LogInAccount()
{
    FILE *file = fopen("accounts.txt", "r");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    char name[31];
    char email[31];
    char password[21];
    char fileEmail[31];
    char filePassword[21];
    printf("Please enter an email: ");
    scanf("%s", email);
    getchar();
    printf("Please enter a password: ");
    scanf("%s", password);
    getchar();
    int logged = 0;
    while(fscanf(file, "%30[^;]; %30[^;]; %20[^;];\n", name, fileEmail, filePassword) != EOF)
    {
        if(strcmp(email, fileEmail) == 0 && strcmp(password, filePassword) == 0)
        {
                logged = 1;
                break;
        }
    }
    fclose(file);

    if(logged == 1)
    {
        printf("You have logged in successfully\n");
        printf("Welcome %s", name);
    }
    else
    {
        printf("Login failed. Please try again");
        exit(1);
    }
}
void redeemACheck()
{

}
void viewBalance()
{

}
void transferMoney()
{

}
void changePassword()
{

}
int main()
{
    printf("--Bank management system---");
    printf("Please choose your desired option:\n1)log into an account   2)create an account\n");
    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        LogInAccount();
        break;
    case 2:
        CreateBankAccount();
        break;
    default:
        printf("Incorrect option");
        exit(1);
    }
    printf("\nThank you for logging in. What would you like to do with your account?\n");
    printf("1)deposit money   2)view balance\n3)withdraw money   4)change password");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        redeemACheck()
        break;
    case 2:
        viewBalance()
        break;
    case 3:
        withdrawMoney()
        break;
    case 4:
        changePassword()
        break;
    default:
        printf("Incorrect option");
        exit(1);
    }
    return 0;
}
