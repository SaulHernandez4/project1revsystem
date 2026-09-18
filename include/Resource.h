#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>

class Resource
{
private:
    std::string id;
    std::string name;
    std::string type;
    std::string status;

public:
    Resource();
    Resource(std::string id, std::string name, std::string type, std::string status);

    std::string getId() const;
    std::string getName() const;
    std::string getType() const;
    std::string getStatus() const;

    void setStatus(std::string newStatus);
};

std::vector<Resource> loadResources(const std::string& filename);
void displayResources(const std::vector<Resource>& resources);
void displayAvailability(const std::vector<Resource>& resources);

#endif
