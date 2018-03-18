/** @file
   Interfejs parsera wielomianów

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-23
*/
#ifndef POLY_PARSER_H
#define POLY_PARSER_H

#include <values.h>
#include "poly.h"

/** Minimalna wartość wspolczynnika wielomianu bedacego stałą*/
#define COEFF_MIN LONG_MIN
/** Maksymalna wartość wspolczynnika wielomianu bedacego stałą*/
#define COEFF_MAX LONG_MAX
/** Minimalna wartość wykładnika wielomianu */
#define EXP_MIN 0
/** Maksymalna wartość wykładnika wielomianu */
#define EXP_MAX INT_MAX
/** Początkowa dlugosc tablicy jednomianow przy wczytywaniu wielomianu(pozniej reallokowana tablica i zmieniaana wielkosc) */
#define STARTING_LENGTH 1

/**
 * Wypisuje wielomian na wyjscie w postaci coeff, lub Mono, lub Mono+Mono+....+Mono.
 * @param[in] p wielomian który ma zostać wypisany
 */
void PrintPoly(Poly *p);

/**
 * Wypisuje jednomian na wyjscie w postaci (coeff,exp).
 * @param[in] m jednomian który ma zostać wypisany
 */
void PrintMono(Mono *m);

/**
 * Wczytuje jednomian z wejscia, lub w razie napotkanego błędu zatrzymuje wczytanie i edytuje isError na true.
 * Funkcja zmienia wartosc parametrow column i isError.
 * @param[in,out] column kolumna aktualnie wczytywanego znaku w wierszu (parametr edytowany) // lub kolumna w ktorej napotkany blad.
 * @param[in,out] isError czy zostal napotkaany jakis błąd podczas wczytywania wiersza (parametr może być edytowany tylko na true).
 * @return Mono który zostal wczytany, lub jednomian (0,0) w przypadku napotkanego błędu.
 */
Mono LoadMonoFromInput(int *column, bool *isError);

/**
 * Wczytuje wielomian z wejscia, lub w razie napotkanego błędu edytuje isError na true.
 * Funckja zawsze przechodzi do następnej linijki
 * Funkcja zmienia wartosc parametrow column i isError.
 * @param[in,out] column kolumna aktualnie wczytywanego znaku w wierszu (parametr edytowany) // lub kolumna w ktorej napotkany blad.
 * @param[in,out] isError czy zostal napotkaany jakis błąd podczas wczytywania wiersza (parametr może być edytowany tylko na true).
 * @return Poly który zostal wczytany, lub PolyZero w przypadku napotkanego błędu.
 */
Poly LoadPolyFromInput(int *column, bool *isError);

#endif //POLY_PARSER_H
