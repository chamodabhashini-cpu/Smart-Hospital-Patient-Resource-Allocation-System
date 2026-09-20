#ifndef HOPITAL_H
#define HOSPITAL_H

void displaySpecialties();
void displayWards();
void displayBedStatus();
void registerPatient();
void displayPatients();
void displayPatientsByPriority(void);
void displayPatientBill(void);

double calculateWaitingTime(int specialtyID);
double calculateEmergencySurcharge(int urgencyLevel,double baseFee);
double calculateWardStayCost(int wardID,int daysAdmitted);
double calculateGrossTotal(double baseFee,double surCharge,double wardCost);
double calculateAgeDiscount(int age,double grossTotal);
double calculateFinalPayable(double grossTotal,double discount);

#endif
