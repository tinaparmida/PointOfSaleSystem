/* Citation and Sources...
Final Project Milestone q=1
Module: POS
Filename: POS.h
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#ifndef SDDS_POS_H
#define SDDS_POS_H

namespace sdds {



	const int MAX_QUANTITY_VALUE = 999;


	const double TAX = 0.13;
	const int MAX_SKU_LEN = 7;

	const int MIN_YEAR = 2000;
	const int MAX_YEAR = 2030;

	const int MAX_STOCK_NUMBER = 99;
	const int MAX_NO_ITEMS = 200;

	const int MAX_NAME_LEN = 40;

	const int POS_LIST = 1;
	const int POS_FORM = 2;

	const char* const ERROR_POS_SKU = "SKU: Empty or Invalid value!";
	const char* const ERROR_POS_NAME = "Name: Invalid value!";
	const char* const ERROR_POS_PRICE = "Price: Invalid value!";
	const char* const ERROR_POS_TAX = "Taxed: Invalid value!";
	const char* const ERROR_POS_QTY = "Quantity: Invalid value!";
	const char* const ERROR_POS_STOCK = "Not enough items in stock.";
	const char* const ERROR_POS_EMPTY = "Item is empty!";

}

#endif
