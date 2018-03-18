/** @file
   Implementacja Stosu Wielomianowego

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-25
*/
#include <stdlib.h>
#include "stack.h"

/**
 * struktura reprezentujaca pojedynczy element stosu (typu Poly)
 */
typedef struct PolyStackElement {
    struct PolyStackElement *next;///<wskaznik na nastepny element stosu
    Poly data;///<wartosc elementu stosu będąca wielomianem
} PolyStackElement;

/**
 * struktura reprezentujaca stos trzymajacy elementy typu Poly
 */
struct PolyStack {
    PolyStackElement *top;///<wierzcholek stosu
};


Poly Pop(PolyStack *s) {
    PolyStackElement *tmp = s->top;
    Poly res = s->top->data;
    s->top = s->top->next;
    free(tmp);
    return res;
};

Poly Top(PolyStack *s) {
    return s->top->data;
};

void Push(PolyStack *s, Poly poly) {
    PolyStackElement *top = malloc(sizeof *top);
    assert(s != NULL);
    top->next = s->top;
    top->data = poly;
    s->top = top;
}


PolyStack *Init(void) {
    PolyStack *s = malloc(sizeof *s);
    assert(s != NULL);
    s->top = NULL;
    return s;
}


bool IsEmpty(PolyStack *s) {
    return s->top == NULL;
}

void StackDestroy(PolyStack *stack) {
    while (!IsEmpty(stack)) {
        Poly p = Pop(stack);
        PolyDestroy(&p);
    }
    free(stack);
}
