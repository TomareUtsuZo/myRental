#include "RentalItem.h"
#include <fmt/format.h>	
#include <string>
#include <iostream>
#include "Customer.h"

// Constructors
Customer::Customer(std::string newName, std::string newAddress, std::string newPhoneNumber,
	std::string newAccountType, std::vector<RentalItem> newListOfRentedItems,
	int newRewardPoints, int numberOfRentalsRetruned) : name(newName), address(newAddress), phoneNumber(newPhoneNumber),
	accountType(newAccountType), listOfRentedItems(newListOfRentedItems), rewardPoints(newRewardPoints) {
	SetID(s_numberOfCustomersServiced);

}

// Internal Private Methods
void Customer::SetID(int vadlidCustomerID) {
	// This will need revisiting. What happens when Customer
	// data is loaded fromt the Database?
	id = fmt::format("C{:03}", vadlidCustomerID);
} // bool SetID(int numberOfCustomersServiced) {

void Customer::SetCanBePromoted(int numberOfRetruns) {
	if (accountType == "Regular" && numberOfRetruns > 2) {
		canBePromoted = true;
	} // if (accountType == "Regular" && numberOfRetruns > 3) {
	else if (accountType == "Guest" && numberOfRetruns > 1) {
		canBePromoted = true;
	} // else if (accountType == "Guest" && numberOfRetruns > 2) {
	else
		canBePromoted = false;
} // void Customer::SetCanBePromoted(int numberOfRetruns) {

void Customer::IncreaseRewardPoints(int pointsToAdd) {
	int newRewardPointsValue = GetRewardPoints() + pointsToAdd;
	SetRewardPoints(newRewardPointsValue);
}

// Setters and Getters
std::string Customer::GetID() { return id; }

bool Customer::GetCanBePromoted() { return canBePromoted; }

std::string Customer::GetName() { return name; }
void Customer::SetName(std::string newName) { name = newName; }

std::string Customer::GetAddress() { return address; }
void Customer::SetAddress(std::string newAddress) { address = newAddress; }

std::string Customer::GetPhoneNumber() { return phoneNumber; }
void Customer::SetPhoneNumber(std::string newPhoneNumber) { phoneNumber = newPhoneNumber; }

std::string Customer::GetAccountType() { return accountType; }
bool Customer::SetAccountType(std::string newAccountType, std::vector<std::string> availableAccountTypes) {
	bool isAccountType = std::find(availableAccountTypes.begin(), availableAccountTypes.end(), newAccountType) != availableAccountTypes.end();
	if (isAccountType == true)
		accountType = newAccountType;
	return isAccountType;
}

std::vector<RentalItem> Customer::GetListOfRentedItems() { return listOfRentedItems; }
void Customer::SetListOfRentedItems(std::vector<RentalItem> newListOfRentedItems) { listOfRentedItems = newListOfRentedItems; }

int Customer::GetRewardPoints() { return rewardPoints; }
void Customer::SetRewardPoints(int newRewardPoints) { rewardPoints = newRewardPoints; }

// Public Interfaces
void Customer::IncreaseRewardPoints(int pointsToAdd) { SetRewardPoints(GetRewardPoints() + pointsToAdd); }

bool Customer::DecreaseRewardPoints(int pointsToSubtract) {
	bool enoughPoints = (GetRewardPoints() - pointsToSubtract) > - 1;
	if (enoughPoints) { // will not do anything if would cause points to fall below zero
		SetRewardPoints(GetRewardPoints() - pointsToSubtract);
	}
	return enoughPoints;
}

bool Customer::PromoteCustomer() {
	bool customerWasPromoted = false;
	if (GetCanBePromoted() == true && numberOfRentalsRetruned > 2 && GetAccountType() == "Regular") {
		SetAccountType("VIP", availableAccountTypes);
		SetCanBePromoted(numberOfRentalsRetruned);
	} // if (canBePromoted == true) {
	else if (GetCanBePromoted() == true && numberOfRentalsRetruned > 1) {
		SetAccountType("Regular", availableAccountTypes);
		SetCanBePromoted(numberOfRentalsRetruned);
	} // else if (canBePromoted == true && numberOfRentalsRetruned > 1) {
	return customerWasPromoted;
}

bool Customer::RentThisWithPoints(RentalItem& item, int copiesToRent) {
	bool hadEnoughPoints = DecreaseRewardPoints(rewardPointCost);
	bool itemIsInStock = item.GetCopiesInStock() - copiesToRent >= 0;
	bool thisCanBeDone = hadEnoughPoints && itemIsInStock;
	if (thisCanBeDone)
		RentThisItem(item, copiesToRent);
	return thisCanBeDone;
} // bool Customer::RentThisWithPoints(std::string item) {


RentalItem Customer::RentThisItem(RentalItem& item, int copiesToRent) {
	bool itemIsInStock = item.GetCopiesInStock() > 0;
	if (itemIsInStock) {
		int indexOfItemInList = 0;
		std::vector<RentalItem> workingList = GetListOfRentedItems();
		int workingListSize = workingList.size();
		if(workingListSize > 0){
			bool idsAreSame = workingList[indexOfItemInList].GetID() != item.GetID();
			while (idsAreSame) {
				indexOfItemInList++;
				if (indexOfItemInList >= workingListSize)
					break;
				idsAreSame = workingList[indexOfItemInList].GetID() != item.GetID();
			} // while (workingList[indexOfItemToReturn].GetID() != item.GetID()) {
		} // if(workingListSize > 0){

		bool notAlreadyRentedBefore = (indexOfItemInList == (workingListSize));
		if (notAlreadyRentedBefore) { // put item into list
			std::vector<RentalItem> rentedList = GetListOfRentedItems();
			item.SetCopiesInStock(1);
			rentedList.push_back(item);
			SetListOfRentedItems(rentedList);
		} // if (notAlreadyRented) {
		else { // if (notAlreadyRented) { // update number of items rented 
			workingList[indexOfItemInList].IncreaseStock(copiesToRent);
			SetListOfRentedItems(workingList);
		} // else { // if (notAlreadyRented) {

		SetRewardPoints(GetRewardPoints() + rewardPointsSize);
	}
	return item;
}

RentalItem Customer::ReturnThisItem(RentalItem& item, int copiesToRent) {
	std::vector<RentalItem> updatededRentedList = ItemReturnedUpdateRentedList(item);
	SetListOfRentedItems(updatededRentedList);
	item.DecreaseStock();
	return item;
}

std::vector<RentalItem> Customer::ItemReturnedUpdateRentedList(RentalItem& updateThisItem, int copiesToReturned) {
	int indexOfItemToReturn = 0;
	bool customerWillReturnAllCopies = updateThisItem.GetCopiesInStock() > copiesToReturned;
	std::vector<RentalItem> workingList = GetListOfRentedItems();
	std::vector<RentalItem> listToReturn;
	while (workingList[indexOfItemToReturn].GetID() != updateThisItem.GetID()) {
		indexOfItemToReturn++;
	} // while (workingList[index] != removeThisItem) {
	for (int i = 0; i < (workingList.size() - customerWillReturnAllCopies); i++) {
		if (i == indexOfItemToReturn) {
			if (!customerWillReturnAllCopies)
				updateThisItem.DecreaseStock(copiesToReturned);
			else
				continue;
		} // if (i == indexOfItemToReturn) {
		listToReturn.push_back(workingList[i]);
	} // for (int i = 0; i < (workingList.size() - 1); i++)) {
	return listToReturn;
}

void Customer::DisplayCustomerInfo() {
	std::vector<RentalItem> itemsRented = GetListOfRentedItems();
	std::cout << fmt::format("\nID\t\t\t{}\n", GetID());
	std::cout << fmt::format("Name\t\t\t{}\n", GetName());
	std::cout << fmt::format("Address\t\t\t{}\n", GetAddress());
	std::cout << fmt::format("Phone Number\t\t{}\n", GetPhoneNumber());
	std::cout << fmt::format("Account Type\t\t{}\n", GetAccountType());
	std::cout << fmt::format("Can be promoted\t\t{}\n", GetCanBePromoted());
	std::cout << fmt::format("Reward points Accrued\t{}\n", GetRewardPoints());
	for (int i = 0; i < itemsRented.size(); i++) {
		itemsRented[i].DisplayItemInfo();
	} // for (int i = 0; i < GetListOfRentedItems().size(); i++) {
} // void Customer::DisplayCustomerInfo() {