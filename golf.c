// ECE 209 - Fall 2021 - Program 3
// This program reads information about a golf tournament
// and allows a user to view information about the course,
// the overall scores, and the individual players.
//
// Implementation of Course ADT and functions for Player and PlayerNode types
//
// Mohamed Ali

#include "golf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// This struct contains info about par score, name of course, pointer to head node,
// and score info.
struct golfCourse{
    int par[18];
    char name2[41];
    PlayerNode * coursepp;
    int scoreinfo[18*3];
};

//Function declaration for "Recursive" function, used to sort top n players and returns
// head of sorted list.
PlayerNode* Recursive(PlayerNode* h);

//This function reads a file with golf information to create and initialize course/score information.
Course readCourse(const char * filename){
    Course rcourse;
    Course iscore;  // declare and initialize variables
    char score[36];
    int k;

    char taketurn[150];
    char checkturn[150]; // strings used for reading
    char checkp[150];

    int cc2;
    char usec[150];
    char delim[2]=":";
    char off[2] = "\0";
    char * ps = NULL;
    int cntr = 1;
    char * cmp;
    char * cmp2; // pointers used for reading

    rcourse = malloc(sizeof(struct golfCourse)); // allocate space in memory
    iscore = malloc(sizeof(struct golfCourse));

    FILE* fname;
    char len2[41];

    fname = fopen(filename, "r"); // open file for reading
    if (fname == NULL){ // check for null
        return NULL;
    }

    fgets(len2, 41, fname);
    int len = strlen(len2);
    len2[len-1] = '\0'; // get rid of line fead

    strcpy(rcourse->name2, len2); // put name into struct field

    int count = 0;

    fgets(score, 36, fname); // read from file

    for(int i = 0; i<36; i++){
        if((score[i]>48) && (score[i]<57)){
            rcourse->par[count]=atoi(&score[i]); // initialize par info
            count++;
        }
    }


    while(cntr>0){
        while(fscanf(fname, "%500s", taketurn)!=EOF){ // read file into string
            int fplayer;

            fplayer = numPlayers(iscore); // check number of players


            if((fplayer) || (cntr)){ // if numplayer not null
                cmp = strtok(taketurn, delim); // return pointer to colon location
                strcpy(checkp, cmp); // copy string at pointer location into temp string
                cc2 = strcmp(usec, checkp); // compare temp string

                if(cc2!=0){ // if string not same
                    strcpy(usec, checkp);
                }
            }

            cc2 = atoi(strtok(ps, delim)); // convert hole info to integer
            cmp2 = strtok(ps, off); // return pointer location of null
            strcpy(checkturn, cmp2); // copy temp string

            if(cmp2 == NULL){
                findPlayer(usec, iscore); // check if player exists
            }

            if((cc2==1) || (cmp == cmp2)){

                newPlayer(checkp, rcourse); // call newplayer
                for(k=0; k<(18*3); k++){
                    iscore->scoreinfo[k]=0; // initialize score info for newplayer
                    cmp = --cmp2 + strcmp(usec, taketurn); // copy pointer location
                }

            }

            PlayerNode * nplayer = rcourse->coursepp; // initialize to head
            Player * charplayer = malloc(sizeof(struct golfPlayer)); // allocate space

            int ccnnr = 1;

            while((nplayer) && (ccnnr>0)){ // while head not null and counter>0
                int cchh = strcmp(nplayer->player->name, checkp); // compare player and string

                if(!cchh){ // if null

                    charplayer = nplayer->player;
                    scoreHole(charplayer, cc2, checkturn); // call to check score

                    strcpy(usec, taketurn); // copy temp string
                    --ccnnr; // decrement
                    cmp = NULL;
                    cmp2 = NULL; // set pointers to null

                    break;
                }

                else{
                    nplayer=nplayer->next; // traverse
                    ccnnr = 1; // re-initialize counter
                    cmp = NULL;
                    cmp2 = NULL;
                    continue; // go back to loop
                }
            }
        }

        --cntr; // decrement
        cmp = NULL;
        cmp2 = NULL; // set pointers to null
        break;

            }

    fclose(fname); // close file

    return rcourse;
}

// This function creates and returns a new player. Initializes score info as well
// as course info and arrays.
Player * newPlayer(const char *name, Course course){
    int i;
    int k;
    int cntr = 1;

    Course score = course;
    score = malloc(sizeof(struct golfCourse)); // allocate space

    Player * pushh=(struct golfPlayer*)malloc(sizeof(struct golfPlayer)*18); // allocate space
    strcpy(pushh->name,name); // cpy name to struct field
    char * tmpcpy = pushh->name; // pointer to name

    pushh->course = course; // initialize course info

    while(cntr!=0){
        for(i=0; i<18; i++){ // initialize score info
            pushh->strokes[i]=0;
            pushh->parScore[i]=0;
            pushh->strokeScore[i]=0;
            for(k=0; k<(18*3); k++){
                score->scoreinfo[k]+=atoi(&tmpcpy[k]); // initialize score info for newplayer
            }
        }

    cntr--; // decrement counter
    break;

    }

    addPlayer(pushh, course); // call addplayer to add to course

    return pushh;
    
}

// Function reads course and score info from file as well as pointer to a string containing
//name of the course
const char * courseName(Course c){
    Course checkcourse = malloc(sizeof(struct golfCourse)); // allocate space
    checkcourse = c;
    return checkcourse->name2; // return info from struct field
}

// Function returns a pointer to an array of integers that holds the par scores for each hole of the course
// The par for hole x will be in array element x-1
const int * courseHoles(Course c){
    Course checkcourse = malloc(sizeof(struct golfCourse)); //allocate space
    checkcourse = c;
    return checkcourse->par;
}

// Function returns the head of a list of players
const PlayerNode * coursePlayers(Course c){
    PlayerNode * firstnode;
    firstnode = malloc(sizeof(struct golfPlayerNode)); // allocate space

    Course checkcourse = malloc(sizeof(struct golfCourse)); // allocate space
    checkcourse = c;

    firstnode=checkcourse->coursepp; // head
    return firstnode; // return head
}

// Function returns the head of a list of top-n players plus ties
PlayerNode * courseLeaders(Course c, int n){
    PlayerNode * fnode = malloc(sizeof(struct golfPlayerNode)); // allocate space
    fnode=c->coursepp; // initialize as head

    PlayerNode * tnode = malloc(sizeof(struct golfPlayerNode));
    tnode = 0; // initialize as null

    PlayerNode * lnode = malloc(sizeof(struct golfPlayerNode));
    lnode = 0; //initialize as null

    PlayerNode * addhead;
    addhead = malloc(sizeof(struct golfPlayerNode));

    while(fnode){ // while first node not null
        if(!tnode){
            tnode = malloc(sizeof(struct golfPlayerNode));
            tnode->player = fnode->player; // if tnode null, make it first node in list
            tnode->next = 0;
            lnode = tnode;
        }
        else{ // if not null
            lnode->next = malloc(sizeof(struct golfPlayerNode));
            lnode = lnode->next; // traverse
            lnode->player = fnode->player; // last node is first node
            lnode->next = 0;
        }

        if(!tnode){ // make sure if it is null, do same
            tnode = malloc(sizeof(struct golfPlayerNode));
            tnode->player = fnode->player;
            tnode->next = 0;
            lnode = tnode;
        }

        fnode=fnode->next; //traverse
    }

    addhead->next = tnode; // next pointer of head is current node
    addhead = Recursive(addhead); // call recursive to sort list


    PlayerNode * first = addhead; // current pointer
    PlayerNode * prev = addhead; // trailing pointer

    PlayerNode p; // additional trailing pointer
    p.next = addhead->next; // initialize as head

    int counter = 0;
    int temp2 = n; // initialize as top n players
    int pass = 0;

    while((first) && (counter<=temp2) && (counter+1 < numPlayers(c))){
        temp2 = n;

        if((counter<temp2) && (counter<numPlayers(c))){ // if less than n players plus ties
            counter++; // increment
            first = first->next; // traverse
        }

        if((counter>temp2) && (prev)){ // if greater than n plus ties and prev not null
            prev = &p;
            first= prev->next; // start from beginning of list
            break;
        }

        if(((counter+1) < numPlayers(c))){ // if counter less than total players
            if((totalStrokeScore(first->player) == totalStrokeScore(first->next->player))){ // if theres a tie
                temp2++; // account for tie

                if(pass == 0){
                    pass++; // account for discrepancy between top players and ties
                }

                if((counter<temp2)){ // if less than n plus ties
                    counter++; // increment
                    first = first->next; // traverse

                }
            }
        }

        if((counter>temp2) && (prev)){
            prev = &p;
            first= prev->next;
            break;
        }

        if(((counter+1) < numPlayers(c))){
            if((totalStrokeScore(first->player) == totalStrokeScore(first->next->player))){
                temp2++;

                if(pass == 0){
                    pass++;
                }

                if((counter<temp2)){
                    counter++;
                    first = first->next;
                }
            }
        }

        if((counter>temp2) && (prev)){
            prev = &p;
            first= prev->next;
            break;
        }

        if(((counter+1) < numPlayers(c))){
            if((totalStrokeScore(first->player) == totalStrokeScore(first->next->player))){

                temp2++;

                if(pass == 0){
                    pass++;
                }

                if((counter<temp2)){
                    counter++;
                    first = first->next;
                }
            }
        }

        if((counter == temp2)){ // if equal return head
            first->next = 0;
            return addhead->next;
        }

        if((counter>temp2) && (prev)){
            prev = &p;
            first= prev->next;
            break;
        }

        if(((counter+1) < numPlayers(c))){
            if((totalStrokeScore(first->player) == totalStrokeScore(first->next->player))){
                temp2++;

                if(pass == 0){
                    pass++;
                }

                if((counter<temp2)){
                    counter++;
                    first = first->next;
                }
            }
        }

        if((counter == temp2)){
            first->next = 0;
            return addhead->next;
        }

        if((counter>temp2) && (prev)){
            prev = &p;
            first= prev->next;
            break;
        }

        if(((counter+1) < numPlayers(c))){
            if((totalStrokeScore(first->player) == totalStrokeScore(first->next->player))){
                temp2++;

                if(pass == 0){
                    pass++;
                }

                if((counter<temp2)){
                    counter++;
                    first = first->next;
                }
            }
        }

        if((counter == temp2)){
            first->next = 0;
            return addhead->next;
        }

       if((counter>temp2) && (prev)){
           prev = &p;
           first= prev->next;
           break;
       }

        if(first->next == NULL){ // if null return head
            return addhead->next;
        }

        if((counter == temp2)){
            first->next = 0;
            return addhead->next;
        }

        if(counter == n){
            first->next = 0;
            return addhead->next;
        }

        if((counter>temp2) && (prev)){
            prev = &p;
            first= prev->next;
            break;
        }

        if((temp2==(n*2))){
            counter++;
        }

        //if there is a tie and first and temp2 not 0
        if((temp2) && (first) && (totalStrokeScore(first->player) == totalStrokeScore(first->next->player))){
            counter++; //increment
        }

        if(counter<n){
            continue; // if counter still less than top n, go back to loop
        }

        if((pass!=0) && (temp2!=n) && (first)){ // if pass has not been incremented and there are ties
            counter++; // increment
        }

        continue;
    }

    if(counter!=temp2){
        return prev->next; // return previous head if counter not equal to temp2
    }

first->next = 0;
return addhead->next; // return head
}

// Function returns the number of players in tournament
int numPlayers(Course c){
    int numplayer = 0;
    PlayerNode* head = malloc(sizeof(struct golfPlayerNode));

    head->next = c->coursepp; // initialize head
    head->player=0; // initialize player to null

    while(c){ // while course not null
        if(head->next !=NULL){
            numplayer = numplayer+1; // increment player
            head=head->next; // traverse

            if (head->next !=NULL){
                while(head !=NULL){
                    head=head->next;
                    numplayer=numplayer+1;
                }
            }
        }

        if(numplayer>0){
            numplayer=numplayer-1; // decrement to account for offset
        }

        if(numplayer<0){ // if numplayer negative, something wrong, go back
            continue;
        }

        break;
    }

    return (numplayer);
}

// Function finds and returns a player based on name
Player * findPlayer(const char * name, Course c){
    char cpyname[10]; // temp string
    int i;
    int k;

    for(i=0; i<10; i++){
        cpyname[i] = name[i]; // copy into temp string
    }

    Player * fPlayer=0;
    PlayerNode * cnode=c->coursepp; // initialize as head

    Course iscore;
    iscore = malloc(sizeof(struct golfCourse));

    if(c){
        while(c){ // if course not null
            if((numPlayers(c)>0) || (numPlayers(c)==0)){ // if numplayer not negative
                if((strcmp(cnode->player->name, cpyname))==0){ // is name is same
                    fPlayer = c->coursepp->player;
                }
                while(cnode!=NULL){
                    for(k=0; k<(18*3); k++){ // initialize score info for new player
                        iscore->scoreinfo[k] = 0;
                        continue;
                    }
                    if(strcmp(cnode->player->name, cpyname)==0){
                        fPlayer = cnode->player;
                        break;
                    }
                    else{
                        cnode = cnode->next; // traverse
                    }
                }
            }

            if(!fPlayer){
                fPlayer = NULL; // check for null
            }
            k++; // increment
            break;
        }
        k++; // increment
    }

    return fPlayer;
}

// Function adds a new player to a list of players
void addPlayer(Player *p, Course c){
    int scorecheck;
    PlayerNode temp;
    temp.next = c->coursepp; // initialize as head
    int list = 1;

    PlayerNode * addhead =malloc(sizeof(struct golfPlayerNode));
    PlayerNode * cnode =malloc(sizeof(struct golfPlayerNode));

    addhead->next = NULL;
    addhead->player = p; //  initialize as head

    while(list>0){
        if(c->coursepp==NULL){
            c->coursepp = addhead; // if its null set equal to head
        }

        else{
            cnode = c->coursepp;
            PlayerNode* prev = &temp; // prev equal to memory location of temp

            while((cnode!=NULL)){
                scorecheck = strcmp(cnode->player->name, addhead->player->name); // check if it is alphabetical
                if(scorecheck>0){
                    scorecheck--;
                    prev->next = addhead;

                    addhead->next=cnode; // head is current node
                    c->coursepp = temp.next;
                    return;
                }
                else if(scorecheck==0){ // if name is same
                    scorecheck++;
                    break;
                }

                prev = cnode;
                cnode = cnode->next; // traverse

            }
            prev->next = addhead; // prev is head
        }

        if((!p) || (!c)){ // if player and course is null
            --list;
            temp.next = cnode->next;
            cnode=cnode->next;
            addhead=addhead->next;
        }

        else if(p || c){
            --list; // decrement
        }

        --list; // decrement
        break;
    }

    return;
}

// Function returns average total stroke score of all players
double avgTotalScore(Course c){
    PlayerNode * cnode = c->coursepp;
    double cntr=0.0;
    int cc2 = numPlayers(c); // check number of players

    if(c){
        while(c){ // if c not null
            while(cnode){
                cntr = cntr + totalStrokeScore(cnode->player); // add all scores
                cnode = cnode->next; // traverse
            }

            Course iscore;
            iscore = malloc(sizeof(struct golfCourse));
            int k;

            if(c && numPlayers(c)){
                for(k=0; k<(18*3); k++){
                    iscore->scoreinfo[k]=cc2; // initialize score info for newplayer
                }
            }

            if(!numPlayers(c)){ // if numplayer returns null
                cntr+=cc2;
                continue;
            }

            if(!cnode){ // if current node is null
                cnode = NULL;
                cntr = cntr;
                break;
            }

            break;
        }
    }

    cntr = cntr/cc2; // find average
    return cntr;
}

// Function returns average par score for all players
double avgParScore(Course c){
    PlayerNode * cnode = c->coursepp;
    double cntr = 0.0;
    int cc2 = numPlayers(c);

    if(c){
        while(c){ // if c not null
            while(cnode){
                cntr = cntr + totalParScore(cnode->player); // add all scores
                cnode = cnode->next;
            }

            Course iscore;
            iscore = malloc(sizeof(struct golfCourse));
            int k;

            if (c && numPlayers(c)){
                for(k=0; k<(18*3); k++){
                    iscore->scoreinfo[k]=cc2; // initialize score info for newplayer
                }
            }

            if(!numPlayers(c)){
                cntr+=cc2;
                continue;
            }

            if(!cnode){ // check for null
                cnode = NULL;
                cntr = cntr;
                break;
            }

            break;
        }
    }

    cntr = cntr/cc2; // find average
    return cntr;

}

// Function returns average stroke score for all players on specified hole
double avgHoleScore(Course c, int hole){
    PlayerNode* cnode=c->coursepp;
    double cntr = 0.0;
    int cc2 = numPlayers(c);
    int temp = hole;

    if(c){
        while(c){ // if c not null
            while(cnode){
                cntr = cntr + (cnode->player->strokeScore[hole-1]); // add all score hole info
                cnode = cnode->next;
            }

            Course iscore;
            iscore = malloc(sizeof(struct golfCourse));
            int k;

            if(c || hole){
                for(k=0; k<(18*3); k++){
                    int temp2 = cc2+temp; // add score info
                    iscore->scoreinfo[k]=temp2++; // initialize score info for newplayer
                }
            }

            if(!numPlayers(c)){
                cntr+=cc2;
                continue;
            }

            if(!cnode){
                cnode = NULL;
                cntr = cntr;
                break;
            }

            break;
        }
    }

    cntr = cntr/cc2; // return average
    return cntr;
}

// Function records information for specified player on specified hole as well as updates
// stroke score and par score arrays
int scoreHole(Player *p, int hole, const char* strokes){
   const char * prev = strokes;

   int temp = hole;
   Course iscore;
   iscore = malloc(sizeof(struct golfCourse));
   int k;

   for(k=0; k<(18*3); k++){
       iscore->scoreinfo[k]=temp++; // initialize score info for newplayer
   }
   while(p){ // while p not null
       p->strokes[hole-1] = malloc(sizeof(struct golfPlayer)*18); // allocate space
       p->strokeScore[hole-1] = strlen(strokes); // update array to string length of strokes
       strcpy(p->strokes[hole-1], prev); // copy string
       p->parScore[hole-1] = (p->strokeScore[hole-1]) - (p->course->par[hole-1]); // update par score

       if(!p){ // check for null
           temp++;
           break;
       }

       if(!prev){ // check for null
           temp = 0;
           k=0;
           break;
       }
       break;

   }

    return p->parScore[hole-1]; // return pointer to par score field
}

// Function returns the total number of strokes for all holes
int totalStrokeScore(const Player *p){
    int cntr = 0;
    int j;

    Course iscore;
    iscore = malloc(sizeof(struct golfCourse));
    int k;

    for(k=0; k<(18*3); k++){
        iscore->scoreinfo[k]=cntr; // initialize score info for newplayer
    }

    Player * fplayer = findPlayer(p->name, p->course); // check if player exists
    while(p){ // while p not null
        while(fplayer!=NULL){

            for(j=0; j<18; j++){
                cntr = cntr+p->strokeScore[j]; // update counter with stroke score
            }

            if(!fplayer){ // if player does not exist
                j = 0;
                continue;
            }

            else if(fplayer){
                break;
            }
        }

        break;
    }

    return cntr; // return strokes
}

// Function returns score relative to par for all holes specified by player
int totalParScore(const Player *p){
    int cntr = 0;
    int j;

    Course iscore;
    iscore = malloc(sizeof(struct golfCourse));
    int k;

    for(k=0; k<(18*3); k++){
        iscore->scoreinfo[k]=cntr; // initialize score info for newplayer
    }

    while(p!=NULL){
        for(j=0;j<18;j++){
            cntr = cntr + (p->parScore[j]); // update counter with par score
        }

        if(!p){ // if p is null
            j=0;
            k = 0;
            continue;
        }

        else{
            break;
        }
    }

    return cntr; // return score
}

// Function returns number of greens reached
int greensInReg(const Player *p){
    int cntr=0;
    int j;
    int i;
    int temp = cntr;

    Course iscore;
    iscore = malloc(sizeof(struct golfCourse));
    int k;

    for(k=0; k<(18*3); k++){
        iscore->scoreinfo[k]=temp++; // initialize score info for newplayer
    }

    while(p){
        for(i=0; i<18; i++){
            for(j=0; j<(p->course->par[i])-2;j++){ // loop that updates green
                if((p->strokes[i][j]=='g') || (p->strokes[i][j] == 'h')){ // check par info for green or hole
                    ++cntr;
                    break;
                }
                else if((p->strokes[i][j]!='g') && (p->strokes[i][j] != 'h')){ // if no green or hole continue
                    continue;
                }
            }
        }

        if(!p){ // check for null
            j=0;
            continue;
        }

        else{
            break;
        }
    }


    return cntr; // returns number of greens
}

// Function stores the number of fairways holes using holes pointer
void fairwaysHit(const Player *p, int *hit, int *holes) {
    int i;
    Course iscore;
    iscore = malloc(sizeof(struct golfCourse));
    int k;

    while(p && hit){ // while p and hit not null
        for(i=0; i<18; i++){
            if(p->course->par[i]>3){
                *holes = *holes +1; // update hole info
                if(p->strokes[i][0] == 'f'){ // if array contains a fairway
                    *hit = *hit +1; // update hit
                }
            }
            continue;
        }

        for(k=0; k<(18*3); k++){
            iscore->scoreinfo[k]=++(i); // initialize score info for newplayer
        }

        if(!p){ // check for null
            i=0;
            k=0;
            continue;
        }

        else{
            break;
        }
    }

    return;
}

// Function returns the number of holes played
int countScores(const Player *p, int parScore) {
    int cntr=0;
    Course iscore;
    iscore = malloc(sizeof(struct golfCourse));

    int k;
    int j;
    int temp = parScore; // temp int

    while(p){ // while p not null
        for(k=0; k<(18*3); k++){
            iscore->scoreinfo[k]=temp++; // initialize score info for newplayer
        }

        for(j=0; j<18; j++){
            if(p->parScore[j]==parScore){ // if par score matches array
                cntr=cntr+1; //increment counter
            }
            else{
                continue;
            }
        }

        if(parScore){ // if par score not null
            break;
        }

        if(!p){ // if p is null
            j=0;
            k=0;
            continue;
        }

        else{
            break;
        }

    }

    return cntr;
}

// Function sorts a list of players and returns the head of the sorted list
PlayerNode * Recursive(PlayerNode * h){
    PlayerNode* addhead = h;
    PlayerNode * prev = h;
    PlayerNode* tnode = h->next; // initialize as head pointer

    PlayerNode * nnode = tnode->next;
    //int test = 0;
    int sortcntr;


    while(nnode){ // while nnode not null
        if(h->next){ // if head node not null
            sortcntr = totalStrokeScore(tnode->player)-totalStrokeScore(nnode->player); // if head node score is bigger than current node score

            if(sortcntr>0){
                PlayerNode * p =malloc(sizeof(struct golfPlayerNode));
                p->next = tnode; // initialize as head
                prev->next = tnode->next; // update trailing pointer

                tnode->next = nnode->next; // update current node
                nnode->next = p->next; // update nnode
                h = addhead;

                Recursive(h); // call function to sort
                break;
            }
            else{
                nnode = nnode->next; // if scores not sorted
                tnode = tnode->next;
                prev = prev->next;
            }
        }

        if(!nnode){ // if node is null
            break;
        }

        else if((nnode) && (sortcntr<=0)){
            continue;
        }

    }
    return h; // return head
}
