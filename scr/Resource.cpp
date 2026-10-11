#include "Resource.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

Resource::Resource()
{
    id = "";
    name = "";
    type = "";
    status = "";
}

Resource::Resource(std::string id, std::string name, std::string type, std::string status)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->status = status;
}

std::string Resource::getId() const
{
    return id;
}

std::string Resource::getName() const
{
    return name;
}

std::string Resource::getType() const
{
    return type;
}

std::string Resource::getStatus() const
{
    return status;
}

void Resource::setStatus(std::string newStatus)
{
    status = newStatus;
}

std::vector<Resource> loadResources(const std::string& filename)
{
    std::vector<Resource> resources;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Error: could not open file " << filename << std::endl;
        return resources;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string id, name, type, status;

        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, type, '|');
        std::getline(ss, status, '|');

        resources.push_back(Resource(id, name, type, status));
    }

    file.close();
    return resources;
}

void displayResources(const std::vector<Resource>& resources)
{
    if (resources.empty())
    {
        std::cout << "No resources available." << std::endl;
        return;
    }

    std::cout << std::left
               << std::setw(10) << "ID"
               << std::setw(20) << "Name"
               << std::setw(24) << "Type"
               << std::setw(15) << "Status" << std::endl;

    for (size_t i = 0; i < resources.size(); i++)
    {
        std::cout << std::left
                   << std::setw(10) << resources[i].getId()
                   << std::setw(20) << resources[i].getName()
                   << std::setw(24) << resources[i].getType()
                   << std::setw(15) << resources[i].getStatus() << std::endl;
    }
}

void displayAvailability(const std::vector<Resource>& resources)
{
    if (resources.empty())
    {
        std::cout << "No resources available." << std::endl;
        return;
    }

    std::cout << std::left
               << std::setw(10) << "ID"
               << std::setw(20) << "Name"
               << std::setw(15) << "Status" << std::endl;

    for (size_t i = 0; i < resources.size(); i++)
    {
        std::cout << std::left
                   << std::setw(10) << resources[i].getId()
                   << std::setw(20) << resources[i].getName()
                   << std::setw(15) << resources[i].getStatus() << std::endl;
    }
}

// quick sorting!

void quickSort(std::vector<Resource>& resources, int field)
{
    if (resources.size() < 2) return;
    quickSortHelper(resources, 0, (int)resources.size() - 1, field);
}

void quickSortHelper(std::vector<Resource>& resources, int low, int high, int field)
{
    if (low < high) {
        int p = partitionResources(resources, low, high, field);
        quickSortHelper(resources, low, p - 1, field);
        quickSortHelper(resources, p + 1, high, field);
    }
}

void swapResources(Resource& a, Resource& b)
{
    Resource temp = a;
    a = b;
    b = temp;
}

bool comesBefore(const Resource& a, const Resource& b, int field)
{
    // 1=resourceid
    // 2=name
    // 3=popularity
    switch (field)
    {
    case 1: return a.getId() < b.getId();
    case 2: return a.getName() < b.getName();
    default: return a.getStatus() < b.getStatus();
    }
}

int partitionResources(std::vector<Resource>& resources, int low, int high, int field)
{
    Resource pivot = resources[high];
    int i = low - 1;

    for (int j = low;j < high;j++) {
        if (comesBefore(resources[j], pivot, field)) {
            i++;
            swapResources(resources[i], resources[j]);
        }
    }
    swapResources(resources[i + 1], resources[high]);
    return i+1;
}
