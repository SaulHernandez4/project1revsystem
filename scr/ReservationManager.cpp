#include "ReservationManager.h"
#include "Reservation.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

ReservationManager::ReservationManager() {
	head = nullptr;
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

		//not done yet need to put reservations in linked list
	}
	file.close();
}

bool ReservationManager::createReservation(const Reservation& reservation) {
	return false;
}

bool ReservationManager::cancelReservation(int reservationID) {
	return false;
}

void ReservationManager::displayReservations() const {
}

bool ReservationManager::validateReservation(const Reservation& reservation) const {
	return false;
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
