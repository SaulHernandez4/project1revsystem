#include "Reservation.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

Reservation::Reservation() {
	reservationID = -1;
	userID = -1;
	name = "";
	resourceID = "";
	date = "";
}

Reservation::Reservation(int reservationID, int userID, std::string name, std::string resourceID, std::string date) {
	this->reservationID = reservationID;
	this->userID = userID;
	this->name = name;
	this->resourceID = resourceID;
	this->date = date;
}

int Reservation::getReservationID() const {
	return reservationID;
}

int Reservation::getUserID() const {
	return userID;
}

std::string Reservation::getName() const {
	return name;
}

std::string Reservation::getResourceID() const {
	return resourceID;
}

std::string Reservation::getDate() const {
	return date;
}