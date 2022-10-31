#include "Videos.h"
#include <string>
#include <iostream>




Videos::Videos(std::string newTitle,
	std::string newRentalType, std::string newLoanType, int newYearPublished,
	int initialCopiesInStock, double newRentalFee, std::string newGenre) : 
	RentalItems(newTitle, newRentalType, newLoanType, newYearPublished, initialCopiesInStock, 
	newRentalFee), genre(newGenre) {}


// Internal Methods
std::string Videos::GetGenre() { return genre; }
bool Videos::SetGenre(std::string newGenre) {
	bool thisIsPassed = std::find(genres.begin(), genres.end(), newGenre) != genres.end();
	if (thisIsPassed == true)
		genre = newGenre;
	return thisIsPassed;
} // bool Videos::SetGenre(std::string newGenre) {