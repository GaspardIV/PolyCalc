#include "poly.h"
#include "const_arr.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define ALL_TESTS "all"
#define MEMORY "memory"
#define LONG_POLYNOMIAL "long-polynomial"
#define DEG "deg"
#define DEG_SIMPLE "deg-simple"
#define DEG_OP "deg-op"
#define SIMPLE_AT "simple-at"
#define SIMPLE_AT2 "simple-at2"
#define AT "at"
#define MUL_SIMPLE "mul-simple"
#define MUL "mul"
#define ADD "add"
#define ADD_REQ "add-req"
#define SUB "sub"
#define SUB_REQ "sub-req"
#define EQ "eq"
#define EQ_SIMPLE "eq-simple"
#define RARE "rare"
#define MONO_ADD "mono-add"
#define OVERFLOW "overflow"
#define SIMPLE_ARITHMETIC "simple-aritmethic"
#define SIMPLE_ARITHMETIC2 "simple-aritmethic2"

bool SimpleArithmeticTest();

bool LongPolynomialTest();

bool DegreeOpChangeTest();

bool SimpleAtTest2();

bool AtTest();

bool DegTest();

bool DegByTest();

bool MulTest();

bool MulTest2();

bool AddTest1();

bool AddTest2();

bool SubTest1();

bool SubTest2();

bool IsEqTest();

bool RarePolynomialTest();

bool SimpleAddTest();

bool SimpleAddMonosTest();

bool SimpleMulTest();

bool SimpleNegTest();

bool SimpleSubTest();

bool SimpleDegByTest();

bool SimpleDegTest();

bool SimpleIsEqTest();

bool SimpleAtTest();

bool OverflowTest();

void MemoryThiefTest();

void MemoryTest();

void PrintHelp(char *);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        PrintHelp(argv[0]);
        return -1;
    }
    if (strcmp(argv[1], MEMORY) == 0)
    {
        MemoryThiefTest();
        MemoryTest();
    }
    else if (strcmp(argv[1], SIMPLE_ARITHMETIC) == 0)
    {
        bool res = true;
        res &= SimpleAddTest();
        res &= SimpleMulTest();
        res &= SimpleNegTest();
        res &= SimpleSubTest();
        return !res;
    }
    else if (strcmp(argv[1], SIMPLE_ARITHMETIC2) == 0)
    {
        return !SimpleArithmeticTest();
    }
    else if (strcmp(argv[1], LONG_POLYNOMIAL) == 0)
    {
        return !LongPolynomialTest();
    }
    else if (strcmp(argv[1], DEG_OP) == 0)
    {
        return !DegreeOpChangeTest();
    }
    else if (strcmp(argv[1], DEG_SIMPLE) == 0)
    {
        bool res = true;
        res &= SimpleDegTest();
        res &= SimpleDegByTest();
        return !res;
    }
    else if (strcmp(argv[1], DEG) == 0)
    {
        bool res = true;
        res &= DegTest();
        res &= DegByTest();
        return !res;
    }
    else if (strcmp(argv[1], SIMPLE_AT) == 0)
    {
        return !SimpleAtTest();
    }
    else if (strcmp(argv[1], SIMPLE_AT2) == 0)
    {
        return !SimpleAtTest2();
    }
    else if (strcmp(argv[1], AT) == 0)
    {
        return !AtTest();
    }
    else if (strcmp(argv[1], MUL_SIMPLE) == 0)
    {
        return !MulTest();
    }
    else if (strcmp(argv[1], MUL) == 0)
    {
        return !MulTest2();
    }
    else if (strcmp(argv[1], ADD) == 0)
    {
        return !AddTest1();
    }
    else if (strcmp(argv[1], ADD_REQ) == 0)
    {
        return !AddTest2();
    }
    else if (strcmp(argv[1], SUB) == 0)
    {
        return !SubTest1();
    }
    else if (strcmp(argv[1], SUB_REQ) == 0)
    {
        return !SubTest2();
    }
    else if (strcmp(argv[1], EQ_SIMPLE) == 0)
    {
        return !SimpleIsEqTest();
    }
    else if (strcmp(argv[1], EQ) == 0)
    {
        return !IsEqTest();
    }
    else if (strcmp(argv[1], RARE) == 0)
    {
        return !RarePolynomialTest();
    }
    else if (strcmp(argv[1], MONO_ADD) == 0)
    {
        return !SimpleAddMonosTest();
    }
    else if (strcmp(argv[1], OVERFLOW) == 0)
    {
        return !OverflowTest();
    }
    else if (strcmp(argv[1], ALL_TESTS) == 0)
    {
        int res = 0;
        res += SimpleArithmeticTest();
        res += LongPolynomialTest();
        MemoryThiefTest();
        MemoryTest();
        res += DegreeOpChangeTest();
        res += DegTest() && DegByTest();
        res += SimpleAtTest2();
        res += AtTest();
        res += MulTest();
        res += MulTest2();
        res += AddTest1();
        res += AddTest2();
        res += SubTest1();
        res += SubTest2();
        res += IsEqTest();
        res += RarePolynomialTest();
        res += SimpleAddMonosTest();
        res += SimpleAddTest() &&
                SimpleMulTest() &&
                SimpleNegTest() &&
                SimpleSubTest();//
        res += SimpleDegByTest() && SimpleDegTest();
        res += SimpleIsEqTest();
        res += SimpleAtTest();//
        res += OverflowTest();
        printf("%d of 20 tests passed\n", res);
    }
    else
    {
        PrintHelp(argv[0]);
        return -1;
    }
    return 0;
}

/**
 * Wypisuje na standardowe wyjście informację o argumentach programu
 * @param program_name nazwa programu
 */
void PrintHelp(char *program_name)
{
    const int width = 18;
    printf("Usage: %s [target]\nWhere target can be:\n", program_name);
    printf("\t%-*s - run all tests\n", width, ALL_TESTS);
    printf("\t%-*s - run memory test (run under valgrind)\n", width, MEMORY);
    printf(
        "\t%-*s - run test which constructing longer and longer polynomials\n",
        width, LONG_POLYNOMIAL);
    printf("\t%-*s - run simple arithmetic test\n", width, SIMPLE_ARITHMETIC);
    printf("\t%-*s - run simple arithmetic test 2\n", width, SIMPLE_ARITHMETIC2);
    printf("\t%-*s - run simple deg test\n", width, DEG_SIMPLE);
    printf("\t%-*s - run deg test\n", width, DEG);
    printf("\t%-*s - run deg chanege after operations test\n", width, DEG_OP);
    printf("\t%-*s - run simple at test\n", width, SIMPLE_AT);
    printf("\t%-*s - run simple at test 2\n", width, SIMPLE_AT);
    printf("\t%-*s - run at test\n", width, AT);
    printf("\t%-*s - run simple mul test\n", width, MUL_SIMPLE);
    printf("\t%-*s - run mul test\n", width, MUL);
    printf("\t%-*s - run add test\n", width, ADD);
    printf("\t%-*s - run recursion add test\n", width, ADD_REQ);
    printf("\t%-*s - run sub test\n", width, SUB);
    printf("\t%-*s - run recursion sub test\n", width, SUB_REQ);
    printf("\t%-*s - run equality test\n", width, EQ);
    printf("\t%-*s - run simple equality test\n", width, EQ_SIMPLE);
    printf("\t%-*s - run rare polynomial test\n", width, RARE);
    printf("\t%-*s - run overflow test\n", width, OVERFLOW);
}

/**
 * Testowanie czy operacja daje spodziewany wynik
 * @param a pierwszy wielomin
 * @param b drugi wielomian
 * @param res spodziewany wynik
 * @param op funkcja przyjmująca dwa wielomiany jako argument i zwracająca wielomian
 * (Domyślnie jedna z PolyAdd , PolySub, PolyMul)
 */
bool TestOp(Poly *a, Poly *b, Poly res, Poly (*op)(const Poly *, const Poly *))
{
    Poly r = op(a, b);
    bool compare_res = PolyIsEq(&r, &res);
    PolyDestroy(&r);
    PolyDestroy(&res);
    return compare_res;
}

/**
 * Funkcja testująca dodawanie, odejmowanie i mnożenie liczb
 * za pomocą wielomianów
 */
bool SimpleArithmeticTest()
{

    for (poly_coeff_t i = -100; i < 100; i++)
    {
        Poly p1 = PolyFromCoeff(i);
        for (poly_coeff_t j = -100; j < 100; j++)
        {
            Poly p2 = PolyFromCoeff(j);
            if (!TestOp(&p1, &p2, PolyFromCoeff(i + j), PolyAdd))
            {
                fprintf(stderr, "Fail on adding %ld %ld\n", i, j);
                return false;
            }
            if (!TestOp(&p1, &p2, PolyFromCoeff(i - j), PolySub))
            {
                fprintf(stderr, "Fail on subbing %ld %ld\n", i, j);
                return false;
            }
            if (!TestOp(&p1, &p2, PolyFromCoeff(i * j), PolyMul))
            {
                fprintf(stderr, "Fail on multiply %ld %ld\n", i, j);
                return false;
            }
            if (TestOp(&p1, &p2, PolyFromCoeff(i + j + 1), PolyAdd))
            {
                fprintf(stderr, "Fail on adding %ld %ld\n", i, j);
                return false;
            }
            if (TestOp(&p1, &p2, PolyFromCoeff(i - j - 1), PolySub))
            {
                fprintf(stderr, "Fail on subbing %ld %ld\n", i, j);
                return false;
            }
            if (TestOp(&p1, &p2, PolyFromCoeff(i * j + 1), PolyMul))
            {
                fprintf(stderr, "Fail on multiply %ld %ld\n", i, j);
                return false;
            }
            PolyDestroy(&p2);
        }
        PolyDestroy(&p1);
    }
    return true;
}

/**
 * Funkcja budująca coraz dłuższe wielomiany
 */
bool LongPolynomialTest()
{
    bool res = true;
    Poly p = PolyFromCoeff(1);
    for (int poly_deg = 10; poly_deg < 90011 && res; poly_deg += 1000)
    {
        Mono *m =
            calloc((size_t)poly_deg + 1, sizeof(Mono)); // +1 bo wyraz wolny
        for (int i = 0; i <= poly_deg; i++)
        {
            Poly tmp = PolyClone(&p);
            m[i] = MonoFromPoly(&tmp, i);
        }
        Poly long_p = PolyAddMonos((unsigned)poly_deg + 1, m);
        // long_p ma postać 1 + x + x^2 + ...
        free(m);
        if (PolyDeg(&long_p) != poly_deg)
        {
            fprintf(stderr,
                    "[LongPolynomialTest] fail creating polynomial of deg %u\n",
                    poly_deg);
            res = false;
        }
        Poly mono_sum = PolyAt(&long_p, 1);
        if (!PolyIsCoeff(&mono_sum))
        {
            fprintf(stderr, "[LongPolynomialTest] fail on PolyAt [1]\n");
            res = false;
        }
        Poly mono_sum_poly = PolyFromCoeff(poly_deg + 1);
        if (!PolyIsEq(&mono_sum, &mono_sum_poly))
        {
            fprintf(stderr, "[LongPolynomialTest] fail on PolyAt [2]\n");
            res = false;
        }
        PolyDestroy(&mono_sum_poly);
        PolyDestroy(&mono_sum);
        mono_sum = PolyAt(&long_p, -1);
        if (!PolyIsEq(&mono_sum, &p))
        {
            fprintf(stderr, "[LongPolynomialTest] fail on PolyAt [3]\n");
            res = false;
        }
        PolyDestroy(&mono_sum);
        PolyDestroy(&long_p);
    }

    PolyDestroy(&p);
    return res;
}

/**
 * Test czy funkcje PolyAddMonos i MonoFromPoly przejmują na własność
 * jednomiany i monomiany.
 * Uruchomione pod valgrindem nie powinno dawać wycieków pamięci
 */
void MemoryThiefTest()
{
    const size_t poly_size = 10;
    const int poly_depth = 3;
    Poly p = PolyFromCoeff(1);
    Mono *m = calloc(poly_size, sizeof(Mono));
    for (int j = 0; j < poly_depth; j++)
    {
        for (int i = 0; i < (int)poly_size; i++)
        {
            Poly tmp = PolyClone(&p);
            m[i] = MonoFromPoly(&tmp, i);
        }
        PolyDestroy(&p);
        p = PolyAddMonos(poly_size, m);
        // p = p + px + px^2
    }
    Poly p2 = PolyClone(&p);
    Mono m2 = MonoFromPoly(&p2, 5);
    MonoDestroy(&m2);
    PolyDestroy(&p);
    free(m);
}

/**
 * Sprawdza czy stopień wielomianu poprawnie się zmienia
 * przy wykonywaniu operacji arytmetycznych
 */
bool DegreeOpChangeTest()
{
    Poly p_one = PolyFromCoeff(1);
    Poly p_res = PolySub(&p_one, &p_one); // 1 - 1
    if (!PolyIsZero(&p_res))
    {
        fprintf(stderr, "[DegreeOpChangeTest] simple sub error\n");
        return false;
    }
    PolyDestroy(&p_res);
    Poly p2 = PolyNeg(&p_one);
    p_res = PolyAdd(&p_one, &p2); // 1 + -1
    if (!PolyIsZero(&p_res))
    {
        fprintf(stderr, "[DegreeOpChangeTest] simple add error\n");
        return false;
    }
    PolyDestroy(&p_res);
    PolyDestroy(&p2);
    {
        const int poly_len = 5;
        Mono m[poly_len];
        for (int i = 0; i < poly_len; i++)
        {
            p2 = PolyClone(&p_one);
            m[i] = MonoFromPoly(&p2, i);
        }
        Mono m2 = MonoClone(&m[poly_len - 1]);
        p2 = PolyAddMonos(poly_len, m);
        Poly p3 = PolyAddMonos(1, &m2);
        p_res = PolySub(&p2, &p3); // (1 + x + ... + x^n) - x^n
        if (PolyDeg(&p_res) != poly_len - 2)
        {
            fprintf(stderr, "[DegreeOpChangeTest] one var poly sub error\n");
            return false;
        }
        PolyDestroy(&p2);
        PolyDestroy(&p3);
        PolyDestroy(&p_res);
    }
    {
        const int poly_len = 5;
        Mono m[poly_len];
        for (int i = 0; i < poly_len - 1; i++)
        {
            p2 = PolyClone(&p_one);
            m[i] = MonoFromPoly(&p2, i);
        }
        p2 = PolyClone(&p_one);
        m[poly_len - 1] = MonoFromPoly(&p2, poly_len);
        Mono m2[2];
        m2[0] = MonoClone(&m[poly_len - 1]);

        p2 = PolyAddMonos(poly_len, m);
        Poly p3;
        p3 = PolyClone(&p_one);
        m2[1] = MonoFromPoly(&p3, poly_len - 1);

        p3 = PolyAddMonos(2, m2);
        p_res = PolySub(&p2, &p3);
        // (1 + x + ... x^(n - 2) + x^n) - (x^(n-1) + x^n)
        if (PolyDeg(&p_res) != poly_len - 1)
        {
            fprintf(stderr, "[DegreeOpChangeTest] one var poly sub error\n");
            return false;
        }
        PolyDestroy(&p2);
        PolyDestroy(&p3);
        PolyDestroy(&p_res);
    }
    PolyDestroy(&p_one);
    return true;
}

/**
 * Prosty test ewaluacji (PolyAt) wielomianów.
 * Testuje czy dobrze są dobrane typy danych.
 * Załada, że poly_coef_r jest typu long
 */
bool SimpleAtTest2()
{
    Poly p_one = PolyFromCoeff(1);
    Poly p_two = PolyFromCoeff(2);
    Poly p, p_res, p_expected_res;
    p_expected_res = PolyFromCoeff(LONG_MAX);
    const int bits_num = sizeof(poly_coeff_t) * CHAR_BIT - 1;
    Mono m[bits_num];
    for (int i = 0; i < bits_num; i++)
    {
        p = PolyClone(&p_one);
        m[i] = MonoFromPoly(&p, i);
    }
    p = PolyAddMonos((unsigned)bits_num, m);
    p_res = PolyAt(&p, 2);
    if (!PolyIsEq(&p_res, &p_expected_res))
    {
        fprintf(stderr, "[SimpleAtTest2] error at first eval\n");
        return false;
    }
    PolyDestroy(&p);
    PolyDestroy(&p_res);
    PolyDestroy(&p_expected_res);
    p_expected_res = PolyFromCoeff(LONG_MAX - 1);
    for (int i = 0; i < bits_num - 1; i++)
    {
        p = PolyClone(&p_two);
        m[i] = MonoFromPoly(&p, i);
    }
    p = PolyAddMonos((unsigned)bits_num - 1, m);
    p_res = PolyAt(&p, 2);
    if (!PolyIsEq(&p_res, &p_expected_res))
    {
        fprintf(stderr, "[SimpleAtTest2] error at second eval\n");
        return false;
    }
    PolyDestroy(&p);
    PolyDestroy(&p_res);
    PolyDestroy(&p_expected_res);
    PolyDestroy(&p_one);
    PolyDestroy(&p_two);
    return true;
}
/**
 * Buduje wielomian rekurencyjnie i sprawdza, czy
 * PolyAt tworzy odpowiedzni wielmian poly_depth zmiennych.
 *
 * Następnie testowane jest PolyDeg i PolyDegBy
 * czy działaja na prostym przypadku
 */
bool AtTest()
{
    const size_t poly_size = 6;
    const int poly_depth = 3;
    const int upper_size = 5;
    bool result = true;
    Poly p = PolyFromCoeff(1);
    Mono *m = calloc(poly_size, sizeof(Mono));
    for (int j = 0; j < poly_depth; j++)
    {
        for (int i = 0; i < (int)poly_size; i++)
        {
            Poly tmp = PolyClone(&p);
            m[i] = MonoFromPoly(&tmp, i);
        }
        PolyDestroy(&p);
        p = PolyAddMonos(poly_size, m);
        // p = p + px + ... + px^n

    }
    Poly p_upper_size = PolyFromCoeff(upper_size);
    Poly p2 = PolyMul(&p_upper_size, &p);
    free(m);
    m = calloc(upper_size, sizeof(Mono));
    for (int i = 0; i < upper_size; i++)
    {
        Poly tmp = PolyClone(&p);
        m[i] = MonoFromPoly(&tmp, i);
    }
    PolyDestroy(&p);
    p = PolyAddMonos(upper_size, m);
    Poly p3 = PolyAt(&p, 1);
    if (!PolyIsEq(&p3, &p2))
    {
        fprintf(stderr, "[AtTest] fail\n");
        result = false;
    }
    if (PolyDeg(&p) !=
        (upper_size - 1) + (poly_depth * ((poly_exp_t)poly_size - 1)))
    {
        fprintf(stderr, "[AtTest] PolyDeg fail\n");
        result = false;
    }
    if (PolyDegBy(&p, 0) != upper_size - 1)
    {
        fprintf(stderr, "[AtTest] PolyDegBy(..., 0) fail\n");
        result = false;
    }
    if (PolyDegBy(&p, 1) != (poly_exp_t)poly_size - 1)
    {
        fprintf(stderr, "[AtTest] PolyDegBy(..., 1) fail\n");
        result = false;
    }
    PolyDestroy(&p);
    PolyDestroy(&p2);
    PolyDestroy(&p3);
    PolyDestroy(&p_upper_size);
    free(m);
    return result;
}

/**
 * Tworzenie wielomianu jednej zmiennej z listy współczynników i wykładników
 * @param count rozmiar tablicy
 * @param val tablica współczynników
 * @param exp tablica wykładników
 */
Poly MakePoly(unsigned count, const poly_coeff_t *val, poly_exp_t *exp)
{
    Mono *tmp = calloc(count, sizeof(struct Mono));
    int shift = 0;
    for (unsigned i = 0; i < count; i++)
    {
        Poly p = PolyFromCoeff(val[i]);
        if (val[i] == 0)
        {
            shift--;
            PolyDestroy(&p);
        }
        else
        {
            tmp[i + shift] = MonoFromPoly(&p, exp[i]);
        }
    }
    Poly res = PolyAddMonos(count + shift, tmp);
    free(tmp);
    return res;
}

/**
 * Tworzenie wielomianu wielu zmiennych z listy wielomianów i wykładników
 * @param count rozmiar tablicy
 * @param val tablica współczynników
 * @param exp tablica wykładników
 */
Poly MakePolyFromPolynomials(unsigned count, const Poly *val, poly_exp_t *exp)
{
    Mono *tmp = calloc(count, sizeof(struct Mono));
    for (unsigned i = 0; i < count; i++)
    {
        tmp[i] = MonoFromPoly(&val[i], exp[i]);
    }
    Poly res = PolyAddMonos(count, tmp);
    free(tmp);
    return res;
}

/**
 * Buduje wielomian o określonej glebokości. Pobiera długość kolejnych
 * wielomianów z tablicy exp_arr i wykładniki z tablicy exp_arr1
 * współczynniki są z tablicy coef_arr1.
 * @param depth głębokość  (ilość zmiennych) wielomianu
 * @param exp_shift wkaźnik do zmiennej przechowywującej pozycje w
 * tablicach exp_arr i exp_arr2 (z const_arr.h)
 * @param coef_shift wkaźnik do zmiennej przechowywującej pozycje w
 * tablicy coef_arr1 (z const_arr.h)
 */
Poly RecursiveBuild(int depth, int * exp_shift, int * coef_shift)
{
    if (depth == 0)
        return PolyFromCoeff(coef_arr1[(*coef_shift)++]);
    else
    {
        int size = exp_arr[*exp_shift];
        *exp_shift += 1;
        Mono m[size];
        for (int i = 0; i < size; i++)
        {
            Poly p = RecursiveBuild(depth - 1, exp_shift, coef_shift);
            if (PolyIsZero(&p))
            {
                PolyDestroy(&p);
                Poly p2 = PolyFromCoeff(1);
                m[i] = MonoFromPoly(&p2, exp_arr2[*exp_shift]);
            }
            else
                m[i] = MonoFromPoly(&p, exp_arr2[*exp_shift]);
            *exp_shift += 1;
        }
        return PolyAddMonos((unsigned) size, m);
    }
}

/**
 * Buduje wielomian o określonej glebokości. Pobiera długość kolejnych
 * wielomianów z tablicy exp_arr i wykładniki z tablicy exp_arr (argument)
 * współczynniki są z tablicy coef_arr(argument).
 * @param depth głębokość (ilość zmiennych) wielomianu
 * @param exp_shift wkaźnik do zmiennej przechowywującej pozycje w
 * tablicy exp_arr
 * @param coef_shift coef_shift wkaźnik do zmiennej przechowywującej pozycje w
 * tablicy coef_arr
 * @param coef_arr tablica współczynników
 * @param exp_arr tablica wykładników i długości
 * @return
 */
Poly RecursiveBuild2(int depth, int *exp_shift, int *coef_shift,
                     const poly_coeff_t *coef_arr, const poly_exp_t *exp_arr)
{
    if (depth == 0)
        return PolyFromCoeff(coef_arr[(*coef_shift)++]);
    else
    {
        int size = exp_arr[*exp_shift];
        *exp_shift += 1;
        Mono m[size];
        for (int i = 0; i < size; i++)
        {
            Poly p = RecursiveBuild2(depth - 1, exp_shift, coef_shift, coef_arr, exp_arr);
            if (PolyIsZero(&p))
            {
                PolyDestroy(&p);
                Poly p2 = PolyFromCoeff(1);
                m[i] = MonoFromPoly(&p2, exp_arr[*exp_shift]);
            }
            else
                m[i] = MonoFromPoly(&p, exp_arr[*exp_shift]);
            *exp_shift += 1;
        }
        return PolyAddMonos((unsigned) size, m);
    }
}

/**
 * Sprawdza czy PolyDegBy i PolyDeg przeglądają wszystkie potrzebne
 * elementy struktury
 */
bool DegByTest()
{
    bool result = true;
    int exp_shift = 0;
    int coef_shift = 0;
    const unsigned depth = 5;
    Poly p = RecursiveBuild(depth, &exp_shift, &coef_shift);
    int deg_arr[] = {355, 368, 384, 399, 399};
    for (unsigned i=0; i < depth; i++)
    {
        if (deg_arr[i] !=  PolyDegBy(&p, i))
        {
            fprintf(stderr, "[DegByTest] PolyDegBy(..., %d) fail\n", i);
            result = false;
        }
    }
    if (1639 != PolyDeg(&p))
    {
        fprintf(stderr, "[DegByTest] PolyDeg fail\n");
        result = false;
    }
    PolyDestroy(&p);

    return result;
}


/**
 * Sprawdza mnożenie na wzorach skróconego mnożenia
 */
bool MulTest()
{
    {
        poly_coeff_t val[] = {1, 1};
        poly_exp_t exp[] = {0, 1};
        Poly p1 = MakePoly(2, val, exp);
        Poly p2 = PolyMul(&p1, &p1);
        poly_coeff_t res_val[] = {1, 2, 1};
        poly_exp_t res_exp[] = {0, 1, 2};
        Poly p_res1 = MakePoly(3, res_val, res_exp);
        if (!PolyIsEq(&p2, &p_res1))
        {
            fprintf(stderr, "[MulTest] PolyMul (1) error\n");
            return false;
        }
        PolyDestroy(&p2);
        PolyDestroy(&p_res1);
        PolyDestroy(&p1);
    }
    {
        poly_coeff_t val1[] = {1, 1};
        poly_coeff_t val2[] = {1, -1};
        poly_exp_t exp[] = {0, 1};
        poly_exp_t exp_res[] = {0, 2};
        Poly p1 = MakePoly(2, val1, exp);
        Poly p2 = MakePoly(2, val2, exp);
        Poly p3 = PolyMul(&p1, &p2);
        Poly p_res1 = MakePoly(2, val2, exp_res);
        if (!PolyIsEq(&p3, &p_res1))
        {
            fprintf(stderr, "[MulTest] PolyMul (2) error\n");
            return false;
        }
        PolyDestroy(&p3);
        PolyDestroy(&p_res1);
        PolyDestroy(&p1);
        PolyDestroy(&p2);
    }
    {
        Poly p_two = PolyFromCoeff(2);
        poly_coeff_t val[] = {1, 1};
        poly_exp_t exp[] = {0, 1};
        Poly p1 = MakePoly(2, val, exp);
        Poly p_arr[] = {PolyClone(&p1), PolyClone(&p1)};
        Poly p2 = MakePolyFromPolynomials(2, p_arr, exp);
        Poly p3 = PolyMul(&p2, &p2);
        poly_coeff_t res_val[] = {1, 2, 1};
        poly_exp_t res_exp[] = {0, 1, 2};
        Poly p_res1 = MakePoly(3, res_val, res_exp);
        Poly p_arr2[] = {PolyClone(&p_res1), PolyMul(&p_res1, &p_two),
                         PolyClone(&p_res1)};
        Poly p_res2 = MakePolyFromPolynomials(3, p_arr2, res_exp);
        if (!PolyIsEq(&p3, &p_res2))
        {
            fprintf(stderr, "[MulTest] PolyMul (3) error\n");
            return false;
        }
        PolyDestroy(&p_two);
        PolyDestroy(&p3);
        PolyDestroy(&p_res1);
        PolyDestroy(&p_res2);
        PolyDestroy(&p1);
        PolyDestroy(&p2);
    }

    return true;
}

/**
 * Buduje wielomian @p rec zmiennych,
 * gdzie każda zmienna występuje w dokładnie jednym jednomianie
 * @param coef_arr
 * @param exp_arr
 * @param rec
 */
Poly BuildRecursivePoly(const poly_coeff_t * coef_arr, const poly_exp_t * exp_arr, size_t rec)
{
    Poly res = PolyZero();
    for (size_t i = rec; i > 0 ; i--){
        poly_coeff_t coef = coef_arr[i - 1];
        poly_exp_t exp = exp_arr[i - 1];
        if (coef == 0)
        {
            if (!PolyIsZero(&res))
            {
                Mono m = MonoFromPoly(&res, 0);
                res = PolyAddMonos(1, &m);
            }
            continue;
        }
        Poly p = PolyFromCoeff(coef);
        if (PolyIsZero(&res))
        {
            Mono m = MonoFromPoly(&p, exp);
            PolyDestroy(&res);
            res = PolyAddMonos(1, &m);
        }
        else
        {
            Mono m[2] = {MonoFromPoly(&p, exp), MonoFromPoly(&res, 0)};
            res = PolyAddMonos(2, m);
        }
    }
    return res;
}

/**
 * Testuje czy dodawanie długich wielomianów jednej zmiennej działa poprawnie
 * Testuje działanie PolyNeg
 */
bool AddTest1()
{
    const poly_exp_t step = 10;
    bool good = true;
    size_t current_max_exp = 10;
    size_t previous_current_max_exp = 0;
    poly_exp_t *exp_list = calloc(conf_size, sizeof(poly_exp_t));
    poly_coeff_t *poly_coef_res_arr = calloc(conf_size, sizeof(poly_coeff_t));
    for (poly_exp_t i = 0; i < (poly_exp_t)conf_size; i++)
    {
        exp_list[i] = i;
        poly_coef_res_arr[i] = coef_arr2[i];
    }
    while (current_max_exp <= conf_size && good)
    {
        for (size_t i = previous_current_max_exp; i < current_max_exp; i++)
        {
            poly_coef_res_arr[i] = coef_arr1[i] + coef_arr2[i];
        }
        previous_current_max_exp = current_max_exp;
        Poly p1 = MakePoly((unsigned)current_max_exp, coef_arr1, exp_list);
        size_t local_max_exp = current_max_exp;
        while (local_max_exp <= conf_size && good)
        {
            Poly p2 = MakePoly((unsigned)local_max_exp, coef_arr2, exp_list);
            Poly p3 = PolyAdd(&p1, &p2);
            PolyDestroy(&p2);
            Poly p_expected_res =
                MakePoly((unsigned)local_max_exp, poly_coef_res_arr, exp_list);
            if (!PolyIsEq(&p3, &p_expected_res))
            {
                fprintf(stderr, "[AddTest1] error for %lu %lu", current_max_exp,
                        local_max_exp);
                good = false;
            }
            PolyDestroy(&p3);
            PolyDestroy(&p_expected_res);
            local_max_exp *= step;
        }
        Poly p2 = PolyNeg(&p1);
        Poly p3 = PolyAdd(&p2, &p1);
        if (!PolyIsZero(&p3))
        {
            fprintf(stderr, "[AddTest1] error for %lu in PolyNeg add",
                    current_max_exp);
            good = false;
        }
        PolyDestroy(&p1);
        PolyDestroy(&p2);
        PolyDestroy(&p3);
        current_max_exp *= step;
    }
    free(exp_list);
    free(poly_coef_res_arr);
    return good;
}

/**
 * Testuje czy dodawanie długich wielomianów wielu zmiennych działa poprawnie
 * Testuje działanie PolyNeg
 */
bool AddTest2()
{
    bool good = true;
    const poly_exp_t step = 2;
    poly_coeff_t *pol_arr_expected_res = calloc(conf_size, sizeof(poly_coeff_t));
    for (size_t j = 0; j < conf_size; ++j)
    {
        pol_arr_expected_res[j] = coef_arr2[j];
    }

    size_t prev_poly_len = 0;
    size_t first_poly_len = 2;
    size_t second_poly_len;
    while (first_poly_len <= conf_size && good)
    {
        for (size_t i = prev_poly_len; i < first_poly_len; ++i)
        {
            pol_arr_expected_res[i] += coef_arr1[i];
        }
        prev_poly_len = first_poly_len;
        Poly p1 = BuildRecursivePoly(coef_arr1, exp_arr, first_poly_len);
        second_poly_len = first_poly_len;
        while (second_poly_len <= conf_size && good)
        {
            Poly p2 = BuildRecursivePoly(coef_arr2, exp_arr, second_poly_len);
            Poly p_res = PolyAdd(&p1, &p2);
            PolyDestroy(&p2);
            Poly p_expected_res = BuildRecursivePoly(pol_arr_expected_res, exp_arr, second_poly_len);
            if (!PolyIsEq(&p_res, &p_expected_res))
            {
                fprintf(stderr, "[AddTest2] error for %lu %lu\n",
                        first_poly_len, second_poly_len);
                good = false;
            }
            PolyDestroy(&p_res);
            PolyDestroy(&p_expected_res);
            second_poly_len *= step;
        }
        Poly p2 = PolyNeg(&p1);
        Poly p3 = PolyAdd(&p2, &p1);
        if (!PolyIsZero(&p3))
        {
            fprintf(stderr, "[AddTest2] error for %lu in PolyNeg add",
                    first_poly_len);
            good = false;
        }
        PolyDestroy(&p1);
        PolyDestroy(&p2);
        PolyDestroy(&p3);
        first_poly_len *= step;
    }
    free(pol_arr_expected_res);

    return good;
}

/**
 * Testuje czy odejmowanie długich wielomianów jednej zmiennej działa poprawnie
 */
bool SubTest1()
{
    const poly_exp_t step = 10;
    bool good = true;
    size_t current_max_exp = 10;
    size_t previous_current_max_exp = 0;
    poly_exp_t *exp_list = calloc(conf_size, sizeof(poly_exp_t));
    poly_coeff_t *poly_coef_res_arr = calloc(conf_size, sizeof(poly_coeff_t));
    for (poly_exp_t i = 0; i < (poly_exp_t)conf_size; i++)
    {
        exp_list[i] = i;
        poly_coef_res_arr[i] = coef_arr2[i];
    }
    while (current_max_exp <= conf_size && good)
    {
        for (size_t i = previous_current_max_exp; i < current_max_exp; i++)
        {
            poly_coef_res_arr[i] = coef_arr2[i] - coef_arr1[i];
        }
        previous_current_max_exp = current_max_exp;
        Poly p1 = MakePoly((unsigned)current_max_exp, coef_arr1, exp_list);
        size_t local_max_exp = current_max_exp;
        while (local_max_exp <= conf_size && good)
        {
            Poly p2 = MakePoly((unsigned)local_max_exp, coef_arr2, exp_list);
            Poly p3 = PolySub(&p2, &p1);
            Poly p_expected_res =
                MakePoly((unsigned)local_max_exp, poly_coef_res_arr, exp_list);
            if (!PolyIsEq(&p3, &p_expected_res))
            {
                fprintf(stderr, "[SubTest1] error for %lu %lu", current_max_exp,
                        local_max_exp);
                good = false;
            }
            PolyDestroy(&p3);
            PolyDestroy(&p2);
            PolyDestroy(&p_expected_res);
            local_max_exp *= step;
        }
        PolyDestroy(&p1);
        current_max_exp *= step;
    }
    free(exp_list);
    free(poly_coef_res_arr);
    return good;
}

/**
 * Testuje czy odejmowanie długich wielomianów wielu zmiennych działa poprawnie
 */
bool SubTest2()
{
    bool good = true;
    const poly_exp_t step = 2;
    poly_coeff_t *pol_arr_expected_res = calloc(conf_size, sizeof(poly_coeff_t));
    for (size_t j = 0; j < conf_size; ++j)
    {
        pol_arr_expected_res[j] = coef_arr2[j];
    }

    size_t prev_poly_len = 0;
    size_t first_poly_len = 2;
    size_t second_poly_len;
    while (first_poly_len <= conf_size && good)
    {
        for (size_t i = prev_poly_len; i < first_poly_len; ++i)
        {
            pol_arr_expected_res[i] -= coef_arr1[i];
        }
        prev_poly_len = first_poly_len;
        Poly p1 = BuildRecursivePoly(coef_arr1, exp_arr, first_poly_len);
        second_poly_len = first_poly_len;
        while (second_poly_len <= conf_size && good)
        {
            Poly p2 = BuildRecursivePoly(coef_arr2, exp_arr, second_poly_len);
            Poly p_res = PolySub(&p2, &p1);
            Poly p_expected_res = BuildRecursivePoly(pol_arr_expected_res, exp_arr, second_poly_len);
            if (!PolyIsEq(&p_res, &p_expected_res))
            {
                fprintf(stderr, "[SubTest2] error for %lu %lu\n",
                        first_poly_len, second_poly_len);
                good = false;
            }
            PolyDestroy(&p2);
            PolyDestroy(&p_res);
            PolyDestroy(&p_expected_res);
            second_poly_len *= step;
        }
        Poly p2 = PolyNeg(&p1);
        Poly p3 = PolyAdd(&p2, &p1);
        if (!PolyIsZero(&p3))
        {
            fprintf(stderr, "[AddTest2] error for %lu in PolyNeg add",
                    first_poly_len);
            good = false;
        }
        PolyDestroy(&p1);
        PolyDestroy(&p2);
        PolyDestroy(&p3);
        first_poly_len *= step;
    };
    free(pol_arr_expected_res);

    return good;
}

/**
 * Funkcja pomocnicza do tworzenie wyników mnożenia wielomianow 
 * @param size1 długość danych w arr_1
 * @param arr_1 tablica wspolczynnikow pierwszego wielomiannu
 * @param size2 długość danych w arr_2
 * @param arr_2 tablica wspolczynnikow drugiego wielomiannu
 */
poly_coeff_t *MullArray(size_t size1, const poly_coeff_t *arr_1, size_t size2,
                        const poly_coeff_t *arr_2)
{
    poly_coeff_t *res = calloc(size1 + size2, sizeof(poly_coeff_t));
    for (size_t i = 0; i < size1; i++)
    {
        for (size_t j = 0; j < size2; ++j)
        {
            res[i + j] += arr_1[i] * arr_2[j];
        }
    }
    return res;
}

/**
 * Test mnożenia długich wielomianów.
 * Sprawdza poprawność i wydajność implementacji
 */
bool MulTest2()
{
    bool good = true;
    size_t step = 10;
    size_t poly_one_len = 5;
    size_t poly_two_len;
    size_t current_conf_size = 501; // conf_size+1; - dla ambitnych: wzorcowe
    // rozwiązanie w trybe relase na studentsie wykonuje się w 1m44.373s (real) 
    poly_exp_t *exp_list = calloc(2 * current_conf_size, sizeof(poly_exp_t));
    for (poly_exp_t i = 0; i < (poly_exp_t)current_conf_size * 2; i++)
    {
        exp_list[i] = i;
    }
    while (poly_one_len < current_conf_size && good)
    {
        poly_two_len = poly_one_len;
        Poly p1 = MakePoly((unsigned)poly_one_len, coef_arr1, exp_list);
        while (poly_two_len < current_conf_size && good)
        {
            Poly p2 = MakePoly((unsigned)poly_two_len, coef_arr2, exp_list);
            poly_coeff_t *expected_res_coef =
                MullArray(poly_one_len, coef_arr1, poly_two_len, coef_arr2);
            Poly p_expected_res =
                MakePoly((unsigned)(poly_one_len + poly_two_len),
                         expected_res_coef, exp_list);
            Poly p_res = PolyMul(&p1, &p2);
            if (!PolyIsEq(&p_expected_res, &p_res))
            {
                fprintf(stderr, "[MulTest2] error for %lu %lu\n", poly_one_len,
                        poly_two_len);
                good = false;
            }
            PolyDestroy(&p2);
            PolyDestroy(&p_expected_res);
            PolyDestroy(&p_res);
            free(expected_res_coef);
            poly_two_len *= step;
        }
        PolyDestroy(&p1);
        poly_one_len *= step;
    }
    free(exp_list);
    return good;
}

/**
 * Sprawdza poprawność działania funkcji PolyIsEq na dłuższych przykładach
 * @return
 */
bool IsEqTest()
{
    bool result = true;
    const size_t copy_size = 1000;
    poly_coeff_t *coef_copy = calloc(copy_size, sizeof(poly_coeff_t));
    memcpy(coef_copy, coef_arr1, copy_size * sizeof(poly_coeff_t));
    coef_copy[90]++;

    {
        Poly p1 = PolyFromCoeff(1);
        Poly p2 = PolyFromCoeff(1);
        Poly p3 = PolyFromCoeff(2);
        if (!PolyIsEq(&p1, &p2))
        {
            fprintf(stderr, "[IsEqTest] fail 1");
            result = false;
        }
        if (PolyIsEq(&p1, &p3))
        {
            fprintf(stderr, "[IsEqTest] fail 2");
            result = false;
        }
        PolyDestroy(&p1);
        PolyDestroy(&p2);
        PolyDestroy(&p3);
    }
    if (result)
    {
        Poly p1 = MakePoly(100, coef_arr1, exp_arr);
        Poly p2 = MakePoly(100, coef_arr1, exp_arr);
        Poly p3 = MakePoly(100, coef_copy, exp_arr);
        if (!PolyIsEq(&p1, &p2))
        {
            fprintf(stderr, "[IsEqTest] fail 3");
            result = false;
        }
        if (PolyIsEq(&p1, &p3))
        {
            fprintf(stderr, "[IsEqTest] fail 4");
            result = false;
        }
        PolyDestroy(&p1);
        PolyDestroy(&p2);
        PolyDestroy(&p3);

    }
    if (result)
    {
        Poly p1 = BuildRecursivePoly(coef_arr1, exp_arr, 100);
        Poly p2 = BuildRecursivePoly(coef_arr1, exp_arr, 100);
        Poly p3 = BuildRecursivePoly(coef_copy, exp_arr, 100);
        if (!PolyIsEq(&p1, &p2))
        {
            fprintf(stderr, "[IsEqTest] fail 5");
            result = false;
        }
        if (PolyIsEq(&p1, &p3))
        {
            fprintf(stderr, "[IsEqTest] fail 6");
            result = false;
        }
        PolyDestroy(&p1);
        PolyDestroy(&p2);
        PolyDestroy(&p3);

    }
    if (result)
    {
        int exp_shift_base = 0;
        int coef_shift_base = 5;
        int exp_shift = exp_shift_base;
        int coef_shift = coef_shift_base;


        Poly p1 = RecursiveBuild2(3, &exp_shift, &coef_shift, coef_arr1, exp_arr);
        exp_shift = exp_shift_base;
        coef_shift = coef_shift_base;
        Poly p2 = RecursiveBuild2(3, &exp_shift, &coef_shift, coef_arr1, exp_arr);
        exp_shift = exp_shift_base;
        coef_shift = coef_shift_base;
        Poly p3 = RecursiveBuild2(3, &exp_shift, &coef_shift, coef_copy, exp_arr);

        if (!PolyIsEq(&p1, &p2))
        {
            fprintf(stderr, "[IsEqTest] fail 7");
            result = false;
        }
        if (PolyIsEq(&p1, &p3))
        {
            fprintf(stderr, "[IsEqTest] fail 8");
            result = false;
        }
        PolyDestroy(&p1);
        PolyDestroy(&p2);
        PolyDestroy(&p3);
    }
    free(coef_copy);

    return result;
}


/**
 * Sprawdza czy jest używana implementacja wielomianów,
 * która nie zajmuje dużej ilości pamięci dla rzadkich wielomianów.
 * Test będzie uruchamiany z małym limitem pamięci.
 */
bool RarePolynomialTest()
{
    bool result = true;
    const size_t size = 4000;
    poly_exp_t rare_exp_arr[size];
    rare_exp_arr[0] = exp_arr2[0];
    poly_coeff_t sum = coef_arr1[0];
    for (size_t i = 1; i < size; ++i)
    {
        rare_exp_arr[i] = rare_exp_arr[i-1] + exp_arr2[i];
        sum += coef_arr1[i];
    }
    Poly p = MakePoly(size, coef_arr1, rare_exp_arr);
    Poly expected_res = PolyFromCoeff(sum);
    Poly res = PolyAt(&p, 1);
    if (!PolyIsEq(&expected_res, &res))
    {
        fprintf(stderr, "[RarePolynomialTest] fail 1");
        result = false;
    }
    if (PolyDeg(&p) != rare_exp_arr[size-1])
    {
        fprintf(stderr, "[RarePolynomialTest] fail 2");
        result = false;
    }
    PolyDestroy(&p);
    PolyDestroy(&res);
    PolyDestroy(&expected_res);
    return result;
}

// Sekcja z testami tworzonymi ręcznie

#define C PolyFromCoeff


Poly MakePolyHelper(int dummy, ...)
{
    va_list list;
    va_start(list, dummy);
    unsigned count = 0;
    while (true)
    {
        va_arg(list, Poly);
        if (va_arg(list, int) < 0)
            break;
        count++;
    }
    va_start(list, dummy);
    Mono *arr = calloc(count, sizeof(Mono));
    for (unsigned i = 0; i < count; ++i)
    {
        Poly p = va_arg(list, Poly);
        arr[i] = MonoFromPoly(&p, va_arg(list, int));
        assert(i == 0 || arr[i].exp > arr[i - 1].exp);
    }
    Poly closing_zero = va_arg(list, Poly);
    va_end(list);
    PolyDestroy(&closing_zero);
    Poly res = PolyAddMonos(count, arr);
    free(arr);
    return res;
}

/**
 * Pomocnicze makro do tworzenia wielomianów.
 * P(@f$ c_0, e_0, c_1, e_1, \ldots @f$) tworzy wielomian
 * @f$ c_0x^{e_0} + c_1x^{e_1} + \ldots @f$
 */
#define P(...) MakePolyHelper(0, __VA_ARGS__, PolyZero(), -1)

/**
 * Testuje czy Stopień wielomianu jest poprawnie liczony rekurencyjnie.
 */
bool DegTest()
{
    Poly p = P(P(C(1), 1, C(1), 10), 1, P(C(1), 1, C(1), 2), 2);
    if (PolyDeg(&p) != 11)
    {
        fprintf(stderr, "[DegTest] PolyDeg error\n");
        return false;
    }
    PolyDestroy(&p);
    return true;
}

static inline bool TestOpC(Poly a, Poly b, Poly res,
                           Poly (*op)(const Poly *, const Poly *))
{
    Poly c = op(&a, &b);
    bool is_eq = PolyIsEq(&c, &res);
    PolyDestroy(&a);
    PolyDestroy(&b);
    PolyDestroy(&c);
    PolyDestroy(&res);
    return is_eq;
}

bool TestAdd(Poly a, Poly b, Poly res)
{
    return TestOpC(a, b, res, PolyAdd);
}

bool TestAddMonos(unsigned count, Mono monos[], Poly res)
{
    Poly b = PolyAddMonos(count, monos);
    bool is_eq = PolyIsEq(&b, &res);
    PolyDestroy(&b);
    PolyDestroy(&res);
    return is_eq;
}

bool TestMul(Poly a, Poly b, Poly res)
{
    return TestOpC(a, b, res, PolyMul);
}

bool TestSub(Poly a, Poly b, Poly res)
{
    return TestOpC(a, b, res, PolySub);
}

bool TestDegBy(Poly a, unsigned var_idx, int res)
{
    bool is_eq = PolyDegBy(&a, var_idx) == res;
    PolyDestroy(&a);
    return is_eq;
}

bool TestDeg(Poly a, int res)
{
    bool is_eq = PolyDeg(&a) == res;
    PolyDestroy(&a);
    return is_eq;
}

bool TestEq(Poly a, Poly b, bool res)
{
    bool is_eq = PolyIsEq(&a, &b) == res;
    PolyDestroy(&a);
    PolyDestroy(&b);
    return is_eq;
}

bool TestAt(Poly a, poly_coeff_t x, Poly res)
{
    Poly b = PolyAt(&a, x);
    bool is_eq = PolyIsEq(&b, &res);
    PolyDestroy(&a);
    PolyDestroy(&b);
    PolyDestroy(&res);
    return is_eq;
}

bool SimpleAddTest()
{
    bool res = true;
    // Różne przypadki wielomian/współczynnik
    res &= TestAdd(
            C(1),
            C(2),
            C(3));
    res &= TestAdd(
            P(C(1), 1),
            C(2),
            P(C(2), 0, C(1), 1));
    res &= TestAdd(
            C(1),
            P(C(2), 2),
            P(C(1), 0, C(2), 2));
    res &= TestAdd(
            P(C(1), 1),
            P(C(2), 2),
            P(C(1), 1, C(2), 2));
    res &= TestAdd(
            C(0),
            P(C(1), 1),
            P(C(1), 1));
    // Upraszczanie się wielomianu
    res &= TestAdd(
            P(C(1), 1),
            P(C(-1), 1),
            C(0));
    res &= TestAdd(
            P(C(1), 1, C(2), 2),
            P(C(-1), 1),
            P(C(2), 2));
    res &= TestAdd(
            P(C(2), 0, C(1), 1),
            P(C(-1), 1),
            C(2));
    // Dodawanie współczynnika i upraszczanie
    res &= TestAdd(
            C(1),
            P(C(-1), 0, C(1), 1),
            P(C(1), 1));
    res &= TestAdd(
            C(1),
            P(P(C(-1), 0, C(1), 1), 0),
            P(P(C(1), 1), 0));
    res &= TestAdd(
            C(1),
            P(C(1), 0, C(2), 2),
            P(C(2), 0, C(2), 2));
    res &= TestAdd(
            C(1),
            P(P(C(1), 0, C(1), 1), 0, C(2), 2),
            P(P(C(2), 0, C(1), 1), 0, C(2), 2));
    res &= TestAdd(
            C(1),
            P(P(C(-1), 0, C(1), 1), 0, C(2), 2),
            P(P(C(1), 1), 0, C(2), 2));
    // Dodawanie wielomianów wielu zmiennych
    res &= TestAdd(
            P(P(C(1), 2), 0, P(C(2), 1), 1, C(1), 2),
            P(P(C(1), 2), 0, P(C(-2), 1), 1, C(1), 2),
            P(P(C(2), 2), 0, C(2), 2));
    res &= TestAdd(
            P(P(C(1), 2), 0, P(C(2), 1), 1, C(1), 2),
            P(P(C(-1), 2), 0, P(C(1), 0, C(2), 1, C(1), 2), 1, C(-1), 2),
            P(P(C(1), 0, C(4), 1, C(1), 2), 1));
    // Redukcja do współczynnika
    res &= TestAdd(
            P(P(C(1), 0, C(1), 1), 0, C(1), 1),
            P(P(C(1), 0, C(-1), 1), 0, C(-1), 1),
            C(2));
    res &= TestAdd(
            P(P(P(C(1), 0, C(1), 1), 0, C(1), 1), 1),
            P(P(P(C(1), 0, C(-1), 1), 0, C(-1), 1), 1),
            P(C(2), 1));
    // Dodawanie wielomianu do siebie
    {
        Poly a = P(C(1), 1);
        Poly b = PolyAdd(&a, &a);
        Poly c = P(C(2), 1);
        res &= PolyIsEq(&b, &c);
        PolyDestroy(&a);
        PolyDestroy(&b);
        PolyDestroy(&c);
    }
    return res;
}

static inline Mono M(Poly p, poly_exp_t e)
{
    return MonoFromPoly(&p, e);
}

bool SimpleAddMonosTest()
{
    bool res = true;
    {
        Mono m[] = { M(C(-1), 0), M(C(1), 0) };
        res &= TestAddMonos(2, m, C(0));
    }
    {
        Mono m[] = { M(C(-1), 1), M(C(1), 1) };
        res &= TestAddMonos(2, m, C(0));
    }
    {
        Mono m[] = { M(C(1), 0), M(C(1), 0) };
        res &= TestAddMonos(2, m, C(2));
    }
    {
        Mono m[] = { M(C(1), 1), M(C(1), 1) };
        res &= TestAddMonos(2, m, P(C(2), 1));
    }
    {
        Mono m[] = { M(P(C(-1), 1), 0), M(P(C(1), 1), 0) };
        res &= TestAddMonos(2, m, C(0));
    }
    {
        Mono m[] = { M(P(C(-1), 0), 1), M(P(C(1), 0), 1),
                     M(C(2), 0), M(C(1), 1),
                     M(P(C(2), 1), 2), M(P(C(2), 2), 2) };
        res &= TestAddMonos(6, m, P(C(2), 0, C(1), 1, P(C(2), 1, C(2), 2), 2));
    }
    return res;
}

bool SimpleMulTest()
{
    bool res = true;
    res &= TestMul(
            C(2),
            C(3),
            C(6));
    res &= TestMul(
            P(C(1), 1),
            C(2),
            P(C(2), 1));
    res &= TestMul(
            C(3),
            P(C(2), 2),
            P(C(6), 2));
    res &= TestMul(
            P(C(1), 1),
            P(C(2), 2),
            P(C(2), 3));
    res &= TestMul(
            P(C(-1), 0, C(1), 1),
            P(C(1), 0, C(1), 1),
            P(C(-1), 0, C(1), 2));
    res &= TestMul(
            P(P(C(1), 2), 0, P(C(1), 1), 1, C(1), 2),
            P(P(C(1), 2), 0, P(C(-1), 1), 1, C(1), 2),
            P(P(C(1), 4), 0, P(C(1), 2), 2, C(1), 4));
    return res;
}

bool SimpleNegTest()
{
    Poly a = P(P(C(1), 0, C(2), 2), 0, P(C(1), 1), 1, C(1), 2);
    Poly b = PolyNeg(&a);
    Poly c = P(P(C(-1), 0, C(-2), 2), 0, P(C(-1), 1), 1, C(-1), 2);
    bool is_eq = PolyIsEq(&b, &c);
    PolyDestroy(&a);
    PolyDestroy(&b);
    PolyDestroy(&c);
    return is_eq;
}

bool SimpleSubTest()
{
    return TestSub(
            P(P(C(1), 2), 0, P(C(2), 1), 1, C(1), 2),
            P(P(C(1), 2), 0, P(C(-1), 0, C(-2), 1, C(-1), 2), 1, C(1), 2),
            P(P(C(1), 0, C(4), 1, C(1), 2), 1));
}

#define POLY_P P(P(C(1), 3), 0, P(C(1), 2), 2, C(1), 3)

bool SimpleDegByTest()
{
    bool res = true;
    res &= TestDegBy(C(0), 1, -1);
    res &= TestDegBy(C(1), 0, 0);
    res &= TestDegBy(P(C(1), 1), 1, 0);
    res &= TestDegBy(POLY_P, 0, 3);
    res &= TestDegBy(POLY_P, 1, 3);
    return res;
}

bool SimpleDegTest()
{
    bool res = true;
    res &= TestDeg(C(0), -1);
    res &= TestDeg(C(1), 0);
    res &= TestDeg(P(C(1), 1), 1);
    res &= TestDeg(POLY_P, 4);
    return res;
}

bool SimpleIsEqTest()
{
    bool res = true;
    res &= TestEq(C(0), C(0), true);
    res &= TestEq(C(0), C(1), false);
    res &= TestEq(C(1), C(1), true);
    res &= TestEq(P(C(1), 1), C(1), false);
    res &= TestEq(P(C(1), 1), P(C(1), 1), true);
    res &= TestEq(P(C(1), 1), P(C(1), 2), false);
    res &= TestEq(P(C(1), 1), P(C(2), 1), false);
    res &= TestEq(POLY_P, POLY_P, true);
    {
        Poly a = C(1);
        Poly b = C(2);
        Poly p = POLY_P;
        res &= TestEq(PolyAdd(&p, &a), PolyAdd(&p, &b), false);
        PolyDestroy(&a);
        PolyDestroy(&b);
        PolyDestroy(&p);
    }
    return res;
}

bool SimpleAtTest()
{
    bool res = true;
    res &= TestAt(C(2), 1, C(2));
    res &= TestAt(P(C(1), 0, C(1), 18), 10, C(1000000000000000001L));
    res &= TestAt(P(C(3), 1, C(2), 3, C(1), 5), 10, C(102030));
    res &= TestAt(P(P(C(1), 4), 0, P(C(1), 2), 2, C(1), 3), 2,
                  P(C(8), 0, C(4), 2, C(1), 4));
    return res;
}

bool OverflowTest()
{
    bool res = true;
    res &= TestMul(P(C(1L << 32), 1), C(1L << 32), C(0));
    res &= TestAt(P(C(1), 64), 2, C(0));
    res &= TestAt(P(C(1), 0, C(1), 64), 2, C(1));
    res &= TestAt(P(P(C(1), 1), 64), 2, C(0));
    return res;
}

void MemoryTest()
{
    Poly *p = malloc(sizeof(struct Poly));
    *p = PolyFromCoeff(5);
    Mono m = MonoFromPoly(p, 4);
    *p = PolyFromCoeff(3);
    PolyDestroy(p);
    free(p); // To nie jest Destroy, to tylko zwalnia malloca
    Poly p2 = PolyAddMonos(1, &m);
    Poly p3 = PolyAt(&p2, 2);
    Poly p4 = PolyFromCoeff(80);
    if (!PolyIsEq(&p4, &p3)){
        fprintf(stderr, "[MemoryTest] error");
    }
    PolyDestroy(&p2);
    PolyDestroy(&p3);
    PolyDestroy(&p4);
}
