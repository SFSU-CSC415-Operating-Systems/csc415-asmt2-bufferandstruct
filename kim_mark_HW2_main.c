/**************************************************************
* Class:  CSC-415-02 Fall 2022
* Name: Mark Kim
* Student ID: 918204214
* GitHub UserID: mkim797
* Project: Assignment 2 – Stucture in Memory and Buffering
*
* File: kim_mark_HW2_main.c
*
* Description:
*
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assignment2.h>

int main ( int argc, char *argv[] ) {

    // Step four:
    // Use sizeof() to ensure correct memory allocation as determined
    // by the struct in case of changes to the personalInfo struct.
    personalInfo *mePtr = malloc(sizeof(personalInfo));
    mePtr->firstName = argv[1];
    mePtr->lastName = argv[2];
    mePtr->studentID = 918204214;
    mePtr->level = SENIOR;
    mePtr->languages = KNOWLEDGE_OF_C + KNOWLEDGE_OF_BASIC
        + KNOWLEDGE_OF_HTML + KNOWLEDGE_OF_CPLUSPLUS
        + KNOWLEDGE_OF_JAVA + KNOWLEDGE_OF_JAVASCRIPT
        + KNOWLEDGE_OF_MIPS_ASSEMBLER + KNOWLEDGE_OF_PYTHON
        + KNOWLEDGE_OF_R + KNOWLEDGE_OF_RUBY + KNOWLEDGE_OF_SQL;

    // strncpy() used to limit the size of the message provided in argv[3]
    // since the struct attribute, message, is limited to 100.  In addition,
    // a terminating null character is inserted at the end of message since
    // C strings are always terminated by a null character.
    strncpy(mePtr->message, argv[3], sizeof(mePtr->message));
    mePtr->message[100] = '\0';

    // Step five:
    writePersonalInfo(mePtr);

    // Step six:
    char *strBuffer = malloc(BLOCK_SIZE);

    char *cStr = getNext();

    while (cStr != NULL) {
        int bufRem = BLOCK_SIZE - strlen(strBuffer);
        while (strlen(cStr) > bufRem) {
            strncat(strBuffer, cStr, bufRem);
            bufRem = BLOCK_SIZE - strlen(strBuffer);
            if (bufRem < 1) {
                commitBlock(strBuffer);
                cStr = cStr + bufRem;
                bufRem = BLOCK_SIZE;
            }
        }
        while (strlen(cStr) <= bufRem) {
            strcat(strBuffer, cStr);
            bufRem = BLOCK_SIZE - strlen(strBuffer);
            if (bufRem < 1) {
                commitBlock(strBuffer);
                bufRem = BLOCK_SIZE;
            }
            cStr = getNext();
            if (cStr == NULL) {
                commitBlock(strBuffer);
            }
        }
    }

    // Step seven:
    checkIt();

    free(mePtr);
    free(strBuffer);
    mePtr = NULL;
    strBuffer = NULL;

    return 0;
}


