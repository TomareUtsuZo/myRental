#include "RentalItems.h"
#include <fmt/format.h>	
#include <string>
#include <iostream>
#include "Customer.h"

// Constructors
Customer::Customer(std::string newName, std::string newAddress, std::string newPhoneNumber,
	std::string newAccountType, std::vector<RentalItems> newListOfRentedItems,
	int newRewardPoints, int numberOfRentalsRetruned) : name(newName), address(newAddress), phoneNumber(newPhoneNumber),
	accountType(newAccountType), listOfRentedItems(newListOfRentedItems), rewardPoints(newRewardPoints) {
	SetID(s_numberOfCustomersServiced);

}

// Internal Methods
void Customer::SetID(int numberOfCustomersServiced) {
	id = fmt::format("C{:03}", numberOfCustomersServiced);
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

void Customer::IncreaseRewardPoints() {

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
	bool thisIsPassed = std::find(availableAccountTypes.begin(), availableAccountTypes.end(), newAccountType) != availableAccountTypes.end();
	if (thisIsPassed == true)
		accountType = newAccountType;
	return thisIsPassed;
}

std::vector<RentalItems> Customer::GetListOfRentedItems() { return listOfRentedItems; }
void Customer::SetListOfRentedItems(std::vector<RentalItems> newListOfRentedItems) { listOfRentedItems = newListOfRentedItems; }

int Customer::GetRewardPoints() { return rewardPoints; }
void Customer::SetRewardPoints(int newRewardPoints) { rewardPoints = newRewardPoints; }

// Public Interfaces
void Customer::IncreaseRewardPoints(int pointsToAdd) { SetRewardPoints(GetRewardPoints() + pointsToAdd); }

bool Customer::DecreaseRewardPoints(int pointsToSubtract) {
	bool didNotGoBelowZero = false;
	if (GetRewardPoints() > 0) { // will not do anything if would cause points to fall below zero
		SetRewardPoints(GetRewardPoints() - pointsToSubtract);
		didNotGoBelowZero = true;
	}
	return didNotGoBelowZero;
}

bool Customer::PromoteCustomer() {
	bool customerWasPromoted = false;
	if (GetCanBePromoted() == true && numberOfRentalsRetruned > 2) {
		SetAccountType("VIP", availableAccountTypes);
		SetCanBePromoted(false);
	} // if (canBePromoted == true) {
	else if (GetCanBePromoted() == true && numberOfRentalsRetruned > 1) {
		SetAccountType("Regular", availableAccountTypes);
		SetCanBePromoted(false);
	} // else if (canBePromoted == true && numberOfRentalsRetruned > 1) {
}

RentalItems Customer::RentThisWithPoints(RentalItems item) {
	bool hadEnoughPoints = DecreaseRewardPoints(rewardPointCost);
	bool itemIsInStock = item.GetCopiesInStock() > 0;
	if (hadEnoughPoints && itemIsInStock)
		item = RentThisItem(item);
	else if (hadEnoughPoints && !itemIsInStock)
		DecreaseRewardPoints(rewardPointCost - rewardPointsSize);
	return item;
} // bool Customer::RentThisWithPoints(std::string item) {


RentalItems Customer::RentThisItem(RentalItems item, int numberOfItems) {
	bool itemIsInStock = item.GetCopiesInStock() > 0;
	if (itemIsInStock) {
		int indexOfItemInList = 0;
		std::vector<RentalItems> workingList = GetListOfRentedItems();
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
			std::vector<RentalItems> rentedList = GetListOfRentedItems();
			item.SetCopiesInStock(1);
			rentedList.push_back(item);
			SetListOfRentedItems(rentedList);
		} // if (notAlreadyRented) {
		else { // if (notAlreadyRented) { // update number of items rented 
			workingList[indexOfItemInList].IncreaseStock(numberOfItems);
			SetListOfRentedItems(workingList);
		} // else { // if (notAlreadyRented) {

		SetRewardPoints(GetRewardPoints() + rewardPointsSize);
	}
	return item;
}

RentalItems Customer::ReturnThisItem(RentalItems item, int itemsReturned) {
	std::vector<RentalItems> updatededRentedList = ItemReturnedUpdateRentedList(item);
	SetListOfRentedItems(updatededRentedList);
	item.ReturnToStock();
	return item;
}

std::vector<RentalItems> Customer::ItemReturnedUpdateRentedList(RentalItems updateThisItem, int itemsReturned) {
	int indexOfItemToReturn = 0;
	bool customerWillReturnAllCopies = updateThisItem.GetCopiesInStock() > itemsReturned;
	std::vector<RentalItems> workingList = GetListOfRentedItems();
	std::vector<RentalItems> listToReturn;
	while (workingList[indexOfItemToReturn].GetID() != updateThisItem.GetID()) {
		indexOfItemToReturn++;
	} // while (workingList[index] != removeThisItem) {
	for (int i = 0; i < (workingList.size() - customerWillReturnAllCopies); i++) {
		if (i == indexOfItemToReturn) {
			if (!customerWillReturnAllCopies)
				updateThisItem.DecreaseStock(itemsReturned);
			else
				continue;
		} // if (i == indexOfItemToReturn) {
		listToReturn.push_back(workingList[i]);
	} // for (int i = 0; i < (workingList.size() - 1); i++)) {
	return listToReturn;
}

void Customer::DisplayCustomerInfo() {
	std::vector<RentalItems> itemsRented = GetListOfRentedItems();
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