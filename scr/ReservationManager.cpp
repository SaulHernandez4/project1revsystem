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
