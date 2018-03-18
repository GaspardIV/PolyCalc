/** @file
   Implementacja parsera komend

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-25
*/

#include <stdio.h>
#include "command_parser.h"
#include "const_commandsarr.h"

int ParseCommand(void) {
    int value = ERROR;
    int actChar;
    int minPossibleIndex = 0;
    int maxPossibleIndex = commandsarrLength - 1;
    int howManyCharsScanned = 0;

    while (minPossibleIndex <= maxPossibleIndex && (actChar = getchar()) != '\n' && actChar != ' ' && actChar != EOF) {
        while (minPossibleIndex <= maxPossibleIndex && actChar != commandsarr[minPossibleIndex][howManyCharsScanned]) {
            minPossibleIndex++;
        }
        while (minPossibleIndex <= maxPossibleIndex && actChar != commandsarr[maxPossibleIndex][howManyCharsScanned]) {
            maxPossibleIndex--;
        }
        howManyCharsScanned++;
    }

    if (actChar == '\n' || actChar == ' ' || actChar == EOF) {
        ungetc(actChar, stdin);
    }

    if (minPossibleIndex <= maxPossibleIndex && commandsarr[minPossibleIndex][howManyCharsScanned - 1] != '\0' &&
        commandsarr[minPossibleIndex][howManyCharsScanned] == '\0') {
        value = FIRST_DEF_VALUE + minPossibleIndex;
    }

    return value;
}
