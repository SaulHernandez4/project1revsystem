================================================================================
CAMPUS RESOURCE RESERVATION SYSTEM
Project 1 - C++ CLI Project
================================================================================

OVERVIEW
--------------------------------------------------------------------------------
A console-based reservation system for shared campus resources such as study
rooms, laptops, calculators, lab equipment, and tutoring appointments.

Students can reserve a resource. If it is already taken, they are placed in a
first-come, first-served waiting list. When a reservation is cancelled, the next
student in line is automatically given the resource. Cancelled reservations are
kept on a stack so the most recent cancellation can be undone.

The project applies object-oriented programming and core data structures
(linked list, queue, stack) to a realistic problem, with data loaded from
plain-text files.


TEAM / AUTHORS
--------------------------------------------------------------------------------
Course:      CSCE 2110
Instructor:  Mokarram
Semester:    Fall 2026
Team:        Saul Hernandez, Cooper Gounah, Colin Segovia

FEATURES
--------------------------------------------------------------------------------
Resource Management
  - Loads resources from data/resources.txt
  - Displays all resources (ID, name, type, status) and a quick availability view
  - Resource types: Study Room, Laptop, Calculator, Lab Equipment,
    Tutoring Appointment
  - Sort resources by a user-selected criterion
  - Search resources and reservations

Reservation Management
  - Loads existing reservations from data/reservations.txt
  - Create a reservation (user ID, name, resource ID, date)
  - Cancel a reservation by reservation ID
  - View and search current reservations
  - Input validation (duplicate reservation ID, invalid user ID, empty name /
    resource ID / date, unknown resource ID)

Waiting List
  - If a requested resource is unavailable, the student joins that resource's
    waiting queue and is shown their position
  - Queues are FIFO (first in, first out)
  - When a resource is freed by a cancellation, the student at the front of
    its queue is automatically assigned a new reservation

Cancellation History / Undo
  - Cancelled reservations are pushed onto a stack
  - "Undo Cancellation" restores only the most recently cancelled reservation
    (and is refused if the resource has since been reserved by someone else)
  - View the full cancellation history

Reporting
  - Most frequently reserved resources
  - Current resource availability
  - Number of active reservations
  - Waiting list report


PROJECT STRUCTURE
--------------------------------------------------------------------------------
project1revsystem/
|
|-- include/                    Header files (class declarations)
|     |-- Resource.h
|     |-- Reservation.h
|     |-- ReservationManager.h
|
|-- scr/                        Source files (implementations + main)
|     |-- main.cpp              Menu loop and user input
|     |-- Resource.cpp          Resource class + load/display helpers
|     |-- Reservation.cpp       Reservation class
|     |-- ReservationManager.cpp  Reservation, waiting list, and undo logic
|
|-- data/
|     |-- resources.txt         Resource input file
|     |-- reservations.txt      Reservation input file
|
|-- README.txt
|-- .gitignore

Note: the source folder is named "scr" in this repository.


CLASSES AND DATA STRUCTURES
--------------------------------------------------------------------------------
Resource
  Stores ID, name, type, and availability status. Also has free functions
  loadResources(), displayResources(), and displayAvailability().

Reservation
  Stores reservation ID, user (student) ID, student name, resource ID, and date.

ReservationManager
  Core logic of the system. Owns:
    - A singly linked list (head/tail Node pointers) of active reservations
    - A std::stack<Reservation> of cancelled reservations (undo history)
    - A std::vector of per-resource waiting lists, each holding a
      std::queue of waiting students
  Handles creating, cancelling, validating, displaying, undoing, and
  auto-assigning reservations from the waiting list. The destructor frees
  all linked-list nodes.

Data structure summary:
  Structure            Used for                          Behavior
  -------------------  --------------------------------  ----------------------
  Linked list          Active reservations               Append at tail, remove
                                                         by ID
  Queue (std::queue)   Waiting list per resource         FIFO
  Stack (std::stack)   Cancellation history              LIFO (undo latest)


REQUIREMENTS
--------------------------------------------------------------------------------
  - A C++ compiler with C++11 or newer support (g++ recommended)
  - Works on Windows, Linux, or macOS


HOW TO BUILD
--------------------------------------------------------------------------------
From the project's root folder (the one containing include/, scr/, and data/):

  g++ -std=c++11 -I include scr/main.cpp scr/Resource.cpp scr/Reservation.cpp scr/ReservationManager.cpp -o main

All four .cpp files must be compiled. Visual Studio users can instead add the
files from scr/ and include/ to a project and set "include" as an additional
include directory.


HOW TO RUN
--------------------------------------------------------------------------------
Run the program from the project's ROOT folder so it can find the data files
(it looks for data/reservations.txt relative to the working directory):

  Windows:        main.exe
  Linux / macOS:  ./main


USING THE PROGRAM
--------------------------------------------------------------------------------
Main menu:

   1. View Resources            Show all resources and availability
   2. Create Reservation        Enter user ID, name, resource ID, date
   3. Cancel Reservation        Enter a reservation ID (-1 to go back)
   4. View Waiting Lists        Show queued students for each resource
   5. Undo Cancellation         Restore the most recent cancellation
   6. Show Reservations         List all active reservations
   7. Sort Resources            Sort resources by a chosen criterion
   8. Generate Report           Usage, availability, and waiting list reports
   9. Show Cancellation History List cancelled reservations
  10. Exit

Example session:
  1. Choose 2 (Create Reservation) for resource R103, which is "Unavailable".
     The student is added to R103's waiting list.
  2. Choose 3 and cancel the existing reservation for R103 (e.g., ID 302).
  3. The resource is freed and the waiting student is automatically assigned
     a new reservation.
  4. Choose 5 to undo the cancellation if desired.

Dates are entered as MM/DD/YYYY.


DATA FILE FORMATS
--------------------------------------------------------------------------------
Fields are separated by the pipe character ( | ), one record per line.

data/resources.txt
  ResourceID|ResourceName|ResourceType|Status
  Example:  R101|Study Room 101|Study Room|Available
  Status is either "Available" or "Unavailable".

data/reservations.txt
  ReservationID|StudentID|StudentName|ResourceID|Date
  Example:  301|1001|Alice Smith|R101|09/15/2026

Blank lines are skipped. New reservation IDs continue from the highest ID found
in the file.


VERSION CONTROL
--------------------------------------------------------------------------------
Developed collaboratively using Git and GitHub. Build outputs (*.exe, *.o) and
IDE folders (.vs/, .vscode/) are excluded through .gitignore.

================================================================================
