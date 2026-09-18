#include <iostream>
#include <vector>
#include <fstream>
#include "Resource.h"

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
        std::cout << "6. Search Reservations" << std::endl;
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
                std::cout << "Create Reservation is not implemented yet." << std::endl;
                break;
            case 3:
                std::cout << "Cancel Reservation is not implemented yet." << std::endl;
                break;
            case 4:
                std::cout << "View Waiting Lists is not implemented yet." << std::endl;
                break;
            case 5:
                std::cout << "Undo Cancellation is not implemented yet." << std::endl;
                break;
            case 6:
                std::cout << "Search Reservations is not implemented yet." << std::endl;
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
