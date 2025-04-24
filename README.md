This repository contains the source code and data files for a **C-based Hospital Management System (HMS)** developed as part of a group assignment for the **Introduction to C Programming** module.

## ❗Overview

The **Hospital Management System (HMS)** is a terminal-based application designed to simulate core hospital operations. It serves various roles, **Administrator**, **Doctor**, **Patient**, and **Staff Nurse**, each with specific functionalities. This system emphasizes modular programming, file-based data storage, and secure access protocols, aligning with best practices in C application development.

## Features

### 🔐Login System
- Role-based login for Administrator, Doctor, Patient, and Nurse.
- Three (3) login attempts limit before access lock.

### 👨‍⚕️Administrator Features
- Register new users: **Patients, Doctors, Nurses**
- Assign patients to doctors (with appointment time)
- Manage inventory (view/search medical supplies and medications)
- View appointment trends to optimize staffing schedules

### 👩‍⚕️Doctor Features
- Manage doctor availability/schedules
- View complete patient Electronic Health Records (EHR)
- Generate reports on treatment trends and patient progress

### 🧑‍🦰Patient Features
- View/reschedule/cancel appointments
- View portions of their medical history, prescriptions, billing info (read-only)
- Billing overview and insurance claim status

### 👩‍⚕️Staff Nurse Features
- Access doctor schedules for coordination
- Manage local inventory (nurse’s station)
- Generate reports on patients or care units for analysis

## Data Storage & Structure
- Data is stored in plain `.txt` files for simplicity and portability
- Role-based login credentials are stored in `users.txt`
- Inventory, appointments, schedules, EHR, and billing are stored in dedicated text files
- System is entirely terminal-based with no GUI


## ❓ How to Compile and Run
1. Download source (`Hospital_Management_System_Final.c`,) and text (`.txt`) files.
2. Use any C compiler to compile.
3. Run the main `.c` file.


