#include <string>
#include <vector>
#include "RentalItems.h"

class Customer {
private:
	std::string id;
	std::string name;
	std::string address;
	std::string phoneNumber;
	std::string accountType;
	std::vector<RentalItems> listOfRentedItems;
	int rewardPoints;
	int numberOfRentalsRetruned = 0;
	bool canBePromoted = false;
	static int s_numberOfCustomersServiced;
	std::vector<std::string> availableAccountTypes = { "Guest", "Regular", "VIP" };
	int rewardPointCost = 100;
	int rewardPointsSize = 10;

	// Internal Methods
	void SetID(int numberOfCustomersServiced);
	void SetCanBePromoted(int numberOfRetruns);
	void IncreaseRewardPoints();

public:
	// Constructors
	Customer(std::string newName, std::string newAddress, std::string newPhoneNumber, 
		std::string newAccountType, std::vector<RentalItems> newListOfRentedItems, 
		int newRewardPoints, int timesRentalReturned);

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

	
	std::vector<RentalItems> GetListOfRentedItems();
	void SetListOfRentedItems(std::vector<RentalItems> newListOfRentedItems);

	int GetRewardPoints();
	void SetRewardPoints(int newRewardPoints);

	// Public Interfaces
	void IncreaseRewardPoints(int pointsToAdd);
	bool DecreaseRewardPoints(int pointsToSubtract);
	bool PromoteCustomer();
	RentalItems RentThisWithPoints(RentalItems item);
	RentalItems RentThisItem(RentalItems item, int numberOfItems=1);
	RentalItems ReturnThisItem(RentalItems item, int itemsReturned=1);
	std::vector<RentalItems> ItemReturnedUpdateRentedList(RentalItems updateThisItem, int itemsReturned = 1);
	void DisplayCustomerInfo();

}; // class Customer {