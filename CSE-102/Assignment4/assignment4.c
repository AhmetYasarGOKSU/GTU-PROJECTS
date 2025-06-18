#include <stdio.h>
#include <math.h>

void simMenu();
void launchParameters();
void simulateRocket();
double totalFlight(int initial_velocity, double gravity, int launch_height);
double maximumAltitude(int initial_velocity, double gravity, int launch_height);
void drawTrajectory(int initial_velocity, double gravity, int launch_height);
void saveTrajectory();

int main() {
    int choice;
    simMenu();
    int ch;

    do {
        printf("Please choose a number between 1 and 4 (included): ");

        if (scanf("%d", &choice) != 1) {  
            while ((ch = getchar()) != '\n' && ch != EOF); 
            continue; 
        }

    } while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4));

    switch (choice) {
        case 1:
            launchParameters();   
            break;
        case 2:
            simulateRocket();
            break;
        case 3:
            saveTrajectory();
            break;
        case 4:
            return;
    }
}

void simMenu() {
    printf("Welcome to the Rocket Launch Simulator!\n");
    printf("----------------------------------------\n");
    printf("1. Enter launch parameters\n");
    printf("2. Simulate rocket trajectory\n");
    printf("3. Save trajectory data\n");
    printf("4. Exit\n");
}

void launchParameters() {
    int initial_velocity, launch_height;
    double gravity;
    
    printf("Enter initial velocity (m/s): ");
    if (scanf("%d", &initial_velocity) != 1) {
        printf("Invalid input! Please enter a number.\n");
        return;
    }
    if (initial_velocity < 0) {
        printf("Initial velocity can not be negative!\n");
        return;
    }

    
    printf("Enter gravity (m/s², default 9.8): ");
    int ch;
    if (scanf("%lf", &gravity) != 1) {
        printf("Invalid input but gravity value has declared as default value (9.8m/s²)\n");
        gravity = 9.8; 
        while ((ch = getchar()) != '\n' && ch != EOF); 


    }
    
    printf("Enter launch height (m): ");
    if (scanf("%d", &launch_height) != 1) {
        printf("Invalid input! Please enter a number.\n");
        return;
    }
    
    if (launch_height < 0) {
        printf("Launch height can not be negative! Please try again.\n");
        return;
    }
    
    FILE * rocket_file;
    rocket_file = fopen("rocket_data.txt", "w");
    
    if (rocket_file == NULL) {
        printf("There is a problem while creating a file.\n");
        return;
    }
    
    fprintf(rocket_file, "%d %.2lf %d", initial_velocity, gravity, launch_height);
    
    fclose(rocket_file);
    printf("Rocket parameters are saved to rocket_data.txt!\n");  
}

void simulateRocket() {
    int initial_velocity, launch_height;
    double gravity, total_flight, max_altitude;
    
    printf("Reading rocket parameters from file...\n");
    
    FILE * read_parameters_file;
    read_parameters_file = fopen("rocket_data.txt", "r");
    
    if (read_parameters_file == NULL) {
        printf("Error! File does not exist or has no data.\n");
        return;
    }
    
    if (fscanf(read_parameters_file, "%d %lf %d", &initial_velocity, &gravity, &launch_height) != 3) {
        printf("Error reading parameters from file.\n");
        fclose(read_parameters_file);
        return;
    }
    
    fclose(read_parameters_file);
    
    printf("Equation: h(t) = %.2lf * t^2 + %d * t + %d\n", -0.5*gravity, initial_velocity, launch_height);
    
    printf("Simulating trajectory...\n");
    
    total_flight = totalFlight(initial_velocity, gravity, launch_height);
    max_altitude = maximumAltitude(initial_velocity, gravity, launch_height);
    
    drawTrajectory(initial_velocity, gravity, launch_height);
}

double totalFlight(int initial_velocity, double gravity, int launch_height) {
    double discriminant, t_flight;
    discriminant = initial_velocity * initial_velocity + 2 * gravity * launch_height;
    if (discriminant < 0) {
        return 0;
    }
    t_flight = (initial_velocity + sqrt(discriminant)) / gravity; 

    return (t_flight);
}

double maximumAltitude(int initial_velocity, double gravity, int launch_height) {
    double maximum_altitude;
    maximum_altitude = launch_height + (initial_velocity * initial_velocity) / (2 * gravity);

    return (maximum_altitude);
}

void drawTrajectory(int initial_velocity, double gravity, int launch_height) {
    int height_divisions;
    double total_flight = totalFlight(initial_velocity, gravity, launch_height);
    double max_altitude = maximumAltitude(initial_velocity, gravity, launch_height);
    int time_steps = (int)total_flight + 1;

    if (max_altitude < 150) {
        height_divisions = 10;
    } else if (max_altitude < 250) {
        height_divisions = 15;
    } else if (max_altitude < 500) {
        height_divisions = 20;
    } else {
        height_divisions = 30;
    }

    int height_step = (int)max_altitude / height_divisions;
    
    int i, j;
    printf("\n");
    for (i = height_divisions + 1; i > 0; i--) {
        double current_height = i * height_step;
        printf("%5.1f |", current_height);
        printf(" ");
        for (j = 1; j <= time_steps; j++) {
            double height = launch_height + initial_velocity * j - 0.5 * gravity * j * j;

            if (height >= current_height - height_step / 2 && height < current_height + height_step / 2) {
                printf(" # ");
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }

    int t;
    printf("  0.0 |-----");
    for (t = 0; t <= time_steps/2 + 1; t++) {
        printf("|-----");
    }
    printf("\n");
    printf("     ");
    for (t = 0; t <= time_steps; t += 2) {
        printf(" %d", t);
        if (t + 2 <= time_steps) {
            printf("    ");
        }
    }
    printf("\n");
}

void saveTrajectory() {
    int initial_velocity, launch_height, check_input, height_divisions;
    double gravity;
    FILE * get_rocket_data_file;
    get_rocket_data_file = fopen("rocket_data.txt", "r");
    if (get_rocket_data_file == NULL) {
        printf("Error!! Rocket data could not be found.\n");
        return;
    }
    
    check_input = fscanf(get_rocket_data_file, "%d %lf %d", &initial_velocity, &gravity, &launch_height);

    if (!check_input) {
        printf("Error!! While reading data from rocket_data.txt");
        return;
    }
    fclose(get_rocket_data_file);
    
    FILE * save_trajectory_file;
    save_trajectory_file = fopen("trajectory.txt", "w");
    
    if (save_trajectory_file == NULL) {
        printf("There is a problem while creating a file.\n");
        return;
    }
    
    printf("Saving trajectory data...\n");

    double total_flight = totalFlight(initial_velocity, gravity, launch_height);
    double max_altitude = maximumAltitude(initial_velocity, gravity, launch_height);
    
    printf("Maxiumum altitude: %.2lf meters\n", max_altitude);
    
    printf("Total flight duration: %.2lf seconds\n", total_flight);
    
    int time_steps = (int)total_flight + 1;
    if (max_altitude < 150) {
        height_divisions = 10;
    } else if (max_altitude < 250) {
        height_divisions = 15;
    } else if (max_altitude < 500) {
        height_divisions = 20;
    } else {
        height_divisions = 30;
    }
    int height_step = (int)max_altitude / height_divisions;
    
    int i, j;
    fprintf(save_trajectory_file, "\n");
    for (i = height_divisions + 1; i > 0; i--) {
        double current_height = i * height_step;
        fprintf(save_trajectory_file, "%5.1f |", current_height);
        fprintf(save_trajectory_file, " ");
        for (j = 1; j <= time_steps; j++) {
            double height = launch_height + initial_velocity * j - 0.5 * gravity * j * j;

            if (height >= current_height - height_step / 2 && height < current_height + height_step / 2) {
                fprintf(save_trajectory_file, " # ");
            } else {
                fprintf(save_trajectory_file, "   ");
            }
        }
        fprintf(save_trajectory_file, "\n");
    }

    int t;
    fprintf(save_trajectory_file, "  0.0 |-----");
    for (t = 0; t <= time_steps / 2 + 1; t++) {
        fprintf(save_trajectory_file, "|-----");
    }

    fprintf(save_trajectory_file, "\n");
    fprintf(save_trajectory_file, "     ");
    
    for (t = 0; t <= time_steps; t += 2) {
        fprintf(save_trajectory_file, " %d", t);
        if (t + 2 <= time_steps) {
            fprintf(save_trajectory_file, "    ");
        }
    }
    fprintf(save_trajectory_file, "\n");
    
    printf("Graph saved to trajectory.txt\n");
    
    fclose(save_trajectory_file);
}

