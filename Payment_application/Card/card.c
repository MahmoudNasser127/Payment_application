#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
#ifndef Card_h
#define Card_h
#endif
//tis function to check the name is only A~Z, a~z or spaces only
EN_cardError_t getCardHolderName (ST_cardData_t* cardData) {

    int length_name = strlen(cardData->cardHolderName);
    if (length_name < 20 || length_name > 25) {
        printf("invalid name has less than 20 char or more than 25\n enter valid name : \n");
        return WRONG_NAME;
    }
    else {
        for (int i = 0; i < length_name; i++) {
            if (!((cardData->cardHolderName[i] >= 65 && cardData->cardHolderName[i] <= 90) || (cardData->cardHolderName[i] >= 97 && cardData->cardHolderName[i] <= 122) || (cardData->cardHolderName[i] == 32)))
            {
                printf("invalid name \n");
                printf("please enter valid name : \n");
                return WRONG_NAME;
            }
        }
        if (cardData->cardHolderName[0] == 32) {
            printf("invalid name with space in the beginning \n please enter valid name : \n");
            return WRONG_NAME;
        }
        if (cardData->cardHolderName[0] == 0) {
            printf("invalid name is empty name \n enter valid name : \n");
            return WRONG_NAME;
        }
        else {
            return OK;
        }   
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    printf("Enter the expirationDate MM/YY \n");
    gets(cardData->cardExpirationDate);
    int length_date = strlen(cardData->cardExpirationDate);
    if (!(length_date == 5)) {
        printf("Enter valid date MM/YY\n");
        return WRONG_EXP_DATE;
    }
    else {

        if (!(((((cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0')) <= 12)) && (cardData->cardExpirationDate[2] == '/'))) {
            printf("in vaild Expiry date\n");
            printf("Enter valid date MM/YY\n");
            return WRONG_EXP_DATE;
        }
        else {
            return OK;

        }
    }
}
EN_cardError_t  getCardPAN(ST_cardData_t* cardData) {
    uint8_t PAN_length = strlen(cardData->primaryAccountNumber);
    if (PAN_length < 16 || PAN_length > 19) {
        printf("please enter a vaild PAN : PAN length must be 16~19 number\n");
        return WRONG_PAN;
    }
    else {
        for (int i = 0; i < PAN_length; i++) {
            if (!(cardData->primaryAccountNumber[i] >= '0' && cardData->primaryAccountNumber[i] <= '9'))
            {
                 printf("invalid PAN \n");
                 printf("please enter a valid PAN : \n");       
                 return WRONG_PAN;
            }
        }
        printf(" OK \n");
        return OK;
    }
}
