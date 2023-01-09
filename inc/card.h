#ifndef CARD_H
#define CARD_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct CARD{
    int num;
    char color;
};

struct CARDPILE{

    struct CARD info ;
    int index;

    struct CARDPILE *index_next;
    struct CARDPILE *seq_next;

};

struct HAND{
    struct CARD card;
    struct HAND *next;
    struct HAND *prev;
};
struct HANDSTK{//point to the top
    struct HAND *top;
    int cardnum;//number of card
};

struct PLAYER{
    bool ice;
    bool win;
};//not used now

int empty(struct HANDSTK *);
void push(struct CARD ,struct HANDSTK *);
void pop(struct HANDSTK *);
void linkswap(struct HAND *,struct HAND *);



#endif