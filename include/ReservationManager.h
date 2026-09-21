#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <string>
#include <vector>
#include <queue>
#include "Reservation.h"

class ReservationManager {
private:
	struct Node {
		Reservation reservation;
		Node* next;
	};

	Node* head;

	//WaitingLists & resources

	struct WaitingStudent{
		int userID;
		std::string name;
		std::string date;
	};

	struct WaitingList {
		std::string resourceID;
		std::queue<WaitingStudent> students;
	};

	std::vector<WaitingList> waitingLists;
	WaitingList* findWaitingList(std::string resourceID);
public:
	ReservationManager();
	~ReservationManager();

	void loadReservations(const std::string& filename);

	bool createReservation(const Reservation& reservation);
	bool cancelReservation(int reservationID);

	void displayReservations() const;
	bool validateReservation(const Reservation& reservation) const;

	void addToWaitingList(std::string resourceID, int userID, std::string name, std::string date);
	void processWaitingList(std::string resourceID);
	void displayWaitingList();
	
};




#endif // !RESERVATIONMANAGER_H
