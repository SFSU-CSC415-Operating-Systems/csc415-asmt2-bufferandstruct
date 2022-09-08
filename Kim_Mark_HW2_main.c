/**************************************************************
* Class:  CSC-415-02 Fall 2022
* Name: Mark Kim
* Student ID: 918204214
* GitHub UserID: mkim797
* Project: Assignment 2 – Stucture in Memory and Buffering
*
* File: Kim_Mark_HW2_main.c
*
* Description: This project populates a struct (personalInfo) provided by 
* assignment2.h.  In addition, this program retrieves a set of strings
* from assignment2.h and copies them to a buffer by sequentially filling
* it in its entirety before committing and clearing the buffer for
* subsequent copies.
*
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment2.h"

void bufferAndCommit() {
    // The string retrieved from getNext() must be stored so that it can be
    // used to fill the string buffer.  Since there is no function to navigate
    // the data structure providing the strings, it is best to process each
    // string completely before moving onto the next.
    const char *cStr = getNext();

    // String buffer of a size as defined in assignment2.h.  This is where we
    // will be copying the C string before committing it.
    char *strBuffer = malloc(BLOCK_SIZE);

    // This variable stores the remaining space in the buffer.  It doubles
    // as a pointer to the next character in the sequence to be copied to the
    // buffer.
    int bufferRemaining;

    while (cStr != NULL) {

        // We are checking to see if the current string exceeds the remaining
        // space in the buffer so that we can apply the correct processing
        // technique.  If larger than the remaining space, we must break up
        // the string so that it fills the buffer before committing it.
        if ( strlen(cStr) > BLOCK_SIZE - strlen(strBuffer) ) {
            bufferRemaining = BLOCK_SIZE - strlen(strBuffer);

            // Since we are appending the string to the end of whatever is already
            // in the buffer, strncat() was used instead of strncpy().  Additionally,
            // we want to ensure that only the portion of the C string that will
            // precisely fill the buffer will be copied.
            strncat(strBuffer, cStr, bufferRemaining);

            // This is where we move the pointer to the character that starts the
            // next sequence of characters for copying into the buffer.
            cStr = cStr + bufferRemaining;
            commitBlock(strBuffer);

            // Since the buffer has been cleared by commitBlock(), a strcpy() is
            // sufficient.
            strcpy(strBuffer, cStr);
        } else {

            // Because in this case the entire string will fit within the available
            // space of the buffer, the entire string can be appended to the buffer.
            strcat(strBuffer, cStr);
        }
        cStr = getNext();

        // Even if we have finished the series of strings, there may still be characters
        // stored in the buffer, hence, the buffer still needs to be committed.
        if (cStr == NULL) {
            commitBlock(strBuffer);
        }
    }

    free(strBuffer);
    strBuffer = NULL;
}

int main ( int argc, char *argv[] ) {

    // STEP FOUR:
    // Use sizeof() to ensure correct memory allocation as determined
    // by the struct in case of changes to the personalInfo struct.
    personalInfo *me = malloc(sizeof(personalInfo));
    me->firstName = argv[1];
    me->lastName = argv[2];
    me->studentID = 918204214;
    me->level = SENIOR;
    me->languages = KNOWLEDGE_OF_C + KNOWLEDGE_OF_BASIC
        + KNOWLEDGE_OF_HTML + KNOWLEDGE_OF_CPLUSPLUS
        + KNOWLEDGE_OF_JAVA + KNOWLEDGE_OF_JAVASCRIPT
        + KNOWLEDGE_OF_MIPS_ASSEMBLER + KNOWLEDGE_OF_PYTHON
        + KNOWLEDGE_OF_R + KNOWLEDGE_OF_RUBY + KNOWLEDGE_OF_SQL;

    // strncpy() used to limit the size of the message provided in argv[3]
    // since the struct attribute, message, is limited to 100.  In addition,
    // a terminating null character is inserted at the end of message since
    // C strings are always terminated by a null character.
    strncpy(me->message, argv[3], sizeof(me->message));
    me->message[100] = '\0';

    // STEP FIVE:
    writePersonalInfo(me);

    // STEP SIX:
    bufferAndCommit();

    // STEP SEVEN:
    checkIt();

    free(me);
    me = NULL;

    return 0;
}