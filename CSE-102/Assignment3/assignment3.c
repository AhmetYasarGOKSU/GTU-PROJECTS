#include <stdio.h>
#include <stdlib.h>

double get_balance();
void update_balance(double new_balance);
void check_balance();
void deposit_money();
void withdraw_money();
void menu();


int main() {
        int option;
        menu();
        /* Get input from user */
        printf("Choose an option: ");
        scanf("%d", &option);
        /* Check what user want to do */
        if (option == 1) {
            check_balance();
        }
        else if (option == 2) {
            deposit_money();
        }
        else if (option == 3) {
            withdraw_money();
        }
        else if (option == 4) {
            printf("Exiting program. See you later.\n");
            return 1;
        }   
        else {
            printf("Invalid input. Please try again later!\n");
            return -1;
        }
        
        
    
    
}

double get_balance() {
    double balance;
    double initial_balance = 100.00;
    int check_input;
    
    FILE * open_file;
    open_file = fopen("account.txt", "r");
    
    /* Check open file and get balance */
    
    if (open_file == NULL) {
        open_file = fopen("account.txt", "w");
        if (open_file == NULL) {
            printf("Error while opening file.\n");
            return 0;
        }
        fprintf(open_file ,"%.2lf", initial_balance);
        fclose(open_file);
        balance = initial_balance;
    }
    else {
        /* Check is input correct */
        check_input = fscanf(open_file, "%lf", &balance);
        if (check_input != 1) {
            balance = initial_balance;
        }
    } 
    return balance;
}
void update_balance(double new_balance) {
    /* Update balance after deposit or withdraw */
    FILE * open_file;
    open_file = fopen("account.txt", "w");
    fprintf(open_file, "%.2lf", new_balance);
    fclose(open_file);
}

void check_balance() {
    double balance = get_balance();
    printf("Current balance: %.2lf\n", balance);
    
}
void deposit_money() {
    double deposit, balance;
    int check;
    printf("Enter amount to deposit: ");
    check = scanf("%lf", &deposit);
    
    /* Check is deposit a number and not negative */
    if (check && deposit > 0) {
        balance = get_balance();
        balance += deposit;
        /* Update new balance */
        printf("Deposit successful! New balance: %.2lf TRY.\n", balance);
        update_balance(balance);
    }
    else {
        printf("Invalid input for deposit!\n");

    }

}
void withdraw_money() {
    double withdraw_money, balance;
    int check;
    balance = get_balance();
    printf("Enter amount to withdraw: ");
    check = scanf("%lf", &withdraw_money);
    /* Check is withdraw a number and not negative */
    if (check && withdraw_money > 0) {
        /* Check withdraw_money is bigger than balance if not printf error */
        if (withdraw_money > balance) {
            printf("Insufficient funds! Your balance is only %.2lf TRY.\n", balance);

        }
        else {
            /* Calculate new balance and update it after withdraw */
            balance -= withdraw_money;
            printf("Withdraw successful! New balance: %.2lf TRY.\n", balance);
            update_balance(balance);
        }
    }
    else {
        printf("Invalid input for deposit!\n");

    }
}

void menu() {
    /* Print Virtual ATM on console */
    printf("----- Virtual ATM -----\n");
    printf("1. Check Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Exit\n");
} 

