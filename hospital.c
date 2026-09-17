#include<stdio.h>
#include "hospital.h"

const char *specialtyNames[]=
{
    "General practice(OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};
const float specialtyFees[]=
{
    1500.00,
    2500.00,
    4500.00,
    5000.00
};
const int consultationTime[]=
{
    15,
    20,
    30,
    30
};
const int dailyPatientCap[]=
{
    30,
    20,
    12,
    10
};
void displaySpecialties()
{
    int i;

    printf("\n");
    printf("=====================================\n");
    printf("      DOCTOR SPECIALTIES\n");
    printf("=====================================\n");

    for(i=0;i<4;i++)
    {
        printf("%d. %s\n",i+1,specialtyNames[i]);
        printf("     Consultation fee: LKR%.2f\n",specialtyFees[i]);
        printf("     Consultation time: %d minutes\n",consultationTime[i]);
        printf("     Daily patient cap: %d\n",dailyPatientCap[i]);
        printf("--------------------------------------\n");


    }
}

