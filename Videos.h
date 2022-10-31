#pragma once
#include "RentalItems.h"
#include <string>
#include <vector>

class Videos : 
    public RentalItems
{
private:
	std::string genre;
	std::vector<std::string> genres = { "Action", "Horror", "Drama", "Comedy" };

	// internal methods


public:
	// Constructors
	Videos(std::string newTitle,
		std::string newRentalType, std::string newLoanType, int newYearPublished,
		int initialCopiesInStock, double newRentalFee, std::string newGenre);

	// Setters and Getters
	std::string GetGenre();
	bool SetGenre(std::string newGenre);
};

