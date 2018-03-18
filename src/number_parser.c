/** @file
   Implementacja parsera liczb

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-25
*/
#include <stdbool.h>
#include <stdio.h>
#include "number_parser.h"

long LoadFromInputLongIntegerBetween(long min, long max, int *column, bool *isError) {
    char actChar;
    long value;
    bool isMinus = false;

    //obsluga '-' na poczatku wyrazenia
    if ((actChar = getchar()) == '-') {
        isMinus = true;
        (*column)++;
    } else {
        ungetc(actChar, stdin);
    }

    //obsluga wyrazen "'correctEndOfLoading'" i "-'correctEndOfLoading'", ktore sa niepoprawne (-0 uwazam za poprawne (i -0 == 0))
    if ((actChar = getchar()) < '0' || '9' < actChar) {
        (*isError) = true;
    } else {
        ungetc(actChar, stdin);
    }

    value = 0;
    while ((!*isError) && '0' <= (actChar = getchar()) && actChar <= '9') {
        if (isMinus) {
            if ((min / 10 <= value) && min + (actChar - '0') <= (value *= 10)) {
                value -= (actChar - '0');
                (*column)++;
            } else {
                (*isError) = true;
            }
        } else {
            if ((max / 10 >= value) && max - (actChar - '0') >= (value *= 10)) {
                value += (actChar - '0');
                (*column)++;
            } else {
                (*isError) = true;
            }
        }
    }

    //zostawia to co przerwalo petle w buforze
    ungetc(actChar, stdin);

    //po to by nie zostawaly jakies smieci na wyjsciu jezeli pojawil sie blad
    if ((*isError)) {
        value = 0;
    }
    return value;
}
