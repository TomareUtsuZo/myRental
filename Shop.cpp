#include "Shop.h"
#include <vector>
#include <iostream>


// Constructor
Shop::Shop(/*std::string newShopID, std::string newShopName, std::string newShopAddress,*/
	std::vector<RentalItem> newStockList, std::vector<Customer> newCustomerList) :
	stockList(newStockList), customerList(newCustomerList) {}

// Private Methods
int Shop::IndexOfRentalItem(std::string itemID) {
	int indexOfRentalItem = -1;
	for(int i = 0; i < stockList.size(); i++) {
		if (stockList[i].GetID() == itemID) {
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
	} // for (int i = 0; i < customerList.size(); i++) {
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
	bool itemPartOfStockSytem = indexOfRentalItem > -1;
	bool customerInSystem = indexOfCustomer > -1;
	if (itemPartOfStockSytem && customerInSystem) {
		itemToRent = stockList[indexOfRentalItem];
		bool enoughCopiesInStock = itemToRent.GetCopiesInStock() >= numberOfItemsToRent;
		if (enoughCopiesInStock) {
			stockList[indexOfRentalItem].DecreaseStock(numberOfItemsToRent);
			bool customerHasEnoughPoints = customerList[indexOfCustomer].GetRewardPoints() >= 100;
			if (rentWithPoints && customerHasEnoughPoints) {
				customerList[indexOfCustomer].RentThisWithPoints(itemToRent, numberOfItemsToRent);
				rentedSucessfully = true;
			} // if (rentWithPoints) {
			else { // if (rentWithPoints) {
				customerList[indexOfCustomer].RentThisItem(itemToRent, numberOfItemsToRent);
				rentedSucessfully = true;
			} // else { // if (rentWithPoints) {
		} // if (enoughCopiesInStock) {
	}
	return rentedSucessfully;
} // bool Shop::RentItemFromStock(std::string customerID, std::string itemID) {

bool Shop::CustomerReturnsItem(std::string customerID, std::string itemID, int numberOfItemsToRent) {

} // bool Shop::CustomerReturnsItem(std::string customerID, std::string itemID, int numberOfItemsToRent) {