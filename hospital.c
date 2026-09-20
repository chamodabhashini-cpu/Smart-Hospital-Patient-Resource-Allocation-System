#include<stdio.h>
#include "hospital.h"

#define MAX_PATIENTS 100

int bedOccupancy[4][20]={0};
char patientNames[MAX_PATIENTS][100];
int patientAges[MAX_PATIENTS];
int patientUrgency[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];
int patientAdmitted[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int patientDays[MAX_PATIENTS];
double patientWaitingTime[MAX_PATIENTS];
double patientSurcharge[MAX_PATIENTS];
double patientWardCost[MAX_PATIENTS];
double patientGrossTotal[MAX_PATIENTS];
double patientDiscount[MAX_PATIENTS];
double patientFinalPayable[MAX_PATIENTS];

int patientCount = 0;

int specialtyQueue[4]={0,0,0,0};


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
const float wardDailyRates[]=
    {
        3000.00,
        6000.00,
        12000.00,
        25000.00
    };
void displayWards()
{
    const char *wardNames[]=
    {
        "General ward",
        "Paediatric ward",
        "Surgical ward",
        "ICU"
    };
    const int bedCapacity[]=
    {
        20,
        10,
        10,
        05
    };


    int i;
    printf("\n");
    printf("==========================\n");
    printf("        HOSPITAL WARDS\n");
    printf("==========================\n");

    for(i=0;i<4;i++)
    {
        printf("%d. %s - Beds: %d - Daily rate: LKR %.2f\n",i+1,wardNames[i],bedCapacity[i],wardDailyRates[i]);
    }

    printf("===========================\n");
}

void displayBedStatus()
{

    int i,j;

    printf("\n");
    printf("=============================\n");
    printf("           HOSPITAL BED STATUS\n");
    printf("==============================\n");

    for(i=0;i<4;i++)
    {
        printf("\nWard %d:\n", i+1);
         for(j=0;j<20;j++)
         {
             if(bedOccupancy[i][j]==0)
             {
                 printf("Bed %02d :Available\n",j+1);
             }
             else
             {
                 printf("Bed %02d :Occupied\n",j+1);
             }
         }
         printf("---------------------------------\n");
    }
}

void registerPatient()
{

    int age;
    int urgencyLevel;
    int specialtyID;
    int isAdmitted;
    int wardID;
    int daysAdmitted;

    printf("\n");
    printf("=======================================\n");
    printf("       PATIENT REGISTRATION\n");
    printf("=======================================\n");

    printf("Enter patient name: ");
    scanf(" %[^\n]",patientNames[patientCount]);

    printf("Enter patient age: ");
    scanf("%d",&patientAges[patientCount]);

    printf("\nUrgency Level:\n");
    printf("1. Urgent\n");
    printf("2. Normal\n");
    printf("3. Critical\n");
    printf("Enter emergency level:");
    scanf("%d",&patientUrgency[patientCount]);


    printf("\nSpecialty:\n");
    printf("1. General practice(OPD)\n");
    printf("2. Paediatrics\n");
    printf("3. Cardiology\n");
    printf("4. Neurology\n");
    printf("Enter specialty ID:");
    scanf("%d",&patientSpecialty[patientCount]);

    patientSurcharge[patientCount]=calculateEmergencySurcharge(patientUrgency[patientCount],specialtyFees[patientSpecialty[patientCount]-1]);


    patientWaitingTime[patientCount] = calculateWaitingTime(patientSpecialty[patientCount]);
    specialtyQueue[patientSpecialty[patientCount] - 1]++;

    printf("\nIs admitted to ward?\n");
    printf("1=yes\n");
    printf("0=No\n");
    printf("Enter choice:");
    scanf("%d",&patientAdmitted[patientCount]);

    if(patientAdmitted[patientCount]==1)
    {
        printf("Enter ward ID(1-4): ");
        scanf("%d",&patientWard[patientCount]);

        printf("Enter number of days admitted: ");
        scanf("%d",&patientDays[patientCount]);

        patientWardCost[patientCount]=calculateWardStayCost(patientWard[patientCount],patientDays[patientCount]);

    }
    else
    {
        patientWard[patientCount] =0;
        patientDays[patientCount] =0;
        patientWardCost[patientCount] =0;

    }
    patientGrossTotal[patientCount]=calculateGrossTotal(specialtyFees[patientSpecialty[patientCount]-1],patientSurcharge[patientCount],patientWardCost[patientCount]);
    patientDiscount[patientCount]=calculateAgeDiscount(patientAges[patientCount],patientGrossTotal[patientCount]);
    patientFinalPayable[patientCount]=calculateFinalPayable(patientGrossTotal[patientCount],patientDiscount[patientCount]);

    printf("\n========================================\n");
    printf("        PATIENT REGISTRATION COMPLETE\n");
    printf("========================================\n");

    printf("Patient Name    : %s\n", patientNames[patientCount]);
    printf("Age             : %d\n", patientAges[patientCount]);
    printf("Urgency Level   : %d\n", patientUrgency[patientCount]);
    printf("Specialty ID    : %d\n", patientSpecialty[patientCount]);

    printf("Emergency Surcharge: LKR%.2f\n",patientSurcharge[patientCount]);

    printf("Estimated Waiting Time : %.2f mins\n",patientWaitingTime[patientCount]);

    printf("Ward stay cost: LKR%.2f\n",patientWardCost[patientCount]);

    printf("============================================\n");
    printf("Gross Total Bill    :LKR%.2f\n",patientGrossTotal[patientCount]);
    printf("Age subsidy discount:LKR-%.2f\n",patientDiscount[patientCount]);
    printf("Final amount payable:LKR%.2f\n",patientFinalPayable[patientCount]);

    if (patientAdmitted[patientCount] == 1)
    {
        printf("Ward ID       : %d\n", patientWard[patientCount]);
        printf("Days Admitted : %d\n", patientDays[patientCount]);
    }
    else
    {
        printf("Status        : Outpatient / OPD\n");
    }

    printf("========================================\n");

    patientCount++;
}
void displayPatients()
{
    int i;

    printf("\n");
    printf("\n========================================\n");
    printf("            REGISTERED PATIENTS\n");
    printf("==========================================\n");

    if (patientCount == 0)
    {
        printf("No patients registered.\n");
    }
    else
    {
        for (i = 0; i < patientCount; i++)
        {
            printf("\nPatient %d\n", i + 1);
            printf("Name          : %s\n", patientNames[i]);
            printf("Age           : %d\n", patientAges[i]);
            printf("Urgency Level : %d\n", patientUrgency[i]);
            printf("Specialty ID  : %d\n", patientSpecialty[i]);
            printf("Estimated Waiting Time : %.2f mins\n",patientWaitingTime[patientCount]);

            if (patientAdmitted[i] == 1)
            {
                printf("Ward ID       : %d\n", patientWard[i]);
                printf("Days Admitted : %d\n", patientDays[i]);
            }
            else
            {
                printf("Status        : Outpatient / OPD\n");
            }
        }
    }

    printf("\n============================================\n");
}

double calculateWaitingTime(int specialtyID)
{
    int averageTime;

    if(specialtyID==1)
    {
        averageTime = 15;
    }
    else if(specialtyID==2)
    {
        averageTime = 20;
    }
    else if(specialtyID==3)
    {
        averageTime = 30;
    }
    else if(specialtyID==4)
    {
        averageTime = 30;
    }
    else
    {
        return 0;
    }
    return specialtyQueue[specialtyID -1]*averageTime;
}
double calculateEmergencySurcharge(int urgencyLevel,double baseFee)
{
    if(urgencyLevel==1)
    {
        return 0;
    }
    else if (urgencyLevel==2)
    {
        return baseFee*0.20;
    }
    else if(urgencyLevel==3)
    {
        return baseFee*0.50;
    }
    else
    {
        return 0;
    }
}
double calculateWardStayCost(int wardID,int daysAdmitted)
{
    if(wardID<1||wardID>4||daysAdmitted<=0)
    {
        return 0;
    }
    return wardDailyRates[wardID -1]*daysAdmitted;
}

double calculateGrossTotal(double baseFee,double surCharge,double wardCost)
{
    return baseFee+surCharge+wardCost;
}

double calculateAgeDiscount(int age,double grossTotal)
{
    if(age<5 || age>65)
    {
        return grossTotal*0.15;
    }
    else
    {
        return 0;
    }
}

double calculateFinalPayable(double grossTotal,double discount)
{
    return grossTotal-discount;
}
void displayPatientsByPriority(void)
{
    int i,j,temp;
    int highestPriority;
    int order [MAX_PATIENTS];

    for(i=0;i<patientCount;i++)
    {
        order[i]=i;
    }

    for(i=0;i<patientCount-1;i++)
    {
        highestPriority=i;
        for(j=i+1;j<patientCount;j++)
        {
         if(patientUrgency[order[j]]>patientUrgency[order[highestPriority]])
        {
            highestPriority=j;
        }
        }

    temp=order[i];
    order[i]=order[highestPriority];
    order[highestPriority]=temp;
    }

    printf("\n");
    printf("=======================================\n");
    printf("        PATIENTS BY PRIORITY\n");
    printf("=======================================\n");

    for(i=0;i<patientCount;i++)
    {
       int index=order[i];
       printf("\nPatient%d\n",i+1);
       printf("Name          : %s\n", patientNames[index]);
        printf("Age           : %d\n", patientAges[index]);
        printf("Urgency Level : %d\n", patientUrgency[index]);
        printf("Specialty ID  : %d\n", patientSpecialty[index]);
        printf("Waiting Time : %.2f mins\n",patientWaitingTime[index]);

    }
    printf("======================================\n");

}
void displayPatientBill(void)
{
    int i;
    double baseFee;
    double surcharge;
    double wardCost;
    double grossTotal;
    double discount;
    double finalPayable;

    printf("\n");
    if(patientCount==0)
    {
        printf("No patients registered.\n");
        return;
    }
    for(i=0;i<patientCount;i++)
    {
        baseFee = specialtyFees[patientSpecialty[i] - 1];
        surcharge = calculateEmergencySurcharge(patientUrgency[i],baseFee);
        wardCost = calculateWardStayCost(patientWard[i],patientDays[i]);
        grossTotal = calculateGrossTotal(baseFee,surcharge,wardCost);
        discount = calculateAgeDiscount(patientAges[i],grossTotal);
        finalPayable = calculateFinalPayable(grossTotal,discount);

        printf("===========================================\n");
        printf("      SMART HOSPITAL ADMISSION & BILL\n");
        printf("-------------------------------------------\n");

        printf("Patient ID: PAT-%04d\n",100+i);
        printf("Patient Name:%s\n",patientNames[i]);
        printf("Age: %d Years\n",patientAges[i]);
         if(patientAges[i]<5 ||patientAges[i]>65 )
         {
             printf("(15%% Subsidy Eligible)\n");
         }

         printf("Specialty: %s\n",specialtyNames[patientSpecialty[i]-1]);
         if(patientAdmitted[i]==1)
         {
             printf("Assigned ward: Ward%d\n",patientWard[i]);
         }
         else
         {
             printf("Assigned Ward: Not Admitted\n");
         }
         printf("Urgency Level: Level%d\n",patientUrgency[i]);
         printf("---------------------------------------------\n");
         printf("Base Consultation Fee: LKR%.2f\n",baseFee);
         printf("Emergency Surcharge: LKR%.2f\n",surcharge);
         printf("Ward stay cost(%d days): LKR%.2f\n",patientDays[i],wardCost);
         printf("---------------------------------------------\n");
         printf("Gross Total Bill: LKR%.2f\n",grossTotal);
         printf("Age Subsidy Discount: LKR-%.2f\n",discount);
         printf("---------------------------------------------\n");
         printf("Final Payable Amount: LKR%.2f\n",finalPayable);
         printf("Estimated Waiting Time: %2f mins\n",patientWaitingTime[i]);
         printf("=============================================\n");
    }
}
void generateReports(void)
{
    int i;
    int urgentCount =0;
    int normalCount =0;
    int criticalCount =0;

    double totalRevenue =0;
    double totalDiscount =0;

    int wardCapacity[4] ={20,10,10,5};
    int occupiedBeds[4] ={0,0,0,0};

    int highestPatient =-1;
    double highestBill =0;

    for(i=0;i<patientCount;i++)
    {
        if(patientUrgency[i]==1)
        {
            urgentCount++;
        }
        else if(patientUrgency[i]==2)
        {
            normalCount++;
        }
        else if(patientUrgency[i]==3)
        {
            criticalCount++;
        }
        totalRevenue+=patientFinalPayable[i];
        totalDiscount+=patientDiscount[i];
        if(patientAdmitted[i]==1)
        {
            if(patientWard[i]>=1 && patientWard[i]<=4)
            {
                occupiedBeds[patientWard[i]-1]++;
            }
        }
        if(highestPatient ==-1 ||patientFinalPayable[i]>highestBill)
        {
            highestBill =patientFinalPayable[i];
            highestPatient=i;
        }
    }
    printf("\n");
    printf("====================================================\n");
    printf("          SMART HOSPITAL PERFORMANCE REPORT\n");
    printf("====================================================\n");

    printf("\n1. PATIENT SUMMARY\n");
    printf("----------------------------------------------------\n");
    printf("Total Patients Registered : %d\n", patientCount);
    printf("Urgent Patients           : %d\n", urgentCount);
    printf("Normal Patients           : %d\n", normalCount);
    printf("Critical Patients         : %d\n", criticalCount);

    printf("\n2. FINANCIAL SUMMARY\n");
    printf("----------------------------------------------------\n");
    printf("Total Revenue Earned      : LKR %.2f\n", totalRevenue);
    printf("Total Discounts Granted   : LKR %.2f\n", totalDiscount);

    printf("\n3. BED OCCUPANCY\n");
    printf("----------------------------------------------------\n");

    for(i=0;i<4;i++)
    {
        double occupancyPercentage = ((double)occupiedBeds[i]/wardCapacity[i])*100;
        printf("Ward %d: %d/%d beds occupied (%.2f%%)\n",i+1,occupiedBeds[i],wardCapacity[i],occupancyPercentage);
    }
    printf("\nHIGHEST PAYING PATIENT\n");
    printf("----------------------------------------------------\n");
    if(highestPatient==-1)
    {
        printf("No patients registered\n");

    }
    else
    {
        printf("Patient name: %s\n",patientNames[highestPatient]);
        printf("Total bill:   %.2f\n",patientFinalPayable[highestPatient]);
    }
     printf("----------------------------------------------------\n");
}
void saveData(void)
{
    FILE *file;
    int i;

    file=fopen("C:\\Users\\USER\\Desktop\\Smart hospital\\patient_records.txt","a");
    if(file==NULL)
    {
        printf("Error opening patient_records.txt\n");
        return;
    }
    for(i=0;i<patientCount;i++)
    {
        fprintf(file,"Patient:%s |Age:%d |Urgency:%d|"
                "Specialty:%d|Final bill: LKR%.2f\n",patientNames[i],patientAges[i],patientUrgency[i],patientSpecialty[i],patientFinalPayable[i]);
    }
    fclose(file);
    printf("Patient Records Saved Data Successfully.\n");

    file=fopen("C:\\Users\\USER\\Desktop\\Smart hospital\\beds_status.txt","w");
    if (file==NULL)
    {
        printf("Error opening beds_status.txt\n");
        return;
    }
    fprintf(file,"SMART HOSPITAL BEDS STATUS\n");
    fprintf(file,"--------------------------\n");
    int j;
    for(i=0;i<4;i++)
    {
        fprintf(file,"\nWard %d:\n",i+1);
        for(j=0;j<20;j++)
        {
            fprintf(file,"Bed %02d: %s\n",j+1,bedOccupancy[i][j]==0?"Available":"Occupied");
        }
    }
    fclose(file);
    printf("Bes Status Successfully\n");
}
