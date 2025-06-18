#include <stdio.h>

void main() {
    int number1, number2;
    float experimental_result, expected_result, error, error_rate, total_error, total_expected_result, average_error_value;
    char operator;
    total_error = 0;
    // FIRST
    
    printf("Enter an operation (Example: 3+2):");
    scanf("%d %c %d", &number1, &operator, &number2); 
	
	if (operator == '+')
	{
		experimental_result = number1 - number2;
		expected_result = number1 + number2;
	} 
	else if (operator == '-') 
	{
		experimental_result = number1 * number2;
		expected_result = number1 - number2;
	} 
	else if (operator == '*') 
	{
		experimental_result = number1 + number2;
		expected_result = number1 * number2;
	} 
	else if (operator == '/') 
	{
	        if (number2 != 0) {
		        experimental_result = number1 - number2;
		        expected_result = number1 / number2;
		}
		else {
		      printf("Second number can not be zero! Please Try Again.\n");
		      return;
		
		}
	}
	else 
	{
		printf("Operator could not be found.\n");
	}
	error = expected_result - experimental_result;
	
	if (error < 0)
	{
		error = error * (-1);
	}
	if (expected_result != 0) {
	      error_rate = (error / expected_result) * 100;
	      total_error += error_rate;
              printf("Expected Result: %.2f\n", expected_result);
              printf("Experimental Result: %.2f\n", experimental_result);
              printf("Error: %.2f\n", error);
              printf("Error Percentage: %.2f%% \n", error_rate);
        }
        else {
	      printf("Expected Result: %.2f\n", expected_result);
	      printf("Experimental Result: %.2f\n", experimental_result);
	      printf("Error: %.2f\n", error);
              printf("Error rate could not be calculated due to divided by 0.\n");
        }

	
	

    // SECOND
    
    printf("Enter an operation (Example: 3+2):");
    scanf("%d %c %d", &number1, &operator, &number2); 
	
	if (operator == '+')
	{
		experimental_result = number1 - number2;
		expected_result = number1 + number2;
	} 
	else if (operator == '-') 
	{
		experimental_result = number1 * number2;
		expected_result = number1 - number2;
	} 
	else if (operator == '*') 
	{
		experimental_result = number1 + number2;
		expected_result = number1 * number2;
	} 
	else if (operator == '/') 
	{
                if (number2 != 0) {
	                experimental_result = number1 - number2;
	                expected_result = number1 / number2;
	        }
	        else {
	              printf("Second number can not be zero! Please Try Again.\n");
	              return;
	        
	        }
	}
	else 
	{
		printf("Operator could not be found.\n");
	}
	error = expected_result - experimental_result;
	
	if (error < 0)
	{
		error = error * (-1);
	}
	
	
	if (expected_result != 0) {
	      error_rate = (error / expected_result) * 100;
	      total_error += error_rate;
              printf("Expected Result: %.2f\n", expected_result);
              printf("Experimental Result: %.2f\n", experimental_result);
              printf("Error: %.2f\n", error);
              printf("Error Percentage: %.2f%% \n", error_rate);
        }
        else {
	      printf("Expected Result: %.2f\n", expected_result);
	      printf("Experimental Result: %.2f\n", experimental_result);
	      printf("Error: %.2f\n", error);
              printf("Error rate could not be calculated due to divided by 0.\n");
        }

    // THIRD
    
    
    printf("Enter an operation (Example: 3+2):");
    scanf("%d %c %d", &number1, &operator, &number2); 
	
	if (operator == '+')
	{
		experimental_result = number1 - number2;
		expected_result = number1 + number2;
	} 
	else if (operator == '-') 
	{
		experimental_result = number1 * number2;
		expected_result = number1 - number2;
	} 
	else if (operator == '*') 
	{
		experimental_result = number1 + number2;
		expected_result = number1 * number2;
	} 
	else if (operator == '/') 
	{
                if (number2 != 0) {
	                experimental_result = number1 - number2;
	                expected_result = number1 / number2;
	        }
	        else {
	              printf("Second number can not be zero! Please Try Again.\n");
	              return;
	        
	        }
	}
	else 
	{
		printf("Operator could not be found.\n");
	}
	error = expected_result - experimental_result;
	if (error < 0)
	{
		error = error * (-1);
	}
	if (expected_result != 0) {
	      error_rate = (error / expected_result) * 100;
	      total_error += error_rate;
              printf("Expected Result: %.2f\n", expected_result);
              printf("Experimental Result: %.2f\n", experimental_result);
              printf("Error: %.2f\n", error);
              printf("Error Percentage: %.2f%% \n", error_rate);
        }
        else {
	      printf("Expected Result: %.2f\n", expected_result);
	      printf("Experimental Result: %.2f\n", experimental_result);
	      printf("Error: %.2f\n", error);
              printf("Error rate could not be calculated due to divided by 0.\n");
        }

    // FOURTH
    
    
    printf("Enter an operation (Example: 3+2):");
    scanf("%d %c %d", &number1, &operator, &number2); 
	
	if (operator == '+')
	{
		experimental_result = number1 - number2;
		expected_result = number1 + number2;
	} 
	else if (operator == '-') 
	{
		experimental_result = number1 * number2;
		expected_result = number1 - number2;
	} 
	else if (operator == '*') 
	{
		experimental_result = number1 + number2;
		expected_result = number1 * number2;
	} 
	else if (operator == '/') 
	{
	        if (number2 != 0) {
		        experimental_result = number1 - number2;
		        expected_result = number1 / number2;
		}
		else {
		      printf("Second number can not be zero! Please Try Again.\n");
		      return;
		
		}
	}
	else 
	{
		printf("Operator could not be found.\n");
	}
	
	error = expected_result - experimental_result;
	if (error < 0)
	{
		error = error * (-1);
	}
	
	
	
	if (expected_result != 0) {
	      error_rate = (error / expected_result) * 100;
	      total_error += error_rate;
              printf("Expected Result: %.2f\n", expected_result);
              printf("Experimental Result: %.2f\n", experimental_result);
              printf("Error: %.2f\n", error);
              printf("Error Percentage: %.2f%% \n", error_rate);
        }
        else {
	      printf("Expected Result: %.2f\n", expected_result);
	      printf("Experimental Result: %.2f\n", experimental_result);
	      printf("Error: %.2f\n", error);
              printf("Error rate could not be calculated due to divided by 0.\n");
        }


	
	average_error_value = total_error / 4;
	printf("Average Error Value: %.2f%% \n", average_error_value);
} 
