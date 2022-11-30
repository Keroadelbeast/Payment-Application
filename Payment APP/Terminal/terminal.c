#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<string.h>
#include"../Card/card.h"
#include"terminal.h"
#include<ctype.h>



ST_terminalData_t term;
ST_cardData_t p1;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Enter Transaction Date:");
	//fseek(stdin, 0, SEEK_END); //Ignoring any past input
	scanf_s("%s", termData->transactionDate, 11);


	SYSTEMTIME CurrentTime;
	GetLocalTime(&CurrentTime);
	printf(termData->transactionDate, "%.2d/%.2d/%.4d\n", CurrentTime.wDay,
		CurrentTime.wMonth,
		CurrentTime.wYear);
	if (strlen(termData->transactionDate) != 10 || termData->transactionDate == NULL) {
		if (termData->transactionDate[2] != '/' || termData->transactionDate[5] == '/') {

			return WRONG_DATE;

		}
		else {
			return TERMINAL_OK;
		}
	}
	else {
		return TERMINAL_OK;
	}




}

void getTransactionDateTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: getTransactionDate\n\n");
	//ST_cardData_t* t1;
	//t1 = &p1;

	printf("Test Case 1: Card transaction date is more than 10 characters\n");
	printf("Input Data: 15/10/20000\n");
	printf("Expected Result : 1\n");
	printf("Actual Results: %d\n", getTransactionDate(&term));

	printf("Test Case 2: Card transaction date doesnt contain '/' \n");
	printf("Input Data: 41122000\n");
	printf("Expected Result: 1\n");
	printf("Actual Results: %d\n", getTransactionDate(&term));

	printf("Test Case 3: Card transaction date is null\n");
	printf("Input Data: 0000000000\n");
	printf("Expected Result: 1\n");
	printf("Actual Results: %d\n", getTransactionDate(&term));

	printf("Test Case 4: card transaction date is good\n");
	printf("Input Data: 12/11/2023\n");
	printf("Expected Result: 0\n");
	printf("Actual Results: %d\n", getTransactionDate(&term));

}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {


	uint8_t expireMounth = ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
	uint8_t expireYear = ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');

	/* Get current Month and Year in integers for comparison */
	uint8_t currentMounth = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
	uint8_t currentYear = ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

	if (currentYear > expireYear)
	{
		return EXPIRED_CARD;
	}
	else if (currentYear == expireYear)
	{
		if (currentMounth > expireMounth)
		{
			return EXPIRED_CARD;
		}
	}
	return TERMINAL_OK;


}

void isCardExpriedTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: isCardExpired\n\n");

	printf("Test Case 1: Card expiry date same as transaction date\n");
	printf("Input Data: \n");
	printf("Expected Result : 0\n");
	printf("Card expiry date: %d\n", getCardExpiryDate(&p1));
	printf("Transaction date: %d\n", getTransactionDate(&term));
	printf("Actual Results: %d\n", isCardExpired(&p1, &term));


	printf("Test Case 2: Card expiry date ends before transaction date\n");
	printf("Input Data: \n");
	printf("Expected Result : 2\n");
	printf("Card expiry date: %d\n", getCardExpiryDate(&p1));
	printf("Transaction date: %d\n", getTransactionDate(&term));
	printf("Actual Results: %d\n", isCardExpired(&p1, &term));

	printf("Test Case 3: Card expiry date is after transaction date\n");
	printf("Input Data: \n");
	printf("Expected Result : 0\n");
	printf("Card expiry date: %d\n", getCardExpiryDate(&p1));
	printf("Transaction date: %d\n", getTransactionDate(&term));
	printf("Actual Results: %d\n", isCardExpired(&p1, &term));


}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

	printf("Please enter the Transaction Amount: ");
	scanf_s("%f", &termData->transAmount);
	if ((termData->transAmount) <= 0)
		return INVALID_AMOUNT;

	//	printf("Your Transaction Amount is: %f\n", termData->transAmount);

	return TERMINAL_OK;
}

void getTransactionAmountTest(void)
{
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: getTransactionAmount\n\n");


	printf("Test Case 1:  get Card transaction amount \n");
	printf("Input Data: 1500\n");
	printf("Expected Result : 0\n");
	printf("Actual Results: %d\n", getTransactionAmount(&term));

	printf("Test Case 2: Card transaction amount < 0\n");
	printf("Input Data: -1500\n");
	printf("Expected Result : 4\n");
	printf("Actual Results: %d\n", getTransactionAmount(&term));


}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {

	termData->maxTransAmount = maxAmount;

	printf("Max Transaction Amount is : %f\n", termData->maxTransAmount);

	if ((termData->maxTransAmount) <= 0)
		return INVALID_MAX_AMOUNT;

	return TERMINAL_OK;

}

void setMaxAmountTest(void) {
	printf("Tester Name:Kyrillos Adel\n");
	printf("Function Name:setMaxAmount\n");
	printf("getting Maximum Amount \n ");

	printf("Test Case 1:  get Card  maximum amount \n");
	printf("Input Data: 15000\n");
	printf("Expected Result : 0\n");
	printf("Actual Results: %d\n", setMaxAmount(&term, 15000));

	printf("Test Case 2: Card transaction amount < 0\n");
	printf("Input Data: -1500.263\n");
	printf("Expected Result : 6\n");
	printf("Actual Results: %d\n", setMaxAmount(&term, -1500.263));
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if ((termData->transAmount) > (termData->maxTransAmount))
		return EXCEED_MAX_AMOUNT;

	return TERMINAL_OK;

}

void isBelowMaxAmountTest(void) {
	printf("Tester Name:Kyrillos Adel\n");
	printf("Function Name:isBelowMaxAmount\n");
	printf("Checking Transaction Amount is Eligible \n ");

	printf("Test Case 1: amount of transaction is more than max amount\n");
	printf("Input Data:15000 \n");
	printf("Expected Result : 5\n");
	printf("Amount of Transaction: %d\n", getTransactionAmount(&term));
	printf("Transaction maximum amount: %d\n", setMaxAmount(&term,1500));
	printf("Actual Results: %d\n", isBelowMaxAmount(&term));

	printf("Test Case 2: amount of transaction is below max amount\n");
	printf("Input Data:1200 \n");
	printf("Expected Result : 0\n");
	printf("Amount of Transaction: %d\n", getTransactionAmount(&term));
	printf("Transaction maximum amount: %d\n", setMaxAmount(&term, 1500));
	printf("Actual Results: %d\n", isBelowMaxAmount(&term));

	printf("Test Case 3: amount of transaction is equal to max amount\n");
	printf("Input Data:1500 \n");
	printf("Expected Result : 0\n");
	printf("Amount of Transaction: %d\n", getTransactionAmount(&term));
	printf("Transaction maximum amount: %d\n", setMaxAmount(&term, 1500));
	printf("Actual Results: %d\n", isBelowMaxAmount(&term));


}





