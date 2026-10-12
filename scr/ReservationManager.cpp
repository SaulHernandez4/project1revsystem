#include "ReservationManager.h"
#include "Reservation.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stack>

ReservationManager::ReservationManager() {
	head = nullptr;
	tail = nullptr;
	nextReservationID = 301;

}

ReservationManager::~ReservationManager() {
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
}

void ReservationManager::loadReservations(const std::string& filename) {

	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cout << "Error: could not open file " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}

		std::stringstream ss(line);

		std::string reservationID;
		std::string userID;
		std::string name;
		std::string resourceID;
		std::string date;

		std::getline(ss, reservationID, '|');
		std::getline(ss, userID, '|');
		std::getline(ss, name, '|');
		std::getline(ss, resourceID, '|');
		std::getline(ss, date, '|');

		Reservation reservation(std::stoi(reservationID), std::stoi(userID), name, resourceID, date);

		Node* newNode = new Node;
		newNode->reservation = reservation;
		newNode->next = nullptr;

		if (reservation.getReservationID() >= nextReservationID) {
			nextReservationID = reservation.getReservationID() + 1;
		}

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
		}

	}
	file.close();
}

bool ReservationManager::createReservation(const Reservation& reservation, std::vector<Resource>& resources) {

	
	Node* current = head;
	if (!validateReservation(reservation)) {
		return false;
	}
	bool found = false;
	//waiting list integration

	for (Resource& resource : resources) {
		if (resource.getId() == reservation.getResourceID()) {
			found = true;
			if (resource.getStatus() == "Unavailable") {
				std::cout << "Resource is already reserved. Adding to waiting list..." << std::endl;
				addToWaitingList(reservation.getResourceID(), reservation.getUserID(), reservation.getName(), reservation.getDate());
				return false;
			}
			else resource.setStatus("Unavailable");
			break;
		}
	}
	
	if (!found) {
		std::cout << "Error: Invalid resource ID." << std::endl;
		return false;
	}
	//waiting list end


	Node* newNode = new Node;
	newNode->reservation = reservation;
	newNode->next = nullptr;

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
	if (reservation.getReservationID() >= nextReservationID) {
		nextReservationID = reservation.getReservationID() + 1;
	}
	return true;
}

bool ReservationManager::cancelReservation(int reservationID, std::vector<Resource>& resources) {
	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr) {
		if (current->reservation.getReservationID() == reservationID) {


			cancelledReservations.push(current->reservation);

			if (previous == nullptr) {
				head = current->next;
			} else {
				previous->next = current->next;
			}

			if (current == tail) {
				tail = previous;
			}

			//Waiting list cancellation
			std::string resourceID = current -> reservation.getResourceID();

			delete current;

			bool stillBooked = false;
			for (Node* n = head;n != nullptr;n = n->next) {
				if (n->reservation.getResourceID() == resourceID) {
					stillBooked = true;
					break;
				}
			}

			std::cout << "Reservation cancelled successfully." << std::endl;

			if (!stillBooked) {
				for (Resource& resource : resources) {
					if (resource.getId() == resourceID) {
						resource.setStatus("Available");
						break;
					}
				}
				processWaitingList(resourceID, resources);
			}

			return true;
		}

		previous = current;
		current = current->next;
	}
	return false;
}

void ReservationManager::displayReservation(const Reservation& reservation) const {
	std::cout << "Reservation ID: " << reservation.getReservationID() << std::endl;
	std::cout << "User ID: " << reservation.getUserID() << std::endl;
	std::cout << "Name: " << reservation.getName() << std::endl;
	std::cout << "Resource ID: " << reservation.getResourceID() << std::endl;
	std::cout << "Date: " << reservation.getDate() << std::endl;
	std::cout << "-----------------------------" << std::endl;
}

void ReservationManager::displayReservations() const {
	Node* current = head;
	std::cout << "-----------------------------" << std::endl;
	while (current != nullptr) {
		displayReservation(current->reservation);
		current = current->next;
	}
}

bool ReservationManager::validateReservation(const Reservation& reservation) const {
	Node* current = head;
	while (current != nullptr) {
		if (current->reservation.getReservationID() == reservation.getReservationID()) {
			std::cout << "Error: Reservation ID already exists." << std::endl;
			return false;
			
		}
		current = current->next;
	}
	if (reservation.getUserID() <= 0) {
		std::cout << "Error: Invalid user ID." << std::endl;
		return false;
	}
	if (reservation.getName().empty()) {
		std::cout<< "Error. Name cannot be empty." << std::endl;
		return false;
	}
	if (reservation.getResourceID().empty()) {
		std::cout << "Error: Resource ID cannot be empty." << std::endl;
		return false;
	}
	if (reservation.getDate().empty()) {
		std::cout << "Error: Date cannot be empty." << std::endl;	
		return false;
	}
	return true;

}

ReservationManager::WaitingList*
ReservationManager::findWaitingList(std::string resourceID) {
	for (size_t i = 0; i < waitingLists.size(); i++) {
		if (waitingLists[i].resourceID == resourceID) {
			return &waitingLists[i];
		}
	} 
	return nullptr;
}

void ReservationManager::addToWaitingList(std::string resourceID, int userID, std::string name, std::string date) {
	WaitingList* list = findWaitingList(resourceID);

	if (list == nullptr) {
		WaitingList newList;
		newList.resourceID = resourceID;
		waitingLists.push_back(newList);
		list = &waitingLists.back();
	}

	WaitingStudent student;

	student.userID = userID;
	student.name = name;
	student.date = date;

	list -> students.push(student);

	std::cout << "Student added to waitlist." << std::endl;
	std::cout << "Current position: " << list->students.size() << std::endl;
}

void ReservationManager::processWaitingList(std::string resourceID, std::vector<Resource>& resources) {
	//WIP

	WaitingList* list = findWaitingList(resourceID);

	if (list == nullptr || list->students.empty()) {
		return;
	}
	
	bool available = false;

	for (Resource& resource : resources) {
		if (resource.getId() == resourceID) {
			if (resource.getStatus() == "Available") {
				available = true;
			}
			break;
		}
	}
	
	if(!available) {
		return;
	}

	WaitingStudent student = list -> students.front();

	int newReservationID = getReservationID();

	Reservation reservation (newReservationID, student.userID, student.name, resourceID, student.date);
	
	if (createReservation(reservation, resources)) {
		list -> students.pop();
		std::cout << "Waiting-list reservation created successfully" << std::endl;
		std::cout << "Reservation ID: " << newReservationID << std::endl;
		std::cout << "Student: " << student.name << std::endl;
	}

}

void ReservationManager::displayWaitingList() {
	std::cout << std::endl;
	std::cout << "===== Waiting List =====";
	std::cout << std::endl;

	if (waitingLists.empty()) {
		std::cout << "No waiting lists exist." << std::endl;
		return;
	}

	for (size_t i = 0; i < waitingLists.size(); i++) {
		std::cout << std::endl << "Resource: " << waitingLists[i].resourceID << std::endl;
		std::cout << "Students waiting: " << waitingLists[i].students.size() << std::endl;

		if (waitingLists[i].students.empty()) {
			std::cout << "Waiting list: Empty" << std::endl;
			continue;
		}

		std::queue<WaitingStudent> temp = waitingLists[i].students;
		int position = 1;

		while (!temp.empty()) {
			WaitingStudent student = temp.front();
			temp.pop();

			std::cout << position << ". " << student.name << " (Student ID: " << student.userID << ") - Date: " << student.date << std::endl;

			position++;
		}
	}
}

int ReservationManager::getReservationID() const {
	return nextReservationID;
}

void ReservationManager::undoCancelledReservation(std::vector<Resource>& resources) {
	if (cancelledReservations.empty()) {
		std::cout << "No cancelled reservations to undo." << std::endl;
		return;
	}

	Reservation reservation = cancelledReservations.top();

	for (Node* n = head;n != nullptr;n = n->next) {
		if (n->reservation.getReservationID() == reservation.getReservationID()) {
			std::cout << "Cannot undo: Reservation ID already exists." << std::endl;
			return;
		}
	}

	for (Resource& resource : resources) {
		if (resource.getId() == reservation.getResourceID()) {
			if (resource.getStatus() == "Unavailable") {
				std::cout << "Cannot undo: Resource is currently reserved." << std::endl;
				return;
			}
			resource.setStatus("Unavailable");
			break;
		}
	}

	cancelledReservations.pop();

	Node* newNode = new Node;
	newNode->reservation = reservation;
	newNode->next = nullptr;

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
	std::cout << "Reservation " << reservation.getReservationID() << " has been restored." << std::endl;
	return;
}


void ReservationManager::displayCancelledReservations() const {
	if (cancelledReservations.empty()) {
		std::cout << "No cancelled reservations." << std::endl;
		return;
	}

	std::stack<Reservation> temp = cancelledReservations;
	std::cout << "\n    Cancelled Reservations   " << std::endl;
	std::cout << "-----------------------------" << std::endl;
	while (!temp.empty()) {
		displayReservation(temp.top());
		temp.pop();
	}
	return;
}

void ReservationManager::generateReport(const std::vector<Resource>& resources) const {
	std::cout << std::endl << "========================================" << std::endl;
	std::cout << "       CAMPUS SYSTEM REPORT" << std::endl;
	std::cout << "========================================" << std::endl;

	int totalReservations = 0;

	Node* current = head;

	while (current != nullptr) {
		totalReservations++;
		current = current -> next;
	}

	std::cout << std::endl << "Total Active Reservations: " << totalReservations << std::endl;
	std::cout << std::endl << "--- Active Reservations ---" << std::endl;

	if (head == nullptr) {
		std::cout << "No active reservations." << std::endl;
	}
	else {
		displayReservations();
	}
	
	std::cout << std::endl << "--- Resource Utilization ---" << std::endl;

	int highestDemand = 0;
	std::string mostRequestedResource = "None";
	int totalWaiting = 0;

	for (const Resource& resource : resources) {
		int reservationCount = 0;
		current = head;

		while (current != nullptr) {
			if (current -> reservation.getResourceID() == resource.getId()) {
				reservationCount++;
			}
			current = current -> next;
		}

		int waitingCount = 0;

		for (const WaitingList& list : waitingLists) {
			if (list.resourceID == resource.getId()) {
				waitingCount = static_cast<int>(list.students.size());
				break;
			}
		}

		int demand = reservationCount + waitingCount;
		totalWaiting += waitingCount;

		std::cout << std::endl << "Resource: " << resource.getName() << " (" << resource.getId() << ")" << std::endl;
		std::cout << "Status: " << resource.getStatus() << std::endl;
		std::cout << "Active Reservations: " << reservationCount << std::endl;
		std::cout << "Students Waiting: " << waitingCount << std::endl;

		if (demand > highestDemand) {
			highestDemand = demand;
			mostRequestedResource = resource.getName();
		}
	}

	std::cout << std::endl << "--- Most Requested Resource ---" << std::endl;

	if (highestDemand == 0) {
		std::cout << "No current resource demand." << std::endl;
	}
	else {
		std::cout << "Resource: " << mostRequestedResource << std::endl;
		std::cout << "Current Demand: " << highestDemand << std::endl;
	}

	std::cout << std::endl << "--- Waiting List Statistics ---" << std::endl;

	if (waitingLists.empty()) {
		std::cout << "No waiting lists exist." << std::endl;
	}
	else {
		for (const WaitingList& list : waitingLists) {
			std::cout << "Resource: " << list.resourceID << " | Students Waiting: " << list.students.size() << std::endl;
		}
	}

	std::cout << "Total Students Waiting: " << totalWaiting << std::endl;

	std::cout << std::endl << "========================================" << std::endl;
	std::cout << "          END OF REPORT" << std::endl;
	std::cout << std::endl << "========================================" << std::endl;

}

bool ReservationManager::searchReservationByID(int reservationID) const {
	Node* current = head;
	while (current != nullptr) {
		if (current->reservation.getReservationID() == reservationID) {
			std::cout << "-----------------------------" << std::endl;
			displayReservation(current->reservation);
			return true;
		}
		current = current->next;
	}
	return false;
}

int ReservationManager::searchReservationsByStudent(int userID) const {
	int count = 0;
	Node* current = head;
	while (current != nullptr) {
		if (current->reservation.getUserID() == userID) {
			std::cout << "-----------------------------" << std::endl;
			displayReservation(current->reservation);
			count++;
		}
		current = current->next;
	}
	return count;
}