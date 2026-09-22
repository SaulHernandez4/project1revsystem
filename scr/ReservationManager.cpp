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

}

ReservationManager::~ReservationManager() {
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

bool ReservationManager::createReservation(const Reservation& reservation) {
	if (!validateReservation(reservation)) {
		return false;
	}
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
	return true;
}

bool ReservationManager::cancelReservation(int reservationID) {
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

			delete current;
			std::cout << "Reservation cancelled successfully." << std::endl;
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

	while (current != nullptr) {
		displayReservation(current->reservation);
		current = current->next;
	}
}

bool ReservationManager::validateReservation(const Reservation& reservation) const {
	Node* current = head;
	while (current != nullptr) {
		if (current->reservation.getReservationID() == reservation.getReservationID()) {
			std::cout << "Error: Reservation ID already exists.";
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
	while (current!=nullptr) {
		if (current->reservation.getResourceID() == reservation.getResourceID() && current->reservation.getDate() == reservation.getDate()) {
			std::cout << "Error: Resource is already reserved on that date." << std::endl;
			return false;
		}

		current = current->next;
	}
	return true;

}

ReservationManager::WaitingList*
ReservationManager::findWaitingList(std::string resourceID) {
	for (int i = 0; i < waitingLists.size(); i++) {
		if (waitingLists[i].resourceID == resourceID) {
			return &waitingLists[i];
		}
	} 
	return nullptr;
}

void ReservationManager::addToWaitingList(std::string resourceID, int userID, std::string name, std::string date) {
	WaitingList* list = findWaitingList(resourceID);

	if (list == nullptr) {
		std::cout << "Error: Waiting list not found." << std::endl;
		return;
	}

	WaitingStudent student;

	student.userID = userID;
	student.name = name;
	student.date = date;

	list -> students.push(student);

	std::cout << "Student added to waitlist." << std::endl;
	std::cout << "Current position: " << list->students.size() << std::endl;
}

void ReservationManager::processWaitingList(std::string resourceID) {
	//WIP

	WaitingList* list = findWaitingList(resourceID);

	if (list == nullptr) {
		return;
	}
	if (list -> students.empty()) {
		return;
	}

	//resource* resource
	//if nullptr, return

	WaitingStudent student = list -> students.front();
	list -> students.pop();

	int newReservationID = 1;

	//reservations

}

void ReservationManager::displayWaitingList() {
	std::cout << std::endl;
	std::cout << "===== Waiting List =====";
	std::cout << std::endl;

	for (int i = 0; i < waitingLists.size(); i++) {
		std::cout << std::endl << "Resource: " << waitingLists[i].resourceID << std::endl;

		if (waitingLists[i].students.empty()) {
			std::cout << "Waitlist: Empty" << std::endl;

			continue;
		}

		std::queue<WaitingStudent> temp = waitingLists[i].students;

		int position = 1;

		while (!temp.empty()) {
			WaitingStudent student = temp.front();
			temp.pop();

			std::cout << position << ". " << student.name << " (Student ID: " << student.userID << ")" << std::endl;

			position++;
		}
	}
}

int ReservationManager::getReservationID() const {
	if (tail == nullptr) {
		return 301;
	}

	return tail->reservation.getReservationID() + 1;
}

void ReservationManager::undoCancelledReservation() {
	if (cancelledReservations.empty()) {
		std::cout << "No cancelled reservations to undo." << std::endl;
		return;
	}

	Reservation reservation = cancelledReservations.top();
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


