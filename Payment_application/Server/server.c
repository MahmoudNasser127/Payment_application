#include "server.h"
#include <string.h>

ST_accountsDB_t accounts[255] = {
{ 25000, RUNNING, "123456789987654321" },
{ 5457.58, RUNNING, "14785236985214700" },
{ 8555, RUNNING, "74125896325874100" },
{ 11111, RUNNING, "36985214785236900" },
{ 154555, RUNNING, "96325874125896300" },
{ 1250000, RUNNING, "78965412365478900" },
{ 20000, RUNNING, "98745632145698700" },
{ 36000, RUNNING, "32145698745632100" },
{ 7500, BLOCKED, "12365478965412300" },
{ 1200, RUNNING, "20202020202020202" },
{ 4300, RUNNING, "333333333333333" }
};
ST_transaction_t transactions[255] = {
	{{"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},	{{"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},	{{"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
	{ {"1","1","1"},{1,1,"1"},APPROVED,1},
};
int i;
EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{
	ST_accountsDB_t accountRefrence;
	if (isValidAccount(&transData->cardHolderData, &accountRefrence) == ACCOUNT_NOT_FOUND) {
		printf("Card doesn't exsist please contact your bank\n");
		transData->transState = FRAUD_CARD;
		return FRAUD_CARD;
	}
	if (isBlockedAccount(&accountRefrence) == BLOCKED_ACCOUNT) {
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}

	if (!(isAmountAvailable(&transData->terminalData) == SERVER_OK)) {
		printf("your account balance is lower than requested amount please try again\n");
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
}




EN_serverError_t isValidAccount(ST_cardData_t* cardData,ST_accountsDB_t* accountRefrence)
{
	for ( i = 0; i < 255; i++)
	{
		if (strcmp(cardData->primaryAccountNumber,accounts[i].primaryAccountNumber) == 0)
		{
		accountRefrence->state = accounts[i].state;
		return SERVER_OK;
		}
		
	}
	printf("Account not found\n");
	return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	if (termData->transAmount <= accounts[i].balance)
	{
		accounts[i].balance = accounts[i].balance - termData->transAmount;
		return SERVER_OK;
	}
	if (termData->transAmount > accounts[i].balance)
	{
		return LOW_BALANCE;
	}
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
if (!(accountRefrence->state == RUNNING))
{
	printf("This Card had been susbended please contact the bank\n");
	return BLOCKED_ACCOUNT;
}
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) 
{

	transData->transactionSequenceNumber++;
	int transno = transData->transactionSequenceNumber;
	transactions[transno].cardHolderData = transData->cardHolderData;
	transactions[transno].terminalData = transData->terminalData;
	transactions[transno].transState = transData->transState;
	transactions[transno].transactionSequenceNumber = transData->transactionSequenceNumber;
	return SERVER_OK;
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	uint32_t x = 0;
	printf(" enter seq\n");
	scanf_s("%d", &x);
	int state = transactions[x].transState;
	printf("***********************************************************\n");
	printf("Card Holder Name : %s\n", transactions[x].cardHolderData.cardHolderName);
	printf("PAN is           : %s\n", transactions[x].cardHolderData.primaryAccountNumber);
	printf("Expiry date      : %s\n", transactions[x].cardHolderData.cardExpirationDate);
	printf("transaction date : %s\n", transactions[x].terminalData.transactionDate);
	switch (state) {
	case (!(DECLINED_STOLEN_CARD)):
		printf("amount withdrwan : %.2f\n", transactions[x].terminalData.transAmount);
		printf("Remaining balance: %.2f\n", accounts[i].balance);
		break;
	}
	printf("trans. Seq. Num. : %d\n",transactions[x].transactionSequenceNumber);
	printf("trans. Status    : ");
	switch (state) {
	case APPROVED:
		printf("APPROVED\n");
		break;

	case FRAUD_CARD:
		printf("FRAUD_CARD\n");
		break;

	case DECLINED_INSUFFECIENT_FUND:
		printf("DECLINED_INSUFFECIENT_FUND\n");
		break;

	case DECLINED_STOLEN_CARD:
		printf("DECLINED_STOLEN_CARD\n");
		break;

	case INTERNAL_SERVER_ERROR:
		printf("INTERNAL_SERVER_ERROR\n");

		break;
	}
	printf("*************************************************************\n");

}