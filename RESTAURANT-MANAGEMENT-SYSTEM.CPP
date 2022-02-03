#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Code Prepared By -
//Mahim Kapoor (N220)
//Vidhi Shah (N211) 
//Ayush Kast (N227)
//Bhumil Dave (N223)
//MBA-Tech CE, Div. A
struct node
{
	char particular [150];
	int quantity;
	float price;
	int data;
	char grammage [100];
	struct node *prev;
	struct node *next;
};
struct node *startc = NULL,*newnode,*endc = NULL;
struct node *starta = NULL, *enda = NULL;
struct node *start_s;

struct node* create_order_admin(struct node *head,int data, char particular[150], float price,char grammage[100])
{

    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->particular,particular);
    strcpy(newnode->grammage,grammage);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *ptr = head;

    if(ptr==NULL)
	starta = enda = newnode;
    else
    {
	while(ptr->next!=NULL)
	    ptr=ptr->next;

	ptr->next=newnode;
	newnode->prev = enda;
	enda = newnode;
    }

    return starta;
}

struct node* create_customer_order(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *ptr = starta;
    int flag = 0;
    while(ptr!=NULL)
    {
	if(ptr->data==data)
	{
	    flag = 1;
	    break;
	}
	ptr = ptr->next;
    }

    if(flag==1)
    {
	newnode->data = data;
	newnode->price = quantity*(ptr->price);
	newnode-> quantity = quantity;
	strcpy(newnode->particular,ptr->particular);
	strcpy(newnode->grammage,ptr->grammage);
	newnode->next = NULL;
	newnode->prev = NULL;

	struct node *temp = head;

	if(temp==NULL)
	    startc = endc = newnode;
	else
	{
	    while(temp->next!=NULL)
		temp=temp->next;

	    temp->next=newnode;
	    newnode->prev = endc;
	    endc = newnode;
	}
    }
    else
    {
	printf("\n\t\t\tOops! We're sorry, this item is currently not present in the menu!\n\n");
    }
    return startc;
}

void displaymenu(struct node *head)
{
struct node *ptr = head;
if(ptr==NULL)
{
printf("\n\t\tOops!\tNo Order Till Now!!\n\t\tPlease Come Back Later!\n\n");
}
else
{
while(ptr!=NULL)
{
if(ptr->quantity==0)
printf("\n\t\t\t\t\t%d\t\t\t\t\t%s\t\t\t\t\t%.5f\t\t\t\t\t%s\n",ptr->data,ptr->particular,ptr->price,ptr->grammage);
else
{
printf("\t\t\t\t\t%d\t\t\t\t\t%s\t\t\t\t\t%d\t\t\t\t\t%.5f\t\t\t\t\t%s\n",ptr->data,ptr->particular,ptr->quantity,ptr->price,ptr->grammage);
}
ptr = ptr->next;
}
}
}

struct node* total_sales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;
    struct node *ptr = starta;
    while(ptr->data!=data)
    {
	ptr = ptr->next;
    }
    newnode->data = data;
    newnode->price = quantity*(ptr->price);
    newnode-> quantity = quantity;
    strcpy(newnode->particular,ptr->particular);
    strcpy(newnode->grammage,ptr->grammage);
    newnode->next = NULL;
    newnode->prev = NULL;
    struct node *temp = start_s;
    if(temp==NULL)
	start_s = newnode;
    else
    {
	while(temp->next!=NULL)
	{
	    if(temp->data==data)
	    {
		flag = 1;
		break;
	    }
	    temp=temp->next;
	}

	if(flag==1)
	{
	    temp->quantity = temp->quantity + newnode-> quantity;
	    temp->price =  temp->price + newnode->price;
	}
	else
	{
	    temp->next=newnode;
	}
    }
    return start_s;
}

void bill_calculate()
{
    struct node *temp = startc;
    while(temp!=NULL)
    {
	start_s = total_sales(temp->data, temp->quantity);
	temp=temp->next;
    }
}


struct node* delete_by_itemno (int data,struct node* head, struct node* tail)
{
    if(head==NULL)
    {
	printf("\n\t\t\tOops! We're sorry, this item is currently not present in the menu!\n\n");
    }
    else
    {
	struct node* ptr;
	if(data==head->data)
	{
	    ptr = head;
	    head = head->next;
	    if (head != NULL)
	    head->prev = NULL;
	    free(ptr);
	}
	else if(data==tail->data)
	{
	    ptr = tail;
	    tail = tail->prev;
	    tail->next = NULL;
	    free(ptr);
	}
	else
	{
	    ptr = head;
	    while(data!=ptr->data)
	    {
		ptr = ptr->next;
	    }
	    (ptr->prev)->next = ptr->next;
	    (ptr->next)->prev = ptr->prev;
	    free(ptr);
	}
    }
    return head;
}

int delete_item_admin()
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=starta;
    while(temp!=NULL)
    {
	if (temp->data == num)
	{
	    starta = delete_by_itemno(num, starta, enda);
	    return 1;
	}
	temp=temp->next;
    }

    return 0;
}

int delete_item_customer()
{
    printf("\n\t\t\t\t\t\tEnter item no. of Delicacy which you want to delete\n\t\t\t\t\t\t");
    int n;
    scanf("%d",&n);
    struct node* ptr=startc;
    while(ptr!=NULL)
    {
	if (ptr->data == n)
	{
	    startc = delete_by_itemno(n, startc, endc);
	    return 1;
	}
	ptr=ptr->next;
    }
    return 0;
}

void display_customer_bill()
{
    displaymenu(startc);
    struct node *ptr = startc;
    float cus_bill = 0;
    while (ptr!=NULL)
    {
	cus_bill = cus_bill + ptr->price;
	ptr = ptr->next;
    }

    printf("\t\t\t\tTotal Bill for you Order : %.03f\n",cus_bill);

}

struct node* delete_complete_order(struct node* head)
{
    if(head==NULL)
    {
	return NULL;
    }
    else
    {
	struct node* ptr = head;
	while(ptr->next!=NULL)
	{
	    ptr = ptr->next;
	    free(ptr->prev);
	}
	free(ptr);
	head = NULL;
    }

    return head;
}

void returnadmin()
{


	int ch;
	printf("\033[0;33m");
	printf("\n___________________________________________________________________________________________________________________________________\n");
        printf("                                         Welcome to The Rooftop Cafe\n");
        printf("                                         --The Sip Of Freshness--\n");
        printf("\n___________________________________________________________________________________________________________________________________\n");
	printf("\033[0m");
	printf("\033[0;36m");
printf("\n___________________________________________________________________________________________________________________________________\n");
printf("                                         ~~~~~~	 Admin  Section   ~~~~~~\n");
printf("\n___________________________________________________________________________________________________________________________________");
	printf("\n\t\t1. View total sales\n");
	printf("\n\t\t2. Add new items in the order menu\n");
	printf("\n\t\t3. Delete items from the order menu\n");
	printf("\n\t\t4. Display order menu\n");
	printf("\n\t\t5. Back To Main Menu\n\n");
	printf("\t\t  Enter Your Choice --->");
	scanf("%d",&ch);
	printf("\033[0m");
	switch (ch)
	{
	    case 1:
		displaymenu(start_s);
		returnadmin();
		break;
	    case 2:

		printf("\n\t\t\t\t\t\t\tEnter the serial number  of food item ordered : ");
		int num,flag = 0;
		char name[150],grammage[100];
		float price;
		scanf("%d",&num);

		struct node *temp = starta;

		while(temp!=NULL)
		{
		    if(temp->data==num)
		    {
			printf("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
			flag = 1;
			break;
		    }
		    temp = temp->next;
		}

		if(flag==1)
		    break;

		printf("\t\t\t\t\t\t\tEnter the name of food item : ");
		scanf("%s",name);
		printf("\t\t\t\t\t\t\tEnter price of food item : ");
		scanf("%f",&price);
		printf("\n\t\t\t\t\t\t\tEnter Grammage of food item :");
		scanf("%s",grammage);
		starta = create_order_admin(starta, num, name, price, grammage);
		printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
		returnadmin();
		break;
	    case 3:
		if(delete_item_admin())
		{
		    printf("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
		    displaymenu(starta);
		}
		else
		    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");
		returnadmin();
		break;
	    case 4:
		printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
		displaymenu(starta);
		returnadmin();
		break;
	    case 5:
		break;
	    default:
		printf("\n\t\t\t\tOops! Wrong Input Detected..\n");
		break;
	}
    }

void admin()
{

	int ch;
	printf("\033[0;33m");
	printf("\n___________________________________________________________________________________________________________________________________\n");
        printf("                                         Welcome to The Rooftop Cafe\n");
        printf("                                         --The Sip Of Freshness--\n");
        printf("\n___________________________________________________________________________________________________________________________________\n");
	printf("\033[0m");
	printf("\033[0;36m");
printf("\n___________________________________________________________________________________________________________________________________\n");
printf("                                         ~~~~~~	 Admin  Section   ~~~~~~\n");
printf("\n___________________________________________________________________________________________________________________________________");
	printf("\n\t\t1. View total sales\n");
	printf("\n\t\t2. Add new items in the order menu\n");
	printf("\n\t\t3. Delete items from the order menu\n");
	printf("\n\t\t4. Display order menu\n");
	printf("\n\t\t5. Back To Main Menu\n\n");
	printf("\t\t  Enter Your Choice --->");
	scanf("%d",&ch);
	printf("\033[0m");
	switch (ch)
	{
	    case 1:
		displaymenu(start_s);
		returnadmin();
		break;
	    case 2:

		printf("\n\t\t\t\t\t\t\tEnter the serial number  of food item ordered : ");
		int num,flag = 0;
		char name[150],grammage[100];
		float price;
		scanf("%d",&num);

		struct node *temp = starta;

		while(temp!=NULL)
		{
		    if(temp->data==num)
		    {
			printf("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
			flag = 1;
			break;
		    }
		    temp = temp->next;
		}

		if(flag==1)
		    break;

		printf("\t\t\t\t\t\t\tEnter the name of food item : ");
		scanf("%s",name);
		printf("\t\t\t\t\t\t\tEnter price of food item : ");
		scanf("%f",&price);
		printf("\n\t\t\t\t\t\t\tEnter Grammage of food item :");
		scanf("%s",grammage);
		starta = create_order_admin(starta, num, name, price, grammage);
		printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
		returnadmin();
		break;
	    case 3:
		if(delete_item_admin())
		{
		    printf("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
		    displaymenu(starta);
		}
		else
		    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");
		returnadmin();
		break;
	    case 4:
		printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
		displaymenu(starta);
		returnadmin();
		break;
	    case 5:
		break;
	    default:
		printf("\n\t\t\t\tOops! Wrong Input Detected..\n");
		break;
	}
    }


void returncustomer()
{

    int ch;
    printf("\033[0;33m");
    printf("\n___________________________________________________________________________________________________________________________________\n");
    printf("                                         Welcome to The Rooftop Cafe\n");
    printf("                                         --The Sip Of Freshness--\n");
    printf("\n___________________________________________________________________________________________________________________________________\n");
    printf("\033[0m");
    printf("\033[0;36m");
printf("\n___________________________________________________________________________________________________________________________________\n");
printf("                                         ~~~~~~	Customer Section  ~~~~~~\n");
printf("\n___________________________________________________________________________________________________________________________________");
    printf("\n\t\t1. Place You Order - Let us make your day :)\n");
    printf("\n\t\t2. View Your Delicious Ordered Items\n");
    printf("\n\t\t3. Delete An Item From Your Order\n");
    printf("\n\t\t4. Display Final Bill For Your Order - Too Close to Happiness ;)\n");
    printf("\n\t\t5. Go Back To Main Menu\n\n");
    printf("\t\t  Enter Your Choice --->");
    scanf("%d",&ch);
    printf("\033[0m");
	switch (ch)
	{
	    case 1:
		displaymenu(starta);
		printf("\n\n\t\t\t\t\t\tItem no. 001 to 007 - Hot Coffee\n");
		printf("\n\t\t\t\t\t\tItem no. 010 to 060 - Cold Coffee\n");
		printf("\n\t\t\t\t\t\tItem no. 100 to 600 - Friends of Frappe\n");
		printf("\n\t\t\t\t\t\tItem no. 880 to 1000 - Big Eats\n");
		printf("\n\t\t\t\t\t\tItem no. 1110 to 1160 - Small Eats\n");
		printf("\n\t\t\t\t\t\tItem no. 30 to 40 - ~ Sundaes ~\n");
		printf("\n\t\t\t\t\t\tKindly Select the item no. which you want to Order today : ");
		int n;
		scanf("%d",&n);
		printf("\t\t\t\t\tKindly Enter Quantity\t");
		int quantity;
		scanf("%d",&quantity);
		startc = create_customer_order(startc, n, quantity);
		returncustomer();
		break;
	    case 2:
		printf("\n\t\t\t\t ~~ List of Delicacies We Serve ~~ \n");
		displaymenu(startc);
		returncustomer();
		break;
	    case 3:
		if(delete_item_customer())
		{
		    printf("\n\t\t\t\t### The Updated Menu Having Finest Delicacies that We serve ###\n");
		    display_customer_bill();
		}
		else
		    printf("\n\t\t\tOops! We're sorry, this item is currently not present in the menu!\n\n");
		returncustomer();
		break;
	    case 4:
		bill_calculate();
		printf("\n\t\t\t\t~~ Final Bill for your Order ~~\n");
		display_customer_bill();
		delete_complete_order(startc);
		returncustomer();
		break;
	    case 5:
		break;
	    default:
		printf("\n\t\t\t\tOops! Wrong Input Detected..\n");
		break;
	}

}

void Customer()
{

    int ch;
    printf("\033[0;33m");
    printf("\n___________________________________________________________________________________________________________________________________\n");
    printf("                                         Welcome to The Rooftop Cafe\n");
    printf("                                         --The Sip Of Freshness--\n");
    printf("\n___________________________________________________________________________________________________________________________________");
    printf("\033[0m");
    printf("\033[0;36m");
printf("\n___________________________________________________________________________________________________________________________________\n");
printf("                                         ~~~~~~	Customer Section  ~~~~~~\n");
printf("\n___________________________________________________________________________________________________________________________________");
    printf("\n\t\t1. Place You Order - Let us make your day :)\n");
    printf("\n\t\t2. View Your Delicious Ordered Items\n");
    printf("\n\t\t3. Delete An Item From Your Order\n");
    printf("\n\t\t4. Display Final Bill For Your Order - Too Close to Happiness ;)\n");
    printf("\n\t\t5. Go Back To Main Menu\n\n");
    printf("\t\t  Enter Your Choice --->");
    scanf("%d",&ch);
    printf("\033[0m");
	switch (ch)
	{
	    case 1:
		displaymenu(starta);
		printf("\n\t\t\tItem no. 001 to 007 - Hot Coffee\n");
		printf("\n\t\t\tItem no. 010 to 060 - Cold Coffee\n");
		printf("\n\t\t\tItem no. 100 to 600 - Friends of Frappe\n");
		printf("\n\t\t\tItem no. 880 to 1000 - Big Eats\n");
		printf("\n\t\t\tItem no. 1110 to 1160 - Small Eats\n");
		printf("\n\t\t\tItem no. 30 to 40 - ~ Sundaes ~\n");
		printf("\n\t\t\tKindly Select the item no. which you want to Order today : ");
		int n;
		scanf("%d",&n);
		printf("\t\t\t\t\tKindly Enter Quantity\t");
		int quantity;
		scanf("%d",&quantity);
		startc = create_customer_order(startc, n, quantity);
		returncustomer();
		break;
	    case 2:
		printf("\n\t\t\t\t ~~ List of Delicacies We Serve ~~ \n");
		displaymenu(startc);
		returncustomer();
		break;
	    case 3:
		if(delete_item_customer())
		{
		    printf("\n\t\t\t\t### The Updated Menu Having Finest Delicacies that We serve ###\n");
		    display_customer_bill();
		}
		else
		    printf("\n\t\t\tOops! We're sorry, this item is currently not present in the menu!\n\n");
		returncustomer();
		break;
	    case 4:
		bill_calculate();
		printf("\n\t\t\t\t~~ Final Bill for your Order ~~\n");
		display_customer_bill();
		delete_complete_order(startc);
		returncustomer();
		break;
	    case 5:
		break;
	    default:
		printf("\n\t\t\t\tOops! Wrong Input Detected..\n");
		break;
	}

}



int cafehistory()
{
	printf("\033[0;33m");
	printf("\n***********************************************************************************************************************************\n\n");
	printf("\n***********************************************************************************************************************************\n\n");

	printf("                                         Welcome to The Rooftop Cafe\n");
	printf("                                         --The Sip Of Freshness--\n");
	printf("************************************************************************************************************************************\n\n\n");
	printf("                                         - This Cafe was built by Mr.Berman Kurley\n");
	printf("                                         - It is a fun place to hangout for all the youngsters around the area\n");
	printf("                                         - We offer many kinds of coffees,shakes,burgers,snacks and sundaes :)\n");
	printf("                                         - Our services are also available on ZOMATO and Swiggy..\n");
	printf("                                         - You can call 9414706528 to ORDER over CALL...\n");
	printf("************************************************************************************************************************************\n\n\n");
printf("\n***********************************************************************************************************************************\n\n");
printf("\033[0m");
printf("\n                                    Enter 1 to return to main menu : ");
int ch;
scanf("%d",&ch);
if(ch==1)
return 0;
}



void insertingmenu()
{
create_order_admin(starta,001,"Cappuccino",62,"220 ml");
create_order_admin(starta,002,"Cafe Latte",66,"250 ml");
create_order_admin(starta,003,"Expresso",50,"220 ml");
create_order_admin(starta,004,"Macchiato",82,"220 ml");
create_order_admin(starta,005,"Irish coffee",62,"220 ml");
create_order_admin(starta,006,"Cafe Americano",64,"220 ml");
create_order_admin(starta,007,"Cafe Mocha",75,"220 ml");
create_order_admin(starta,010,"Devil's Own",62,"220 ml");
create_order_admin(starta,020,"Kaapi Nirvana",110,"220 ml");
create_order_admin(starta,030,"Iced Eskimo",150,"220 ml");
create_order_admin(starta,050,"vegan shake",450,"220 ml");
create_order_admin(starta,060,"Cold Sparkel",150,"220 ml");
create_order_admin(starta,100,"Café Frappe",70,"300 ml");
create_order_admin(starta,200,"Choco Frappe",100,"300 ml");
create_order_admin(starta,400,"crunchy Frappe",500,"300 ml");
create_order_admin(starta,500,"Crunchy Vanilla Frappe",100,"300 ml");
create_order_admin(starta,600,"Snowy vanilla Frappe",300,"300 ml");
create_order_admin(starta,880,"Tandoori Paneer sandwich",600,"150ml");
create_order_admin(starta,1110,"French Croissant",450,"80 ml");
create_order_admin(starta,1120,"AztecCreamy Choco Donut",555,"90 ml");
create_order_admin(starta,1130,"Hot'N'Spicy Veg Puff",600,"300 ml");
create_order_admin(starta,1140,"Chilli cheese Toastizza",900,"300 ml");
create_order_admin(starta,1150,"Veg Samosa",780,"250 ml");
create_order_admin(starta,1160,"Chocomoco chocolate",530,"300 ml");
create_order_admin(starta,30,"vanilla Ice Cream",80,"100 ml");
create_order_admin(starta,40,"Chocolate Ice Cream",120,"100 ml");
}
void cstrev(int k)
{
int ch;
int rating,n;
char review[200];
switch(k)
{
case 1 :
           printf("\n\t\t\t\t\tEnter no. of reviews you want to add?\n");
            scanf("%d",&n);
for(int i=0;i<n;i++)
{
printf("\n\t\t\t\t\tRate our Cafe out of 5\n");
scanf("\t\t\t\t\t%d",&rating);
printf("\n\t\t\t\t\tWrite a Review for our cafe\n");
scanf("\t\t\t\t\t%s",review);
}
break;
case 2: printf("\n\t\t\t\t\t3 out of 5\n","\n\t\t\t\t\tReally good! Here's something else you could say instead of delicious. ...");
printf("\n\t\t\t\t\t2 out of 5\n","\n\t\t\t\t\tYummy");
printf("\n\t\t\t\t\t\1 out of 5\n","\n\t\t\t\t\tFlavorful. ...");
printf("\n\t\t\t\t\t5 out of 5\n","\n\t\t\t\t\tMouth-watering.");
break;
default: printf("\n\t\t\t\t\t\tOops! Wrong Input Detected..\n");
break;
}
}
void returnmainmenu()
{   int ch,k,n;
    system("cls");
	insertingmenu();
	printf("\033[0;33m");
	printf("\n***********************************************************************************************************************************\n");
	printf("                                         Welcome to The Rooftop Cafe\n");
	printf("                                         --The Sip Of Freshness--\n");
	printf("************************************************************************************************************************************\n\n\n");
	printf("\t\t\t1. Cafe History..\n");
	printf("\t\t\t2. Admin Portal --> \n");
	printf("\t\t\t3. Customer Zone--> \n");
	printf("\t\t\t4. Customer Reviews..\n\n");
	printf("\t\t\t5. Exit\n\n");
	printf("\033[0;36m");
	printf("\n\n\n\n\t\t\t\t\tNOW YOU CAN ORDER ONLINE 24/7\n");
	printf("\t\t\t\t\tEnter Your Choice -");
	scanf("%d",&ch);
	printf("\033[0m");
	switch (ch)
	{
	    case 1:
		cafehistory();
		returnmainmenu();
		break;
	    case 2:
		admin();
		returnmainmenu();
		break;
	    case 3:
		Customer();
		returnmainmenu();
		break;
	    case 4:
			printf("\t\t\t\t\t1. Add A Review..\n");
			printf("\t\t\t\t\t2. Show Customer Reviews\n");
			printf("\t\t\t\t\t3. Exit\n");

			printf("\t\t\t\t\tEnter Your Choice -");
			scanf("%d",&k);
	switch(k)
		{
				case 1: cstrev(k);
				break;
				case 2:
				printf("\n\t\t\t\t\t3 out of 5\n","\n\t\t\t\t\tReally good! Here's something else you could say instead of delicious. ...");
printf("\n\t\t\t\t\t2 out of 5\n","\n\t\t\t\t\tYummy");
printf("\n\t\t\t\t\t\1 out of 5\n","\n\t\t\t\t\tFlavorful. ...");
printf("\n\t\t\t\t\t5 out of 5\n","\n\t\t\t\t\tMouth-watering.");
				break;
				case 3: exit(0);
				break;
				default: printf("\n\t\t\t\tOops! Wrong Input Detected..\n");
				break;
				}
				returnmainmenu();
				break;

	    case 5:
		exit(0);
		returnmainmenu();
		break;
	    default:
		printf("\n\t\t\t\t\t\tOops! Wrong Input Detected..\n");
		break;
	}
}


void main()
{
system("cls");
	insertingmenu();
	int ch;
	int k,rating,n;
	char review[200];
	printf("\033[0;33m");
	printf("\n***********************************************************************************************************************************\n");
	printf("                                         Welcome to The Rooftop Cafe\n");
	printf("                                         --The Sip Of Freshness--\n");
	printf("************************************************************************************************************************************\n\n\n");
	printf("\t\t\t\t\t1. Cafe History..\n");
	printf("\t\t\t\t\t2. Admin Portal --> \n");
	printf("\t\t\t\t\t3. Customer Zone--> \n");
	printf("\t\t\t\t\t4. Customer Reviews..\n");
	printf("\t\t\t\t\t5. Exit\n\n");
	printf("\033[0m");
	printf("\033[0;36m");
	printf("\n\n\n\n\t\t\t\t\tNOW YOU CAN ORDER ONLINE 24/7\n");
	printf("\t\t\t\t\tEnter Your Choice -");
	scanf("%d",&ch);
	printf("\033[0m");
	switch (ch)
	{
	    case 1:
		cafehistory();
		returnmainmenu();
		break;
	    case 2:
		admin();
		returnmainmenu();
		break;
	    case 3:
		Customer();
		returnmainmenu();
		break;
	    case 4:
			printf("\t\t\t\t\t1. Add A Review..\n");
			printf("\t\t\t\t\t2. Show Customer Reviews\n");
			printf("\t\t\t\t\t3. Exit\n");

			printf("\t\t\t\t\tEnter Your Choice -");
			scanf("%d",&k);
	switch(k)
		{
				case 1: cstrev(k);
				break;
				case 2:
				printf("\n\t\t\t\t\t3 out of 5\n","\n\t\t\t\t\tReally good! Here's something else you could say instead of delicious. ...");
printf("\n\t\t\t\t\t2 out of 5\n","\n\t\t\t\t\tYummy");
printf("\n\t\t\t\t\t\1 out of 5\n","\n\t\t\t\t\tFlavorful. ...");
printf("\n\t\t\t\t\t5 out of 5\n","\n\t\t\t\t\tMouth-watering.");
				break;
				case 3: exit(0);
				break;

				default: printf("\n\t\t\t\tOops! Wrong Input Detected..\n");
				break;
				}
				returnmainmenu();
				break;
	    case 5:
		exit(0);
		returnmainmenu();
		break;
	    default:
		printf("\n\t\t\t\t\t\tOops! Wrong Input Detected..\n");
		break;
	}
}
