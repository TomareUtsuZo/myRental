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
	int IndexOfRentalItem(std::string itemID);
	int IndexOfRentalItem(std::string itemID, std::vector<RentalItem> workingVector);
	int IndexOfCustomer(std::string customerID);
	int IndexOfCustomer(std::string customerID, std::vector<Customer> workingVector);


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
}; // class MyRentalFunctions

