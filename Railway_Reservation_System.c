#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define size 5

typedef struct NODE
{
	int registration_number;
	int age;
	char name[20];
	struct NODE *next;
} node;

node* dequeue();
void create();
int reserve(node*);
int cancel_ticket(int);
void enqueue(node*);
void display();

node *stack_start;
node *queue_front;
node *queue_rear;
int number_of_waiting_tickets = 0;
int number_of_confirmed_tickets = 0;

void create()
{
	node *new;
	new = (node *)malloc(sizeof(node));
	new->registration_number = 1;
	printf("Name : ");
	scanf("%s", new->name);
	printf("Age : ");
	scanf("%d", &new->age);
	stack_start = new;
	new->next = NULL;
	number_of_confirmed_tickets = number_of_confirmed_tickets + 1;
}

int reserve(node *stack_start)
{
	if(stack_start == NULL)
	{
   		 create(stack_start);
		 return 1;
	}
	else 
	{
		node *temporary_node, *new_node;
		temporary_node = stack_start;
		while(temporary_node->next != NULL)
		{ 
	  		temporary_node = temporary_node->next;
		}
		new_node = (node *)malloc(sizeof(node));
		printf("Name : ");
		scanf("%s", new_node->name);
		printf("Age : ");
		scanf("%d", &new_node->age);
		new_node->next = NULL;
		if(number_of_confirmed_tickets <= size)
		{
			number_of_confirmed_tickets = number_of_confirmed_tickets + 1;
			new_node->registration_number = number_of_confirmed_tickets;
			temporary_node->next = new_node;
			return 1;
		}
		else
		{
			enqueue(new_node);
			return 0;
		}
	}
}

int cancel_ticket(int registration)
{
	node *ptr, *previous, *new;
	ptr = stack_start;
	previous = NULL;
	if(stack_start == NULL)
		return -1;
	else if(ptr->next == NULL && ptr->registration_number == registration)
	{
		stack_start = NULL;
		number_of_confirmed_tickets = number_of_confirmed_tickets - 1;
		free(ptr);
		return 1;
	}	
	else
	{	
		while(ptr->registration_number != registration && ptr->next != NULL)
		{
			previous = ptr;
			ptr = ptr->next;
		}
		if(ptr->next == NULL && ptr->registration_number != registration)
			return -1;
		else
			previous->next = ptr->next;
		free(ptr);
		new = dequeue();
		while(previous->next != NULL)
			previous=previous->next;
		previous->next = new;
		if new == None :
			number_of_confirmed_tickets = number_of_confirmed_tickets - 1;
		return 1;
	}
}

void enqueue(node *new_node)
{
	if(queue_rear == NULL)
	{
		queue_rear = new_node;
		queue_rear->next = NULL;
		queue_front = queue_rear;
	}
	else
	{
		node *temporary_node;
		temporary_node = new_node;
		queue_rear->next = temporary_node;
		temporary_node->next = NULL;
		queue_rear = temporary_node;
	}
	number_of_waiting_tickets = number_of_waiting_tickets + 1;
}

node* dequeue()
{
	node *queue_front1;
	queue_front1 = queue_front;
	if(queue_front == NULL)
		return NULL;
	else
	{
	    	number_of_waiting_tickets = number_of_waiting_tickets - 1;
		if(queue_front->next != NULL)
		{
			queue_front = queue_front->next;
			queue_front1->next = NULL;
			return queue_front1;
		}
		else
		{
			queue_front=NULL;
			queue_rear=NULL;	
			return queue_front1;
		}
	}	
}

void display()
{
	node *temporary_node;
	temporary_node = stack_start;
	while(temporary_node != NULL)
	{
		printf("\nRegistration number : %d\n", temporary_node->registration_number);
		printf("Name : %s\n\n", temporary_node->name);
		temporary_node = temporary_node->next;
    	}
}

int main()
{
	int choice, status = 0, cancellation = 0, reg = 0;
	stack_start = NULL, queue_rear = NULL, queue_front = NULL;

	printf("\t\t\t***RAILWAY RESERVATION SYSTEM***\t\t\t\t\n");
	while(1)
	{
		printf("\n\nWhat would you like to do ? \n 1. Reserve a ticket \n 2. Cancel your Booking \n 3. Display passenger details \n 4. exit\n\n");
		scanf("%d", &choice); 
		switch(choice)
		{	
			case 1 : status = reserve(stack_start);
	              		 if(status == 0)
	                	 	printf("\nAll Bookings are Full !!! \nYou have been added to the Waiting List. Your Waiting list number is %d", number_of_waiting_tickets);
	              		 else
	                		printf(" \nYour Booking was Successful !!! Enjoy your journey !!! Your Registration number is %d\n\n", number_of_confirmed_tickets);
	              		 break;
	        
	    		case 2 : printf("\nProvide the Registration number to be cancelled : ");
	              		 scanf("%d", &registration);
	              		 if(registration > number_of_confirmed_tickets)
	              		 	printf("Please enter a valid Registration number !!!");
	              		 else
	              		 {
	              		 	cancellation = cancel_ticket(registration);
	              			if(cancellation == -1)
	              				printf("\nPlease enter a valid Registration number !!!\n");
	              			else
	              				printf("\nYour Registration was Cancelled successfully !!!\n");
	              		 }
	              		 break;
	              
	    		case 3 : display();
	    			 break;
	    		case 4 : exit(0);   
	    			 break;
	    		default : printf("\nPlease enter a valid choice!!!\n");
		}	
	}
}