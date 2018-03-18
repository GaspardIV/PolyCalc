/** @file
   Implementacja Kalkulatora Stosowego Wielomianów

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-25
*/


#include <stdio.h>
#include "command_parser.h"
#include "number_parser.h"
#include "poly_parser.h"
#include "stack.h"

void PolyCalcLoop(void);

bool isCommandAtEntry(void);

void TryToExecCommand(PolyStack *stack, int row);

void TryToLoadPoly(PolyStack *stack, int row);

bool UnderFlowProtector(PolyStack *stack, int row);

/**
 * Po prostu main.
 * @return 0 jeśli okej wszystko, wpp niezero.
 */
int main(void) {
    PolyCalcLoop();
    return 0;
}

/**
 * Główna pętla kalkulatora.
 * Inicjalizuje stos. Wstawia na niego dane wielomiany i wykonuje na nim dane komendy.
 * (dane z wejścia). Na końcu usuwa stos.
 */
void PolyCalcLoop(void) {
    int actChar;
    PolyStack *stack = Init();
    int row = 1;
    while ((actChar = getchar()) != EOF) {
        ungetc(actChar, stdin);
        if (isCommandAtEntry()) {
            TryToExecCommand(stack, row);
        } else {
            TryToLoadPoly(stack, row);
        }
        row++;
    }
    StackDestroy(stack);
}

/**
 * Funkcja stara się wczytać komende i ją wykonać.
 * Jeśli komenda jest niepoprawna - wypisuje komunikat o błędzie na stderr.
 * @param[in,out] stack : stos potrzebny do wykonania komend.
 * @param[in] row : numer wiersza, który ma zostać wypisany w komunikacie o błędzie, jeśli się nie wykonać komendy.
 */
void TryToExecCommand(PolyStack *stack, int row) {
    int command = ParseCommand();
    int ch_tmp;
    if (command != DEG_BY && command != AT && command != COMPOSE) { //komendy po ktorych jest spacja
        if (getchar() != '\n') {
            command = ERROR;
        } else {
            ungetc('\n', stdin);
        }
    }
    switch (command) {
        case ZERO:
            Push(stack, PolyZero());
            break;
        case IS_COEFF:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Top(stack);
                printf("%d\n", PolyIsCoeff(&p));
            }
            break;
        case IS_ZERO:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Top(stack);
                printf("%d\n", PolyIsZero(&p));
            }
            break;
        case CLONE:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Top(stack);
                Push(stack, PolyClone(&p));
            }
            break;
        case ADD:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Pop(stack);
                if (UnderFlowProtector(stack, row)) {
                    Poly q = Pop(stack);
                    Push(stack, PolyAdd(&p, &q));
                    PolyDestroy(&p);
                    PolyDestroy(&q);
                } else {
                    Push(stack, p);
                }
            }
            break;
        case MUL:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Pop(stack);
                if (UnderFlowProtector(stack, row)) {
                    Poly q = Pop(stack);
                    Push(stack, PolyMul(&p, &q));
                    PolyDestroy(&p);
                    PolyDestroy(&q);
                } else {
                    Push(stack, p);
                }
            }
            break;
        case NEG:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Pop(stack);
                Push(stack, PolyNeg(&p));
                PolyDestroy(&p);
            }
            break;
        case SUB:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Pop(stack);
                if (UnderFlowProtector(stack, row)) {
                    Poly q = Pop(stack);
                    Push(stack, PolySub(&p, &q));
                    PolyDestroy(&p);
                    PolyDestroy(&q);
                } else {
                    Push(stack, p);
                }
            }
            break;
        case IS_EQ:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Pop(stack);
                if (UnderFlowProtector(stack, row)) {
                    Poly q = Pop(stack);
                    printf("%d\n", PolyIsEq(&p, &q));
                    Push(stack, q);
                }
                Push(stack, p);
            }
            break;
        case DEG:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Top(stack);
                printf("%d\n", PolyDeg(&p));
            }
            break;
        case DEG_BY: {
            bool isError = false;
            if (getchar() == '\n') {
                ungetc('\n', stdin);
                isError = true;
            }
            int column = 0;
            int exp = LoadFromInputLongIntegerBetween(0, UINT_MAX, &column, &isError);
            if (getchar() != '\n') {
                isError = true;
            } else {
                ungetc('\n', stdin);
            }
            if (isError) {
                fprintf(stderr, "ERROR %d WRONG VARIABLE\n", row);
            } else if (UnderFlowProtector(stack, row)) {
                Poly p = Top(stack);
                printf("%d\n", PolyDegBy(&p, exp));
            }
            break;
        }
        case AT: {
            bool isError = false;
            if (getchar() == '\n') {
                ungetc('\n', stdin);
                isError = true;
            }
            int column = 0;
            int exp = LoadFromInputLongIntegerBetween(LONG_MIN, LONG_MAX, &column, &isError);
            if (getchar() != '\n') {
                isError = true;
            } else {
                ungetc('\n', stdin);
            }
            if (isError) {
                fprintf(stderr, "ERROR %d WRONG VALUE\n", row);
            } else if (UnderFlowProtector(stack, row)) {
                Poly p = Pop(stack);
                Push(stack, PolyAt(&p, exp));
                PolyDestroy(&p);
            }
            break;
        }
        case COMPOSE: {
            bool isError = false;
            if (getchar() == '\n') { //czyli jest spacja
                ungetc('\n', stdin);
                isError = true;
            }
            int column = 0;
            int count = LoadFromInputLongIntegerBetween(0, UINT_MAX, &column, &isError);
            if (getchar() != '\n') {
                isError = true;
            } else {
                ungetc('\n', stdin);
            }
            if (isError) {
                fprintf(stderr, "ERROR %d WRONG COUNT\n", row);
            } else {
                if (UnderFlowProtector(stack, row)) {
                    Poly p = Pop(stack);
                    Poly x[count];
                    for (long i = 0; i < count && !isError; ++i) {
                        if (UnderFlowProtector(stack, row)) {
                            x[i] = Pop(stack);
                        } else {
                            isError = true;
                            PolyDestroy(&p);
                            for (unsigned j = 0; j < i; ++j) {
                                PolyDestroy(&(x[j]));
                            }
                        }
                    }
                    if (!isError) {
                        Push(stack, PolyCompose(&p, count, x));
                        PolyDestroy(&p);
                        for (long j = 0; j < count; ++j) {
                            PolyDestroy(&(x[j]));
                        }
                    }
                }
            }
            break;
        }
        case PRINT:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Top(stack);
                PrintPoly(&p);
                printf("\n");
            }
            break;
        case POP:
            if (UnderFlowProtector(stack, row)) {
                Poly p = Pop(stack);
                PolyDestroy(&p);
            }
            break;
        default:
            fprintf(stderr, "ERROR %d WRONG COMMAND\n", row);
            break;
    }
    /* przejście do następnego wiersza */
    while ((ch_tmp = getchar()) != '\n' && ch_tmp != EOF);
    if (ch_tmp == EOF) ungetc(EOF, stdin);
}

/**
 * Funkcja stara sie wczytać z wejscia Poly.
 * Jeśli się nie uda wyświetla komunikat o blędzie, wpp wstawia Poly na stos.
 * @param[in,out] stack : stos na który ma zostać wstawiona wielomian (jeśli się uda go wczytać).
 * @param[in] row : numer wiersza, który ma zostać wypisany w komunikacie o błędzie, jeśli się nie uda wczytać wielomianu.
 */
void TryToLoadPoly(PolyStack *stack, int row) {
    bool isError = false;
    int column = 1;
    Poly p = LoadPolyFromInput(&column, &isError);
    if (!isError) {
        Push(stack, p);
    } else {
        fprintf(stderr, "ERROR %d %d\n", row, column);
    }
}

/**
 * Ta funkcja chroni nas przed underflow.
 * Sprawdza czy można zdjąć element, jeśli nie to wypisuje komunikat o błędzie na stderr.
 * @param[in] stack : stack który ma zostać sprawdzony, czy można z niego zdjąć element
 * @param[in] row : numer wiersza, który ma zostać wypisany w komunikacie o błędzie, jeśli się nie uda wczytać wielomianu.
 * @return true - jeśli mozna smialo zrzucac ze stosu. false - jeśli nie można i wypisany błąd.
 */
bool UnderFlowProtector(PolyStack *stack, int row) {
    if (IsEmpty(stack)) {
        fprintf(stderr, "ERROR %d STACK UNDERFLOW\n", row);
        return false;
    } else {
        return true;
    }
}

/**
 * Rozpoznaje czy na wejściu może być komenda.
 * @return true jeśli na wejściu może być komenda, false wpp.
 */
bool isCommandAtEntry(void) {
    int actChar = getchar();
    ungetc(actChar, stdin);
    if (('a' <= actChar && actChar <= 'z') || ('A' <= actChar && actChar <= 'Z')) {
        return true;
    } else {
        return false;
    }
}
