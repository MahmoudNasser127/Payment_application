#include "app.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction_t transData;
int transno;


void appStart() {
setMaxAmount:
	if (setMaxAmount(&termData) == INVALID_MAX_AMOUNT) {
		goto setMaxAmount;
	}
	transData.transactionSequenceNumber = 0;
	
	while (1)
	{

	name_step:
		
		printf("Enter card holder name\n");
		gets(cardData.cardHolderName);
		EN_cardError_t Name_results = getCardHolderName(&cardData);
		switch (Name_results) {
		case WRONG_NAME:
			goto name_step;
		}
		
	expirydate_step:
		switch (getCardExpiryDate(&cardData)) {
		case WRONG_EXP_DATE:
			goto expirydate_step;
		}
		
		printf("Enter the card PAN\n");
	PAN_step:
		gets(cardData.primaryAccountNumber);
		EN_cardError_t PAN_results = getCardPAN(&cardData);
		switch (PAN_results) {
		case WRONG_PAN:
			goto PAN_step;
		}
		
		printf("YOUR CARD DATA IS\n");
		puts(cardData.cardHolderName);
		puts(&cardData.cardExpirationDate);
		puts(cardData.primaryAccountNumber);


	TransactionDT_step:
	switch (getTransactionDate(&termData)) {
		case WRONG_DATE:
			goto TransactionDT_step;
		}
		printf("Checking**********\n");
		if (isCardExpired(cardData, termData) == EXPIRED_CARD) {
			printf("Declined Expired Card\n");
			goto name_step;
		}
	Transactionamount_step:
		switch (getTransactionAmount(&termData)) {
		case INVALID_AMOUNT:
			goto Transactionamount_step;
		}
		printf("Checking**********\n");
		if ((isBelowMaxAmount(&termData)) == EXCEED_MAX_AMOUNT) {
			goto Transactionamount_step;
		}
		transData.cardHolderData = cardData;
		transData.terminalData = termData;
		EN_transStat_t transST = recieveTransactionData(&transData);
	
		saveTransaction(&transData);
		getTransaction(&transno, &transData);
	}
}