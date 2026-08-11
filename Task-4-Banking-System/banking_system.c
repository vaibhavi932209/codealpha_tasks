#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCOUNT_FILE "accounts.dat"
#define TRANSACTION_FILE "transactions.dat"
#define MAX 50
#define MIN_BALANCE 500.0

// ===============================
// Structure for Bank Account
// ===============================
struct Account {
    int     accountNumber;
    char    holderName[MAX];
    float   balance;
    int     transactionCount;
};

// ===============================
// Structure for Transaction
// ===============================
struct Transaction {
    int      accountNumber;
    char     type[20];
    float    amount;
    float    balanceAfter;
};

// ===============================
// Check Account Number
// ===============================
int accountExists(int accountNumber) {

    FILE *file;
    struct Account account;

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
        return 0;

    while (fread(&account, sizeof(account), 1, file)) {

        if (account.accountNumber == accountNumber) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// ===============================
// Find Account Position
// ===============================
long findAccount(int accountNumber) {

    FILE *file;
    struct Account account;
    long position;

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
        return -1;

    while (1) {

        position = ftell(file);

        if (fread(&account, sizeof(account), 1, file) != 1)
            break;

        if (account.accountNumber == accountNumber) {
            fclose(file);
            return position;
        }
    }

    fclose(file);
    return -1;
}

// ===============================
// Record Transaction
// ===============================
void recordTransaction(int accountNumber,
                       const char type[],
                       float amount,
                       float balanceAfter) {

    FILE *file;
    struct Transaction transaction;

    transaction.accountNumber = accountNumber;
    strcpy(transaction.type, type);
    transaction.amount =        amount;
    transaction.balanceAfter =  balanceAfter;

    file = fopen(TRANSACTION_FILE, "ab");

    if (file == NULL) {
        printf("\nError opening transaction file!\n");
        return;
    }

    fwrite(&transaction, sizeof(transaction), 1, file);

    fclose(file);
}

// ===============================
// Create Account
// ===============================
void createAccount() {

    FILE *file;
    struct Account account;

    printf("\n============================================\n");
    printf("              CREATE ACCOUNT\n");
    printf("============================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &account.accountNumber);

    if (account.accountNumber <= 0) {
        printf("\nInvalid account number!\n");
        return;
    }

    if (accountExists(account.accountNumber)) {
        printf("\nAccount number already exists!\n");
        return;
    }

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", account.holderName);

    printf("Enter Initial Deposit (Minimum Rs. %.2f): ",
           MIN_BALANCE);
    scanf("%f", &account.balance);

    if (account.balance < MIN_BALANCE) {
        printf("\nInitial deposit must be at least Rs. %.2f\n",
               MIN_BALANCE);
        return;
    }

    account.transactionCount = 1;

    file = fopen(ACCOUNT_FILE, "ab");

    if (file == NULL) {
        printf("\nError opening account file!\n");
        return;
    }

    fwrite(&account, sizeof(account), 1, file);

    fclose(file);

    // Record initial deposit
    recordTransaction(
        account.accountNumber,
        "Initial Deposit",
        account.balance,
        account.balance
    );

    printf("\n============================================\n");
    printf("       ACCOUNT CREATED SUCCESSFULLY!\n");
    printf("============================================\n");

    printf("Account Number : %d\n", account.accountNumber);
    printf("Holder Name    : %s\n", account.holderName);
    printf("Balance        : Rs. %.2f\n", account.balance);
}

// ===============================
// Deposit Money
// ===============================
void depositMoney() {

    FILE *file;
    struct Account account;

    int accountNumber;
    float amount;
    long position;

    printf("\n============================================\n");
    printf("               DEPOSIT MONEY\n");
    printf("============================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    position = findAccount(accountNumber);

    if (position == -1) {
        printf("\nAccount not found!\n");
        return;
    }

    printf("Enter Deposit Amount: Rs. ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nDeposit amount must be greater than zero!\n");
        return;
    }

    file = fopen(ACCOUNT_FILE, "rb+");

    if (file == NULL) {
        printf("\nError opening account file!\n");
        return;
    }

    fseek(file, position, SEEK_SET);

    fread(&account, sizeof(account), 1, file);

    account.balance += amount;
    account.transactionCount++;

    fseek(file, position, SEEK_SET);

    fwrite(&account, sizeof(account), 1, file);

    fclose(file);

    recordTransaction(
        account.accountNumber,
        "Deposit",
        amount,
        account.balance
    );

    printf("\n--------------------------------------------\n");
    printf("Deposit successful! ✓\n");
    printf("Previous Balance : Rs. %.2f\n",
           account.balance - amount);
    printf("Deposited Amount : Rs. %.2f\n", amount);
    printf("New Balance      : Rs. %.2f\n",
           account.balance);
    printf("--------------------------------------------\n");
}

// ===============================
// Withdraw Money
// ===============================
void withdrawMoney() {

    FILE *file;
    struct Account account;

    int accountNumber;
    float amount;
    long position;

    printf("\n============================================\n");
    printf("              WITHDRAW MONEY\n");
    printf("============================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    position = findAccount(accountNumber);

    if (position == -1) {
        printf("\nAccount not found!\n");
        return;
    }

    printf("Enter Withdrawal Amount: Rs. ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nWithdrawal amount must be greater than zero!\n");
        return;
    }

    file = fopen(ACCOUNT_FILE, "rb+");

    if (file == NULL) {
        printf("\nError opening account file!\n");
        return;
    }

    fseek(file, position, SEEK_SET);

    fread(&account, sizeof(account), 1, file);

    // Maintain minimum balance
    if (account.balance - amount < MIN_BALANCE) {

        printf("\nWithdrawal cannot be completed.\n");
        printf("Minimum balance of Rs. %.2f must be maintained.\n",
               MIN_BALANCE);

        fclose(file);
        return;
    }

    account.balance -= amount;
    account.transactionCount++;

    fseek(file, position, SEEK_SET);

    fwrite(&account, sizeof(account), 1, file);

    fclose(file);

    recordTransaction(
        account.accountNumber,
        "Withdrawal",
        amount,
        account.balance
    );

    printf("\n--------------------------------------------\n");
    printf("Withdrawal successful! ✓\n");
    printf("Withdrawn Amount : Rs. %.2f\n", amount);
    printf("Remaining Balance : Rs. %.2f\n",
           account.balance);
    printf("--------------------------------------------\n");
}

// ===============================
// Balance Enquiry
// ===============================
void balanceEnquiry() {

    FILE *file;
    struct Account account;

    int accountNumber;
    int found = 0;

    printf("\n============================================\n");
    printf("              BALANCE ENQUIRY\n");
    printf("============================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL) {
        printf("\nNo account records found!\n");
        return;
    }

    while (fread(&account, sizeof(account), 1, file)) {

        if (account.accountNumber == accountNumber) {

            printf("\n--------------------------------------------\n");
            printf("Account Number     : %d\n",
                   account.accountNumber);

            printf("Account Holder     : %s\n",
                   account.holderName);

            printf("Current Balance    : Rs. %.2f\n",
                   account.balance);

            printf("Total Transactions : %d\n",
                   account.transactionCount);

            printf("--------------------------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
        printf("\nAccount not found!\n");
}

// ===============================
// Search Account
// ===============================
void searchAccount() {

    FILE *file;
    struct Account account;

    int accountNumber;
    int found = 0;

    printf("\n============================================\n");
    printf("                SEARCH ACCOUNT\n");
    printf("============================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL) {
        printf("\nNo account records found!\n");
        return;
    }

    while (fread(&account, sizeof(account), 1, file)) {

        if (account.accountNumber == accountNumber) {

            printf("\n✓ Account Found!\n");
            printf("--------------------------------------------\n");

            printf("Account Number : %d\n",
                   account.accountNumber);

            printf("Holder Name    : %s\n",
                   account.holderName);

            printf("Balance        : Rs. %.2f\n",
                   account.balance);

            printf("Transactions   : %d\n",
                   account.transactionCount);

            printf("--------------------------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
        printf("\nAccount not found!\n");
}

// ===============================
// Transaction History
// ===============================
void transactionHistory() {

    FILE *file;
    struct Transaction transaction;

    int accountNumber;
    int found = 0;

    printf("\n============================================\n");
    printf("             TRANSACTION HISTORY\n");
    printf("============================================\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    file = fopen(TRANSACTION_FILE, "rb");

    if (file == NULL) {
        printf("\nNo transaction records found!\n");
        return;
    }

    printf("\n%-20s %-15s %-18s\n",
           "Transaction", "Amount", "Balance");

    printf("--------------------------------------------\n");

    while (fread(&transaction,
                 sizeof(transaction), 1, file)) {

        if (transaction.accountNumber == accountNumber) {

            printf("%-20s Rs. %-11.2f Rs. %.2f\n",
                   transaction.type,
                   transaction.amount,
                   transaction.balanceAfter);

            found = 1;
        }
    }

    fclose(file);

    if (!found)
        printf("No transactions found for this account.\n");
}

// ===============================
// Display All Accounts
// ===============================
void displayAllAccounts() {

    FILE *file;
    struct Account account;

    int count = 0;

    printf("\n============================================================\n");
    printf("                  ALL BANK ACCOUNTS\n");
    printf("============================================================\n");

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("%-8s %-20s %-15s %-10s\n",
           "Number", "Holder Name",
           "Balance", "Transactions");

    printf("------------------------------------------------------------\n");

    while (fread(&account, sizeof(account), 1, file)) {

        printf("%-8d %-20s Rs. %-11.2f %-10d\n",
               account.accountNumber,
               account.holderName,
               account.balance,
               account.transactionCount);

        count++;
    }

    fclose(file);

    if (count == 0)
        printf("No accounts available.\n");
}

// ===============================
// Main Menu
// ===============================
void displayMenu() {

    printf("\n============================================\n");
    printf("              SMART BANKING SYSTEM\n");
    printf("============================================\n");
    printf("  1. Create Account\n");
    printf("  2. Deposit Money\n");
    printf("  3. Withdraw Money\n");
    printf("  4. Balance Enquiry\n");
    printf("  5. Search Account\n");
    printf("  6. Transaction History\n");
    printf("  7. Display All Accounts\n");
    printf("  8. Exit\n");
    printf("============================================\n");
}

// ===============================
// Main Function
// ===============================
int main() {

    int choice;

    printf("\n============================================\n");
    printf("          WELCOME TO SMART BANK\n");
    printf("       Account Management System\n");
    printf("============================================\n");

    do {

        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                searchAccount();
                break;

            case 6:
                transactionHistory();
                break;

            case 7:
                displayAllAccounts();
                break;

            case 8:

                printf("\n============================================\n");
                printf("     Thank you for using Smart Bank!\n");
                printf("        Have a great day! \n");
                printf("============================================\n");

                break;

            default:

                printf("\n Invalid choice!\n");
                printf("Please select an option between 1 and 8.\n");
        }

    } while (choice != 8);

    return 0;
}
