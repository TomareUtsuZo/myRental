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
	template<class T>
	Shop(/*std::string newShopID, std::string newShopName, std::string newShopAddress,*/
		std::vector<T> newStockList, std::vector<T> newCustomerList);

	// Public Setters and Getters
	void SetStockList(std::vector<RentalItem> newStockList);
	std::vector<RentalItem> GetStockList();

	template<class T>
	void SetCustomerList(std::vector<T> newCustomerList);
	template<class T>
	std::vector<T> GetCustomerList();

	// Public Functions
	bool AddNewItemToStockList();

}; // class MyRentalFunctions

