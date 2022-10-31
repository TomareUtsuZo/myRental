#pragma once
#include "RentalItem.h"
#include <string>
#include <vector>

class Video : 
    public RentalItem
{
private:
	std::string genre;
	std::vector<std::string> genres = { "Action", "Horror", "Drama", "Comedy" };

	// internal methods


public:
	// Constructors
	Video(std::string newTitle,
		std::string newRentalType, std::string newLoanType, int newYearPublished,
		int initialCopiesInStock, double newRentalFee, std::string newGenre);

	// Setters and Getters
	std::string GetGenre();
	bool SetGenre(std::string newGenre);
};

