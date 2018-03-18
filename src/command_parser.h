/** @file
   Interfejs parsera komend

   @author Kacper Konecki <kkonecki@student.uw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-25
*/

#ifndef POLY_COMMAND_PARSER_H
#define POLY_COMMAND_PARSER_H

/*ABY DODAC NOWĄ KOMENDĘ TRZEBA WSTAWIĆ JĄ DO TABLICY W ODPOWINIM MIEJSCU I TU TEZ NO W ODPOWIEDNIM MIEJSCU*/
/** ID alfabetycznie pierwszej komendy */
#define    FIRST_DEF_VALUE 100
/** ID komendy ADD */
#define    ADD      (FIRST_DEF_VALUE)
/** ID komendy AT */
#define    AT       (ADD + 1)
/** ID komendy CLONE */
#define    CLONE    (AT + 1)
/** ID komendy COMPOSE */
#define    COMPOSE  (CLONE + 1)
/** ID komendy DEG */
#define    DEG      (COMPOSE + 1)
/** ID komendy DEG_BY */
#define    DEG_BY   (DEG + 1)
/** ID komendy IS_COEFF */
#define    IS_COEFF (DEG_BY + 1)
/** ID komendy IS_EQ */
#define    IS_EQ    (IS_COEFF + 1)
/** ID komendy IS_ZERO */
#define    IS_ZERO  (IS_EQ + 1)
/** ID komendy MUL */
#define    MUL      (IS_ZERO + 1)
/** ID komendy NEG */
#define    NEG      (MUL + 1)
/** ID komendy POP */
#define    POP      (NEG + 1)
/** ID komendy PRINT */
#define    PRINT    (POP + 1)
/** ID komendy SUB */
#define    SUB      (PRINT + 1)
/** ID komendy ZERO */
#define    ZERO     (SUB + 1)
/** ID ERROR'A */
#define    ERROR    (ZERO + 1)

/**
 * Wczytuje i rozpoznaje komende z wejscia.
 * Wczytuje komende do pierwszego znaku spacji, lub nowej linii.
 * po wykonaniu funkcji na wejsciu jest albo znak spacji, lub nowej linii, albo nic nie ma (koniec pliku), albo pierwszy znak na ktorym wykryto niezgodnosc z każdą z podanych komend.
 * @return ID komendy, lub ID ERROR w przypadku nieprawidłowej komendy
 */
int ParseCommand(void);

#endif //POLY_COMMAND_PARSER_H
