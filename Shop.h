#pragma once 
#include <iostream>
#include "RentalItem.h"
#include "Shop.h"
#include "Customer.h"
#include "Video.h"


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


public:
	// Constructor
	Shop(/*std::string newShopID, std::string newShopName, std::string newShopAddress,*/
		std::vector<RentalItem> newStockList, std::vector<Customer> newCustomerList);

	// Public Setters and Getters
	void SetStockList(std::vector<RentalItem> newStockList);
	std::vector<RentalItem> GetStockList();

	void SetCustomerList(std::vector<Customer> newCustomerList);
	std::vector<Customer> GetCustomerList();

	// Public Functions
	bool CustomerRentsItem(std::string customerID, std::string itemID, int numberOfItemsToRent,
		bool rentWithPoints);
	
	bool CustomerReturnsItem(std::string customerID, std::string itemID, int numberOfItemsToRent);

}; // class MyRentalFunctions

