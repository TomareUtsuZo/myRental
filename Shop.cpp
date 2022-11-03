#include "Shop.h"
#include <vector>
#include <iostream>
#include <fmt/format.h>


// Constructor
Shop::Shop(/*std::string newShopID, std::string newShopName, std::string newShopAddress,*/
	std::vector<RentalItem> newStockList, std::vector<Customer> newCustomerList) :
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

// Public Setters and Getters
void Shop::SetStockList(std::vector<RentalItem> newStockList) { stockList = newStockList; }
std::vector<RentalItem> Shop::GetStockList() { return stockList; }

void Shop::SetCustomerList(std::vector<Customer> newCustomerList) { customerList = newCustomerList; }
std::vector<Customer> Shop::GetCustomerList() { return customerList; }

// Public Functions
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

void Shop::AddNewItemToStockList() {

} // void Shop::AddNewItemToStockList() {