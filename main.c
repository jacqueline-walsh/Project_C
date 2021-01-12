#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Employee structure
typedef struct {
    int employee_code;
    char employee_lastName[20];
    char employee_firstName[20];
    int insurable_weeks;
    float gross_pay;
    float subsidy;
    float subsidy_amount;
}  Employee;

// Employee array
Employee empArray[sizeof(Employee)];
Employee *emp = empArray;

int fileSize = 0;

// prototype functions
void load_data();
void display_menu();
void add_new_employee();
void delete_employee();
void view_all_employees();
void view_qualifying_employees();
void view_disqualifying_employees();
void sort_employees_by_name();
void sort_employees_by_subsidy_amount();
void view_total_subsidy_amount();
void save_data();
void showAllEmployees(Employee *emp);

int main(void) {
    // call load data function
    load_data();

    return (0);
}

//  function to load employee records from file data.txt
void load_data() {

    int fileEnd = 0;
    FILE* file = fopen("data.txt", "r"); //initialise file pointer and open file to read
    FILE* fileWrite = fopen("temp.txt", "w"); // initialise file pointer to write to file

    if (file == NULL) {  // if file can't be found output message and create a new file
        puts("An existing file cannot be found.  A new file has been created.");
        file = fopen("data.txt", "wb");  // create new file
        display_menu();
    }
    emp = (Employee *) malloc(sizeof(Employee));  // allocate dynamic memory to array emp
    do  {
        //  scan file and
        fileEnd = fscanf(file, "%d%s%s%d%f", &emp->employee_code, emp->employee_firstName,
               emp->employee_lastName, &emp->insurable_weeks, &emp->gross_pay);
        fileSize++;
        if (emp->insurable_weeks > 0 && emp->insurable_weeks <= 5) {
            if (emp->gross_pay <= 151.50) {
                emp->subsidy = 0.00;
            } else if (emp->gross_pay > 151.50 && emp->gross_pay <= 203.00) {
                emp->subsidy = 203.00;
            } else if (emp->gross_pay > 203.00 && emp->gross_pay <= 300.00) {
                emp->subsidy = 250.00;
            } else if (emp->gross_pay > 300.00 && emp->gross_pay <= 400.00) {
                emp->subsidy = 300.00;
            } else if (emp->gross_pay > 400 && emp->gross_pay <= 1462.00) {
                emp->subsidy = 350.00;
            } else if (emp->gross_pay > 1462.00) {
                emp->subsidy = 0.00;
            }
        } else {
            emp->subsidy = 0.00;
        }

        //  total subsidy paid to each employee
        emp->subsidy_amount = (emp->subsidy * emp->insurable_weeks);

        // print to temp.txt file
        fprintf(fileWrite, "%d %s %s %d %0.2f %0.2f %0.2f\n", emp->employee_code, emp->employee_firstName,
                emp->employee_lastName, emp->insurable_weeks, emp->gross_pay, emp->subsidy, emp->subsidy_amount);
    } while (fileEnd != EOF);

    //  close files
    fclose(file);
    fclose(fileWrite);
    // free malloc
    free(emp);
    display_menu();
}

void display_menu() {

    // output menu for employment
    puts("   ------------------------------   ");
    puts("** Employment Wage Subsidy Scheme **");
    puts("   ------------------------------   ");
    puts("1. Add new Employee");
    puts("2. Delete Employee");
    puts("3. View all Employees");
    puts("4. View only qualifying Employees");
    puts("5. View disqualified Employees");
    puts("6. Sort Employees by name");
    puts("7. Sort employees by subsidy amount");
    puts("8. View total subsidy amount for all Employees");
    puts("9. Exit");
    puts("10. Show All Employees");

    int menuItem;  // declare menuItem
    bool flag = true;  // declare flag and set to true

    // do loop until flag is false
    do {
        puts("Enter item number from menu: ");  // ask user for a menu item
        scanf("%d", &menuItem);  // store menu item in menuItem

        // if menuItem less than 1 or greater than 9 flag = true and do while loop continues
        if (menuItem < 1 || menuItem > 10) {
            flag = true;
            // switch statement will call function for menuItem input
        } else {
            switch (menuItem) {
                case 1:
                    add_new_employee();
                    break;
                case 2:
                    delete_employee();
                    break;
                case 3:
                    view_all_employees();
                    break;
                case 4:
                    view_qualifying_employees();
                    break;
                case 5:
                    view_disqualifying_employees();
                    break;
                case 6:
                    sort_employees_by_name();
                    break;
                case 7:
                    sort_employees_by_subsidy_amount();
                    break;
                case 8:
                    view_total_subsidy_amount();
                    break;
                case 9:
                    save_data();
                    break;
                case 10:
                    showAllEmployees(emp);
                    break;
            }
            flag = false;  // set flag to false and quit do while loop
        }
    } while (flag);  // keep looping while flag is true
}

void showAllEmployees(Employee *emp) {
    printf("\n********************************************************************************************\n%-10s %-15s %-15s %-10s %10s %10s %16s "
           "\n********************************************************************************************\n",
           "EMP CODE", "LAST NAME", "FIRST NAME", "INS WEEKS", "GROSS PAY", "SUBSIDY", "TOTAL SUBSIDY");

    for (int i = 0; i < fileSize; i++) {
        printf("%-10d %-15s %-15s %-10d %10.2f %10.2f  %15.2f\n", emp[i].employee_code, emp[i].employee_firstName,
               emp[i].employee_lastName, emp[i].insurable_weeks, emp[i].gross_pay, emp[i].subsidy, emp[i].subsidy_amount);
    }

}

void add_new_employee() {
    puts("Please enter employees code, first name, last name, insurable weeks and gross pay in that order");
    scanf("%d%s%s%d%f", &emp->employee_code, emp->employee_firstName, emp->employee_lastName, &emp->insurable_weeks, &emp->gross_pay);

    FILE *file = fopen("data.txt", "a+");
    fprintf(file, "%d %s %s %d %0.2f\n", emp->employee_code, emp->employee_firstName,
            emp->employee_lastName, emp->insurable_weeks, emp->gross_pay);

    fclose(file);
    puts("Thank you for your entry this has now been added to the file");
    display_menu();
}

void delete_employee() {
    int employeeCode = 0;
    puts("Please enter employees code to delete from records");
    scanf("%d", &employeeCode);

    int fileEnd = 0;
    FILE *fileRead = fopen("data.txt", "r");
    FILE *fileWrite = fopen("dataRemove.txt", "w");
    do {
        fileEnd = fscanf(fileRead, "%d%s%s%d%f", &emp->employee_code, emp->employee_firstName,
                         emp->employee_lastName, &emp->insurable_weeks, &emp->gross_pay);
        if (emp->employee_code != employeeCode) {
            fprintf(fileWrite, "%d %s %s %d %0.2f\n", emp->employee_code, emp->employee_firstName,
                    emp->employee_lastName, emp->insurable_weeks, emp->gross_pay);
        } else if (emp->employee_code == employeeCode) {
            printf("The record for employee code %d has been removed\n", employeeCode);
        } else {
            puts("Sorry that employee code is not recognised");
        }
    } while (fileEnd != EOF);

    fclose(fileRead);
    fclose(fileWrite);
    remove("data.txt");
    rename("dataRemove.txt", "data.txt");
    display_menu();
}

void view_all_employees() {
    int fileEnd=0;
    FILE* file = fopen("temp.txt", "r"); //initialise file pointer and open file to read
    printf("\n********************************************************************************************\n%-10s %-15s %-15s %-10s %10s %10s %16s "
           "\n********************************************************************************************\n",
           "EMP CODE", "LAST NAME", "FIRST NAME", "INS WEEKS", "GROSS PAY", "SUBSIDY", "TOTAL SUBSIDY");
    do {
        fileEnd = fscanf(file, "%d%s%s%d%f%f%f", &emp->employee_code, emp->employee_firstName,
                         emp->employee_lastName, &emp->insurable_weeks, &emp->gross_pay, &emp->subsidy, &emp->subsidy_amount);
        if (fileEnd != EOF) {
            printf("%-10d %-15s %-15s %-10d %10.2f %10.2f  %15.2f\n", emp->employee_code, emp->employee_firstName,
                   emp->employee_lastName, emp->insurable_weeks, emp->gross_pay, emp->subsidy, emp->subsidy_amount);
        }
    }  while (fileEnd != EOF);
    puts("********************************************************************************************\n");
    fclose(file);
    display_menu();
}

void view_qualifying_employees() {
    int fileEnd=0;
    FILE* file = fopen("temp.txt", "r"); //initialise file pointer and open file to read

        printf("\n********************************************************************************************\n%-10s %-15s %-15s %-10s %10s %10s %16s "
               "\n********************************************************************************************\n",
               "EMP CODE", "LAST NAME", "FIRST NAME", "INS WEEKS", "GROSS PAY", "SUBSIDY", "TOTAL SUBSIDY");
        do {
            fileEnd = fscanf(file, "%d%s%s%d%f%f%f", &emp->employee_code, emp->employee_firstName,
                             emp->employee_lastName, &emp->insurable_weeks, &emp->gross_pay, &emp->subsidy,
                             &emp->subsidy_amount);
            if (fileEnd != EOF && emp->subsidy > 0.00) {
                printf("%-10d %-15s %-15s %-10d %10.2f %10.2f  %15.2f\n", emp->employee_code, emp->employee_firstName,
                       emp->employee_lastName, emp->insurable_weeks, emp->gross_pay, emp->subsidy, emp->subsidy_amount);
            }
        } while (fileEnd != EOF);
        puts("********************************************************************************************\n");
        fclose(file);
    display_menu();
}

void view_disqualifying_employees() {
    int fileEnd=0;
    FILE* file = fopen("temp.txt", "r"); //initialise file pointer and open file to read

    printf("\n********************************************************************************************\n%-10s %-15s %-15s %-10s %10s %10s %16s "
           "\n********************************************************************************************\n",
           "EMP CODE", "LAST NAME", "FIRST NAME", "INS WEEKS", "GROSS PAY", "SUBSIDY", "TOTAL SUBSIDY");
    do {
        fileEnd = fscanf(file, "%d%s%s%d%f%f%f", &emp->employee_code, emp->employee_firstName,
                         emp->employee_lastName, &emp->insurable_weeks, &emp->gross_pay, &emp->subsidy,
                         &emp->subsidy_amount);
        if (fileEnd != EOF && emp->subsidy == 0.00) {
            printf("%-10d %-15s %-15s %-10d %10.2f %10.2f  %15.2f\n", emp->employee_code, emp->employee_firstName,
                   emp->employee_lastName, emp->insurable_weeks, emp->gross_pay, emp->subsidy, emp->subsidy_amount);
        }
    } while (fileEnd != EOF);
    puts("********************************************************************************************\n");
    fclose(file);
    display_menu();
}

void sort_employees_by_name() {

}
void sort_employees_by_subsidy_amount() {

}

void view_total_subsidy_amount() {
    float total_subsidy = 0.00;
    FILE* file = fopen("temp.txt", "r"); //initialise file pointer and open file to read
    while (!feof(file)) {
        fscanf(file, "%d%s%s%d%f%f%f", &emp->employee_code, emp->employee_firstName,
                 emp->employee_lastName, &emp->insurable_weeks, &emp->gross_pay, &emp->subsidy,
                 &emp->subsidy_amount);

        total_subsidy += emp->subsidy_amount;
    }
    printf("Total employee subsidy amount is €%.2f", total_subsidy);
    display_menu();
}


void save_data() {

    exit(0);
}

