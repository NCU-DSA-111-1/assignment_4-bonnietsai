#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "card.h"

struct HANDSTK* initialstk();
void swap(int *,int *,char *,char *);
void shuffle(struct CARD *);
void deal(struct HANDSTK *,struct HANDSTK *,struct HANDSTK *,struct HANDSTK *,struct CARD *);
void showcard(struct HANDSTK *,struct HANDSTK *,struct HANDSTK *,struct HANDSTK *);//show the card on player's hands
void drawcard(struct HANDSTK *,struct HANDSTK *);
void sorting_num(struct HANDSTK *);
struct CARDPILE *PUT_ON_PILE(struct CARD *,struct CARDPILE *,int );
struct CARDPILE *chosecard(struct HANDSTK *,struct CARDPILE *,int,int,struct CARDPILE *,struct HANDSTK*,struct HANDSTK **,int *);
int check(struct CARD *,struct HANDSTK *,int ,int);
void after_playcard(struct HANDSTK *,struct CARD [],int );//delete the card in hand
void delete_hand(struct HANDSTK * ,struct CARD );
void showfield(struct CARDPILE *);//show the card on the field
int game_finished(struct HANDSTK *,struct HANDSTK *,struct HANDSTK *);
int check_sequence(struct CARD *,int);
struct CARDPILE *insert_cardpile(int,/*struct CARD,*/struct CARDPILE *,struct HANDSTK *player);
struct CARDPILE *cut_cardpile(int,struct CARDPILE *);
int check_index(int ,struct CARDPILE *);
int check_insert(struct CARD ,struct CARDPILE *,int);
int check_field(struct CARDPILE *);
void show_one_card(struct HANDSTK *,int);//show only a player's hands
struct HANDSTK *clone_hand(struct HANDSTK* );
struct CARDPILE* getNewNode(struct CARD );
struct CARDPILE* cloneBinaryTree(struct CARDPILE *);
struct CARDPILE *move_to_other_cardpile(int,struct CARDPILE *);
struct CARDPILE *move_insert(int ,struct CARD ,struct CARDPILE *,int );
struct CARDPILE *move_delete(int ,struct CARD ,struct CARDPILE *,int );

int main(){
    int turns=1;//use for record whose turn
    int *pturns=&turns;
    int check_draw;//use for check whether player want to draw a card
    int draw_penalty=0;//if someone draw a card, it will become 1
    int winner;
    int mode;
    struct CARD deck[106];
    struct HANDSTK *player1=initialstk();player1->cardnum=0;
    struct HANDSTK *player2=initialstk();player2->cardnum=0;
    struct HANDSTK *player3=initialstk();player3->cardnum=0;
    struct HANDSTK *pile=initialstk();pile->cardnum=0;
    struct CARDPILE *clone;
    struct HANDSTK *clonehand;
    shuffle(deck);//shuffle pile
    deal(player1,player2,player3,pile,deck);//deal card to the players
    printf("\nGame Start!!\nAfter Sorting:\n");
    sorting_num(player1);
    sorting_num(player2);
    sorting_num(player3);
    showcard(player1,player2,player3,pile);
    struct CARDPILE *PILE = NULL;
    while(1){
        printf("\nNow is player\033[2;7;1m%d\033[2;7;0m's turn\n",(turns%3==0)?3:turns%3);
        printf("Do you want to draw a card? (1 for Yes, 0 for No): ");
        scanf("%d",&check_draw);
        printf("\n");
        while(check_draw){
            switch(turns%3){
                case 1: drawcard(player1,pile);sorting_num(player1);break;
                case 2: drawcard(player2,pile);sorting_num(player2);break;
                case 0: drawcard(player3,pile);sorting_num(player3);break;
                default: break;
            }
            showcard(player1,player2,player3,pile);
            showfield(PILE);
            draw_penalty=1;
            check_draw=0;     
        }
        if(draw_penalty){
            turns++;
            draw_penalty=0;
        }
        else{
            while(1){
                printf("\n               0:Construct a new cardpile in field\n");
                printf("               1:Connect or cut cardpile or movecard in current field\n");
                printf("               2:Return to last step(draw card)\n");
                printf("\nChoose Play-Card Mode in this turn: ");
                scanf("%d",&mode);
                clone=cloneBinaryTree(PILE);
                if(mode==1 || mode==0){
                    switch(turns%3){
                        case 1: clonehand=clone_hand(player1);PILE = chosecard(player1,PILE,turns%3,mode,clone,clonehand,&player1,pturns); break;
                        case 2: clonehand=clone_hand(player2);PILE = chosecard(player2,PILE,turns%3,mode,clone,clonehand,&player2,pturns); break;
                        case 0: clonehand=clone_hand(player3);PILE = chosecard(player3,PILE,turns%3,mode,clone,clonehand,&player3,pturns); break;
                        default: break;
                    }
                    showfield(PILE);
                    turns++;//next player
                    showcard(player1,player2,player3,pile);
                    break;
                }
                if(mode==2){
                    break;
                }
                printf("Wrong mode input!!\n");    
            }
        }
        // Game_finish condition
        //winner=game_finished(player1,player2,player3);
        /*
        if(!winner){
            printf("Winner is player%d!!",winner); 
            break;
        }
        */
        // Game_finish condition
    }
    return 0;
}

struct HANDSTK* initialstk(){
    struct HANDSTK *s=(struct HANDSTK *)malloc(sizeof(struct HANDSTK));
    s->top=NULL;
    //s->top->cardnum=0;
    return s;
}
//Following funciton is about card processing
void swap(int *a,int *b,char *aa,char *bb){
    int temp;
    char temp2;
    temp=*a;
    *a=*b;
    *b=temp;
    temp2=*aa;
    *aa=*bb;
    *bb=temp2;
}
void shuffle(struct CARD *deck){
    srand(time(NULL));
    //initialize the card
    for(int i=0;i<=12;i++){
        deck[i].num=i+1;
        deck[i].color='k';
    }
    for(int i=13;i<=25;i++){
        deck[i].num=i-12;
        deck[i].color='k';
    }
    for(int i=26;i<=38;i++){
        deck[i].num=i-25;
        deck[i].color='o';
    }
    for(int i=39;i<=51;i++){
        deck[i].num=i-38;
        deck[i].color='o';
    }
    for(int i=52;i<=64;i++){
        deck[i].num=i-51;
        deck[i].color='r';
    }
    for(int i=65;i<=77;i++){
        deck[i].num=i-64;
        deck[i].color='r';
    }
    for(int i=78;i<=90;i++){
        deck[i].num=i-77;
        deck[i].color='b';
    }
    for(int i=91;i<=103;i++){
        deck[i].num=i-90;
        deck[i].color='b';
    }
    deck[104].num=0;deck[104].color='J';
    deck[105].num=0;deck[105].color='J';
    //end initialize
    //shuffle
    for(int i=0;i<=105;i++){
        int a =rand()%106;
        swap(&deck[a].num,&deck[i].num,&deck[a].color,&deck[i].color);
    }
}
void deal(struct HANDSTK *p1,struct HANDSTK *p2,struct HANDSTK *p3,struct HANDSTK *pile,struct CARD *deck){
    for(int i=0;i<=13;i++){
        push(deck[i],p1);
    }
    for(int i=14;i<=27;i++){
        push(deck[i],p2);
    }
    for(int i=28;i<=41;i++){
        push(deck[i],p3);
    }
    for(int i=42;i<=105;i++){
        push(deck[i],pile);
    }

}
void showcard(struct HANDSTK *player1,struct HANDSTK *player2,struct HANDSTK *player3,struct HANDSTK *pile){
    struct HAND *temp1=player1->top;
    struct HAND *temp2=player2->top;
    struct HAND *temp3=player3->top;
    struct HAND *tempp=pile->top;
    printf("Player1 has \033[2;7;1m%d\033[2;7;0m cards which are: ",player1->cardnum);
    while(temp1!=NULL){
        switch(temp1->card.color){
            case 'b':printf("\033[34m%-6d\033[0m",temp1->card.num);break;
            case 'k':printf("%-6d",temp1->card.num);break;
            case 'o':printf("\033[33m%-6d\033[0m",temp1->card.num);break;
            case 'r':printf("\033[31m%-6d\033[0m",temp1->card.num);break;
            case 'J':printf("\033[35m%-6c\033[0m",temp1->card.color);break; 
            default:break;
        }
        temp1=temp1->prev;
    }
    printf("\nPlayer2 has \033[2;7;1m%d\033[2;7;0m cards which are: ",player2->cardnum);
    while(temp2!=NULL){
        switch(temp2->card.color){
            case 'b':printf("\033[34m%-6d\033[0m",temp2->card.num);break;
            case 'k':printf("%-6d",temp2->card.num);break;
            case 'o':printf("\033[33m%-6d\033[0m",temp2->card.num);break;
            case 'r':printf("\033[31m%-6d\033[0m",temp2->card.num);break;
            case 'J':printf("\033[35m%-6c\033[0m",temp2->card.color);break; 
            default:break;
        }
        temp2=temp2->prev;
    }
    printf("\nPlayer3 has \033[2;7;1m%d\033[2;7;0m cards which are: ",player3->cardnum);
    while(temp3!=NULL){
        switch(temp3->card.color){
            case 'b':printf("\033[34m%-6d\033[0m",temp3->card.num);break;
            case 'k':printf("%-6d",temp3->card.num);break;
            case 'o':printf("\033[33m%-6d\033[0m",temp3->card.num);break;
            case 'r':printf("\033[31m%-6d\033[0m",temp3->card.num);break;
            case 'J':printf("\033[35m%-6c\033[0m",temp3->card.color);break; 
            default:break;
        }
        temp3=temp3->prev;
    }
    /*
    printf("\nThere are \033[42m%d\033[m cards in piles which are: ",pile->cardnum);
    int counter=0;
    while(tempp!=NULL){
        if(counter%5==0){
            printf("\n");
        }
        switch(tempp->card.color){
            case 'b':printf("\033[34m%-6d\033[0m",tempp->card.num);break;
            case 'k':printf("%-6d",tempp->card.num);break;
            case 'o':printf("\033[33m%-6d\033[0m",tempp->card.num);break;
            case 'r':printf("\033[31m%-6d\033[0m",tempp->card.num);break;
            case 'J':printf("\033[35m%-6c\033[0m",tempp->card.color);break; 
            default:break;
        }
        tempp=tempp->prev;
        counter++;
    }
    */
    printf("\n");
}
void drawcard(struct HANDSTK *player,struct HANDSTK *pile){
    //struct CARD *temp=(struct CARD *)malloc(sizeof(struct CARD));
    struct CARD temp=pile->top->card;
    push(temp,player);
    pop(pile);
}
void sorting_num(struct HANDSTK *player){//bubble sort
    struct HAND *temp=player->top;
    for(int i=0;i<player->cardnum-1;i++){
        for(int j=0;j<player->cardnum-i-1;j++){
            if(temp->card.num > temp->prev->card.num){
                linkswap(temp,temp->prev);
            }else if(temp->card.num == temp->prev->card.num){//order: b->k->o->r
                int num1,num2;
                switch(temp->card.color){
                    case 'b': num1=1;break;
                    case 'k': num1=2;break;
                    case 'o': num1=3;break;
                    case 'r': num1=4;break;
                    default: break;
                }
                switch(temp->prev->card.color){
                    case 'b': num2=1;break;
                    case 'k': num2=2;break;
                    case 'o': num2=3;break;
                    case 'r': num2=4;break;
                    default: break;
                }
                if(num1>num2){
                    linkswap(temp,temp->prev);
                }
            }
            temp=temp->prev;
        }
        temp=player->top;
    }
}
struct CARDPILE *PUT_ON_PILE(struct CARD *input,struct CARDPILE *PILE ,int total_in)
{
    struct CARDPILE *NEW = (struct CARDPILE *)malloc(sizeof(struct CARDPILE));
    if(PILE==NULL)
    {
        PILE = NEW;
        NEW->index_next = NULL;
        NEW->index = 0;
        //return PILE;

    }else{
        struct CARDPILE *tmp = PILE;
        PILE = NEW;
        NEW->index_next = tmp;
        PILE->index = tmp->index + 1;
    }
    struct CARDPILE *tmp = PILE;
    for(/*int i=total_in-1 ; i>=0 ; i--*/int i=0;i<total_in;i++)
    {   
        struct CARDPILE *seq = (struct CARDPILE *)malloc(sizeof(struct CARDPILE));
        if(/*i==total_in-1*/i==0){
            //PILE->seq_next = seq;
            //seq->seq_next = NULL;
            PILE->info.num = input[i].num;
            PILE->info.color = input[i].color;
            PILE->seq_next=NULL;
        }
        else{
            //struct CARDPILE *tmp = PILE->seq_next;
            //PILE->seq_next = seq;
            //seq->seq_next = tmp;
            tmp->seq_next = seq;
            seq->seq_next = NULL;
            tmp=seq;
        }
        seq->info.num = input[i].num;
        seq->info.color = input[i].color;
    }
    return PILE;

}
struct CARDPILE *chosecard(struct HANDSTK *player, struct CARDPILE *PILE,int turns,int mode,struct CARDPILE *clone,struct HANDSTK* cloneh,struct HANDSTK **dPtrplayer,int *pturn)
{
    if(turns==0){
        turns=3;
        *pturn=turns;
    }
    while(1){
        if(mode==0){
            int total_in;
            printf("\nPlease input the number of card you will put in the pile: ");
	        scanf("%d", &total_in);
            struct CARD input[total_in];
            for(int i=0 ; i<total_in ; i++)
            {
                printf("Please input the card info (joker=0):  ");
                scanf("%d", &input[i].num);

                printf("Please input the card color (blue=b, white=k, yellow=o, red=r, joker=j):  ");
                scanf(" %c", &input[i].color);
            }

            if(check(input,player,total_in,mode))
            {
                printf("Player%d input \033[2;7;1m%d\033[2;7;0m cards which are: ",turns,total_in);
                for(int i=0 ; i<total_in ; i++)
                {
                    switch(input[i].color){
                        case 'b':printf("\033[34m%-6d\033[0m",input[i].num);break;
                        case 'k':printf("%-6d",input[i].num);break;
                        case 'o':printf("\033[33m%-6d\033[0m",input[i].num);break;
                        case 'r':printf("\033[31m%-6d\033[0m",input[i].num);break;
                        case 'J':printf("\033[35m%-6c\033[0m",input[i].color);break; 
                        default:break;
                    }
                    printf(" ");
                }
                printf("\n");
                PILE = PUT_ON_PILE(input, PILE, total_in);//need to revise
                
                after_playcard( player, input,total_in);
                
                break;
            }else {
                printf("\nInput wrong cards!\n\n");
            }
        }
        else if(mode==1){
            int index,cut_insert,keep_play;
            keep_play=1;
            while(keep_play==1){
                printf("\n*****************************************************************************************************\n");
                printf("Do you want to continue? (1 for yes,0 for no): ");scanf("%d",&keep_play);
                
                
                if(keep_play==0){
                    if(check_field(PILE)){
                        break;
                    }
                    else{
                        printf("The move is wrong!\n");
                        player=cloneh;
                        *dPtrplayer=cloneh;
                        
                        *pturn-=1;
                        show_one_card(player,turns%3);
                        
                        return clone;
                    }
                }
                printf("\nIn this mode, you can play ""only one"" cards in a time\n");
                do{
                    printf("Please choose an index of cardpile to cut or insert or move: ");scanf("%d",&index);
                }while(!check_index(index,PILE));
                printf("What do you want to do in this step? (Type 2 for move, 1 for insert, 0 for cut ): ");scanf("%d",&cut_insert);
                if(cut_insert==1){//just insert
                    PILE=insert_cardpile(index,PILE,player);
                    showfield(PILE);
                    show_one_card(player,turns%3);
                    break;
                }
                else if(cut_insert==0){//cut and insert
                    PILE=cut_cardpile(index,PILE);
                    showfield(PILE);
                    show_one_card(player,turns%3);
                    //set a FLAGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
                    break;
                }
                else if(cut_insert==2){//move
                    PILE=move_to_other_cardpile(index,PILE);
                    showfield(PILE);
                    show_one_card(player,turns%3);
                    break;
                }    
            }
            if(keep_play==0){
                break;
            }
        }
    }
    return PILE;
}
int check_sequence(struct CARD *input,int total_in)
{
    int control=0;
    char tmp_color = input[0].color;
    for(int i=0 ; i<total_in-1 ; i++)
    {
        int tmp1 = input[i].num;
        int tmp2 = input[i+1].num;
                    
        if( input[i+1].color=='J' || input[i+1].color == tmp_color) 
            control = 0;
        else 
            return 0;

        if( tmp1 == 0 )//double J for ex: J、J
            tmp1 = input[i-1].num + 1 ;

        if( tmp2 == 0 )
            tmp2 = tmp1+1;
                    
        if( tmp1 != tmp2-1 || tmp2>13 )
            control = 1;
                    
        if(control==1)
            return 0;
                    
    }
    if(control==0)
        return 1;
    else 
        return 0;
}
int check(struct CARD *input,struct HANDSTK *player,int total_in,int mode)// return 0 for failed, 1 for success
{
    int control=0;//check whether it exist the cards in the hand
    int same_num=0;//check for same_number_series ex: 7r,7k,7o
    int num;//record the "same number"
    int joker_num=0;//check the number of joker
    int counter_b=0,counter_k=0,counter_o=0,counter_r=0;//use to count num of color
    struct HAND *tmp;
    for(int i=0;i<total_in;i++){
        if(input[i].color=='J'){
            joker_num++;
        }
    }
    for(int i=0;i<total_in-1;i++){
        for(int j=i+1;j<total_in;j++){
            if(input[i].num==input[j].num && input[i].color!='J'){
                same_num=1;
                num=input[i].num;
                break;
            }
        }
    }

    if(mode==0){ //construct new cardpile in field
        if(total_in<3){ //new cardpile must >3 cards
            printf("< 3\n");
            return 0;
        }else if(joker_num==2 && total_in>=4){
            return 0;
        }else if(joker_num==2 && total_in==3){
            return 1;
        }else if(same_num==1){
            for(int i=0;i<total_in;i++){
                if(input[i].num!=num && input[i].color!='J'){//number is not same ex:3、3、4、4
                    return 0;
                }
                switch(input[i].color){
                    case 'b':counter_b++;break;
                    case 'k':counter_k++;break;
                    case 'o':counter_o++;break;
                    case 'r':counter_r++;break;
                    default:break; 
                }
            }
            if(counter_b>1 || counter_k>1 || counter_o>1 || counter_r>1){
                return 0;
            }
        }else{
            if(input[0].num==0 && input[1].num==1){// ->if(input[0]==j && input[1]==1) J、1、...
                return 0;
            }else if(input[0].num==0){   
                return check_sequence(&input[1],total_in-1); // J、...
            }else{
                return check_sequence(input,total_in);
            }    
        }
            
    }else if(mode==1){//connect or cut to cardpile in field
        /*not do anything*/
    }

    //check the cards in hand
    for(int i=0 ; i < total_in ; i++)
    {   
        tmp = player->top;
        while(tmp!=NULL)
        {   
            if( input[i].num == tmp->card.num && input[i].color == tmp->card.color ){//doesn't exist this card in hand
                control += 1;
                break;  
            }     
            tmp = tmp->prev;
        }
    }
    if(control==total_in){
        return 1;
    }
    return 0;
}
void after_playcard(struct HANDSTK * player, struct CARD *card,int total_num){
    struct HAND *temp=player->top;
    for(int i=0;i<total_num;i++){
        temp=player->top;
        while(temp!=NULL){
            if(temp->card.num==card[i].num && temp->card.color==card[i].color){
                delete_hand(player,card[i]);
                break;
            }
            temp=temp->prev;    
        }
        
    }
}
void delete_hand(struct HANDSTK * player,struct CARD card){
    struct HAND *temp=player->top;
    struct HAND *delete=player->top;
    while(temp!=NULL){
        if(temp->card.num==card.num && temp->card.color==card.color){
            delete=temp;
            break;    
        }
        temp=temp->prev;
    }
    if(delete->next==NULL){
        delete->prev->next=NULL;
        player->top=delete->prev;
    }
    else if(delete->prev==NULL){
        delete->next->prev=NULL;
    }
    else{
        delete->prev->next=delete->next;
        delete->next->prev=delete->prev;
    }
    free(delete);
    player->cardnum-=1;
}
void showfield(struct CARDPILE * cardpile){
    printf("\nThe cardpile in the field now is following:\n\n");
    struct CARDPILE *tmp =cardpile;
    struct CARDPILE *tmp_index = cardpile;
    int counter=0;
    while(tmp_index != NULL ){
        while (tmp!=NULL) {
            if(counter==0){
                printf("index%d:  ", tmp->index);    
            }
            switch(tmp->info.color){
                case 'b':printf("\033[34m%-6d\033[0m",tmp->info.num);break;
                case 'k':printf("%-6d",tmp->info.num);break;
                case 'o':printf("\033[33m%-6d\033[0m",tmp->info.num);break;
                case 'r':printf("\033[31m%-6d\033[0m",tmp->info.num);break;
                case 'J':printf("\033[35m%-6c\033[0m",tmp->info.color);break; 
                default:break;
            }     
            tmp = tmp->seq_next; 
            counter++;
        }
        printf("\n\n");
        counter=0;
        tmp_index=tmp_index->index_next;
        tmp=tmp_index;
    }
}
int game_finished(struct HANDSTK *player1,struct HANDSTK *player2,struct HANDSTK *player3){
    if(player1->cardnum==0){
        return 1;
    }
    else if(player2->cardnum==0){
        return 2;
    }
    else if(player3->cardnum==0){
        return 3;
    }
    else return 0;// Game Continue
}
struct CARDPILE *insert_cardpile(int index,/*struct CARD card,*/struct CARDPILE *PILE,struct HANDSTK *player){
    int begin_end,flag;
    struct CARD OneCard;
    struct CARDPILE *temp=PILE;//the link be inserted
    struct CARDPILE *temp2=PILE;//index before temp
    struct CARDPILE *insert=(struct CARDPILE *)malloc(sizeof(struct CARDPILE));
    do{
        printf("Please input the card info (joker=0):  ");
        scanf("%d", &OneCard.num);
        printf("Please input the card color (blue=b, white=k, yellow=o, red=r, joker=j):  ");
        scanf(" %c", &OneCard.color);
        flag=check(&OneCard,player,1,1);
        if(!flag){
            printf("You don't have this card!\n");
        }
    }
    while(!flag);
    insert->info.num=OneCard.num;
    insert->info.color=OneCard.color;
    insert->index=index;
    printf("Where do you want to insert? (0 for begin, 1 for end): ");scanf("%d",&begin_end);
    while(temp!=NULL){
        if(temp->index==index){
            break;
        }
        temp=temp->index_next;
    }
    if(temp!=temp2){
        while(temp2->index_next!=temp){
            temp2=temp2->index_next;
        }
    }
    if(check_insert(OneCard,temp,begin_end)){
        if(begin_end==0){//begin
            if(temp2->index==temp->index){
                PILE=insert;
                insert->index_next=temp->index_next;
                insert->seq_next=temp;
                temp->index_next=NULL;
            }else{
                temp2->index_next=insert;
                insert->seq_next=temp;
                insert->index_next=temp->index_next;
                temp->index_next=NULL;
                //PILE=temp2; 
            }
        }else if(begin_end==1){
            while(temp->seq_next!=NULL){
                temp=temp->seq_next;
            }
            temp->seq_next=insert;
            insert->seq_next=NULL;
        }
    }
    
    after_playcard(player,&OneCard,1);

    return PILE;
}
int check_index(int index,struct CARDPILE *PILE){
    struct CARDPILE *temp=PILE;
    while(temp!=NULL){
        if(temp->index==index){
            return 1;
        }
        temp=temp->index_next;
    }
    return 0;
}
int check_insert(struct CARD card,struct CARDPILE *link,int begin_end){
    int same_num;
    int same_color;
    struct CARDPILE *temp1=link;int num1;
    struct CARDPILE *temp2=link;int num2;
    struct CARDPILE *temp3=link;
    if(temp1->seq_next==NULL && temp1->info.num==0){//only a J
        return 1;
    }else{
        while(temp1!=NULL){
            if(temp1->info.num!=0){
                num1=temp1->info.num;
                break;
            }
            temp1=temp1->seq_next;
        }
        temp2=temp1->seq_next;
        while(temp2!=NULL){
            if(temp2->info.num!=0 ){
                num2=temp2->info.num;
                break;
            }
            temp2=temp2->seq_next;
        }    
    }
    if(temp2==NULL && temp1!=NULL){ //special situaiton: 2 Joker or move or cut
        int type;
        printf("Which type do you want to insert? (1 for Same_num, 0 for Same_color): ");scanf("%d",&type);
        if(type==1){
            same_num=1;
            same_color=0;
        }else if(type==0){
            same_color=1;
            same_num=0;
        }
    }
    else{
        if(num1==num2){
            same_num=1;
            same_color=0;
        }else{
            same_color=1;
            same_num=0;
        }
    }
    if(same_num){
        int counter_b=0,counter_k=0,counter_o=0,counter_r=0,counter_j=0;
        while(temp3!=NULL){
            switch(temp3->info.color){
                case 'b':counter_b++;break;
                case 'k':counter_k++;break;
                case 'o':counter_o++;break;
                case 'r':counter_r++;break;
                case 'J':counter_j++;break;
                default:break; 
            }
            temp3=temp3->seq_next;
        }
        if(counter_b+counter_k+counter_o+counter_r+counter_j>=4){
            return 0;
        }
        switch(card.color){
            case 'b':counter_b++;break;
            case 'k':counter_k++;break;
            case 'o':counter_o++;break;
            case 'r':counter_r++;break;
            default:break; 
        }
        if(counter_b>1 || counter_k>1 || counter_o>1 || counter_r>1){
            return 0;
        }
        return 1;
    }else if(same_color){
        if(card.color!=temp1->info.color && card.color!='J'){
            printf("error1\n");
            return 0;
        }
        if(begin_end==1){
            while(temp3!=NULL){
                if(temp3->seq_next==NULL){//X (temp3) (card)
                    if(card.num-temp3->info.num!=1){
                        printf("error4\n");return 0;
                    }
                    return 1;
                }else if(temp3->seq_next->info.color=='J' && temp3->seq_next->seq_next==NULL){//X (temp3) J (card)
                    if(card.color=='J' && temp3->info.num<12){
                        return 1;
                    }
                    else if(card.num-temp3->info.num==2){
                        return 1;
                    }
                    printf("error3\n");return 0;
                }else if(temp3->seq_next->info.color=='J' && temp3->seq_next->seq_next->info.color=='J'
                    && temp3->seq_next->seq_next->seq_next==NULL ){//X (temp3) J　J (card)
                    if(card.num-temp3->info.num!=3){
                        printf("error2\n");return 0;
                    }
                    return 1;
                }
                temp3=temp3->seq_next;
            }
        }else if(begin_end==0){
            if(temp3->info.color=='J' && temp3->seq_next->info.color=='J' ){// (card) [J(temp3)]　J  X
                if(temp3->seq_next->seq_next->info.num-card.num!=3){
                    printf("ERROR2\n");return 0;
                }
                return 1;
            }
            else if(temp3->info.color=='J' && temp3->seq_next->info.color!='J'){// (card) [J(temp3)] X
                if(card.color=='J' && temp3->seq_next->info.num>2){
                    return 1;
                }
                else if(temp3->seq_next->info.num-card.num==2){
                    return 1;
                }
                printf("ERROR3\n");return 0;
            }
            else if(card.color=='J'){//[J(card)] temp3 X
                if(temp3->info.num<2){
                    printf("ERROR233\n");return 0;
                }
                return 1;
            }
            else if(temp3->info.num-card.num!=1){//(card) temp3 X
                printf("ERROR77\n");return 0;
            }
            return 1;
        }
    }  
}
struct CARDPILE *cut_cardpile(int index,struct CARDPILE *PILE){
    struct CARD choose_card;
    printf("Please choose the card, after that card as a new sequence: \n");
    printf("Please input the info of the card which you want to cut (joker=0):  ");
    scanf("%d", &choose_card.num);
    printf("Please input the card color (blue=b, white=k, yellow=o, red=r, joker=j):  ");
    scanf(" %c", &choose_card.color);

    struct CARDPILE *tmp = PILE;
    while(tmp->index!=index)//!=input_index
    {
        tmp = tmp->index_next;
    }
    while (tmp->info.num!=choose_card.num || tmp->info.color!=choose_card.color) {
        tmp = tmp->seq_next;
    }

    struct CARDPILE *ground = tmp;
    tmp = tmp->seq_next;
    ground->seq_next = NULL;
    struct CARDPILE *tmp1 = PILE;
    PILE = tmp;
    tmp->index_next = tmp1;
    PILE->index = tmp1->index + 1;//?
    return PILE;
}
void show_one_card(struct HANDSTK *player,int turns){
    if(turns==0){
        turns=3;
    }
    struct HAND *temp=player->top;
    printf("Player%d has \033[2;7;1m%d\033[2;7;0m cards which are: ",turns,player->cardnum);
    while(temp!=NULL){
        switch(temp->card.color){
            case 'b':printf("\033[34m%-6d\033[0m",temp->card.num);break;
            case 'k':printf("%-6d",temp->card.num);break;
            case 'o':printf("\033[33m%-6d\033[0m",temp->card.num);break;
            case 'r':printf("\033[31m%-6d\033[0m",temp->card.num);break;
            case 'J':printf("\033[35m%-6c\033[0m",temp->card.color);break; 
            default:break;
        }
        temp=temp->prev;
    }
    printf("\n");
}
int check_field(struct CARDPILE *PILE){
    
    struct CARDPILE *TMP_PILE = PILE;
    int control = 0;

    while(TMP_PILE!=NULL)
    {   
        struct CARDPILE *TMP_SEQ = TMP_PILE;
        int total_in = 0;
        while(TMP_SEQ != NULL)
        {
            TMP_SEQ = TMP_SEQ->seq_next;
            total_in++;
        }

        if(total_in<3)
            control = 1;

        if(control==1)
            return 0;

        TMP_PILE = TMP_PILE->index_next;

    }

    if(control==0)
        return 1;

}//test
struct HANDSTK *clone_hand(struct HANDSTK *player){
    struct HAND* temp=player->top;
    struct HANDSTK* node=initialstk();node->cardnum=0;


    while(temp->prev!=NULL){
        temp=temp->prev;
    }
    while(temp!=NULL){
        push(temp->card,node);
        temp=temp->next;
    }
    return node;

}
struct CARDPILE* getNewNode(struct CARD card){
    struct CARDPILE* newNode = (struct CARDPILE*)malloc(sizeof(struct CARDPILE));
    newNode->info.color = card.color;
    newNode->info.num = card.num;
    newNode->index_next = NULL;
    newNode->seq_next = NULL;

    return newNode;
}
struct CARDPILE* cloneBinaryTree(struct CARDPILE *pile){
    if(pile == NULL){
        return NULL;
    }
    struct CARDPILE* newNode = getNewNode(pile->info);

    newNode->index_next = cloneBinaryTree(pile->index_next);
    newNode->seq_next = cloneBinaryTree(pile->seq_next);

    return newNode;
}
struct CARDPILE *move_to_other_cardpile(int index,struct CARDPILE *PILE){
    
    int destination;//index
    struct CARD OneCard;
    struct CARDPILE* tmp=PILE;//the card need to move
    struct CARDPILE* tmp2=PILE;//use to find end
    struct CARDPILE* end;
    struct CARDPILE* linkhead;//first of origin link 
    struct CARDPILE* desthead=PILE;//first of destination link
    //struct CARDPILE* tmp3=PILE;//use to find before_index
    //struct CARDPILE* before_index;
    //struct CARDPILE* tmp4=PILE;//use to find before_seq
    //struct CARDPILE* before_seq;
    int begin_end,counter;
    counter=0;
    int create;
    printf("Do you want to create a index?(1 for yes, 0 for no): ");scanf("%d",&create);
    if(create==0){
        printf("Which index is your destination: ");scanf("%d",&destination);
        if(check_index(destination,PILE)){
            while(tmp->index!=index)//!=input_index
            {
                //tmp3=tmp;
                tmp = tmp->index_next;
            }
            //before_index=tmp3;
            tmp2=tmp;
            linkhead=tmp;
            while(desthead->index!=destination){
                desthead=desthead->index_next;
            }
            //tmp4=tmp;
            printf("Please input the card info which you want to move(joker=0):  ");
            scanf("%d", &OneCard.num);
            printf("Please input the card color which you want to move(blue=b, white=k, yellow=o, red=r, joker=j):  ");
            scanf(" %c", &OneCard.color);
            while(tmp2!=NULL){
                if(tmp2->seq_next==NULL){
                    end=tmp2;
                    //before_seq=tmp4;
                    break;
                }
                //tmp4=tmp2;
                tmp2=tmp2->seq_next;
            }
            while(tmp!=NULL){
                if(tmp->info.num==OneCard.num && tmp->info.color==OneCard.color){
                    break;
                }
                tmp = tmp->seq_next;
                counter++;
            }
            if(tmp==NULL){
                printf("The field doesn't have this card!\n");
                return PILE;
            }
            else{//temp!=NULL
                int first_last;
                    printf("In destination, Where do you want to insert?(0 for begin, 1 for end): ");scanf("%d",&first_last);
                if(counter==0){
                    begin_end=0;
                }else if(OneCard.num!=end->info.num || OneCard.color!=end->info.color){
                    printf("Please cut the cardpile first, not to move the center card!\n");
                    return PILE;
                }else{
                    begin_end=1;
                }
                if(check_insert(OneCard,desthead,first_last)){//first_last->destinaiton, begin_end->from
                    PILE=move_delete(index,OneCard,PILE,begin_end);
                    PILE=move_insert(destination,OneCard,PILE,first_last); 
                }else{
                    printf("Insert ERROR!!\n");
                    return PILE;
                }
            }    
        }else{
            printf("Wrong Index\n");
            return PILE;
        }
    }
    else if(create==1){//create one card new pile
        struct CARDPILE *new=(struct CARDPILE *)malloc(sizeof(struct CARDPILE));
        struct CARDPILE *tmp3=PILE;
        new->index=PILE->index+1;
        while(tmp->index!=index)//!=input_index
        {
            tmp = tmp->index_next;
        }
        tmp2=tmp;
        printf("Please input the card info which you want to move(joker=0):  ");
        scanf("%d", &OneCard.num);
        printf("Please input the card color which you want to move(blue=b, white=k, yellow=o, red=r, joker=j):  ");
        scanf(" %c", &OneCard.color);
        while(tmp2!=NULL){
            if(tmp2->seq_next==NULL){
                end=tmp2;
                
                break;
            }
               
            tmp2=tmp2->seq_next;
        }
       
        while(tmp!=NULL){
            if(tmp->info.num==OneCard.num && tmp->info.color==OneCard.color){
                break;
            }
            tmp = tmp->seq_next;
            counter++;
        }

        if(tmp==NULL){
            printf("The field doesn't have this card!\n");
            return PILE;
        }
        else{//temp!=NULL
               
            if(counter==0){
                begin_end=0;
            }else if(OneCard.num!=end->info.num || OneCard.color!=end->info.color){
                printf("Please cut the cardpile first, not to move the center card!\n");
                return PILE;
            }else{
                begin_end=1;
            }
            new->info.num=OneCard.num;
            new->info.color=OneCard.color;
            PILE=move_delete(index,OneCard,PILE,begin_end);
            new->seq_next=NULL;
            tmp3=PILE;
            PILE=new;
            new->index_next=tmp3;

        } 
        
    }

    return PILE;

}
struct CARDPILE *move_insert(int destination,struct CARD OneCard,struct CARDPILE *PILE,int begin_end){
    struct CARDPILE *temp=PILE;//the link be inserted
    struct CARDPILE *temp2=PILE;//index before temp
    struct CARDPILE *insert=(struct CARDPILE *)malloc(sizeof(struct CARDPILE));
    
    insert->info.num=OneCard.num;
    insert->info.color=OneCard.color;
    insert->index=destination;

    while(temp!=NULL){
        if(temp->index==destination){
            break;
        }
        temp=temp->index_next;
    }
    if(temp!=temp2){
        while(temp2->index_next!=temp){
            temp2=temp2->index_next;
        }
    }
    
    if(begin_end==0){//begin
        if(temp2->index==temp->index){
            PILE=insert;
            insert->index_next=temp->index_next;
            insert->seq_next=temp;
            temp->index_next=NULL;
        }else{
            temp2->index_next=insert;
            insert->seq_next=temp;
            insert->index_next=temp->index_next;
            temp->index_next=NULL;
                //PILE=temp2; 
        }
    }else if(begin_end==1){///////////////////////////////////////////
        while(temp->seq_next!=NULL){
            temp=temp->seq_next;
        }
        temp->seq_next=insert;
        insert->seq_next=NULL;
    }
    return PILE;
}
struct CARDPILE *move_delete(int index,struct CARD OneCard,struct CARDPILE *PILE,int begin_end){
    struct CARDPILE *tmp=PILE;
    struct CARDPILE *before_index=PILE;
    struct CARDPILE *before_seq;
    struct CARDPILE *after_seq;
    
    while(tmp->index!=index){
        before_index=tmp;
        tmp=tmp->index_next;
    }
    
    
    if(begin_end==1){
        while(tmp->info.num!=OneCard.num || tmp->info.color!=OneCard.color){
            before_seq=tmp;
            tmp=tmp->seq_next;
        }
        before_seq->seq_next=NULL;
        free(tmp);
    }else if(begin_end==0){
        if(tmp->seq_next!=NULL){
            after_seq=tmp->seq_next;
            after_seq->index=index;
            if(tmp==PILE){
                PILE=after_seq;
            }
            else{
                before_index->index_next=after_seq;
            }
      
            after_seq->index_next=tmp->index_next;
        }
        else if(tmp->seq_next==NULL){
            if(before_index==PILE){
                PILE=tmp->index_next;
            }else{
                before_index->index_next=tmp->index_next;
            }   
        }
        
        free(tmp);
    }
    return PILE;
    
    
}
