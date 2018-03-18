/** @file
   Implementacja parsera wielomianów

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-23
*/

#include <stdio.h>
#include <stdlib.h>
#include "poly_parser.h"
#include "number_parser.h"

/**
 * Wczytuje wspolczynnik będący stała z wejscia.
 * Funkcja zmienia wartosc parametrow column i isError.
 * @param[in,out] column kolumna aktualnie wczytywanego znaku w wierszu (parametr edytowany) // lub kolumna w ktorej napotkany blad.
 * @param[in,out] isError czy zostal napotkaany jakis błąd podczas wczytywania wiersza (parametr może być edytowany tylko na true).
 * @return współczynnik wielomianu będący stałą jesli nie bylo bledu / jesli byl blad to 0.
 */
static poly_coeff_t LoadCoeffFromInput(int *column, bool *isError) {
    return LoadFromInputLongIntegerBetween(COEFF_MIN, COEFF_MAX, column, isError);
}

/**
 * Wczytuje wykladnik będący z zakresu od EXP_MIN DO EXP_MAX (<0,INTMAX>) + dodatkowo wczytuje nawias zamykający jednomian.
 * Funkcja zmienia wartosc parametrow column i isError.
 * @param[in,out] column kolumna aktualnie wczytywanego znaku w wierszu (parametr edytowany) // lub kolumna w ktorej napotkany blad
 * @param[in,out] isError czy zostal napotkaany jakis błąd podczas wczytywania wiersza (parametr może być edytowany tylko na true)
 * @return wykladnik wielomianu jesli nie bylo bledu / jesli byl blad to 0
 */
static poly_exp_t LoadExpFromInput(int *column, bool *isError) {
    poly_exp_t value = (poly_exp_t) LoadFromInputLongIntegerBetween(EXP_MIN, EXP_MAX, column, isError);
    char actChar;
    if ((actChar = getchar()) != ')') {
        ungetc(actChar, stdin);//moze byc koniec wiersza czy cos xd?
        (*isError) = true;
    }
    if (!(*isError)) {
        (*column)++;
    }
    return value;
}

/**
 * Czy pierwszy znak na wejsciu jest cyfra, lub minusem.
 * @return prawda jesli pierwszy znak na wejsciu jest cyfra, lub minusem. Falsz wpp.
 */
static bool isFirstCharInBufferNumeric() {
    char actChar;
    if (((actChar = getchar()) == '-') || ('0' <= actChar && actChar <= '9')) {
        ungetc(actChar, stdin);
        return true;
    } else {
        ungetc(actChar, stdin);
        return false;
    }
}

/**
 * Funkcja zajmuje sie rekurencyjnym wcczytaniem wielomianu niebędącym stałą z wejscia.
 * @param[in,out] column kolumna aktualnie wczytywanego znaku w wierszu (parametr edytowany) // lub kolumna w ktorej napotkany blad.
 * @param[in,out] isError czy zostal napotkaany jakis błąd podczas wczytywania wiersza (parametr może być edytowany tylko na true).
 * @return wielomian wczytany z wejscia, lub PolyZero w przypadku błedu.
 */
static Poly LoadPolyRecursive(int *column, bool *isError) {
    assert(!(*isError));

    char actChar;
    Poly result = PolyZero();

    int maxSize = STARTING_LENGTH;
    int actSize = 0;

    Mono *arr = calloc(maxSize, sizeof(Mono));
    assert(arr != NULL);

    (*column)--;

    do {
        Mono mono = LoadMonoFromInput(column, isError);
        if (!PolyIsZero(&(mono.p))) {
            if (actSize >= maxSize) {
                maxSize *= 2;
                arr = realloc(arr, maxSize * sizeof(Mono));
                assert(arr != NULL);
            }
            arr[actSize++] = mono;
        }
        (*column)++;
    } while (!(*isError) && (actChar = getchar()) == '+');

    if (!(*isError)) {
        ungetc(actChar, stdin);//to co przerwalo petle;
        result = PolyAddMonos(actSize, arr);
    } else {
        for (int i = 0; i < actSize; ++i) {
            PolyDestroy(&(arr[i].p));
        }
    }

    free(arr);

    return result;
}

Mono LoadMonoFromInput(int *column, bool *isError) {
    assert((*isError) == false);
    char actChar;
    Mono result = (Mono) {.p = PolyZero(), .exp = 0};
    if ((actChar = getchar()) != '(') {
        ungetc(actChar, stdin);
        (*isError) = true;
    } else /* actChar == '(' */ {
        (*column)++;
        if (isFirstCharInBufferNumeric()) {
            result.p = PolyFromCoeff(LoadCoeffFromInput(column, isError));
        } else {
            result.p = LoadPolyRecursive(column, isError);
        }
        if ((actChar = getchar()) != ',') {
            ungetc(actChar, stdin);//moze byc koniec wiersza czy cos xd
            (*isError) = true;
        }
        if (!(*isError)) {
            (*column)++;
            result.exp = LoadExpFromInput(column, isError);
        }

    }
    return result;
}

Poly LoadPolyFromInput(int *column, bool *isError) {
    Poly result;
    int ch_tmp;

    if (isFirstCharInBufferNumeric()) {
        result = PolyFromCoeff(LoadCoeffFromInput(column, isError));
    } else {
        result = LoadPolyRecursive(column, isError);
    }

    if ((ch_tmp = getchar()) != '\n') {
        (*isError) = true;
    }
    ungetc(ch_tmp, stdin);

    if ((*isError)) {
        PolyDestroy(&result);
        result = PolyZero();
    }

    while ((ch_tmp = getchar()) != '\n' && ch_tmp != EOF)/*do nothing*/;
    if (ch_tmp == EOF) ungetc(EOF, stdin);

    return result;
}

void PrintMono(Mono *m) {
    printf("(");
    PrintPoly(&(m->p));
    printf(",%d)", m->exp);
}

void PrintPoly(Poly *p) {
    if (PolyIsCoeff(p)) {
        printf("%ld", p->coeff);
    } else {
        PrintMono(&(p->arr[0]));
        for (size_t i = 1; i < p->size; i++) {
            printf("+");
            PrintMono(&(p->arr[i]));
        }
    }
}
