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
	int IndexOfCustomer(std::string customerID);
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
	bool AddNewItemToStockList();

	bool ModifyItemInStock(std::string itemIdOrTitle);

}; // class MyRentalFunctions

