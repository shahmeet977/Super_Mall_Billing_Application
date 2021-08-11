//AUTHOR :- MEET SHAH
#include<bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define size 10             // Here I use the concept of Hash table
using namespace std; 
struct INVENTORY            // Special Datatype for Inventory dataset
{
    long inventory_id;
    string name;
    int rate;
    int quantity;
    INVENTORY *next;
};
class inventory             
{
    public:
    struct INVENTORY *Inventory_hashtable[size];
    void add_item();
    void delete_item();
    void update_item();
    void gettotalnumber();
}inventory_data;
struct CUSTOMER             // Special Datatype for Customer dataset
{
    long cust_ID;
    string name;
    int points;
    CUSTOMER *next;
};
class customer
{
    public:
    struct CUSTOMER *Customer_hashtable[size];
    void add_customer();
    void update_points();
}customer_data;

class manager: public inventory     //Class for Manager
{
    long ID;
    string name;
}manager;
struct BILLING              // Special Datatype for Billing
{
    long item_id;
    string name;
    long transaction_id;
    int rate;
    int quantity;
    int amount;
    BILLING *next;
};
class billing : public customer,public inventory //Use of Inheritance
{
    public:
    long Transaction_ID;
    long Customer_id;
    struct BILLING *Billing_hashtable[size];
    int Totalamount;
    void buy_item();
    void cancel_item();
    void make_payment();
    void assign_customer_id();
    void checkcustomer();
    int checkproduct(long);
    int checkavailibility(long,int);
    
}billing_data;
void INSERT_CUSTOMER_DATASET(long ID,string name,long points)//Function which store Customer Dataset in Hashtable
{
    CUSTOMER *newnode=new CUSTOMER;
    newnode->cust_ID=ID;
    newnode->name=name;
    newnode->points=points;
    newnode->next=NULL;
    long index;
    index=ID%size;
    if(customer_data.Customer_hashtable[index]==NULL||((customer_data.Customer_hashtable[index]->cust_ID)>(newnode->cust_ID)))
    {
        newnode->next=customer_data.Customer_hashtable[index];
        customer_data.Customer_hashtable[index]=newnode;
    }
    else
    {
        struct CUSTOMER *tmp=customer_data.Customer_hashtable[index];
        while(tmp->next!=NULL)
        {
            if(((tmp->next)->cust_ID)<(newnode->cust_ID))
            {
                tmp=tmp->next;
            }
            else
            {
                if(((tmp->next)->cust_ID)>=(newnode->cust_ID))
                {
                    newnode->next=tmp->next;
                    tmp->next=newnode;
                    tmp=tmp->next;
                    break;
                }
            }
        }
        if(tmp->next==NULL)
        {
            tmp->next=newnode;
        }
        
        
    }
}
void INSERT_INVENTORY_DATASET(long ID,string name,long rate,long quantity)//Function which store Customer Dataset in Hashtable
{
    INVENTORY *newnode=new INVENTORY;
    newnode->inventory_id=ID;
    newnode->name=name;
    newnode->rate=rate;
    newnode->quantity=quantity;
    newnode->next=NULL;
    long index;
    index=ID%size;
    if(inventory_data.Inventory_hashtable[index]==NULL||((inventory_data.Inventory_hashtable[index]->inventory_id)>(newnode->inventory_id)))
    {
        newnode->next=inventory_data.Inventory_hashtable[index];
        inventory_data.Inventory_hashtable[index]=newnode;
    }
    else
    {
        struct INVENTORY *tmp=inventory_data.Inventory_hashtable[index];
        while(tmp->next!=NULL)
        {
            if(((tmp->next)->inventory_id)<(newnode->inventory_id))
            {
                tmp=tmp->next;
            }
            else
            {
                if(((tmp->next)->inventory_id)>=(newnode->inventory_id))
                {
                    newnode->next=tmp->next;
                    tmp->next=newnode;
                    tmp=tmp->next;
                    break;
                }
            }
        }
        if(tmp->next==NULL)
        {
            tmp->next=newnode;
        }
    }
}
//From here to end all functions work as their name and there is also included the case of manager.
void customer::add_customer()
{
    long phone_num;
    string name;
    cout<<"Enter the ID number of Customer: "<<endl;
    cin>>phone_num;
    
    billing_data.Customer_id=phone_num;
    cout<<"Enter the Name of new Customer: "<<endl;
    cin>>name;
    
    CUSTOMER *newnode=new CUSTOMER;
    newnode->cust_ID=phone_num;
    newnode->name=name;
    newnode->points=0;
    newnode->next=NULL;
    
    long index;
    index=phone_num%size;
    if(customer_data.Customer_hashtable[index]==NULL||((customer_data.Customer_hashtable[index]->cust_ID)>(newnode->cust_ID)))
    {
        newnode->next=customer_data.Customer_hashtable[index];
        customer_data.Customer_hashtable[index]=newnode;
    }
    else
    {
        struct CUSTOMER *tmp=customer_data.Customer_hashtable[index];
        while(tmp->next!=NULL)
        {
            if(((tmp->next)->cust_ID)<(newnode->cust_ID))
            {
                tmp=tmp->next;
            }
            else
            {
                if(((tmp->next)->cust_ID)>=(newnode->cust_ID))
                {
                    newnode->next=tmp->next;
                    tmp->next=newnode;
                    tmp=tmp->next;
                    break;
                }
            }
        }
        if(tmp->next==NULL)
        {
            tmp->next=newnode;
        }
        
        
    }
    
}
void billing::checkcustomer()
{
    int X;
    X=0;
    for(int i=0;i<size;i++)
    {
        struct CUSTOMER *tmp=customer_data.Customer_hashtable[i];
        while(tmp)
        {
            if(tmp->cust_ID==billing_data.Customer_id)
            {
                X=1;
                break;
            }
            tmp=tmp->next;
        }
    }
    if(X==0)
    {
        cout<<"Sorry, There is no data of such Customer ID."<<endl;
        cout<<"Try creating a new ID for Customer. "<<endl;
        billing_data.add_customer();
    }
}
int billing::checkavailibility(long ID,int quantity)
{
    long index;
    int availibility=0;
    index=ID%size;
    struct INVENTORY *tmp=inventory_data.Inventory_hashtable[index];
    while(tmp)
    {
        if(tmp->inventory_id==ID)
        {
            if(tmp->quantity>=quantity)
            {
                availibility=1;
            }
        }
        tmp=tmp->next;
    }
    if(availibility==1)
        return 1;
    else
        return 0;
}
int billing::checkproduct(long ID)
{
    int X=0;
    long index;
    index=ID%size;
    struct INVENTORY *tmp=inventory_data.Inventory_hashtable[index];
    while(tmp) {
        if(tmp->inventory_id==ID)
        {
            X=1;
            break;
        }
        tmp=tmp->next;
    }
    if(X==0)
    {
        cout<<"Sorry, There is no data of such Customer ID."<<endl;
        cout<<"Try creating a new ID for Customer. "<<endl;
    }
    return X;
}
void billing::buy_item()
{
    long ID;
    int quantity;
    int availibility;
    int check=0;
    do
    {
        cout<<"Enter the Product ID to buy: "<<endl;
        cin>>ID;
        check=billing_data.checkproduct(ID);
    }
    while(check==0);
    do
    {
        cout<<"Enter the Quantity: "<<endl;
        cin>>quantity;
        availibility=billing_data.checkavailibility(ID,quantity);
        if(availibility==0)
            cout<<"Stock is not sufficient to fulfill your requirements please retry: "<<endl;
    }
    while(availibility==0);
    long index,index1;
    index=ID%size;
    struct INVENTORY *tmp=inventory_data.Inventory_hashtable[index];
    while(tmp)
    {
        if(tmp->inventory_id==ID)
        {
            index1=ID%size;
            struct BILLING *tmp1=billing_data.Billing_hashtable[index1];
            BILLING *newnode=new BILLING;
            newnode->item_id=tmp->inventory_id;
            newnode->name=tmp->name;
            newnode->transaction_id=billing_data.Transaction_ID;
            newnode->rate=tmp->rate;
            newnode->quantity=quantity;
            newnode->amount=(newnode->rate)*(newnode->quantity);
            newnode->next=NULL;
            if(billing_data.Billing_hashtable[index1]==NULL)
            {
                billing_data.Billing_hashtable[index1]=newnode;
            }
            else
            {
                while(tmp1->next!=NULL)
                {
                    tmp1=tmp1->next;
                }
                tmp1->next=newnode;
            }
            break;
            }
        tmp=tmp->next;
            
    }
    tmp->quantity=(tmp->quantity)-quantity;
}
void billing::cancel_item()
{
    long ID;
    int index;
    cout<<"Enter the product ID to cancel: "<<endl;
    cin>>ID;
    BILLING *newnode=new BILLING;
    BILLING *tmpprevious=new BILLING;
    BILLING *tmpnext=new BILLING;
    newnode->item_id=ID;
    newnode->next=NULL;
    long index1;
    index1=ID%size;
    
    struct BILLING *tmp=billing_data.Billing_hashtable[index1];
    while(tmp!=NULL)
    {
        if(tmp->item_id==newnode->item_id)
        {
            break;
        }
        tmpprevious=tmp;
        tmp=tmp->next;
        tmpnext=tmp->next;
    }
    index=ID%size;
    struct INVENTORY *tmp1=inventory_data.Inventory_hashtable[index];
    while(tmp1->next!=NULL)
    {
        if(tmp1->inventory_id==ID)
        {
            tmp1->quantity=tmp1->quantity+tmp->quantity;
        }
        tmp1=tmp1->next;
    }
    if(tmpprevious->item_id==0)
    {
        billing_data.Billing_hashtable[index1]=tmp->next;
    }
    if(tmpnext==NULL)
    {
        tmpprevious->next=NULL;
    }
    if(tmpprevious!=NULL&&tmpnext!=NULL)
    {
        tmpprevious->next=tmpnext;
    }
}
void customer::update_points()
{
    long target_transaction,target_customer;
    target_transaction=billing_data.Transaction_ID;
    target_customer=billing_data.Customer_id;
    int amount=0;
    for(int i=0;i<size;i++)
    {
        struct BILLING *tmp=billing_data.Billing_hashtable[i];
        while(tmp)
        {
            if(tmp->transaction_id==target_transaction)
            {
                amount=amount+(tmp->amount);
            }
            tmp=tmp->next;
        }
    }
    int index;
    index=target_customer%size;
    struct CUSTOMER *tmp=customer_data.Customer_hashtable[index];
    while(tmp->next!=NULL)
    {
        if(tmp->cust_ID==target_customer)
        {
            tmp->points=amount;
            break;
        }
        tmp=tmp->next;
    }
}
void billing::make_payment()
{
    long target_transaction;
    long target_customer;
    double total=0;
    target_transaction=billing_data.Transaction_ID;
    target_customer=billing_data.Customer_id;
    cout<<"\n\n";
    cout<<"----------BILL AMOUNT----------"<<endl;
    cout<<"Transaction ID: "<<target_transaction<<endl;
    cout<<"Customer ID: "<<target_customer<<endl;
    cout<<"Product ID  "<<"Name  "<<"Rate  "<<"Quantity  "<<"Amount  "<<endl;
    for(int i=0;i<size;i++)
    {
        struct BILLING *tmp=billing_data.Billing_hashtable[i];
        while(tmp)
        {
            if(tmp->transaction_id==target_transaction)
            {
                total=total+(tmp->amount);
                cout<<tmp->item_id<<"  "<<tmp->name<<"   "<<tmp->rate<<"   "<<tmp->quantity<<"\t  "<<tmp->amount<<endl;
            }
            tmp=tmp->next;
            }
    }
        cout<<"--------------------------------------------\n";
    if(total>=5000)
    {
        total=0.85*total;
        cout<<"\n Congratulation You got 15% discount. "<<endl;
        cout<<"                     "<<"Total: "<<total<<endl;
    }
    else
    {
        cout<<"                     "<<"Total: "<<total<<endl;
    }
}
void inventory::delete_item()
{
    long ID;
    cout<<"Enter Product ID which you want to delete: "<<endl;
    cin>>ID;
    
    INVENTORY *newnode=new INVENTORY;
    INVENTORY *tmpprevious=new INVENTORY;
    INVENTORY *tmpnext=new INVENTORY;
    newnode->inventory_id=ID;
    newnode->next=NULL;
    
    long index;
    index=ID%size;
    struct INVENTORY *tmp=inventory_data.Inventory_hashtable[index];
    while(tmp!=NULL)
    {
        if(tmp->inventory_id==newnode->inventory_id)
        {
            break;
        }
        tmpprevious=tmp;
        tmp=tmp->next;
        tmpnext=tmp->next;
    }
    if(tmpprevious->inventory_id==0)
    {
        inventory_data.Inventory_hashtable[index]=tmp->next;
    }
    if(tmpnext==NULL)
    {
        tmpprevious->next=NULL;
    }
    if(tmpprevious!=NULL&&tmpnext!=NULL)
    {
        tmpprevious->next=tmpnext;
    }
}
void inventory::update_item()
{
    int i;
    long ID;
    string Newname;
    int Newrate=0;
    int Newquantity=0;
    cout<<"Enter the ID of the Product which you want to update"<<endl;
    cin>>ID;
    cout<<"There are Four characteristic of a product(i.e ID,Name,Rate,Quantity)."<<endl;
    cout<<"What do you want to update?"<<endl;
    cout<<"1.Name\n2.Rate\n3.Quantity"<<endl;
    cin>>i;
    switch(i)
    {
            case 1:
            {
                cout<<"Enter the new name of Product"<<endl;
                cin>>Newname;
                break;
            }
        case 2:
            {
                cout<<"Enter the new Rate of Product"<<endl;
                cin>>Newrate;
                break;
            }
        case 3:
            {
                cout<<"Enter the new quantity of Product"<<endl;
                cin>>Newquantity;
                break;
            }
    }
    long index=ID%size;
    struct INVENTORY *tmp=inventory_data.Inventory_hashtable[index];
    while(tmp->next!=NULL)
    {
        if(tmp->inventory_id==ID)
        {
            if(i==1)
            {
                tmp->name=Newname;
                break;
            }
            if(i==2)
            {
                tmp->rate=Newrate;
                break;
            }
            if(i==3)
            {
                tmp->quantity=Newquantity;
                break;
            }
        }
        tmp=tmp->next;
    }
    
}

void inventory::add_item()
{
    long ID;
    string name;
    int rate;
    int quantity;
    cout<<"Enter Product ID: "<<endl;
    cin>>ID;
    cout<<"Enter Name of the Product: "<<endl;
    cin>>name;
    cout<<"Enter Rate of Product: "<<endl;
    cin>>rate;
    cout<<"Enter Quantity of Product: "<<endl;
    cin>>quantity;
    
    INVENTORY *newnode=new INVENTORY;
    newnode->inventory_id=ID;
    newnode->name=name;
    newnode->rate=rate;
    newnode->quantity=quantity;
    newnode->next=NULL;
    
    long index,k=0;
    index=ID%size;
    if(inventory_data.Inventory_hashtable[index]==NULL||((inventory_data.Inventory_hashtable[index]->inventory_id)>(newnode->inventory_id)))
    {
        newnode->next=inventory_data.Inventory_hashtable[index];
        inventory_data.Inventory_hashtable[index]=newnode;
    }
    else
    {
        struct INVENTORY *tmp=inventory_data.Inventory_hashtable[index];
        while(tmp->next!=NULL)
        {
            if(((tmp->next)->inventory_id)<(newnode->inventory_id))
            {
                tmp=tmp->next;
            }
            else
            {
                if(((tmp->next)->inventory_id)>=(newnode->inventory_id))
                {
                    newnode->next=tmp->next;
                    tmp->next=newnode;
                    tmp=tmp->next;
                    k=1;
                    break;
                }
            }
        }
        if(tmp->next==NULL&&k==0)
        {
            tmp->next=newnode;
        }
    }
}
void inventory::gettotalnumber()
{
    int total=0;
    for(int j=0;j<size;j++)
    {
        struct INVENTORY *tmp=inventory_data.Inventory_hashtable[j];
        while(tmp)
        {
            total=total+(tmp->quantity);
            tmp=tmp->next;
        }
    }
    cout<<"\n\n Total number of Products in Inventory is: "<<total<<endl;
}
void print_inventory()
{
    for(int j=0;j<size;j++)
    {
        INVENTORY *tmp=inventory_data.Inventory_hashtable[j];
        while(tmp)
        {
            cout<<tmp->name<<" & ";
            tmp=tmp->next;
        }
        cout<<"\n";
    }
}
void print_customer()
{
    for(int j=0;j<size;j++)
    {
        CUSTOMER *tmp=customer_data.Customer_hashtable[j];
        while(tmp)
        {
            cout<<tmp->cust_ID<<" & ";
            tmp=tmp->next;
        }
        cout<<"\n";
    }
}
void print()
{
    for(int j=0;j<size;j++)
    {
        struct INVENTORY *tmp=inventory_data.Inventory_hashtable[j];
        cout<<"HASH TABLE"<<"["<<j<<"]";
        while(tmp)
        {
            cout<<"--"<<tmp->inventory_id;
            cout<<"--"<<tmp->name;
            cout<<"--"<<tmp->rate;
            cout<<"--"<<tmp->quantity;
            tmp=tmp->next;
        }
        cout<<"NULL";
    }
    cout<<endl;
}
int main()
{
    long INVENTORY_DATASET[100][4] =
    { {111100000002,2,110,20},{111100000001,1,100,20},{111100000003,3,120,20},{111100000004,4,130,20},{111100000005,5,140,20},{111100000006,6,150,20},{111100000007,7,160,20},{111100000008,8,170,20},{111100000009,9,180,20},{111100000010,10,190,20},{111100000021,21,300,21},{111100000012,12,210,20},{111100000013,13,220,20},{111100000014,14,230,20},{111100000015,15,240,20},{111100000016,16,250,20},{111100000017,17,260,20},{111100000018,18,270,20},{111100000019,19,280,20},{111100000020,20,290,20},
 {111100000011,11,200,20}
 ,{111100000022,22,310,20},{111100000023,23,320,20},{111100000024,24,330,20},{111100000025,25,340,20},{111100000026,26,350,20},{111100000027,27,360,20},{111100000028,28,370,20},{111100000029,29,380,20},{111100000030,30,390,20},
 {111100000031,31,400,20},{111100000032,32,410,20},{111100000033,33,420,20},{111100000034,34,430,20},{111100000035,35,440,20},{111100000036,36,450,20},{111100000037,37,460,20},{111100000038,38,470,20},{111100000039,39,480,20},{111100000040,40,490,20},
 {111100000041,41,500,20},{111100000042,42,510,20},{111100000043,43,520,20},{111100000044,44,530,20},{111100000045,45,540,20},{111100000046,46,550,20},{111100000047,47,560,20},{111100000048,48,570,20},{111100000049,49,580,20},{222200001111,50,590,20},
 {222200001114,51,600,20},{222200001117,52,610,20},{222200001120,53,620,20},{222200001123,54,630,20},{222200001126,55,640,20},{222200001129,56,650,20},{222200001132,57,660,20},{222200001135,58,670,20},{222200001138,59,680,20},{222200001141,60,690,20},
 {222200001144,61,700,20},{222200001147,62,710,20},{222200001150,63,720,20},{222200001153,64,730,20},{222200001156,65,740,20},{222200001159,66,750,20},{222200001162,67,760,20},{222200001165,68,770,20},{222200001168,69,780,20},{222200001171,70,790,20},
 {222200001174,71,800,20},{222200001177,72,810,20},{222200001180,73,820,20},{222200001183,74,830,20},{222200001186,75,840,20},{222200001189,76,850,20},{222200001192,77,860,20},{222200001195,78,870,20},{222200001198,79,880,20},{222200001201,80,890,20},
 {222200001204,81,900,20},{222200001207,82,910,20},{222200001210,83,920,20},{222200001213,84,930,20},{222200001216,85,940,20},{222200001219,86,950,20},{222200001222,87,960,20},{222200001225,88,970,20},{222200001228,89,980,20},{222200001231,90,990,20},
 {222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20},{222200001246,95,1040,20},{222200001249,96,1050,20},{222200001252,97,1060,20},{222200001255,98,1070,20},{222200001258,99,1080,20},{222200001261,100,1090,20},
 } ;
     
    
    long CUSTOMER_DATASET[100][3] = 
     {
     {9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},{9400000009,9,0},{9400000010,10,0},
     {9400000011,11,0},{9400000012,12,0},{9400000013,13,0},{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},{9400000020,20,0},
     {9400000021,21,0},{9400000022,22,0},{9400000023,23,0},{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},{9400000030,30,0},
     {9400000031,31,0},{9400000032,32,0},{9400000033,33,0},{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},{9400000040,40,0},
     {9400000041,41,0},{9400000042,42,0},{9400000043,43,0},{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},{9400000050,50,0},
     {9400000051,51,0},{9400000052,52,0},{9400000053,53,0},{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},{9400000060,60,0},
     {9400000061,61,0},{9400000062,62,0},{9400000063,63,0},{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},{9400000070,70,0},
     {9400000071,71,0},{9400000072,72,0},{9400000073,73,0},{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},{9400000080,80,0},
     {9400000081,81,0},{9400000082,82,0},{9400000083,83,0},{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},{9400000090,90,0},
     {9400000091,91,0},{9400000092,92,0},{9400000093,93,0},{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},{9400000100,100,0},
     } ;
    
    int j;
     for(j=0;j<100;j++)
     {
         INSERT_CUSTOMER_DATASET(CUSTOMER_DATASET[j][0],to_string(CUSTOMER_DATASET[j][1]),CUSTOMER_DATASET[j][2]);
     }
     cout<<endl;
     for(j=0;j<100;j++)
     {
         INSERT_INVENTORY_DATASET(INVENTORY_DATASET[j][0],to_string(INVENTORY_DATASET[j][1]),INVENTORY_DATASET[j][2],INVENTORY_DATASET[j][3]);     
     }
    
    cout<<"\n\t\t\t\tPROJECT ASSIGNMENT " ; 
    cout<<"\n\t\t\t\t-------------------"<<endl ;
  
    int a;
     cout<<"WELCOME : \n How can you like to go ahead?"<<endl ;
     cout<<" 1. Billing Person"<<endl ;
     cout<<" 2. Manager"<<endl ;
     cout<<" 3. Exit" ;
     cout << "\nPlease entrer your choice :- \n" ;
     cin>>a ;
    
    switch(a)
    {
        case 1:
            {
                int b ;
                cout<< "\nIf you are new customer than press else press any key. \n" ;
                cin>>b ;
                if(b==1)
                {
                    billing_data.add_customer(); 
                }
                long tid,cid;
                     cout<<"Enter your Transaction ID :  \n";
                         cin>>tid;
                     cout<<"Enter your Customer ID :  \n";
                     cin>>cid ;
                     billing_data.Transaction_ID=tid ;
                     billing_data.Customer_id=cid ;
                     
                billing_data.checkcustomer() ;
                     char ch ;
                     int c ;
                     ch='y';
                         cout << "\t\tMenu for Billing" ;
                         cout << "\n\t 1. To Buy Item " ;
                         cout << "\n\t 2. To Make Payment" ;
                         cout << "\n\t 3. To Cancel Item" ;
                         cout << "\n\t 4. Exit" ;
                         cout << "\n\tPlease enter your choice :- "<<endl ;
                    while (ch == 'y' || ch == 'Y')
                     {                         
                         cin>>c;
                         switch (c) 
                         {
                             case 1:
                             {
                                 billing_data.buy_item() ;
                                 break ;
                             }
                                 case 2:
                             {
                                 billing_data.update_points() ;
                                 billing_data.make_payment() ;
                                 break ;
                             }
                                 case 3:
                             {
                                 billing_data.cancel_item() ;
                                 break ;
                             }
                             default:
                                 break ;
                         }
                         cout<<"Are you want to continue(y/n)?"<<endl ;
                         cin>>ch ;
                     }
                     break;
                 }
            
            case 2:
                 {
                     int choice3 ;
                     cout << "\n\n\t\tAccess for Manager Only" ;
                     cout << "\n\t1. To Add Item" ;
                     cout << "\n\t2. To Remove Item" ;
                     cout << "\n\t3. To Update Item" ;
                     cout << "\n\t4. To Get Total number of products" ;
                     cout << "\n\t5. Exit" ;
                     cout << "\n\tPlease entrer your choice :- " ;
                     cin>>choice3 ;
                     switch (choice3)
                     {
                         case 1:
                         { 
                             manager.add_item() ;
                             break ;
                         }
                         case 2:
                         {
                             manager.delete_item() ;
                             break ;
                         }
                         case 3:
                         {
                             manager.update_item() ;
                             break ;
                         }
                         case 4:
                         {
                             manager.gettotalnumber() ;
                           break ;
                         }
                         case 5:
                         {
                             exit(0) ;
                         }
                         default:
                             break ;
                     }
                 }
            
        case 3:
            exit(0) ;      
            }
     cout<<"\n\n\t Thank You ."<<endl ;
    return 0;
}
/*Give this as an input to check the programme.
Press 1 for Billing Person OR 2 for Manager
If you press 1 then it goes to check for the existance of customer
Then it take your ID number as a Transaction ID and Customer ID
Then it ask you for billing menu to buy,delete and for making payment option.
And for option 2 you have access as a manager.
INPUT:
1
0
201901041
9400000041
1
111100000039
7
y
1
111100000021
20
y 
2
n
*/