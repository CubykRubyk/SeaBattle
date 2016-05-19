#ifndef COMUN_H
#define COMUN_H

#define CELULA 25 //marimea unei celule
#define PUNCT CELULA / 8 //marimea punctului
#define CIMP_OFFSET 20 //distanta cimpului  de la marginea

//numarul corabiilor
#define CORABIE1_AMOUNT 4
#define CORABIE2_AMOUNT 3
#define CORABIE3_AMOUNT 2
#define CORABIE4_AMOUNT 1

//marimea corabiilot
#define CORABIE1 1
#define CORABIE2 2
#define CORABIE3 3
#define CORABIE4 4

//port default
#define PORT_DEFAULT

#define PORT 17000

enum direction{ORIZONTAL, VERTICAL}; // directia corabiilor
enum CELL_STATUS{EMPTY, DOT, DAMAGED, KILLED}; // situatia celulei
enum POCKET_TYPE{READY_TO_GAME, SETUP_TURN, TURN, TURN_RESPONSE}; // tipul pachetelor trimise
enum GAME_STATUS{NONE, READY, YOUR_TURN, ENEMY_TURN}; // statutul jocului
enum PLAYERS{ME, ENEMY}; // jucatori

#endif // COMUN_H

