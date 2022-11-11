#pragma once 
#include <iostream>
#include "RentalItem.h"
#include "Customer.h"


class Shop
{
private:/*
	std::string shopID;
	std::string shopName;
	std::string shopAddress;
	std::string phoneNumber;*/
	std::vector<RentalItem> stockList;
	std::vector<Customer> customerList;


	// internal methods
	int GetIndexOfRentalItem(std::string itemID);
	int GetIndexOfRentalItem(std::string itemID, std::vector<RentalItem> workingVector);
	int GetIndexOfCustomer(std::string customerID);
	int GetIndexOfCustomer(std::string customerID, std::vector<Customer> workingVector);
	bool CustomerRentsItem(std::string customerID, std::string itemID, int numberOfItemsToRent,
		bool rentWithPoints);
	bool CustomerReturnsItem(std::string customerID, std::string itemID, int numberOfItemsToReturn);


public:
	// Constructor
	Shop(std::vector<RentalItem> newStockList, std::vector<Customer> newCustomerList);

	// Public Setters and Getters
	void SetStockList(std::vector<RentalItem> newStockList);
	std::vector<RentalItem> GetStockList();

	void SetCustomerList(std::vector<Customer> newCustomerList);
	std::vector<Customer> GetCustomerList();

	// Public Functions
	// Menu 1 Options 
	bool AddNewItemToStockList();
	bool ModifyItemInStock(std::string itemIdOrTitle);
	bool DeleteExistingItem(std::string itemIdOrTitle);
	// Menu 2 Options
	bool AddNewCustomer();
	bool ModifyCustomerInfo(std::string customerIdOrTitle);
	// Menu 3 Promote Existing Customer
	bool PromoteExistingCustomer(std::string customerIdOrTitle);
	// Menu 4 Rent Item
	bool RentItem(std::string customerIdOrName, std::string itemIdOrTitle);
}; // class MyRentalFunctions

