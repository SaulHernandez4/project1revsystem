#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "Reservation.h"
#include "Resource.h"

class ReservationManager {
private:
	struct Node {
		Reservation reservation;
		Node* next;
	};

	Node* head;
	Node* tail;
	std::stack<Reservation>  cancelledReservations;
	int nextReservationID;

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

	bool createReservation(const Reservation& reservation, std::vector<Resource>& resources);
	bool cancelReservation(int reservationID, std::vector<Resource>& resources);

	void displayReservation(const Reservation& reservation) const;
	void displayReservations() const;
	bool validateReservation(const Reservation& reservation) const;

	void addToWaitingList(std::string resourceID, int userID, std::string name, std::string date);
	void processWaitingList(std::string resourceID, std::vector<Resource>& resources);
	void displayWaitingList();

	int getReservationID() const;
	
	void undoCancelledReservation(std::vector<Resource>& resources);
	void displayCancelledReservations() const;
	void generateReport(const std::vector<Resource>& resources) const;

	bool searchReservationByID(int reservationID) const;
	int searchReservationsByStudent(int userID) const;
};


#endif // !RESERVATIONMANAGER_H
