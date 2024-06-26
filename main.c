#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Account
{
    char name[31];
    char email[31];
    char password[21];
    float money;
}Account;

void CreateBankAccount(Account *acc)
{
    FILE *file = fopen("accounts.txt", "a");
    if (!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    char password2[21];
    printf("Please enter your name: ");
    scanf("%30s", acc->name);
    getchar();
    printf("Please enter an email: ");
    scanf("%30s", acc->email);
    getchar();
    printf("Please enter a password: ");
    scanf("%20s", acc->password);
    getchar();
    printf("Please enter the password again: ");
    scanf("%20s", password2);
    getchar();
    if (strcmp(acc->password, password2) == 0)
    {
        acc->money = 0.00;
        fprintf(file, "%s; %s; %s; %.2f\n", acc->name, acc->email, acc->password, acc->money);
        printf("Account created successfully\n");
    }
    else
    {
        printf("Passwords do not match. Account not created.\n");
    }
    fclose(file);
}

void LogInAccount(Account *acc)
{
    FILE *file = fopen("accounts.txt", "r");
    if (!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    Account fileAccount;
    printf("Please enter an email: ");
    scanf("%30s", acc->email);
    getchar();
    printf("Please enter a password: ");
    scanf("%20s", acc->password);
    getchar();
    int logged = 0;
    while (fscanf(file, "%30[^;]; %30[^;]; %20[^;]; %f\n", fileAccount.name, fileAccount.email, fileAccount.password, &fileAccount.money) != EOF)
    {
        if (strcmp(acc->email, fileAccount.email) == 0 && strcmp(acc->password, fileAccount.password) == 0)
        {
            logged = 1;
            strcpy(acc->name, fileAccount.name);
            acc->money = fileAccount.money;
            break;
        }
    }
    fclose(file);
    if (logged == 1)
    {
        printf("You have logged in successfully\n");
        printf("Welcome %s\n", acc->name);
    }
    else
    {
        printf("Login failed. Please try again\n");
        exit(1);
    }
}

void redeemACheck(Account *acc)
{
    FILE *file = fopen("accounts.txt", "r+");
    if(!file)
    {
        printf("File could not be opened.");
        exit(1);
    }
    double checkValue = 0.00;
    printf("Please enter check value: ");
    scanf("%f", &checkValue);
    Account fileAccount;
    long pos;
    while ((pos = ftell(file)) >= 0 &&
           fscanf(file, "%30[^;]; %30[^;]; %20[^;]; %f\n", fileAccount.name, fileAccount.email, fileAccount.password, &fileAccount.money) != EOF)
    {
        if (strcmp(acc->email, fileAccount.email) == 0 && strcmp(acc->password, fileAccount.password) == 0)
        {
            fileAccount.money += checkValue;
            acc->money = fileAccount.money;
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s; %s; %s; %.2f\n", fileAccount.name, fileAccount.email, fileAccount.password, fileAccount.money);
            break;
        }
    }
    fclose(file);
}

void viewBalance(Account *acc)
{
    FILE *file = fopen("accounts.txt", "r");
    if(!file)
    {
        printf("File could not be opened.");
        exit(1);
    }
    Account fileAccount;
    while (fscanf(file, "%30[^;]; %30[^;]; %20[^;]; %f\n", fileAccount.name, fileAccount.email, fileAccount.password, &fileAccount.money) != EOF)
    {
        if (strcmp(acc->email, fileAccount.email) == 0 && strcmp(acc->password, fileAccount.password) == 0)
        {
            printf("Your balance is: %.2f \n", acc->money);
            break;
        }
    }
    fclose(file);
}

void changePassword(Account *acc)
{
    FILE *file = fopen("accounts.txt", "r+");
    if(!file)
    {
        printf("File could not be opened.");
        exit(1);
    }
    char newPassword[21];
    char newPassword2[21];
    printf("Please enter your new password: ");
    scanf("%20s", newPassword);
    getchar();
    printf("Please enter your new password again: ");
    scanf("%20s", newPassword2);
    getchar();
    if(strcmp(newPassword, newPassword2) != 0)
    {
        printf("Incorrectly entered password.");
        exit(1);
    }
    else
    {
        Account fileAccount;
        long pos;
        while ((pos = ftell(file)) >= 0 &&
               fscanf(file, "%30[^;]; %30[^;]; %20[^;]; %f\n", fileAccount.name, fileAccount.email, fileAccount.password, &fileAccount.money) != EOF)
        {
            if (strcmp(acc->email, fileAccount.email) == 0 && strcmp(acc->password, fileAccount.password) == 0)
            {
                strcpy(fileAccount.password, newPassword);
                strcpy(acc->password,fileAccount.password);
                fseek(file, pos, SEEK_SET);
                fprintf(file, "%s; %s; %s; %.2f\n", fileAccount.name, fileAccount.email, fileAccount.password, fileAccount.money);
                break;
            }
        }
    }
    fclose(file);
}

void transferMoney()
{
    printf("Idea for transfer money functionality is not implemented yet.\n");
}
int main()
{
    printf("--Bank management system---\n");
    printf("Please choose your desired option:\n1) log into an account   2) create an account\n");
    Account account;
    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            LogInAccount(&account);
            break;
        case 2:
            CreateBankAccount(&account);
            break;
        default:
            printf("Incorrect option\n");
            exit(1);
    }
    printf("%s\n", account.name);
    printf("%.2f\n", account.money);
    printf("\nThank you for logging in. What would you like to do with your account?\n");
    printf("1) redeem a check\n2) view balance\n3) change password\n");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            redeemACheck(&account);
            break;
        case 2:
            viewBalance(&account);
            break;
        case 3:
            changePassword(&account);
            break;
        default:
            printf("Incorrect option\n");
            exit(1);
    }
    printf("Thank you for using our bank! Have a nice day!");
    return 0;
}
