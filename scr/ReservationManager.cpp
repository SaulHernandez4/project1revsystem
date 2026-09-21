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

		Node* newNode = new Node;
		newNode->reservation = reservation;
		newNode->next = nullptr;

		if (head == nullptr) {
			head = newNode;
		} else {
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
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
	}
	else {
		Node* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}
	return true;
}

bool ReservationManager::cancelReservation(int reservationID) {
	return false; //NEED TO ADD
}

void ReservationManager::displayReservations() const {
	Node* current = head;

	while (current != nullptr) {
		std::cout << "Reservation ID: " << current->reservation.getReservationID() << std::endl;
		std::cout << "User ID: " << current->reservation.getUserID() << std::endl;
		std::cout << "Name: " << current->reservation.getName() << std::endl;
		std::cout << "Resource ID: " << current->reservation.getResourceID() << std::endl;
		std::cout << "Date: " << current->reservation.getDate() << std::endl;
		std::cout << "-----------------------------" << std::endl;
		
		current = current->next;
	}
}

bool ReservationManager::validateReservation(const Reservation& reservation) const {
	return true; //NEED TO ADD
}
