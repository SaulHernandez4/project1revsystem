#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <string>
#include <vector>
#include "Reservation.h"

class ReservationManager {
private:
	struct Node {
		Reservation reservation;
		node* next;
	};

	Node* head;

public:
	ReservationManager();
	~ReservationManager();

	void loadReservations(const std::string& filename);

	bool createReservation(const Reservation& reservation);
	bool cancelReservation(int reservationID);

	void displayReservations() const;
	bool validateReservation(const Reservation& reservation) const;
	
};




#endif // !RESERVATIONMANAGER_H
