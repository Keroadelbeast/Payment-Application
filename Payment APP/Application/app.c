#include"app.h"
#include<stdio.h>
#include<string.h>

#include"../Terminal/terminal.h"
#include"../Card/card.h"
#include"../Server/server.h"
#pragma warning(disable : 4996)



void appStart(void) {
	ST_cardData_t p1;
	ST_terminalData_t term;

	if (getCardHolderName(&p1) == WRONG_NAME) {
		printf("Wrong card holder name\n");
		return;

	}
	if (getCardPAN(&p1) == WRONG_PAN) {
		printf("Wrong card PAN\n");
		return;
	}
	if (getCardExpiryDate(&p1) == WRONG_EXP_DATE) {
		printf("Wrong  Expiry Date\n");
		return;
	}
	if (getTransactionDate(&term) == WRONG_DATE) {
		printf("Wrong transaction date\n");
		return;
	}

	if (isCardExpired(&p1, &term) != TERMINAL_OK) {
		printf("Declined Expired card\n");
	}
	else{
		while (getTransactionAmount(&term) != TERMINAL_OK)
		{
			printf("Wrong trasaction amount enter number > 0 \n");
		}
		setMaxAmount(&term, 30000);


		if (isBelowMaxAmount(&term) != TERMINAL_OK)
		{
			printf("Declined Amount Exceeding Limit 30000\n");
		}
		else
		{
			printf("\n------- terminal data collected  -------\n");

			ST_transaction_t transData = { .cardHolderData = p1 , .terminalData = term };

			char status[5][27] = { "APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };


			EN_transState_t state = recieveTransactionData(&transData);

			printf("\nTransaction shortened state: %s \n", status[(int)state]);
		}

	}


}
int main() {
	appStart();


}