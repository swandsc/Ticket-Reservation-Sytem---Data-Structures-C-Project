#include<stdio.h>
#include<stdlib.h>
#include<String.h>
#define size 3

//Used linked list implementation of queues

//Structure to store person's details
typedef struct NODE{
    int res_no;
    char name[50];
    int age;
    char sex;
    int detail;
    struct NODE *next;
    int waiting_no;
}NODE;

//Queue structure 
typedef struct QUEUE{
    NODE *front;
    NODE *rear;
}QUEUE;

//Function to create a new linked list node
NODE* create_newNODE()
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    printf("\n Please enter your name : ");
    
    scanf("%s", temp->name);
    printf(" Please enter your age : ");
    fflush(stdin);
    scanf("%d", &temp->age);
    while((temp->age)<18 || (temp->age)>120)
    {
        printf(" Please enter a valid age : ");
        fflush(stdin);
        scanf("%d", &temp->age);
    }
    printf(" Please enter your gender (M/F) : ");
    fflush(stdin);
    scanf("%c", &temp->sex);
    while((temp->sex)!='m' && (temp->sex)!='M' && (temp->sex)!='f' && (temp->sex)!='F')
    {
        printf(" Please enter a valid option : ");
        fflush(stdin);
        scanf("%c", &temp->sex);
    }
    temp->detail=-1;
    temp->next = NULL;
    temp->res_no = -1;
    temp->waiting_no = -1;
    return temp;
}

//Function to create an empty queue
QUEUE* createQUEUE()
{
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

//Enqueue function
void enQUEUE(QUEUE* q, NODE* person)
{
    //NODE* temp = create_newNODE();
    //if queue is empty, then the new node is the front and the rear
    if(q->rear==NULL)
    {
        q->front = q->rear = person;
        return;
    }
    //add the new node at the end of the queue and change the rear
    q->rear->next = person;
    q->rear = person;
}

//Dequeue function
NODE* deQUEUE(QUEUE* q)
{
    //if queue is empty, return NULL
    if(q->front==NULL)
        return NULL;
    //store previous front and move front one node ahead
    NODE* temp = q->front;

    q->front = q->front->next;

    //if front becomes NULL, change rear also to NULL
    if(q->front==NULL)
        q->rear = NULL;
    return temp;
}

//main function
int main()
{   QUEUE* queue;
    queue = createQUEUE();
    int view_det_num;
    int cancel_no;
    int counter;
    int counter_details;
    int index=200;
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    NODE* waiting_person = (NODE*)malloc(sizeof(NODE));
    NODE* seats[size];
    for(int i=0;i<size;i++)
        seats[i]=NULL;
    printf("\t\t\t\t\t\t\t\t\t\t***RAILWAY TICKET RESERVATION***\t\t\t\t\t\t\t\t\t\t");
    int choice;
    printf("\n");
    int ch=0;
    while(ch!=4)
    {
        
        printf("\n ~ MAIN MENU ~ \n");
        printf("\n 1. Reserve a ticket \n 2. Cancel a ticket \n 3. Check booking details \n 4.Exit \n");
        printf("\n Please enter your choice (1/2/3/4) : ");
        scanf("%d", &choice);
        while(choice!=1 && choice!=2 && choice!=3 && choice!=4)
        {
            printf("\n Please enter a valid option : ");
            scanf("%d", &choice);
        }
        switch(choice)
        {
            case 1 : //reserve a ticket
                    
                    printf("\n Please enter your details : \n");
                    NODE* person = create_newNODE();
                    counter=0;
                    for(int i=0;i<size;i++)
                    {
                        
                        if(seats[i]==NULL)
                        {
                            person->detail = 1;
                            person->res_no = i;
                            seats[i] = person;
                            counter = 1;
                            printf(" Your ticket has been booked successfully. Your reservation number is %d.\n", i);
                            break;
                        }
                        else
                            continue;
                    }
                    
                    if(counter==0)
                        {
                            index++;
                            printf(" Bookings are full at the moment. You have been added to the waiting list. Your waiting number is %d \n", index);
                            person->detail=0;
                            person->waiting_no=index;
                            enQUEUE(queue,person);
                        }
                
                    break;
            
            case 2 ://cancel a ticket
                    //int cancel_no; 
                    //NODE* waiting_person = (NODE*)malloc(sizeof(NODE));
                    printf(" Please enter your reservation number : \n");
                    scanf("%d", &cancel_no);
                    seats[cancel_no]=NULL;
                    waiting_person = deQUEUE(queue);
                    waiting_person->detail = 1;
                    waiting_person->res_no = cancel_no;
                    seats[cancel_no] = waiting_person;
                    printf(" You have cancelled your ticket succesfully. \n");
                    break;  

            case 3 : //view booking details
                    printf(" Please enter your reservation number/waiting number to view your booking details : ");
                    scanf("%d", &view_det_num);
                    counter_details=0;
                    for(int i=0;i<size;i++)
                    {
                        if(seats[i]->res_no==view_det_num || seats[i]->waiting_no==view_det_num)
                        {
                            printf("\n Your booking details are : \n");
                            printf(" Name : %s \n", seats[i]->name);
                            printf(" Age : %d \n", seats[i]->age);
                            printf(" Sex : %c \n", seats[i]->sex);
                            printf(" Booking status : Your booking is confirmed. Your reservation number is %d \n", i);
                            counter_details=1;
                            break;
                        }
                        else 
                            continue;
                    }
                   if(counter==0)
                   {
                        if(view_det_num>200)
                        {
                        temp=queue->front;
                        while(temp!=NULL && temp->waiting_no!=view_det_num)
                            temp=temp->next;
                        if(temp->waiting_no==view_det_num)
                        {
                            printf("\n Your booking details are : \n");
                            printf(" Name : %s \n", temp->name);
                            printf(" Age : %d \n", temp->age);
                            printf(" Sex : %c \n", temp->sex);
                            printf(" You've been added to the waiting list. Please check in later for confirmation of seat booking. \n");
                            break;
                        }
                        else
                            printf("\n Invalid number. \n");
                        }
                    }
                    else
                        printf("\n Invalid number. \n");   
            case 4:
                    exit(0);
                    break;

            default : printf("Wrong choice!");
        }
    }
    
}


