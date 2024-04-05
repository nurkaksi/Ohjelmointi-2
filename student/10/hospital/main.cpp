/**
 * HOSPITAL
 *
 *  This program is a hospital system where patients are admitted in and out
 *  and staff are recruited and added to patients care periods.
 *  Patients can come and leave from a care period multiple times.
 *  Patients can get medicine or it can be removed from them.
 *
 *  The commands available are:
 *    - HELP H: Prints all the commands available
 *    - RECRUIT R: Recruit a staff member (needs a name behind the command)
 *    - ENTER E: Sign in a patient to a care period
 *      (needs a name behind the command)
 *    - LEAVE L: Sing out a patient and close the care period
 *      (needs patients name behind the command)
 *    - ASSIGN_STAFF AS: Assign staff to a patients care period
 *      (needs staff name and patient name)
 *    - ADD_MEDICINE AM: Add medicine to patient
 *      (needs medicine name, strength, dosage and patient name)
 *    - REMOVE_MEDICINE RM: Remove medicine from patient
 *      (needs medicine name and patient name)
 *    - PRINT_PATIENT_INFO PPI: Print one patients care periods, staff
 *      and medicine (needs patient name)
 *    - PRINT_CARE_PERIODS PCPS: Prints care periods and patients the staff
 *      is in (needs staff name)
 *    - PRINT_ALL_MEDICINES PAM: Print all medicines and who it has been
 *      prescripted to
 *    - PRINT_ALL_STAFF PAS:
 *    - PRINT_ALL_PATIENTS PAP: Print all patients ever been in hospital,
 *      their care periods, staff and medicine
 *    - PRINT_CURRENT_PATIENTS PCP: Print patients info that are currently in
 *      the hospital, their open care period, staff and medicine
 *    - SET_DATE SD: Set a new date (needs day month year)
 *    - ADVANCE_DATE: Advance date forward (needs number how many days
 *      to go forward)
 *    - READ_FROM RF: Read from file (needs a file name)
 *    - QUIT Q: Quit program
 *
 * Program author
 * Name: Lotta Luomajärvi
 * Student ID: 152038946
 * Username: qhlolu
 * E-Mail: lotta.luomajarvi@tuni.fi
 * */



#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
