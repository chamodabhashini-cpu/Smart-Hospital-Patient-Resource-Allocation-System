#include <stdio.h>
#include "hospital.h"

void displayMenu()
{
    printf("\n");
    printf("=======================================\n");
    printf("        SMART HOSPITAL SYSTEM\n");
    printf("=======================================\n");
    printf("1.Register patient\n");
    printf("2.Display patient bill\n");
    printf("3.Display bed status\n");
    printf("4.Display patients by priority\n");
    printf("5.Generate reports\n");
    printf("6.Save data\n");
    printf("7.Exit\n");
    printf("=======================================\n");
}

int main()
{
    int choice;

        do
        {
            displayMenu();

            printf("Enter choice:");
            scanf("%d",&choice);

            switch (choice)
            {
            case 1:
                registerPatient();
                break;

            case 2:
                displayPatientBill();
                break;

            case 3:
                displayBedStatus();
                break;

            case 4:
                displayPatientsByPriority();
                break;

            case 5:
                generateReports();
                break;

            case 6:
                saveData();
                break;

            case 7:
                printf("Exiting smart hospital system...\n");
                break;

            default:
                printf("Invalid choice.Please try again..\n");
            }
        }while(choice != 7);

    return 0;
}
