#include <iostream>
#include <vector>
#include <fstream>
#include "Resource.h"
#include "ReservationManager.h"

std::string findResourcesFile()
{
    std::vector<std::string> candidates = {
        "data/resources.txt",
        "../data/resources.txt",
        "../../data/resources.txt"
    };

    for (size_t i = 0; i < candidates.size(); i++)
    {
        std::ifstream test(candidates[i]);
        if (test.good())
        {
            return candidates[i];
        }
    }

    return candidates[0];
}

int main()
{
    ReservationManager manager;
    manager.loadReservations("data/reservations.txt");

    std::vector<Resource> resources = loadResources(findResourcesFile());
    int choice = 0;

    while (choice != 9)
    {
        std::cout << std::endl;
        std::cout << "===== Campus Resource Reservation System =====" << std::endl;
        std::cout << "1. View Resources" << std::endl;
        std::cout << "2. Create Reservation" << std::endl;
        std::cout << "3. Cancel Reservation" << std::endl;
        std::cout << "4. View Waiting Lists" << std::endl;
        std::cout << "5. Undo Cancellation" << std::endl;
        std::cout << "6. Show Reservations" << std::endl;
        std::cout << "7. Sort Resources" << std::endl;
        std::cout << "8. Generate Report" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter Choice: ";

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input." << std::endl;
            continue;
        }

        switch (choice)
        {
            case 1:
                std::cout << std::endl;
                displayResources(resources);
                std::cout << std::endl;
                displayAvailability(resources);
                break;
            case 2:
            {
                int reservationID = manager.getReservationID();
                int userID;
                std::string name;
                std::string resourceID;
                std::string date;
                std::cout << "Enter user ID: ";
                std::cin >> userID;
                std::cout << "Enter Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter Resource ID: ";
                std::cin >> resourceID;
                std::cout << "Enter Date (MM/DD/YYYY): ";
                std::cin >> date;

                Reservation reservation(reservationID, userID, name, resourceID, date);
                if (manager.createReservation(reservation)) {
                    std::cout << "Reservation created successfully!" << std::endl;
                }
                break;
            }
            case 3:
                int reservationID;
                std::cout << "Enter reservation ID (Enter -1 to go back): ";
                std::cin >> reservationID;
                if (reservationID == -1) break;
                if (!manager.cancelReservation(reservationID)) {
                    std::cout << "No such reservation found." << std::endl;
                }
                break;
            case 4:
                std::cout << "View Waiting Lists is not implemented yet." << std::endl;
                break;
            case 5:
                manager.undoCancelledReservation();
                break;
            case 6:
                manager.displayReservations();
                break;
            case 7:
                std::cout << "Sort Resources is not implemented yet." << std::endl;
                break;
            case 8:
                std::cout << "Generate Report is not implemented yet." << std::endl;
                break;
            case 9:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
                break;
        }
    }

    return 0;
}
