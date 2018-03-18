/** @file
   tablica wszystkich dostepnych komend.
   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-25
 */

 /**
  * Deklaracja tablicy wszystkich dostepnych komend.
  * !!!!!POSORTOWANA LEKSYKOGRAFICZNIE NALEZY TO ZACHOWAC PRZY DODAWANIU NOWEJ KOMENDY!!!!!!!
 */
static const char *commandsarr[] = {
        "ADD",
        "AT",
        "CLONE",
        "COMPOSE",
        "DEG",
        "DEG_BY",
        "IS_COEFF",
        "IS_EQ",
        "IS_ZERO",
        "MUL",
        "NEG",
        "POP",
        "PRINT",
        "SUB",
        "ZERO"
};
/**
 * dlugosc tablicy wszystkich komend.
 */
static const int commandsarrLength = sizeof(commandsarr) / sizeof(void *);
