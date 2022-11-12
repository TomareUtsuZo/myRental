// myRental.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RentalItem.h"
#include "Shop.h"
#include "Customer.h"

int RentalItem::s_numberOfItemsAdded{ 0 }; // start counting number of items created
int Customer::s_numberOfCustomersServiced{ 0 }; // start counting number of customers serviced



int main()
{
    std::vector<RentalItem> stockList;
    
    std::vector<RentalItem> customerStockList;
    std::vector<Customer> customerList;
    customerList.push_back(Customer("Carl", "200 Duong D5", "0903702342", "Guest", 
        customerStockList, 900, 3));
    
    Shop shopOne = Shop(stockList, customerList);
    std::vector<RentalItem> workingList = {
        RentalItem("Movie", "DVD", "two day rental", "2000", 13, 0.99, "Action"),
        RentalItem("A Movie", "DVD", "two day rental", "1999", 3, 1.99, "Drama"),
        RentalItem("Great Game", "Game", "two day rental", "2020", 1, 3.00),
        RentalItem("Great Game II", "Game", "two day rental", "2020", 0, 3.00),
        RentalItem("Great Game III", "Game", "two day rental", "2020", 0, 3.00)
    };
    shopOne.SetStockList(workingList);
    //std::cout << shopOne.ModifyItemInStock("Movie");
    //std::cout << shopOne.DeleteExistingItem("I001-1999") << std::endl;


    for (int i = 0; i < shopOne.GetCustomerList().size(); i++)
        shopOne.GetCustomerList()[i].DisplayCustomerInfo();
    // shopOne.ModifyCustomerInfo("Carl");
    // shopOne.PromoteExistingCustomer("Carl");
    // shopOne.PromoteExistingCustomer("Carl");
    shopOne.RentItemToCustomer("Carl", "Movie");
    shopOne.DisplayOutOfStockItems();
    shopOne.ReturnItemFromCustomer("Carl", "Movie");
    for(int i = 0; i < shopOne.GetCustomerList().size(); i++)
        shopOne.GetCustomerList()[i].DisplayCustomerInfo();
    for (int i = 0; i < shopOne.GetStockList().size(); i++)
        shopOne.GetStockList()[i].DisplayItemInfo();

        
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
