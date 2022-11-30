#include"../Standards/std.h"
#include"../Card/card.h"
#include"../Terminal/terminal.h"
#include"server.h"
#include<stdio.h>
#include<string.h>
#pragma warning(disable : 4996)

ST_terminalData_t term;
ST_cardData_t p1;
EN_transState_t result;
ST_transaction_t trans;

ST_accountsDB_t accountsDB[255] = {
	{ 2000.0, RUNNING, "8989374615436851"},
	{100000.0, BLOCKED,"5807007076043875"},
	{5000.0, RUNNING,  "6807007073813876"},
	{ 68000.0, BLOCKED,"1589374619646851"}
};

ST_transaction_t transactionDB[255] = { {0,0,0,0} };
//static uint32_t transCounter = 1;
ST_accountsDB_t acc;
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	transData->transState = APPROVED;
	if (isValidAccount(&transData->cardHolderData, &acc) == ACCOUNT_NOT_FOUND)
	{
		//printf("This Account can't be found\n");
		transData->transState = FRAUD_CARD;
		return FRAUD_CARD;
	}

	else if (isAmountAvailable(&transData->terminalData, &acc) == LOW_BALANCE) {
		//printf("This amount is not available\n");
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	else if (isBlockedAccount(&acc) == BLOCKED_ACCOUNT) {
		//printf("This account is blocked\n");
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}

	else if (saveTransaction(transData) == SAVING_FAILED) {
		//printf("This transaction can't proceed\n");
		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}

	//printf("Approved Transaction\n");
	else if (transData->transState == APPROVED) {


		for (uint32_t f = 0; f <= 255; f++)
		{

			if (strcmp(transData->cardHolderData.primaryAccountNumber, accountsDB[f].primaryAccountNumber) == 0)
			{
				printf("Your Old Balance is: %f\n", accountsDB[f].balance);
				accountsDB[f].balance -= transData->terminalData.transAmount;

				printf("Your New Balance is: %f\n", accountsDB[f].balance);
				break;
			}
		}
	}
	return transData->transState;

}
void recieveTransactionDataTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: recieveTransactionData\n");

	printf("Test Case 1: Account Exists and there is no problem\n");
	printf("Input Data: 8989374615436851 \n");
	printf("Expected Result : 0\n");
	printf("Card holder Pan: %d\n", getCardPAN(&trans));
	printf("Availability of card:%d\n", isValidAccount(&trans, &acc));
	printf("Account Status: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&trans.terminalData));
	printf("Availability of Amount: %d\n", isAmountAvailable(&trans, &acc));
	printf("check if Transaction is saved:%d\n", saveTransaction(&trans));
	printf("Actual Results: %d\n", recieveTransactionData(&trans));


	printf("Test Case 2: Account doesn't exist and there is a problem\n");
	printf("Input Data: 8989374615436866 \n");
	printf("Expected Result : 3\n");
	printf("Card holder Pan: %d\n", getCardPAN(&trans));
	printf("Availability of card:%d\n", isValidAccount(&trans, &acc));
	printf("Account Status: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&trans.terminalData));
	printf("Availability of Amount: %d\n", isAmountAvailable(&trans, &acc));
	printf("check if Transaction is saved:%d\n", saveTransaction(&trans));
	printf("Actual Results: %d\n", recieveTransactionData(&trans));

	printf("Test Case 3: Account has no sufficent fund\n");
	printf("Input Data: 8989374615436851 \n");
	printf("Expected Result : 1\n");
	printf("Card holder Pan: %d\n", getCardPAN(&trans));
	printf("Availability of card:%d\n", isValidAccount(&trans, &acc));
	printf("Account Status: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&trans.terminalData));
	printf("Availability of Amount: %d\n", isAmountAvailable(&trans, &acc));
	printf("check if Transaction is saved:%d\n", saveTransaction(&trans));
	printf("Actual Results: %d\n", recieveTransactionData(&trans));

	printf("Test Case 4: Account is blocked\n");
	printf("Input Data: 5807007076043875 \n");
	printf("Expected Result : 2\n");
	printf("Card holder Pan: %d\n", getCardPAN(&trans));
	printf("Availability of card:%d\n", isValidAccount(&trans, &acc));
	printf("Account Status: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&trans.terminalData));
	printf("Availability of Amount: %d\n", isAmountAvailable(&trans, &acc));
	printf("check if Transaction is saved:%d\n", saveTransaction(&trans));
	printf("Actual Results: %d\n", recieveTransactionData(&trans));

	printf("Test Case 5: Account transaction isn't saved\n");
	printf("Input Data: 5807007076043848 \n");
	printf("Expected Result : 4\n");
	printf("Card holder Pan: %d\n", getCardPAN(&trans));
	printf("Availability of card:%d\n", isValidAccount(&trans, &acc));
	printf("Account Status: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&trans.terminalData));
	printf("Availability of Amount: %d\n", isAmountAvailable(&trans, &acc));
	printf("check if Transaction is saved:%d\n", saveTransaction(&trans));
	printf("Actual Results: %d\n", recieveTransactionData(&trans));




}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {

	for (uint32_t i = 0; i < 4; i++) {
		if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {


			accountRefrence->state = accountsDB[i].state;
			accountRefrence->balance = accountsDB[i].balance;


			return SERVER_OK;
		}

	}
	return ACCOUNT_NOT_FOUND;
	//printf("Account Reference is: NULL");

}

void isValidAccountTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: isValidAccount\n");

	printf("Test Case 1: Account Exists and there is no problem\n");
	printf("Input Data: 8989374615436851 \n");
	printf("Expected Result : 0\n");
	printf("Card holder Pan: %d\n", getCardPAN(&p1));
	printf("Actual Results: %d\n", isValidAccount(&p1, &acc));

	printf("Test Case 2: Account doesn't exist and there is a problem\n");
	printf("Input Data: 8989374615436843 \n");
	printf("Expected Result : 3\n");
	printf("Card holder Pan: %d\n", getCardPAN(&p1));
	printf("Actual Results: %d\n", isValidAccount(&p1, &acc));

}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == BLOCKED) {
		//printf("This Account is Blocked");
		return BLOCKED_ACCOUNT;
	}
	if (accountRefrence->state == RUNNING) {
		//printf("This Account is Running");
		return SERVER_OK;
	}
}

void isBlockedAccountTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: isBlockedAccount\n");

	printf("Test Case 1: Account is Blocked\n");
	printf("Input Data: 5807007076043875\n");
	printf("Expected Result : 5\n");
	printf("Card holder Pan: %d\n", getCardPAN(&p1));
	printf("Is Valid account:%d\n", isValidAccount(&p1, &acc));
	printf("Actual Results: %d\n", isBlockedAccount(&acc));

	printf("Test Case 2: Account is Running\n");
	printf("Input Data: 8989374615436851 \n");
	printf("Expected Result : 0\n");
	printf("Card holder Pan: %d\n", getCardPAN(&p1));
	printf("Is Valid account:%d\n", isValidAccount(&p1, &acc));
	printf("Actual Results: %d\n", isBlockedAccount(&acc));
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == RUNNING && termData->transAmount <= accountRefrence->balance) {
		return SERVER_OK;
	}
	
		return LOW_BALANCE;
	
}

void isAmountAvailableTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: isAmountAvailable\n");

	printf("Test Case 1: Amount of transaction is less than that in balance but is blocked\n");
	printf("Input Data: 5807007076043875\n");
	printf("Expected Result : 5\n");
	printf("Card holder Pan: %d\n", getCardPAN(&p1));
	printf("Is Valid account:%d\n", isValidAccount(&p1, &acc));
	printf("Check if blocked or running: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&term));
	printf("Actual Result:%d\n", isAmountAvailable(&term, &acc));

	printf("Test Case 2: Amount of transaction is more than that in balance but is blocked\n");
	printf("Input Data: 5807007076043875\n");
	printf("Expected Result : 5\n");
	printf("Card holder Pan: %d\n", getCardPAN(&p1));
	printf("Is Valid account:%d\n", isValidAccount(&p1, &acc));
	printf("Check if blocked or running: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&term));
	printf("Actual Result:%d\n", isAmountAvailable(&term, &acc));

	printf("Test Case 3: Amount of transaction is more than that in balance and running account\n");
	printf("Input Data:6807007073813876 \n");
	printf("Expected Result : 5\n");
	printf("Card holder Pan: %d\n", getCardPAN(&p1));
	printf("Is Valid account:%d\n", isValidAccount(&p1, &acc));
	printf("Check if blocked or running: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&term));
	printf("Actual Result:%d\n", isAmountAvailable(&term, &acc));

	printf("Test Case 4: Amount of transaction is less than that in balance and is running\n");
	printf("Input Data: 6807007073813876\n");
	printf("Expected Result : 5\n");
	printf("Card holder Pan: %d\n", getCardPAN(&p1));
	printf("Is Valid account:%d\n", isValidAccount(&p1, &acc));
	printf("Check if blocked or running: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&term));
	printf("Actual Result:%d\n", isAmountAvailable(&term, &acc));

}


uint32_t seqNum = 0;
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{

	if (transData->transState == FRAUD_CARD)
	{

		return SAVING_FAILED;
	}

	else if (transData->transState == DECLINED_INSUFFECIENT_FUND) {

		return SAVING_FAILED;

	}

	else if (transData->transState == DECLINED_STOLEN_CARD) {

		return SAVING_FAILED;
	}

	else if (transData->transState == INTERNAL_SERVER_ERROR) {
		return SAVING_FAILED;
	}
	else if (transData->transState == APPROVED) {
		transData->transactionSequenceNumber = 0 + seqNum;
		if (transData->transactionSequenceNumber < 255)
		{
			transactionDB[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
			transactionDB[transData->transactionSequenceNumber].terminalData = transData->terminalData;
			transactionDB[transData->transactionSequenceNumber].transState = transData->transState;
			transactionDB[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber + 1;

			seqNum++;
			listSavedTransactions();
			return SERVER_OK;
		}
	}



}
void saveTransactionTest(void) {
	char state[5][27] = { "APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: saveTransaction\n");

	printf("Test Case 1: Transaction is saved\n");
	printf("Input Data:8989374615436851\n");
	printf("Expected Result : 0\n");
	printf("Transaction Sequence Number : %d\n", seqNum);
	printf("PAN : %d\n", getCardPAN(&trans));
	printf("Card Holder Name : %d\n", getCardHolderName(&trans));
	printf("Card Expiration Date : %d\n", getCardExpiryDate(&trans));
	printf("Is Valid account:%d\n", isValidAccount(&trans, &acc));
	printf("Check if blocked or running: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&trans.terminalData));
	printf("Amount availability:%d\n", isAmountAvailable(&trans.terminalData, &acc));
	printf("Transaction Date : %d\n", getTransactionDate(&trans));
	printf("Recieve data: %d\n", recieveTransactionData(&trans));
	printf("Actual result:%d\n", saveTransaction(&trans));

	printf("\nTest Case 2: Transaction isn't saved as there was an error\n");
	printf("Input Data:8989374615436865\n");
	printf("Expected Result : 1\n");
	printf("Transaction Sequence Number : %d\n", seqNum);
	printf("PAN : %d\n", getCardPAN(&trans));
	printf("Card Holder Name :%d\n", getCardHolderName(&trans.cardHolderData));
	printf("Card Expiration Date : %d\n", getCardExpiryDate(&trans));
	printf("Is Valid account:%d\n", isValidAccount(&trans, &acc));
	printf("Check if blocked or running: %d\n", isBlockedAccount(&acc));
	printf("Amount of transaction: %d\n", getTransactionAmount(&trans.terminalData));
	printf("Amount availability:%d\n", isAmountAvailable(&trans, &acc));
	printf("Terminal Max Amount : %d\n", setMaxAmount(&trans, 500));
	printf("Transaction Date : %d\n", getTransactionDate(&trans));
	printf("Recieve data: %d\n", recieveTransactionData(&trans));
	printf("Actual result:%d\n", saveTransaction(&trans));


}


void listSavedTransactions(void) {

	char state[5][27] = { "APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
	for (uint8_t i = 0; i < seqNum; i++) {

		printf("\n#######################\n");
		printf("Transaction Sequence Number : %d\n", seqNum);
		printf("Transaction Date : %s\n", transactionDB[i].terminalData.transactionDate);
		printf("Transaction Amount : %.02f\n", transactionDB[i].terminalData.transAmount);
		uint16_t status = accountsDB[i].state;
		printf("Transaction State : %s\n", state[status]);
		printf("Terminal Max Amount : %.02f\n", transactionDB[i].terminalData.maxTransAmount);
		printf("Card Holder Name : %s\n", transactionDB[i].cardHolderData.cardHolderName);
		printf("PAN : %s\n", transactionDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date : %s\n", transactionDB[i].cardHolderData.cardExpirationDate);
		printf("#######################\n");
	}

}
void listSavedTransactionsTest(void) {
	ST_cardData_t card[1] =
	{
		{.cardExpirationDate = "05/22",.cardHolderName = "kyrillos adel sedhom",.primaryAccountNumber = "36599236423902204"},

	};

	ST_terminalData_t term[1] =
	{
		{.maxTransAmount = 10000,.transactionDate = "05/02/2022",.transAmount = 500},

	};

	EN_transState_t state[2] = { APPROVED,DECLINED_STOLEN_CARD };

	printf("Tester Name: Kyrillos Adel\n");
	printf("Functions Name: saveTransactionTest & listSavedTransactions\n");

	ST_transaction_t trans1 = { .cardHolderData = card[0],.terminalData = term[0],.transactionSequenceNumber = 0,.transState = state[0] };
	printf("Test Case 1: \n");
	saveTransaction(&trans1);
}
