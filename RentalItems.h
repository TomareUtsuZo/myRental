#include <string>
#include <vector>

class RentalItems {
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

	// Internal Methods
	void SetIsAvailableForRent();
	void SetID(int numberOfItemsAdded, int yearPublished);

public:
	// Constructors
	RentalItems(std::string newTitle, std::string newRentalType, 
		std::string newLoanType, int newYearPublished,
		int initialCopiesInStock, double newRentalFee);

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

	// Public interfaces

	void IncreaseStock(int numberOfNewCopies);

	bool DecreaseStock(int numberOfRemovedCopies);

	bool RentFromStock(int copiesRented=1);

	void ReturnToStock(int copiesReturned=1);

	void DisplayItemInfo();


}; // class RentalItems {
#pragma once
