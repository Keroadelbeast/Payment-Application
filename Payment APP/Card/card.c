#include"card.h"
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable : 4996)

ST_cardData_t p1;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter card holder name:");
	//getchar();
	scanf("%[^\n]s", &cardData->cardHolderName);
	if ((cardData->cardHolderName) == NULL || strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24) {

		//printf("Wrong name,Please enter name with max 25 charachters and not less than 20\n ");
		return WRONG_NAME;
	}
	else {
		//printf("Hello %s\n", cardData->cardHolderName);
		return CARD_OK;

	}

}


void getCardHolderNameTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: getCardHolderName\n\n");
	//ST_cardData_t* t1;
	//t1 = &p1;

	printf("Test Case 1: Card Holder Name is More than 25 Characters\n");
	printf("Input Data: Kyrillos adel sedhom salib\n");
	printf("Expected Result : 1\n");
	printf("Actual Results: %d\n", getCardHolderName(&p1));

	printf("Test Case 2: Card Holder Name is Less than 20 Characters\n");
	printf("Input Data: kyrillos\n");
	printf("Expected Result: 1\n");
	printf("Actual Results: %d\n", getCardHolderName(&p1));

	printf("Test Case 3: Card Holder Name is More than 20 Characters and Less Than 25\n");
	printf("Input Data: Kyrillos adel sedhom\n");
	printf("Expected Result: 0\n");
	printf("Actual Results: %d\n", getCardHolderName(&p1));
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	printf("\nEnter Card expiry date:");
	scanf_s("%s", &cardData->cardExpirationDate, 6);
	if (strlen(cardData->cardExpirationDate) == 5 || cardData->cardExpirationDate != NULL) {
		if (cardData->cardExpirationDate[0] == '0' || cardData->cardExpirationDate[0] == '1') {
			if (isdigit(cardData->cardExpirationDate[1])) {
				if ((cardData->cardExpirationDate[2]) == '/') {
					if (isdigit(cardData->cardExpirationDate[3])) {
						if (isdigit(cardData->cardExpirationDate[4])) {
							return CARD_OK;
						}
						else {
							return WRONG_EXP_DATE;
						}
					}
					else {
						return WRONG_EXP_DATE;
					}
				}
				else {
					return WRONG_EXP_DATE;
				}
			}
			else {
				return WRONG_EXP_DATE;
			}
		}
		else {
			return WRONG_EXP_DATE;
		}
	}
	else {
		return WRONG_EXP_DATE;
	}

}


void getCardExpiryDateTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: getCardExpiryDate\n\n");
	//ST_cardData_t* t1;
	//t1 = &p1;

	printf("Test Case 1: Card expiry date more than 5 numbers \n");
	printf("Input Data:01/252\n");
	printf("Expected Result : 2\n");
	printf("Actual Results: %d\n", getCardExpiryDate(&p1));

	printf("Test Case 2: Card expiry date is Less than 5 numbers\n");
	printf("Input Data: 01/2\n");
	printf("Expected Result: 2\n");
	printf("Actual Results: %d\n", getCardExpiryDate(&p1));

	printf("Test Case 3: Card expiry date is 5 numbers\n");
	printf("Input Data:12/25 \n");
	printf("Expected Result: 0\n");
	printf("Actual Results: %d\n", getCardExpiryDate(&p1));

	printf("Test Case 4:Data entered in Card expiry date is not integers\n");
	printf("Input Data:aa/bb \n");
	printf("Expected Result: 2\n");
	printf("Actual Results: %d\n", getCardExpiryDate(&p1));

	printf("Test Case 5:typed in first element in month more than 1\n");
	printf("Input Data:22/25 \n");
	printf("Expected Result: 2\n");
	printf("Actual Results: %d\n", getCardExpiryDate(&p1));


}




EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter Primary account number:");
	scanf_s("%s", &cardData->primaryAccountNumber, 30);
	getchar();

	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 || (cardData->primaryAccountNumber) == NULL) {
		return WRONG_PAN;
	}
	else {
		return CARD_OK;
	};

}



void getCardPANTest(void) {
	printf("Tester Name: Kyrillos Adel\n");
	printf("Function Name: getCardPAN\n\n");
	//ST_cardData_t* t1;
	//t1 = &p1;

	printf("Test Case 1: Card pan more than 19 numbers\n");
	printf("Input Data:123456789123456789123456\n");
	printf("Expected Result : 3\n");
	printf("Actual Results: %d\n", getCardPAN(&p1));

	printf("Test Case 2: Card pan less than 16 numbers\n");
	printf("Input Data: 123456789\n");
	printf("Expected Result: 3\n");
	printf("Actual Results: %d\n", getCardPAN(&p1));

	printf("Test Case 3: Card pan less than 19 numbers & more than 16 numbers\n");
	printf("Input Data: 123456789123456789\n");
	printf("Expected Result: 0\n");
	printf("Actual Results: %d\n", getCardPAN(&p1));
}
