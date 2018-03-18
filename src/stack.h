/** @file
   Interfejs Stosu o elementach typu Poly

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-25
*/

#ifndef POLY_STACK_H
#define POLY_STACK_H

#include "poly.h"

/**
 * Typ Stosu przetrzymującego elementy typu Poly
 */
typedef struct PolyStack PolyStack;


/**
 * Zrzuca i zwraca szczyt stosu
 * @param[in,out] s stos z którego ma być zrzucony szczyt
 * @return Wielomian będący na szczycie stosu
 */
Poly Pop(PolyStack *s);

/**
 * Zwraca szczyt stosu nie zrzucając go.
 * @param[in] s stos którego wierzchołek ma być zrzucony.
 * @return Wielomian będący na szczycie stosu.
 */
Poly Top(PolyStack *s);

/**
 * Sprawdza czy stos jest pusty.
 * @param[in] s stos do sprawdzenia.
 * @return true jeśli stos jest pusty, false wpp.
 */
bool IsEmpty(PolyStack *s);

/**
 * inicjalizuje stos
 * @return Zainicjalizowany Stos
 */
PolyStack *Init(void);

/**
 * wrzuca wielomian na gore stosu
 * @param[in,out] s : stos na który wrzucany jest wielomian
 * @param[in] poly : wielomian, który funkcja wrzuca na stos
 */
void Push(PolyStack *s, Poly poly);

/**
 * Usuwa stos i wielomiany na nim będące.
 * @param[in] stack stos do usunięcia.
 */
void StackDestroy(PolyStack *stack);

#endif //POLY_STACK_H
