#include <stdio.h>
#include <string.h>
#include "terminal.h"
#ifndef term_h
#define term_h
#endif
ST_terminalData_t termData;
ST_cardData_t CardDat;
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Enter the current date DD/MM/YYYY\n");
	gets((char *)termData->transactionDate);
	uint8_t termdate = strlen(termData->transactionDate);
	if (!(termdate == 10)) {
		printf("Wrong transaction date format\n");
		return WRONG_DATE;
	}
	else {
		if (!((((((termData->transactionDate[0] - '0') * 10 + (termData->transactionDate[1] - '0')) <= 31)) && ((termData->transactionDate[2] == '/')) && (termData->transactionDate[5]== '/')) && (((termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0')) <= 12)))
		{
			printf("Wrong transaction date format\n");
			return WRONG_DATE;
		}

		else {
			return TERMINAL_OK;
		}
	}
	return TERMINAL_OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	if(cardData.cardExpirationDate[3] < termData.transactionDate [8]){
	return EXPIRED_CARD;
	}
	if (cardData.cardExpirationDate[3] > termData.transactionDate[8]) {
	return TERMINAL_OK;
	}
	if (cardData.cardExpirationDate[3] = termData.transactionDate[8]) {
		if (cardData.cardExpirationDate[4] < termData.transactionDate[9]) {
			return EXPIRED_CARD;
		}
		if (cardData.cardExpirationDate[4] > termData.transactionDate[9]) {
			return TERMINAL_OK;
		}
		if (cardData.cardExpirationDate[4] = termData.transactionDate[9]) {
			if (cardData.cardExpirationDate[0] > termData.transactionDate[3]) {
				return TERMINAL_OK;
			}
			if (cardData.cardExpirationDate[0] < termData.transactionDate[3]) {
				return EXPIRED_CARD;
			}
			if (cardData.cardExpirationDate[0] = termData.transactionDate[3]) {
				if (cardData.cardExpirationDate[1] <= termData.transactionDate[4]) {
					return EXPIRED_CARD;
				}
				if (cardData.cardExpirationDate[1] > termData.transactionDate[4]) {
					return TERMINAL_OK;
				}
			}
		}
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Pls Enter Transaction Amount\n");
	scanf_s("%f", &termData->transAmount);
	if (!(termData->transAmount > 0))
	{
		printf("The amount you have enterd isn't valid\n");
		return INVALID_AMOUNT;

	}
	return TERMINAL_OK;

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		printf("Declined Amount Exceeding Limit\n");
		printf("THE MA AMOUBNT IS %.2f\n", termData->maxTransAmount);

		return EXCEED_MAX_AMOUNT;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Enter Max Transaction Amount\n");
	scanf_s("%f", &termData->maxTransAmount);
	//printf("%f\n", termData->maxTransAmount);
	if  (!(termData->maxTransAmount > 0)) { 
		printf("INVALID_MAX_AMOUNT\n");
		return INVALID_MAX_AMOUNT;
		
	}
	return TERMINAL_OK;
}


