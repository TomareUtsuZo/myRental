#include "RentalItem.h"
#include <fmt/format.h>	
#include <string>
#include <iostream>
#include "Customer.h"
#include "Shop.h"

// Constructors
Customer::Customer(std::string newName, std::string newAddress, std::string newPhoneNumber,
	std::string newAccountType, std::vector<RentalItem> newListOfRentedItems,
	int newRewardPoints, int timesRentalReturned) : name(newName), address(newAddress),
	phoneNumber(newPhoneNumber), accountType(newAccountType), listOfRentedItems(newListOfRentedItems), 
	rewardPoints(newRewardPoints), numberOfRentalsReturned(timesRentalReturned) { SetID();
}
Customer::Customer() {}

// Internal Private Methods
void Customer::SetID(std::string newID) {
	int newIDNumber = stoi(newID.substr(1, 3));
	int oldIDNumber = stoi(id.substr(1, 3));
	if (newIDNumber != -10) {
		s_usedCustomerIDs[oldIDNumber] = false;

		while (s_usedCustomerIDs[newIDNumber]) {
			std::cout << newIDNumber << " is already in use. Try another xxx number.\n";
			std::cin >> newIDNumber;
		}
	}
	else {
		for (int i = 0; i < 1000; i++) {
			if (s_usedCustomerIDs[i] == false) {
				newIDNumber = i;
				break;
			}
		}
	}
	if (s_usedCustomerIDs[newIDNumber] == false) {
		id = fmt::format("C{:03}", newIDNumber);
		s_usedCustomerIDs[newIDNumber] = true;
	}
}

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

int Customer::GetRewardPointCost() { return rewardPointCost; }

int Customer::TheItemExistsAt(int workingListSize, std::vector<RentalItem> workingList, 
	RentalItem item) {
	int indexOfItemInList = 0;
	if (workingListSize > 0) {
		bool idsAreDifferent = workingList[indexOfItemInList].GetID() != item.GetID();
		while (idsAreDifferent) {
			indexOfItemInList++;
			if (indexOfItemInList >= workingListSize)
				break;
			idsAreDifferent = workingList[indexOfItemInList].GetID() != item.GetID();
		} // while (workingList[indexOfItemToReturn].GetID() != item.GetID()) {
	} // if(workingListSize > 0){
	return indexOfItemInList;
}

std::vector<RentalItem> Customer::UpdatedListToReturn(int indexOfItemToReturn, int copiesToReturn, 
	std::vector<RentalItem>workingList, RentalItem updateThisItem) {
	int oneIfCustomerWillNotReturnAllCopies = updateThisItem.GetCopiesInStock() > copiesToReturn;
	std::vector<RentalItem> listToReturn;
	for (int i = 0; i < (workingList.size() - oneIfCustomerWillNotReturnAllCopies); i++) {
		if (i == indexOfItemToReturn) {
			if (!oneIfCustomerWillNotReturnAllCopies)
				updateThisItem.DecreaseStock(copiesToReturn);
			else
				continue;
		} // if (i == indexOfItemToReturn) {
		listToReturn.push_back(workingList[i]);
	} // for (int i = 0; i < (workingList.size() - 1); i++)) {
	return listToReturn;
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
	bool isAccountType = std::find(availableAccountTypes.begin(), availableAccountTypes.end(), 
		newAccountType) != availableAccountTypes.end();
	if (isAccountType == true)
		accountType = newAccountType;
	return isAccountType;
}
std::vector<std::string> Customer::GetAvailableAccountTypes() { return availableAccountTypes; }

int Customer::GetNumberOfRentalsReturned() { return numberOfRentalsReturned; }
void Customer::SetNumberOfRentalsReturned(int newNumberOfRentalsReturned) {
	numberOfRentalsReturned = newNumberOfRentalsReturned; }

std::vector<RentalItem> Customer::GetListOfRentedItems() { return listOfRentedItems; }
void Customer::SetListOfRentedItems(std::vector<RentalItem> newListOfRentedItems) { 
	listOfRentedItems = newListOfRentedItems; }

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
	SetCanBePromoted(numberOfRentalsReturned);
	if (GetCanBePromoted() == true && numberOfRentalsReturned > 2 && GetAccountType() == "Regular") {
		SetAccountType("VIP", availableAccountTypes);
		SetCanBePromoted(numberOfRentalsReturned);
		customerWasPromoted = true;
	} // if (canBePromoted == true) {
	else if (GetCanBePromoted() == true && numberOfRentalsReturned > 1) {
		SetAccountType("Regular", availableAccountTypes);
		SetCanBePromoted(numberOfRentalsReturned);
		customerWasPromoted = true;
	} // else if (canBePromoted == true && numberOfRentalsRetruned > 1) {
	return customerWasPromoted;
}

bool Customer::RentThisWithPoints(RentalItem item, int copiesToRent) {
	bool hadEnoughPoints = DecreaseRewardPoints(rewardPointCost);
	bool itemIsInStock = item.GetCopiesInStock() - copiesToRent >= 0;
	bool thisCanBeDone = hadEnoughPoints && itemIsInStock;
	if (thisCanBeDone)
		RentThisItem(item, copiesToRent);
	return thisCanBeDone;
} // bool Customer::RentThisWithPoints(std::string item) {

bool Customer::RentThisItem(RentalItem item, int copiesToRent) {
	bool thisHasBeenRented = false;
	bool itemIsInStock = item.GetCopiesInStock() >= copiesToRent;
	if (itemIsInStock) {
		int indexOfItemInList = 0;
		std::vector<RentalItem> workingList = GetListOfRentedItems();
		int workingListSize = workingList.size();

		indexOfItemInList = TheItemExistsAt(workingListSize, workingList, item);

		bool notAlreadyRentedBefore = (indexOfItemInList == workingListSize);

		if (notAlreadyRentedBefore) { // put item into list
			std::vector<RentalItem> rentedList = GetListOfRentedItems();
			item.SetCopiesInStock(copiesToRent);
			rentedList.push_back(item);
			SetListOfRentedItems(rentedList);
			thisHasBeenRented = true;
			SetRewardPoints(GetRewardPoints() + rewardPointsSize);
		} // if (notAlreadyRented) {
		else { // if (notAlreadyRented) { // update number of items rented 
			workingList[indexOfItemInList].IncreaseStock(copiesToRent);
			SetListOfRentedItems(workingList);
			thisHasBeenRented = true;
			SetRewardPoints(GetRewardPoints() + rewardPointsSize);
		} // else { // if (notAlreadyRented) {
	}
	return thisHasBeenRented;
}

bool Customer::CustomerReturnsItem(std::string itemID, int copiesToReturn) {
	bool thisWasRemovedFromCustomerInventory = false;
	int indexOfItemInCustomerList = GetIndexOfItemInList(itemID);
	int copiesCustomerHasToReturn = GetListOfRentedItems()[indexOfItemInCustomerList].GetCopiesInStock();
	int customerHasEnoughCopiesToReturn = copiesCustomerHasToReturn - copiesToReturn;
	bool customerHasCopiesToReturn = (indexOfItemInCustomerList > -1) && customerHasEnoughCopiesToReturn > -1;
	if (customerHasCopiesToReturn) {
		bool customerReturnsAllCopies = customerHasEnoughCopiesToReturn == 0;
		std::vector<RentalItem> updatededRentedList;
		if (customerReturnsAllCopies) {
			for (int i = 0; i < GetListOfRentedItems().size(); i++) {
				if (indexOfItemInCustomerList != i) {
					updatededRentedList.push_back(GetListOfRentedItems()[i]);
				} // if (indexOfItemInCustomerList != i) {
			} // for (int i = 0; i < workingList.size(); i++) {
			thisWasRemovedFromCustomerInventory = true;
		} // if (customerReturnsAllCopies) {
		else { // if (customerReturnsAllCopies) {
			listOfRentedItems[indexOfItemInCustomerList].DecreaseStock(copiesToReturn);
			updatededRentedList = GetListOfRentedItems();
			thisWasRemovedFromCustomerInventory = true;
		} // else { // if (customerReturnsAllCopies) {
		SetListOfRentedItems(updatededRentedList);
	} // if (customerHasCopiesToReturn) {
	return thisWasRemovedFromCustomerInventory;
}

int Customer::GetIndexOfItemInList(std::string itemID) {
	int indexOfItemToReturn = -1;
	std::vector<RentalItem> workingList = GetListOfRentedItems();
	for (int i = 0; i < workingList.size(); i++) {
		if (workingList[i].GetID() == itemID || workingList[i].GetTitle() == itemID) {
			indexOfItemToReturn = i;
			break;
		} // if (workingList[i].GetID() == itemID || workingList[i].GetTitle() == itemID) {
	} // while (workingList[index] != removeThisItem) {	
	return indexOfItemToReturn;
}

void Customer::DisplayCustomerInfo() {
	std::vector<RentalItem> itemsRented = GetListOfRentedItems();
	SetCanBePromoted(numberOfRentalsReturned);
	std::cout << fmt::format("\nID\t\t\t{}\n", GetID());
	std::cout << fmt::format("Name\t\t\t{}\n", GetName());
	std::cout << fmt::format("Address\t\t\t{}\n", GetAddress());
	std::cout << fmt::format("Phone Number\t\t{}\n", GetPhoneNumber());
	std::cout << fmt::format("Account Type\t\t{}\n", GetAccountType());
	std::cout << fmt::format("Can be promoted\t\t{}\n", GetCanBePromoted());
	std::cout << fmt::format("Reward points Accrued\t{}\n", GetRewardPoints());
	std::cout << fmt::format("Rentals Returned\t{}\n", numberOfRentalsReturned);
	for (int i = 0; i < itemsRented.size(); i++) {
		itemsRented[i].DisplayItemInfo();
	} // for (int i = 0; i < GetListOfRentedItems().size(); i++) {
} // void Customer::DisplayCustomerInfo() {