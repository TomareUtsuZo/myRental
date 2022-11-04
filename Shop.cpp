#include "Shop.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <fmt/format.h>


// Constructor
template<class T>
Shop::Shop(/*std::string newShopID, std::string newShopName, std::string newShopAddress,*/
	std::vector<T> newStockList, std::vector<T> newCustomerList) :
	stockList(newStockList), customerList(newCustomerList) {}

// Private Methods
int Shop::IndexOfRentalItem(std::string itemID) {
	int indexOfRentalItem = -1;
	for(int i = 0; i < stockList.size(); i++) {
		if (stockList[i].GetID() == itemID || stockList[i].GetTitle() == itemID) {
			indexOfRentalItem = i;
			break;
		} // if (stockList[i].GetID() == itemID) {
	} // for(int i = 0; i < stockList.size(); i++) {
	return indexOfRentalItem;
} // int IndexOfRentalItem(std::string itemID) {

int Shop::IndexOfCustomer(std::string customerID) {
	int indexOfCustomer = -1;
	for (int i = 0; i < customerList.size(); i++) {
		if (customerList[i].GetID() == customerID) {
			indexOfCustomer = i;
			break;
		} // if (customerList[i].GetID() == customerID) {
		else if (customerList[i].GetName() == customerID) {
			indexOfCustomer = i;
			break;
		} // else if (customerList[i].GetName() == customerID) {
	} // for (int i = 0; i < customerList.size(); i++) {
	return indexOfCustomer;
} // int Shop::IndexOfCustomer(std::string customerID) {

bool Shop::CustomerRentsItem(std::string customerID, std::string itemID, int numberOfItemsToRent,
	bool rentWithPoints) {
	bool rentedSucessfully = false;
	RentalItem itemToRent = RentalItem();
	bool enoughCopiesInStock = false;
	int indexOfRentalItem = IndexOfRentalItem(itemID);
	int indexOfCustomer = IndexOfCustomer(customerID);
	bool itemPartOfStockSystem = indexOfRentalItem > -1;
	bool customerInSystem = indexOfCustomer > -1;
	if (itemPartOfStockSystem && customerInSystem) {
		itemToRent = stockList[indexOfRentalItem];
		bool enoughCopiesInStock = itemToRent.GetCopiesInStock() >= numberOfItemsToRent;
		if (enoughCopiesInStock) {
			stockList[indexOfRentalItem].DecreaseStock(numberOfItemsToRent);
			bool customerHasEnoughPoints =
				customerList[indexOfCustomer].GetRewardPoints() >=
				customerList[indexOfCustomer].GetRewardPointCost();
			if (rentWithPoints) {
				if (customerHasEnoughPoints) {
					customerList[indexOfCustomer].RentThisWithPoints(itemToRent, numberOfItemsToRent);
					rentedSucessfully = true;
				} // if(customerHasEnoughPoints) {
				else // if(customerHasEnoughPoints) {
					std::cout << fmt::format("Customer does not have enough points for that.");
			} // if (rentWithPoints) {
			else { // if (rentWithPoints) {
				customerList[indexOfCustomer].RentThisItem(itemToRent, numberOfItemsToRent);
				rentedSucessfully = true;
			} // else { // if (rentWithPoints) {
		} // if (enoughCopiesInStock) {
		else //if (enoughCopiesInStock) {
			std::cout << fmt::format("There are not enough copies in stock to rent that many.");
	} // if (itemPartOfStockSytem && customerInSystem) 
	else { // if (itemPartOfStockSytem && customerInSystem) 
		if (!itemPartOfStockSystem)
			std::cout << fmt::format("There is no {} in stock.", itemID);
		if (!customerInSystem)
			std::cout << fmt::format("There is no {} in the sytem.", customerID);
	} // else { // if (itemPartOfStockSytem && customerInSystem) 
	return rentedSucessfully;
} // bool Shop::RentItemFromStock(std::string customerID, std::string itemID) {

bool Shop::CustomerReturnsItem(std::string customerID, std::string itemID, int numberOfItemsToReturn) {
	bool returnedSucessfully = false;
	RentalItem itemToReturn = RentalItem();
	bool enoughCopiesToReturn = false;
	int indexOfRentalItem = IndexOfRentalItem(itemID);
	int indexOfCustomer = IndexOfCustomer(customerID);
	bool itemPartOfStockSystem = indexOfRentalItem > -1;
	bool customerInSystem = indexOfCustomer > -1;
	if (itemPartOfStockSystem && customerInSystem) {
		enoughCopiesToReturn = customerList[indexOfCustomer].CustomerReturnsItem(customerID,
			numberOfItemsToReturn);
		if (enoughCopiesToReturn) {
			stockList[indexOfRentalItem].SetCopiesInStock(numberOfItemsToReturn);
			returnedSucessfully = true;
		} // if (enoughCopiesToReturn) {
		else
			std::cout << "Customer's return was not correct. Please check.";
	} // if (itemPartOfStockSystem && customerInSystem) {
	else { //if (itemPartOfStockSystem && customerInSystem) {
		if (!itemPartOfStockSystem)
			std::cout << "Item was not part of stock system. Did you correctly input the ID/Title?";
		else if (!customerInSystem)
			std::cout << "Customer is not in system. Did you correctly input thier ID/Name?";
	} // else { //if (itemPartOfStockSystem && customerInSystem) {
	return returnedSucessfully;
} // bool Shop::CustomerReturnsItem(std::string customerID, std::string itemID, int numberOfItemsToRent) {

// Public Setters and Getters
void Shop::SetStockList(std::vector<RentalItem> newStockList) { stockList = newStockList; }
std::vector<RentalItem> Shop::GetStockList() { return stockList; }

template<class T>
void Shop::SetCustomerList(std::vector<T> newCustomerList) { customerList = newCustomerList; }
template<class T>
std::vector<T> Shop::GetCustomerList() { return customerList; }

// Internal Utilities
bool SetYearPublished(bool yearPublishedSet, RentalItem workingRentalItem, std::string& inputYearPublished) {
	while (!yearPublishedSet) {
		std::string userInput;
		std::cout << "What year was this title published? \n";
		std::cin >> userInput;
		yearPublishedSet = workingRentalItem.SetYearPublished(userInput);
		if (yearPublishedSet)
			inputYearPublished = userInput;
	} // while (noYearPublished) {
	return yearPublishedSet;
}

bool SetCopiesInStock(bool copiesInStockSet, RentalItem workingRentalItem, int& inputCopiesInStock) {
	while (!copiesInStockSet) {
		std::string userInput;
		int userInputInt = 0;
		while (userInputInt == 0) {
			std::cout << "How many copies will you initially put out for rent? (Whole number only, please.)\n";
			std::stringstream(userInput) >> userInputInt;
			if (userInputInt != 0) {
				workingRentalItem.SetCopiesInStock(userInputInt);
				copiesInStockSet = true;
				inputCopiesInStock = userInputInt;
			} // if (userInputInt != 0) {
		} // while (userInputInt != 0) {
	} // while (copiesInStockIncorrect) {
	return copiesInStockSet;
}


bool SetRentalType(bool rentalTypeSet, RentalItem workingRentalItem, std::string& inputRentalType) {
	while (!rentalTypeSet) {
		std::cout << "What Rental Type is this? (Capitalization matters.\n)";
		for (int i = 0; i < workingRentalItem.GetAvailableRentalTypes().size(); i++)
			std::cout << workingRentalItem.GetAvailableRentalTypes()[i] << " ";
		std::cout << std::endl;
		std::cin >> inputRentalType;
		rentalTypeSet = workingRentalItem.SetRentalType(inputRentalType);
	} // while (!rentalTypeIncorrect) {
	return rentalTypeSet;
}

bool SetRentalFee(bool rentalFeeSet, RentalItem workingRentalItem, double& inputRentalFee) {
	while (!rentalFeeSet) {
		std::string userInput;
		double userInputDouble;
		std::cout << "What will the rental fee be? (x.xx format expected)\n";
		std::cin >> userInput;
		try {
			std::stringstream(userInput) >> userInputDouble;
			workingRentalItem.SetRentalFee(userInputDouble);
			rentalFeeSet = true;
			inputRentalFee = userInputDouble;
		}
		catch (int error) {
			std::cout << "That wasn't a dollar and cent input.";
		}
	} // while (!rentalFeeSet) {
	return rentalFeeSet;
}

bool SetGenreType(bool genreTypeSet, RentalItem workingRentalItem, std::string& inputGenreType) {
	while (!genreTypeSet) {
		std::cout << "What Loan Type is this? (Capitalziation matters.)\n";
		for (int i = 0; i < workingRentalItem.GetAvailableGenres().size(); i++)
			std::cout << workingRentalItem.GetAvailableGenres()[i] << " ";
		std::cout << std::endl;
		std::cin >> inputGenreType;
		genreTypeSet = workingRentalItem.SetLoanType(inputGenreType);
	} // while (loanTypeIncorrect) {
	return genreTypeSet;
}

bool SetLoanType(bool loanTypeSet, RentalItem workingRentalItem, std::string& inputLoanType) {
	while (!loanTypeSet) {
		std::cout << "What Loan Type is this? (Capitalziation matters.)\n";
		for (int i = 0; i < workingRentalItem.GetAvailableLoanTypes().size(); i++)
			std::cout << workingRentalItem.GetAvailableLoanTypes()[i] << " ";
		std::cout << std::endl;
		std::cin >> inputLoanType;
		loanTypeSet = workingRentalItem.SetLoanType(inputLoanType);
	} // while (loanTypeIncorrect) {
	return loanTypeSet;
}

// Public Functions
bool Shop::AddNewItemToStockList() {
	bool newItemSucessfullyAdded = false;
	// std::string validID = ValidIdGenerator()

	std::string inputTitle;
	std::string inputRentalType;
	std::string inputLoanType;
	int inputCopiesInStock;
	std::string inputYearPublished;
	double inputRentalFee;
	std::string inputGenre;
	RentalItem workingRentalItem = RentalItem();

	std::cout << "What is the title of this new rental item?\n";
	std::getline(std::cin, inputTitle);

	bool rentalTypeSet = false;
	SetRentalType(rentalTypeSet, workingRentalItem, inputRentalType);

	bool loanTypeSet = false;
	loanTypeSet = SetLoanType(loanTypeSet, workingRentalItem, inputLoanType);

	bool copiesInStockSet = false;
	copiesInStockSet = SetCopiesInStock(copiesInStockSet, workingRentalItem, inputCopiesInStock);

	bool yearPublishedSet = false;
	yearPublishedSet = SetYearPublished(yearPublishedSet, workingRentalItem, inputYearPublished);

	bool rentalFeeSet = false;
	rentalFeeSet = SetRentalFee(rentalFeeSet, workingRentalItem, inputRentalFee);

	if (inputLoanType == "DVD") {
		bool genreTypeSet = false;
		genreTypeSet = SetGenreType(genreTypeSet, workingRentalItem, inputGenre);
	}
	else {
		if (rentalTypeSet, loanTypeSet, copiesInStockSet, yearPublishedSet, rentalFeeSet) {
			workingRentalItem = RentalItem(inputTitle, inputRentalType, inputLoanType, inputYearPublished,
				inputCopiesInStock, inputRentalFee);
		}
	}


	stockList.push_back(workingRentalItem);
	return newItemSucessfullyAdded;
} // void Shop::AddNewItemToStockList() {

