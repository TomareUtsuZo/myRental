#pragma once 
#include <string>
#include <vector>
#include "RentalItem.h"

class Customer {
private:
	std::string id;
	std::string name;
	std::string address;
	std::string phoneNumber;
	std::string accountType;
	std::vector<RentalItem> listOfRentedItems;
	int rewardPoints;
	int rewardPointCost = 100;
	int rewardPointsSize = 10;
	int numberOfRentalsRetruned = 0;
	bool canBePromoted = false;
	static int s_numberOfCustomersServiced;
	std::vector<std::string> availableAccountTypes = { "Guest", "Regular", "VIP" };

	// Internal Methods
	void SetID(int numberOfCustomersServiced);
	void SetCanBePromoted(int numberOfRetruns);
	int TheItemExistsAt(int indexOfItemInList, int workingListSize, 
		std::vector<RentalItem> workingList, RentalItem item);
	std::vector<RentalItem> UpdatedListToReturn(int indexOfItemToReturn, int copiesToReturn,
		std::vector<RentalItem>workingList, RentalItem updateThisItem);

public:
	// Constructors
	Customer(std::string newName, std::string newAddress, std::string newPhoneNumber, 
		std::string newAccountType, std::vector<RentalItem> newListOfRentedItems, 
		int newRewardPoints, int timesRentalReturned);

	Customer();

	// Setters and Getters
	std::string GetID();


	bool GetCanBePromoted();

	std::string GetName();
	void SetName(std::string newName);

	std::string GetAddress();
	void SetAddress(std::string newAddress);

	std::string GetPhoneNumber();
	void SetPhoneNumber(std::string newPhoneNumber);

	std::string GetAccountType();
	bool SetAccountType(std::string newAccountType, std::vector<std::string> availableAccountTypes);

	
	std::vector<RentalItem> GetListOfRentedItems();
	void SetListOfRentedItems(std::vector<RentalItem> newListOfRentedItems);

	int GetRewardPoints();
	void SetRewardPoints(int newRewardPoints);

	int GetRewardPointCost();

	// Public Interfaces
	void IncreaseRewardPoints(int pointsToAdd);
	bool DecreaseRewardPoints(int pointsToSubtract);
	bool PromoteCustomer();
	bool RentThisWithPoints(RentalItem item, int copiesToRent);
	bool RentThisItem(RentalItem item, int copiesToRent);
	bool CustomerReturnsItem(std::string itemID, int copiesToRent);
	int GetIndexOfItemInList(std::string itemID);
	void DisplayCustomerInfo();

}; // class Customer {