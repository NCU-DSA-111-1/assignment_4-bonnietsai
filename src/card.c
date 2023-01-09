#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

int empty(struct HANDSTK *ptr){   
    if(ptr->top==NULL)
        return 1;
    return 0;
}
void pop(struct HANDSTK *ptr){
    struct HAND *temp=ptr->top;
    if(temp->prev!=NULL){
        ptr->top=temp->prev;
        ptr->top->next=NULL;
        free(temp);
        ptr->cardnum-=1;   
    }
    else{//temp->prev==NULL
        ptr->top=NULL;
        free(temp);
        //ptr->top->cardnum-=1;
        ptr->cardnum-=1; 
    }
    return;
}
void push(struct CARD data,struct HANDSTK *ptr){
    struct HAND *temp=(struct HAND *)malloc(sizeof(struct HAND));
    temp->card=data;
    temp->next=NULL;
    temp->prev=NULL;
    if(ptr->top){
        ptr->top->next=temp;
        temp->prev=ptr->top;
    }
    ptr->top=temp;
    ptr->cardnum+=1; 
    return;
}
void linkswap(struct HAND *ptr1,struct HAND *ptr2){
    struct HAND *temp=(struct HAND *)malloc(sizeof(struct HAND));
    temp->card=ptr1->card;
    ptr1->card=ptr2->card;
    ptr2->card=temp->card;
}










