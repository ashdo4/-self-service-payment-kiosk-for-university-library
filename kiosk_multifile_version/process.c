#include<stdio.h>

#define M_500 0
#define M_200 1
#define M_100 2
#define M_50 3
#define M_20 4

extern int discounts();

extern int b_slots, renewals, c_slots;
extern int s;
extern int books;
extern float fine, card_fee, renew_fee, book_fee;

int process(){
    int days=0;
   
    if(s==1){
        printf("enter the num of overdue days\n");
        scanf("%d",&days);
        if(days<0){
            printf("Invalid date\n");
            return 0;
        }
        else{
        fine=days*20;
        }
    }

    else if(s==2){
        printf("how many books do you want?(max 3)\n");
        scanf("%d",&books);
        if(books<1 || books>3){
            printf("Invalid book number. Transaction cancelled.\n");
            return 0 ;
        }
        else if(books> b_slots){
            printf("Service unavailable.No reservation slots available!\n");
            return 0;
        }
        else{
        book_fee=books*100;
        if (discounts()==0){
            return 0;
        }
       
        }
      
        }
    


    else if(s==3){
        if(renewals<=0){
            printf("Service unavailable.Membership renewal limit reached.\n");
            return 0 ;
        }
        else{
        renew_fee=500;
        if (discounts()==0){
            return 0;
        }
        }
    }


    else if(s==4){
        if(c_slots<=0){
            printf("Service Unavailable. No card replacement slots available!\n");
            return 0;
        }
        else {
        card_fee=250;
       
        }
        return 1;
    }


    else if(s==5){
        return 0 ;
    }

    else if(s<1 || s>5){
        printf("Invalid input\n");
        return 0 ;
    }

    return 1;
}
