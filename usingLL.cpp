#include <stdio.h>
#include <conio.h> //for kbhit and getch
#include <stdlib.h> //for rand function
#include <time.h> //for(generating random numbers as time changes)
#include <unistd.h> //for sleep function
#define l 25
#define b 40

class pair //pair
{
    public:
    int first;
    int second;

    pair(int data1,int data2)
    {
        first=data1;
        second=data2;
    }
};

class Node  //Linked list
{
    public:
    pair* data;
    Node* next;

    Node(int data1,int data2)
    {
        data=new pair(data1,data2);
        next=NULL;
    }
};

char name[100];
int direction;  //controls the movement of head of snake
int dir;  //controls the direction of head of snake
bool game=true;  //tells if game is over or not
int x,y;  //controls the current position of head of snake
pair food(0,0);  //controls the position of food
int points=0;  //counts the score
int len=1;  //length of snake
int faultX=l+1,faultY=b+1;  //position where snake dies
int reason;  //tells why the game was over
Node* snakePath;  //stores position of whole length of snake

void start()  //sets initial values 
{
    game=true;
    x=l/2;
    y=b/2;
    Node* helper=new Node(x,y);
    snakePath=helper;
    points=0;
    dir=30;

    do
    {srand(time(0)); // to give a differnt result for each program run
    food.first=(rand()% (l-3)+2); //(upperLimit-lowerLimit+1)+lowerLimit=(l-2-1+1)+1
    food.second=(rand()% (b-3)+2);}while(food.first==x && food.second==y);
}

void board()  //draws the game board
{
    system("cls");  //clears the previous board to display the latest positions
    for(int i=0;i<l;i++)
    {
        for(int j=0;j<b;j++)
        {
            if(i==faultX && j==faultY)
            {
                printf("%c" ,dir);
            }
            else if(i==0 || i==l-1)
            {
                printf("-");
            }
            else if(j==0 || j==b-1)
            {
                printf("|");
            }
            else if(i==food.first && j==food.second)
            {
                printf("%c" ,5);
            }
            else if(snakePath->data->first==i && snakePath->data->second==j)
            {
                printf("%c" ,dir);
            }
            else
            {int flag=0;
            Node* temp=snakePath->next;
            while(temp!=NULL)
            {
                if(temp->data->first==i && temp->data->second==j)
                {
                    flag=1;
                    printf("o");
                    break;
                }
                temp=temp->next;
            }
            if(flag==0)
            {printf(" ");}
            }
        }
        printf("\n");
    }
    
    printf("SCORE : %d" ,points);
    printf("\nPress escape  to quit the game!!");
}

void input()  //stores the input of user
{
    if(kbhit())  //If a key is pressed kbhit return 1 else 0
    {
        switch(getch())  //Inputs the character entered
        {
            case 75: //left   
            direction=1;
            break;
            
            case 80: //down
            direction=2;
            break;
            
            case 72: //up
            direction=3;
            break;
            
            case 77: //right
            direction=4;
            break;

            case 27: //escape
            game=false;
            reason=3;
            break;
        }
    }
    
}

void play()  //Logic for the game
{
    sleep(0.03);
    Node* temp=snakePath;
    Node* prev=NULL;
    for(int i=1;i<len;i++)
    {
        prev=temp;
        temp=temp->next;
    }
    if(prev==NULL)
    {snakePath=NULL;}
    else if(temp!=NULL)
    {prev->next=NULL;}
    
    
    switch(direction)
    {
        case 1:
        y--;
        dir=17; //left
        break;
        
        case 2:
        x++;
        dir=31; //down
        break;

        case 3:
        x--;
        dir=30; //up
        break;

        case 4:
        y++;
        dir=16; //right
        break;
    }

    Node* head=new Node(x,y);
    head->next=snakePath;
    snakePath=head;

    //If game ends
    if(x<=0 || x>=l-1 || y<=0 || y>=b-1)
    {
        faultX=x;
        faultY=y;
        game =false;
        reason=2;}
    
    //If the snake touches itself
    Node* temp0=snakePath->next;
    while(temp0!=NULL)
    {
        if(snakePath->data->first==temp0->data->first && snakePath->data->second==temp0->data->second)
        {
            faultX=temp0->data->first;
            faultY=temp0->data->second;
            game=false;
            reason=1;
        }
        temp0=temp0->next;
    }

    //If snake eats the star
    if(x==food.first && y==food.second)
    {
        srand(time(0));
        food.first=(rand() % (l-2))+1;
        food.second=(rand() % (b-2))+1;

        points+=10;
        len++;
    }
}

void endGameDisplay()  //Displayed when game is over
{
    char over[13][30]={"#####  ####  #   #  #####    ",
                       "#      #  #  ## ##  #        ", 
                       "#  ##  ####  # # #  ###      ",
                       "#   #  #  #  #   #  #        ",
                       "#####  #  #  #   #  #####    ",
                       "                             ",
                       "                             ",
                       "#####  #    #  ####  #####  #",
                       "#   #  #    #  #     #   #  #",
                       "#   #  #    #  ###   #####  #",
                       "#   #  #    #  #     ##     #",
                       "#   #   #  #   #     # #    #",
                       "#####    #     ####  #   #  o"};

    for(int i=0;i<13;i++)
    {
        for(int j=0;j<29;j++)
        {
            printf("%c" ,over[i][j]);
        }
        printf("\n");
    }
    if(reason==1)
    {
        printf("\nSnake bit it's tail  :(\n");
    }
    else if(reason==2){
        printf("\nSnake touched the boundary  :(\n ");
    }
    else{
        printf("\nYou quit the game !!");
    }
    printf("\n");                 
    printf("%s, Your final score is %d :)\n\n",name ,points);
}

int main()  //main part of code
{
    printf("Enter your name : ");
    gets(name);
    start();
    while(game)
    {
        board();
        input();
        play();
    }
    board();
    sleep(1.5);
    system("cls");
    printf("\n\n");
    endGameDisplay();

    FILE* ptr=NULL;
    ptr=fopen("system.txt","r");
    FILE* rec=NULL;
    rec=fopen("records.txt","a");
        int maxScore;
        fscanf(ptr,"%d",&maxScore);
        fclose(ptr);

        ptr=fopen("system.txt","w");
        if(points==maxScore)
        {
            printf("You reached the max Score !!!");
            fprintf(ptr,"%d",points);
        }
        else if(points>maxScore)
        {
            printf("You beat the max Sccore!!!\nOld max score : %d\nNew max score : %d" ,maxScore,points);
            fprintf(ptr,"%d" ,points);
        }
         else{
            fprintf(ptr,"%d" ,maxScore);
         }

         fputs(name,rec);
         fputs("          ",rec);
         fprintf(rec,"%d" ,points);
         fprintf(rec,"\n");

    int newMax;
    fclose(ptr);
    fclose(rec);
 
    ptr=fopen("system.txt","r");
    fscanf(ptr,"%d",&newMax);
    fclose(ptr);
 
    rec=fopen("records.txt","r");
    printf("\n\n    MAX SCORE : %d" ,newMax);
    printf("\n-------Game Record-------");
    printf("\nNAME           SCORE\n");
    char c = fgetc(rec);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(rec);
    }
    fclose(rec);
}
