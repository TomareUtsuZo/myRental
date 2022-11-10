#include "Shop.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <fmt/format.h>


// Constructor
Shop::Shop(std::vector<RentalItem> newStockList, std::vector<Customer> newCustomerList) :
	stockList(newStockList), customerList(newCustomerList) {}


// Public Setters and Getters
void Shop::SetStockList(std::vector<RentalItem> newStockList) { stockList = newStockList; }
std::vector<RentalItem> Shop::GetStockList() { return stockList; }

void Shop::SetCustomerList(std::vector<Customer> newCustomerList) { customerList = newCustomerList; }
std::vector<Customer> Shop::GetCustomerList() { return customerList; }

// Internal Utilities
int GetUserInputInt(int minInput, int maxInput) {
	int userInputInt = -1;
	std::string userInput = "";
	while (userInput == "") {
		std::cin >> userInput;
		try {
			userInputInt = std::stoi(userInput);
			if (!((userInputInt >= minInput) && (userInputInt <= maxInput))) {
				std::cout << "Invalid input: Choose a number that is associated with the modification you want to make\n";
				userInput = "";
				userInputInt = -1;
			}
		}
		catch (const std::exception& e) {
			std::cout << "Invalid input: Choose a number that is associated with the modification you want to make.\n";
			userInput = "";
			userInputInt = -1;
		}
	}
	return userInputInt;
} // int GetUserInputInt(int minInput, int maxInput) {

bool ModiyFromOptionsLocal(bool xTypeSet, std::string& itemToModify,
	std::vector<std::string> listOfPossibleInputs, std::string inputRequestSting) {
	while (xTypeSet == false) {
		itemToModify = "";
		std::cout << inputRequestSting;
		for (int i = 0; i < listOfPossibleInputs.size(); i++)
			std::cout << listOfPossibleInputs[i] << ", ";
		std::cout << std::endl;
		std::cin.ignore(INT_MAX, '\n');
		std::getline(std::cin, itemToModify);
		for (int i = 0; i < listOfPossibleInputs.size(); i++) {
			if (itemToModify == listOfPossibleInputs[i]) {
				xTypeSet = true;
				break;
			}
		}
	} // while (loanTypeIncorrect) {
	return xTypeSet;
}

bool InputBasicIntHandlerLocal(int& inputToPass, bool jobsDone=false,
	std::string requestForInput = "Enter a whole in the proper range.\n",
	int minRange=-2147483647, int maxRange=2147483647) {
	inputToPass = minRange - 1;
	while (inputToPass < minRange) {
		std::cout << requestForInput;
		try {
			std::cin >> inputToPass;
			jobsDone = true;
		}
		catch (const std::exception& e) {
			inputToPass = minRange - 1;
		}
	} // while (numberOfRentalsReturnedToModify < 0) {
	return jobsDone;
}
// Stock Related Utilities
int Shop::IndexOfRentalItem(std::string itemID) {
	int indexOfRentalItem = -1;
	for (int i = 0; i < stockList.size(); i++) {
		if (stockList[i].GetID() == itemID || stockList[i].GetTitle() == itemID) {
			indexOfRentalItem = i;
			break;
		} // if (stockList[i].GetID() == itemID) {
	} // for(int i = 0; i < stockList.size(); i++) {
	return indexOfRentalItem;
} // int IndexOfRentalItem(std::string itemID) {

int Shop::IndexOfRentalItem(std::string itemID, std::vector<RentalItem> workingVector) {
	int indexOfRentalItem = -1;
	for (int i = 0; i < workingVector.size(); i++) {
		if (workingVector[i].GetID() == itemID || workingVector[i].GetTitle() == itemID) {
			indexOfRentalItem = i;
			break;
		} // if (stockList[i].GetID() == itemID) {
	} // for(int i = 0; i < stockList.size(); i++) {
	return indexOfRentalItem;
}

bool SetYearPublishedLocal(bool yearPublishedSet, RentalItem workingRentalItem, std::string& inputYearPublished) {
	while (!yearPublishedSet) {
		std::string userInput;
		std::cout << "\nWhat year was this title published? \n";
		std::cin >> userInput;
		yearPublishedSet = workingRentalItem.SetYearPublished(userInput);
		if (yearPublishedSet)
			inputYearPublished = userInput;
	} // while (noYearPublished) {
	return yearPublishedSet;
}

bool SetCopiesInStockLocal(bool copiesInStockSet, RentalItem workingRentalItem, int& inputCopiesInStock) {
	while (copiesInStockSet == false) {
		std::string userInput;
		int userInputInt = 0;
		while (userInputInt == 0) {
			std::cout << "How many copies will you initially put out for rent? (Whole number only, please.)\n";
			std::cin >> userInput;
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

bool SetGenreTypeLocal(bool genreTypeSet, RentalItem workingRentalItem, std::string& inputGenreType) {
	while (genreTypeSet == false) {
		std::cout << "What Genre Type is this? (Capitalziation matters.)\n";
		for (int i = 0; i < workingRentalItem.GetAvailableGenres().size(); i++)
			std::cout << workingRentalItem.GetAvailableGenres()[i] << " ";
		std::cout << std::endl;
		std::cin >> inputGenreType;
		genreTypeSet = workingRentalItem.SetGenre(inputGenreType);
	} // while (loanTypeIncorrect) {
	return genreTypeSet;
}

bool SetRentalTypeLocal(bool rentalTypeSet, RentalItem workingRentalItem, std::string& inputRentalType,
	std::string& inputGenre) {
	while (rentalTypeSet == false) {
		std::cout << "What Rental Type is this? (Capitalization matters.)\n";
		for (int i = 0; i < workingRentalItem.GetAvailableRentalTypes().size(); i++)
			std::cout << workingRentalItem.GetAvailableRentalTypes()[i] << ", ";
		std::cout << std::endl;
		std::getline(std::cin, inputRentalType);
		if (inputRentalType == "DVD") {
			bool genreTypeSet = false;
			genreTypeSet = SetGenreTypeLocal(genreTypeSet, workingRentalItem, inputGenre);
		}
		rentalTypeSet = workingRentalItem.SetRentalType(inputRentalType);
	} // while (!rentalTypeIncorrect) {
	return rentalTypeSet;
}

bool SetRentalFeeLocal(bool rentalFeeSet, RentalItem workingRentalItem, double& inputRentalFee) {
	while (rentalFeeSet == false) {
		std::string userInput;
		double userInputDouble;
		std::cout << "What will the rental fee be? (x.xx format expected)\n";
		std::cin >> userInput;
		try {
			userInputDouble = std::stof(userInput);
			workingRentalItem.SetRentalFee(userInputDouble);
			rentalFeeSet = true;
			inputRentalFee = userInputDouble;
		}
		catch (const std::exception& e) {
			std::cout << "Invalid input: make it fit the x.xx format";
		}
	} // while (!rentalFeeSet) {
	return rentalFeeSet;
}

bool SetLoanTypeLocal(bool loanTypeSet, RentalItem workingRentalItem, std::string& inputLoanType) {
	inputLoanType = "";
	while (loanTypeSet == false) {
		std::cout << "What Loan Type is this? (Capitalziation matters.)\n";
		for (int i = 0; i < workingRentalItem.GetAvailableLoanTypes().size(); i++)
			std::cout << workingRentalItem.GetAvailableLoanTypes()[i] << ", ";
		std::cout << std::endl;
		std::getline(std::cin, inputLoanType);
		loanTypeSet = workingRentalItem.SetLoanType(inputLoanType);
	} // while (loanTypeIncorrect) {
	return loanTypeSet;
}

std::string ManualCreateIDRentalItem(std::string yearPublished) {
	std::string newID = "";
	std::cout << "What new ID do you want to set? (Ixxx) \n";
	std::cout << "Or leave empty to auto generate ID";
	while (newID == "") {
		std::cin >> newID;
		int testForInt = 1;
		bool iFirst = newID[0] == 'I';
		bool isThreeDigitInt = false;
		if (iFirst && newID.size() == 4) {
			std::string workingID = newID;
			workingID.erase(0, 1);
			try {
				int digitsString = std::stoi(workingID);
				isThreeDigitInt = true;
			}
			catch (const std::exception& e) {
				std::cout << "Invalid input: Must conform to IXXX format.\n";
			}
		}
		else{
			std::cout << "This requires an IXXX format.";
		}
		
		if (isThreeDigitInt == true) {
			break;			
		}
		else
			newID = "";		
	}
	return newID + "-" + yearPublished;
}

// Customer Related Utilites
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

int IndexOfCustomer(std::string customerID, std::vector<Customer> workingVector) {
	int indexOfCustomer = -1;
	for (int i = 0; i < workingVector.size(); i++) {
		if (workingVector[i].GetID() == customerID) {
			indexOfCustomer = i;
			break;
		} // if (customerList[i].GetID() == customerID) {
		else if (workingVector[i].GetName() == customerID) {
			indexOfCustomer = i;
			break;
		} // else if (customerList[i].GetName() == customerID) {
	} // for (int i = 0; i < customerList.size(); i++) {
	return indexOfCustomer;
}

bool AutomatedCreateCustomerID(std::vector<Customer> workingCustomerList, std::string& workingCustomerID) {
	bool idCreatedSucessfully = false;
	for (int i = 0; i < 1000; i++) {
		bool notInList = true;
		std::string testableID;
		for (int index = 0; index < workingCustomerList.size(); index++) {
			testableID = fmt::format("C{:0>3}", i);
			if (workingCustomerList[index].GetID() == testableID) {
				notInList = false;
				break;
			} // if (workingCustomerlist[index].GetID() == testableID) {
		} // for (int index = 0; index < workingCustomerlist.size(); index++) {
		if (notInList) {
			workingCustomerID = testableID;
			idCreatedSucessfully = true;
			break;
		}
	} // for (int i = 0; i < 1000; i++) {
	return idCreatedSucessfully;
}

bool ManualCreateIDCustomer(std::vector<Customer> workingCustomerList, std::string& idToCreate) {
	bool idCreatedSucessfully = false;
	std::string inputID = "-000";
	std::string outputID;
	while (inputID == "-000") {
		std::cout << "Enter a three digit number not already in use by another customer,";
		std::cout << "or leave empty to auto generate ID.\n";
		std::cin.ignore(INT_MAX, '\n');
		std::cin >> inputID;
		if (inputID == "") {
			AutomatedCreateCustomerID(workingCustomerList, outputID);
		} // if (inputID == "") {
		else if (inputID.size() == 3) {
			bool notInList = true;
			try {
				std::stoi(inputID);
				std::string testableID;
				for (int index = 0; index < workingCustomerList.size(); index++) {
					testableID = fmt::format("C{}", inputID);
					if (workingCustomerList[index].GetID() == testableID) {
						notInList = false;
						inputID = "-000";
						break;
					} // if (workingCustomerlist[index].GetID() == testableID) {
				} // for (int index = 0; index < workingCustomerlist.size(); index++) {
				if (notInList) {
					outputID = testableID;
					idCreatedSucessfully = true;
				} // if(notInList) {
			} // try {
			catch (const std::exception& e) {
				std::cout << "Invalid input: make it fit the HTO format.";
				inputID = "-000";
			} // catch (const std::exception& e) {
		}
		else
			inputID = "-000";
	}
	idToCreate = outputID;
	return idCreatedSucessfully;
}

bool Shop::CustomerRentsItem(std::string customerID, std::string itemID, int numberOfItemsToRent,
	bool rentWithPoints) {
	bool rentedSucessfully = false;
	RentalItem itemToRent = RentalItem();
	int indexOfRentalItem = IndexOfRentalItem(itemID);
	int indexOfCustomer = IndexOfCustomer(customerID);
	bool itemPartOfStockSystem = indexOfRentalItem > -1;
	bool customerInSystem = indexOfCustomer > -1;
	if (itemPartOfStockSystem && customerInSystem) {
		bool enoughCopiesInStock = itemToRent.GetCopiesInStock() >= numberOfItemsToRent;
		itemToRent = stockList[indexOfRentalItem];
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
		if (itemPartOfStockSystem == false)
			std::cout << fmt::format("There is no {} in stock.", itemID);
		if (customerInSystem == false)
			std::cout << fmt::format("There is no {} in the sytem.", customerID);
	} // else { // if (itemPartOfStockSytem && customerInSystem) 
	return rentedSucessfully;
} // bool Shop::RentItemFromStock(std::string customerID, std::string itemID) {

bool Shop::CustomerReturnsItem(std::string customerID, std::string itemID, int numberOfItemsToReturn) {
	bool returnedSucessfully = false;
	RentalItem itemToReturn = RentalItem();
	int indexOfRentalItem = IndexOfRentalItem(itemID);
	int indexOfCustomer = IndexOfCustomer(customerID);
	bool itemPartOfStockSystem = indexOfRentalItem > -1;
	bool customerInSystem = indexOfCustomer > -1;
	if (itemPartOfStockSystem && customerInSystem) {
		bool enoughCopiesToReturn = false;
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
		if (itemPartOfStockSystem == false)
			std::cout << "Item was not part of stock system. Did you correctly input the ID/Title?";
		if (customerInSystem == false)
			std::cout << "Customer is not in system. Did you correctly input thier ID/Name?";
	} // else { //if (itemPartOfStockSystem && customerInSystem) {
	return returnedSucessfully;
} // bool Shop::CustomerReturnsItem(std::string customerID, std::string itemID, int numberOfItemsToRent) {

bool ModifyCustomerTypeLocal(bool customerTypeSet, Customer workingCustomerObject,
	std::string& accountTypeToModify) {
	while (customerTypeSet == false) {
		accountTypeToModify = "";
		std::cout << "What Account Type is this? (Capitalziation matters.)\n";
		for (int i = 0; i < workingCustomerObject.GetAvailableAccountTypes().size(); i++)
			std::cout << workingCustomerObject.GetAvailableAccountTypes()[i] << ", ";
		std::cout << std::endl;
		std::getline(std::cin, accountTypeToModify);
		customerTypeSet = workingCustomerObject.SetAccountType(accountTypeToModify, 
			workingCustomerObject.GetAvailableAccountTypes());
	} // while (loanTypeIncorrect) {
	return customerTypeSet;
}

// Public Functions
// Menu Items 1
bool Shop::AddNewItemToStockList() {
	bool newItemSucessfullyAdded = false;
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
	SetRentalTypeLocal(rentalTypeSet, workingRentalItem, inputRentalType, inputGenre);

	bool loanTypeSet = false;
	loanTypeSet = SetLoanTypeLocal(loanTypeSet, workingRentalItem, inputLoanType);

	bool copiesInStockSet = false;
	copiesInStockSet = SetCopiesInStockLocal(copiesInStockSet, workingRentalItem, inputCopiesInStock);

	bool yearPublishedSet = false;
	yearPublishedSet = SetYearPublishedLocal(yearPublishedSet, workingRentalItem, inputYearPublished);

	bool rentalFeeSet = false;
	rentalFeeSet = SetRentalFeeLocal(rentalFeeSet, workingRentalItem, inputRentalFee);

	if (inputLoanType == "DVD") {
		bool genreTypeSet = false;
		genreTypeSet = SetGenreTypeLocal(genreTypeSet, workingRentalItem, inputGenre);
	}
	else {
		if (rentalTypeSet && loanTypeSet && copiesInStockSet && yearPublishedSet && rentalFeeSet) {
			workingRentalItem = RentalItem(inputTitle, inputRentalType, inputLoanType, inputYearPublished,
				inputCopiesInStock, inputRentalFee);
		}
	}


	stockList.push_back(workingRentalItem);
	return newItemSucessfullyAdded;
} // void Shop::AddNewItemToStockList() {

bool Shop::ModifyItemInStock(std::string itemIdOrTitle) {
	bool modificationComplete = false;
	std::string inputTitle = "";
	std::string inputRentalType;
	std::string inputGenreType;
	std::string inputLoanType;
	std::string inputYearPublished;
	double inputRentalFee;
	int indexOfItem = IndexOfRentalItem(itemIdOrTitle);
	if (indexOfItem > -1) {
		int userModificationInput = 0;
		RentalItem workingItem = stockList[indexOfItem];
		std::cout << "What did you want to change?\n1. The ID\n2. The Title\n3. The Rental Type\n";
		std::cout << "4. The Loan Type\n5. The Year Published \n6. The Rental Fee\n";
		if (stockList[indexOfItem].GetRentalType() == "DVD"){
			std::cout << "7. The Genre\n";
			userModificationInput = GetUserInputInt(1, 7);
		}
		else
			userModificationInput = GetUserInputInt(1, 6);
		switch (userModificationInput) {
		case(1):
			stockList[indexOfItem].SetIdManual(ManualCreateIDRentalItem(stockList[indexOfItem].GetYearPublished()));
			modificationComplete = true;
			break;
		case(2):
			std::cout << "What is the title of this new rental item?\n";
			std::cin.ignore(INT_MAX, '\n');
			std::getline(std::cin, inputTitle);
			stockList[indexOfItem].SetTitle(inputTitle);
			modificationComplete = true;
			break;
		case(3):
			modificationComplete = SetRentalTypeLocal(modificationComplete, workingItem, 
				inputRentalType, inputGenreType);
			if (modificationComplete) {
				stockList[indexOfItem].SetRentalType(inputRentalType);
				stockList[indexOfItem].SetGenre(inputGenreType);
			}
			break;
		case(4):
			modificationComplete = ModiyFromOptionsLocal(modificationComplete, inputLoanType,
				workingItem.GetAvailableLoanTypes(), "What Loan Type is this? (Capitalziation matters.)\n");
			if (modificationComplete)
				stockList[indexOfItem].SetLoanType(inputLoanType);
			break;
		case(5):
			modificationComplete = SetYearPublishedLocal(modificationComplete, workingItem,
				inputYearPublished);
			if(modificationComplete)
				stockList[indexOfItem].SetYearPublished(inputYearPublished);
			break;
		case(6):
			modificationComplete = SetRentalFeeLocal(modificationComplete, workingItem, inputRentalFee);
			if (modificationComplete)
				stockList[indexOfItem].SetRentalFee(inputRentalFee);
			break;
		case(7):
			modificationComplete = SetGenreTypeLocal(modificationComplete, workingItem, inputGenreType);
			if (modificationComplete)
				stockList[indexOfItem].SetGenre(inputGenreType);
			break;
		}
	}
	else { // if (indexOfItem > -1) {
		std::cout << "No such Item in the Stock System. Maybe a different Id or Title?";
		return modificationComplete;
	} // else { // if (indexOfItem > -1) {
	return modificationComplete;
}

bool Shop::DeleteExistingItem(std::string itemIdOrTitle) {
	bool itemDeletedSuccessfully = false;
	int indexOfItem = IndexOfRentalItem(itemIdOrTitle);

	if (indexOfItem > -1) {
		std::vector<RentalItem> updatededRentedList;
			for (int i = 0; i < stockList.size(); i++) {
				if (indexOfItem != i) {
					updatededRentedList.push_back(stockList[i]);
				} // if (indexOfItem != i) {
			} // for (int i = 0; i < workingStockList.size(); i++) {

			indexOfItem = IndexOfRentalItem(itemIdOrTitle, updatededRentedList);
			if (indexOfItem == -1) {
				itemDeletedSuccessfully = true;
				std::cout << fmt::format("Successfully removed {} from stock.\n", itemIdOrTitle);
				SetStockList(updatededRentedList);

			}
	} // if (indexOfItem > -1) {
	else { // if (indexOfItem > -1) {
		std::cout << "That item was not found in the inventory. Maybe you mistyped the name or ID?";

	} // else { // if (indexOfItem > -1) {
	return itemDeletedSuccessfully;
}


// Menu Items 2
bool Shop::AddNewCustomer() {
	bool newCustomerAdded = false;
	std::string nameToAdd = "update this";
	std::string addressToAdd = "update this";
	std::string phoneNumberToAdd = "000-000-0000";
	std::string accountTypeToAdd = "Guest";
	std::vector<RentalItem> listOfRentedItemsToAdd;
	int rewardPointsToAdd = 0;
	int numberOfRentalsRetrunedToAdd = 0;

	std::cout << "What is the name of this new customer?\n";
	std::cin.ignore(INT_MAX, '\n');
	std::getline(std::cin, nameToAdd);

	std::cout << "What is the address of this new customer?\n";
	std::cin.ignore(INT_MAX, '\n');
	std::getline(std::cin, addressToAdd);

	std::cout << "What is the phone number of this new customer?\n";
	std::cin.ignore(INT_MAX, '\n');
	std::getline(std::cin, phoneNumberToAdd);
	
	customerList.push_back(Customer(nameToAdd, addressToAdd, phoneNumberToAdd, accountTypeToAdd, listOfRentedItemsToAdd,
		rewardPointsToAdd, numberOfRentalsRetrunedToAdd));
	newCustomerAdded = true; // this is likely not needed, but incase I change my mind later.
	return newCustomerAdded;
}

bool Shop::ModifyCustomerInfo(std::string customerIdOrTitle) {
	bool customerInfoModified = false;

	std::string idToModify;
	std::string nameToModify = "update this";
	std::string addressToModify = "update this";
	std::string phoneNumberToModify = "000-000-0000";
	std::string accountTypeToModify = "Guest";
	std::vector<RentalItem> listOfRentedItemsToModify;
	int rewardPointsToModify = 0;
	int numberOfRentalsReturnedToModify = 0;
	int indexOfCutomer = IndexOfCustomer(customerIdOrTitle);
	if (indexOfCutomer > -1) {
		int userModificationInput = 0;
		Customer workingCustomerObject = customerList[indexOfCutomer];
		workingCustomerObject.DisplayCustomerInfo();

		std::cout << "What did you want to change?\n1. Modify ID\n2. Modify Name\n3. Modify Address\n";
		std::cout << "4. Modify Phone Nubmer\n5. Modify AccountType\n6. Modify Reward Points\n";
		std::cout << "7. Modify Rentals Returned\n";
		userModificationInput = GetUserInputInt(1, 9);
		switch (userModificationInput) {
		case(1):
			customerInfoModified = ManualCreateIDCustomer(customerList, idToModify);
			customerList[indexOfCutomer].SetID(idToModify);
			break;
		case(2):
			std::cout << "What is the name of this customer?\n";
			std::cin.ignore(INT_MAX, '\n');
			std::getline(std::cin, nameToModify);
			customerInfoModified = true;
			customerList[indexOfCutomer].SetName(nameToModify);
			break;
		case(3):
			std::cout << "What is the address of this customer?\n";
			std::cin.ignore(INT_MAX, '\n');
			std::getline(std::cin, addressToModify);
			customerInfoModified = true;
			customerList[indexOfCutomer].SetAddress(addressToModify);
			break;
		case(4):
			std::cout << "What is the phone number of this customer?\n";
			std::cin.ignore(INT_MAX, '\n');
			std::getline(std::cin, phoneNumberToModify);
			customerInfoModified = true;
			customerList[indexOfCutomer].SetPhoneNumber(phoneNumberToModify);
			break;
		case(5):
			customerInfoModified = ModiyFromOptionsLocal(customerInfoModified, accountTypeToModify,
				workingCustomerObject.GetAvailableAccountTypes(), "What Account Type should be set?\n");
			if (customerInfoModified)
				customerList[indexOfCutomer].SetAccountType(accountTypeToModify,
					workingCustomerObject.GetAvailableAccountTypes());
			break;
		case(6):
			customerInfoModified = InputBasicIntHandlerLocal(rewardPointsToModify, customerInfoModified,
				"How many points should the customer have? (Zero or more)", 0);
			if (customerInfoModified)
				customerList[indexOfCutomer].SetRewardPoints(rewardPointsToModify);
			break;
		case(7):
			customerInfoModified = InputBasicIntHandlerLocal(numberOfRentalsReturnedToModify,
				customerInfoModified, "How many rentals has this customer returned?\n", 0);
			if(customerInfoModified)
				customerList[indexOfCutomer].SetNumberOfRentalsReturned(numberOfRentalsReturnedToModify);
			break;
		}
	}
	return customerInfoModified;
}