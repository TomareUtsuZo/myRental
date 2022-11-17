#include "RentalItem.h"
#include <fmt/format.h>	
#include <string>
#include <sstream>
#include <iostream>


// Constructors
RentalItem::RentalItem() {}
RentalItem::RentalItem(std::string newTitle, std::string newRentalType,
	std::string newLoanType, std::string newYearPublished, int initialCopiesInStock,
	double newRentalFee, std::string newGenre) : title(newTitle), rentalType(newRentalType),
	loanType(newLoanType), yearPublished(newYearPublished), copiesInStock(initialCopiesInStock),
	rentalFee(newRentalFee), genre(newGenre) {
	SetID(stoi(newYearPublished), "I-10"); }



// Private Setters and Getters
void RentalItem::SetIsAvailableForRent() {
	if (GetCopiesInStock() > 0) {
		isAvailableForRent = true;
	} // if (isAvailableForRent < 0) {
	else { //if (isAvailableForRent < 0) {
		isAvailableForRent = false;
	} // else { //if (isAvailableForRent < 0) {	
} // void SetIsAvailableForRent() {

// Public Setters and Getters
std::string RentalItem::GetID() { return id; }
void RentalItem::SetID(int yearPublished, std::string newID) {
	int newIDNumber = stoi(newID.substr(1, 3));
	int oldIDNumber = stoi(id.substr(1, 3));
	if (newIDNumber != -10){
		s_rentalIdUsed[oldIDNumber] = false;

		while (s_rentalIdUsed[newIDNumber]) {
			std::cout << newIDNumber << " is already in use. Try another xxx number.\n";
			std::cin >> newIDNumber;
		}
	}
	else {
		for(int i = 0; i < 1000; i++){
			if (s_rentalIdUsed[i] == false) {
				newIDNumber = i;
				break;
			}
		}
	}
	if (s_rentalIdUsed[newIDNumber] == false) {
		id = fmt::format("I{:03}-{}", newIDNumber, yearPublished);
		s_rentalIdUsed[newIDNumber] = true;
	}
}

std::string RentalItem::GetTitle() { return title; }
void RentalItem::SetTitle(std::string newTitle) { title = newTitle; }

std::string RentalItem::GetRentalType() { return rentalType; }
bool RentalItem::SetRentalType(std::string newRentalType) {
	bool thisIsRentalType = std::find(availableRentalTypes.begin(), availableRentalTypes.end(), newRentalType) != availableRentalTypes.end();
	if (thisIsRentalType == true)
		rentalType = newRentalType;
	return thisIsRentalType;
} // bool RentalItems::SetRentalType(std::string newRentalType) {
std::vector<std::string> RentalItem::GetAvailableRentalTypes() { return availableRentalTypes; }

std::string RentalItem::GetLoanType() { return loanType; }
bool RentalItem::SetLoanType(std::string newLoanType) { 
	bool thisIsLoanType = std::find(availableLoanTypes.begin(), availableLoanTypes.end(), newLoanType) != availableLoanTypes.end();
	if (thisIsLoanType == true)
		loanType = newLoanType; 
	return thisIsLoanType;
} // bool RentalItems::SetRentalType(std::string newRentalType) {
std::vector<std::string> RentalItem::GetAvailableLoanTypes() { return availableLoanTypes; }

int RentalItem::GetCopiesInStock() { return copiesInStock; }
void RentalItem::SetCopiesInStock(int newCopiesInStock) { copiesInStock = newCopiesInStock; }

double RentalItem::GetRentalFee() { return rentalFee; }
void RentalItem::SetRentalFee(double newRentalFee) { rentalFee = newRentalFee; }

bool RentalItem::GetIsAvailableForRent() { return isAvailableForRent; }

std::string RentalItem::GetGenre() { return genre; }
bool RentalItem::SetGenre(std::string newGenre) {
	bool thisIsPassed = std::find(availableGenres.begin(), availableGenres.end(), newGenre) != availableGenres.end();
	if (thisIsPassed == true)
		genre = newGenre;
	return thisIsPassed;
} // bool Videos::SetGenre(std::string newGenre) {
std::vector<std::string> RentalItem::GetAvailableGenres() { return availableGenres;  }

std::string RentalItem::GetYearPublished() { return yearPublished; }
bool RentalItem::SetYearPublished(std::string yearPublishedInput) {
	bool yearPublishedWasSet = false;
	try {
		int makeAnInt;
		std::stringstream(yearPublishedInput) >> makeAnInt;
		if (makeAnInt > 1882) {
			yearPublished = yearPublishedInput;
			yearPublishedWasSet = true;
		} // if (stoi(yearPublishedInput) > 1882) {
		else
			throw yearPublishedInput;
	} // try {
	catch (std::string error){
		std::cout << error << " is an incorect year.\n";
	}
	return yearPublishedWasSet;
}

// Public interfaces
bool RentalItem::IncreaseStock(int numberOfNewCopies) {
	SetCopiesInStock(GetCopiesInStock() + numberOfNewCopies);
	return true;
} // void RentalItems::IncreaseStock(int numberOfNewCopies) {

bool RentalItem::DecreaseStock(int numberOfRemovedCopies) {
	bool thisGotDone = false;
	if (numberOfRemovedCopies <= GetCopiesInStock()) {
		SetCopiesInStock(GetCopiesInStock() - numberOfRemovedCopies);
		thisGotDone = true;
	} // if (numberOfRemovedCopies = < GetCopiesInStock()) {
	return thisGotDone;
} // bool RentalItems::DecreaseStock(int numberOfRemovedCopies) {


void RentalItem::DisplayItemInfo() {
	std::cout << fmt::format("\nID\t\t\t{}\n", GetID());
	std::cout << fmt::format("Title\t\t\t{}\n", GetTitle());
	std::cout << fmt::format("Year Published\t\t{}\n", GetYearPublished());
	std::cout << fmt::format("Rental Type:\t\t{}\n", GetRentalType());
	std::cout << fmt::format("Loan Type\t\t{}\n", GetLoanType());
	std::cout << fmt::format("Copies in stock\t\t{}\n", GetCopiesInStock());
	std::cout << fmt::format("Rental Fee\t\t{:.2f}\n", GetRentalFee());
} // void RentalItems:RentFromStock:DisplayItemInfo() {


