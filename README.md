# PolyCalc
# Exercise

This project is based on exercise we had to do on `Warsaw University, Poland`
on the `Individual Programistic Project` subject.

### Task

The exercise was to design and implement:
* Provide dynamically-allocated lists implementation - *pre-exercise*

* Polynomial handling library in pure C99 - *part no. 1*

* Interactive calculator for that library - *part no. 2*

* Implement additional functionality - *part no. 3*

### Project structure

The project provides:
* library `src/poly.h` for handling polynomials

* additional helper libraries like dynamically allocated arrays etc.

* interactive calculator `src/calc_poly.c`

# Building

To build do the following:

* Create release folder - `mkdir release`

* Go to that folder - `cd release`

* Generate makefiles - `cmake ..`

* Build everything - `make`

* Optionally generate documentation (needs Doxygen to be installed) - `make doc`

* Optionally clean everything - `make clean`

# Polynomial library

All the documentation is provided in header files.

There you've got example usage of the library:

```c
  #include "poly.h"

  int main(void) {

    Poly p = PolyC(4);
    // Create constant polynomial
    // p(x) = 4

    Poly q = PolyP( PolyC(1), 2 );
    // Create polynomial that consists of
    // variable square multiplied by
    // coefficient 1
    // q(x) = 1*x^2

    // As you may see the coefficients that are placed
    // next to variables may be other polynomials
    // (polynomials from other variable)

    Poly r = PolyP( PolyP( PolyC(1), 2 ), 3 );
    // In this example
    // r(x,y) = (1*y^2)*(x^3)

    // Now you can do arithemtic operations on them
    // for example addition:
    Poly sum = PolyAdd(&p, &q);
    // sum(x) = 4 + x^2
    // If you are not sure what would happen if we sum
    // q and r then we say that the result is
    //
    // q(x) + r(x,y) = 1*x^2 + (1*y^2)*(x^3)
    // that is:
    //   x^2 + (y^2)(x^3)
    //

    // Or evalue at specific point:
    Poly rAtTwo = PolyAt(&r, 2);
    // Now we assume the first variable is equal to 2
    // So we calculate r(x,y) for x->2
    // rAtTwo = r(2,y) = (2^3)*y^2 = 8*y^2

    // You can print them nicely:
    PolyPrint(&rAtTwo);
    // ^ Do it yourself and see what the output is

    // After everything we must free them all
    PolyDestroy(&p);
    PolyDestroy(&q);
    PolyDestroy(&r);
    PolyDestroy(&sum);
    PolyDestroy(&rAtTwo);

  }
```

# Polynomial calculator

The calulator resides in `src/calc_poly.c`.
