/** @file
   Interfejs parsera liczb

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-23
*/
#ifndef POLY_NUMBER_PARSER_H
#define POLY_NUMBER_PARSER_H

#include <stdbool.h>

/**
 * Wczytuje z stdin Long Inta z zakresu <min, max>.
 * Wczytuje Long Inta z zakresu <min, max> az do pierwszego napotkanego znaku nie będącego cyfrą
 * Dozwolony jest pierwszy znak będący '-', tylko w przypadku gdy nastepny jest cyfrą, wpp (gdy np. -a) ustawia isError na true.
 * Funkcja zmienia wartosc parametrow column i isError.
 * Po wykonaniu funkcji pierwszym znakiem na wejsciu będzie pierwszy znak po ostatniej wczytanej cyfrze.
 * @param[in] min minimalna liczba którą funkcja ma przyjmowac za prawidlowa
 * @param[in] max maksymalna liczba którą funkcja ma przyjmowac za prawidlowa
 * @param[in,out] column kolumna znaku ktory bedzie teraz wczytany (zarowno przed jak i w trakcie jak i po wykonaniu funkcji) // lub kolumna w ktorej napotkany blad
 * @param[in,out] isError ustawiane na true jezeli wczytana liczbaa jest spoza przedzialu <min, max>, albo nastapilo wyrazenie -'znak niebedacy cyfra'
 * @return wczytana liczba, lub 0 w przypadku błędu
 */
long LoadFromInputLongIntegerBetween(long min, long max, int *column, bool *isError);

#endif //POLY_NUMBER_PARSER_H
