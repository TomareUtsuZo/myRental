#pragma once 
#include <string>
#include <vector>

class RentalItem {
private:
	std::string id;
	std::string title;
	std::string rentalType;
	std::string loanType;
	int copiesInStock;
	int yearPublished;
	double rentalFee;
	bool isAvailableForRent;
	std::vector<std::string> availableRentalTypes = { "Record", "DVD", "Game"};
	std::vector<std::string> availableLoanTypes = { "two day rental", "one week rental" };
	static int s_numberOfItemsAdded;


	std::string genre;
	std::vector<std::string> genres = { "Action", "Horror", "Drama", "Comedy", "None"};

	// Internal Methods
	void SetIsAvailableForRent();
	void SetID(int numberOfItemsAdded, int yearPublished);

public:
	// Constructors
	RentalItem();
	RentalItem(std::string newTitle, std::string newRentalType, std::string newLoanType, 
		int newYearPublished, int initialCopiesInStock, double newRentalFee, std::string newGenre="None");

	// Setters and Getters
	std::string GetID();

	std::string GetTitle();
	void SetTitle(std::string newTitle);

	std::string GetRentalType();
	bool SetRentalType(std::string newRentalType);

	std::string GetLoanType();
	bool SetLoanType(std::string newLoanType);

	int GetCopiesInStock();
	void SetCopiesInStock(int newCopiesInStock);

	double GetRentalFee();
	void SetRentalFee(double newRentalFee);

	bool GetIsAvailableForRent();

	std::string GetGenre();
	bool SetGenre(std::string newGenre);

	// Public interfaces

	void IncreaseStock(int numberOfNewCopies=1);

	bool DecreaseStock(int numberOfRemovedCopies=1);

	void DisplayItemInfo();


}; // class RentalItems {
