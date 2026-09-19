#ifndef HOPITAL_H
#define HOSPITAL_H

void displaySpecialties();
void displayWards();
void displayBedStatus();
void registerPatient();
void displayPatients();

double calculateWaitingTime(int specialtyID);
double calculateEmergencySurcharge(int urgencyLevel,double baseFee);
double calculateWardStayCost(int wardID,int daysAdmitted);

#endif
