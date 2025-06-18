#include <stdio.h> 

int main() {
    double unit_consumed, to_paid, total_unit_consumed;
    
    printf("Enter the units consumed: ");
    scanf("%lf", &unit_consumed);
    
    if (unit_consumed < 0) {
        printf("Invalid Input.\n");
        return 0;
    }
    
    
    if (unit_consumed <= 50) {
        total_unit_consumed = unit_consumed * 0.50;
    }
    else {
        if (unit_consumed > 50 && unit_consumed <= 100) {
            total_unit_consumed = (50 * 0.50) + ((unit_consumed - 50) * 0.75);
            
        }
        else {
            if (unit_consumed > 100 && unit_consumed <= 250) {
                total_unit_consumed = (50 * 0.50) + (50 * 0.75) + ((unit_consumed - 100) * 1.20);
            
            
            }
            else {
                if (unit_consumed > 250) {
                    total_unit_consumed = (50 * 0.50) + (50 * 0.75) + (150 * 1.20) + ((unit_consumed - 250) * 1.50);
            
                }
                else {
                    printf("Could not be calculated. Please try again.\n");
                    return 0;
                
                }
            }
        }
    }
    to_paid = total_unit_consumed * 120 / 100;
    
    printf("Net amount to be paid: %.0f\n", to_paid);
    
    
    
} 
