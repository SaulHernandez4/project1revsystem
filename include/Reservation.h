#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>
#include <queue>

class Reservation {
private:
	int reservationID;
	int userID;
	std::string name;
	std::string resourceID;
	std::string date;

public:
	Reservation();
	Reservation(int reservationID, int userID, std::string name, std::string resourceID, std::string date);

	int getReservationID() const;
	int getUserID() const;
	std::string getName() const;
	std::string getResourceID() const;
	std::string getDate() const;

	
};


#endif // !RESERVATION_H
