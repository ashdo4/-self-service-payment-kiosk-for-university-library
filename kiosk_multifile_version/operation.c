#include<stdio.h>

extern int remaining_change, change_inv[],  change_give[];
extern int s;
extern float   fine,card_fee,book_fee, renew_fee;
static int deno[5]={500,200,100,50,20};



int discounts(){
    //d1 is the discount type
    int d1;
    float discount_factor = 1.0;

   printf("enter 1 if you are an undergraduate\nenter 2 if you are a postgraduate\nenter 3  for other\n");
   scanf("%d",&d1);
   if(d1==1){
    discount_factor=0.85;
    printf("Undergraduate discount applied.\n");
   }
   else if(d1==2){
    discount_factor=0.90;
    printf("Postgraduate discount applied.\n");
   }
   else if(d1==3){
    printf("No discount applied.\n");
   }
   else{
    printf("Invalid input.\n");
    return 0;
   }
    if (s == 1) fine *= discount_factor;
    else if (s == 2) book_fee *= discount_factor;
    else if (s == 3) renew_fee *= discount_factor;

   return 1;
}

int changes(int remaining_change,int change_inv[], int change_give[]){
    int deno[5]={500,200,100,50,20};

    // Clear previous exchange data
    for (int i = 0; i < 5; i++) {
            change_give[i]=0;
        }

    for (int i = 0; i < 5; i++) {
        if (remaining_change >= deno[i] && change_inv[i] > 0) {
           remaining_change -= deno[i];
            change_give[i]=1;
        }
    }
  
    
    if (remaining_change==0){
         for (int i = 0; i < 5; i++) {
            change_inv[i]-= change_give[i];
        }
        return 1;
    }
    return 0;
}



int handle_payment(){

    int cash_inserted=0;
    int change_due;
    float common_fee;
   
    if(s==2){
        common_fee=book_fee;
    }
    else if(s==3){
        common_fee=renew_fee;
    }
     else if(s==1){
        common_fee=fine;
     }
     else if(s==4){
        common_fee=card_fee;
     }

    printf("Insert money note (Accepted: 1000, 500, 200, 100): ");
    printf("Enter amuont of cash you inserted\n");
    scanf("%d",&cash_inserted);
   
    if (cash_inserted!= 1000 && cash_inserted != 500 && cash_inserted != 200 && cash_inserted != 100) {
        printf("Invalid note denomination.\n");
        return 0 ;
    }

    if (cash_inserted < common_fee ) {
        printf("Insufficient money inserted.\n");
        return 0;
    }
    
    change_due = cash_inserted - common_fee;

    if (changes(change_due, change_inv, change_give) == 1) {
        printf("Change returned: Rs. %d\n", change_due);

       if (cash_inserted == 500)       change_inv[0]++; 
        else if (cash_inserted == 200)  change_inv[1]++; 
        else if (cash_inserted == 100)  change_inv[2]++; 
        else if (cash_inserted == 50)   change_inv[3]++; 
        else if (cash_inserted == 20)   change_inv[4]++;

        return 1 ; // Exact payment
    }
    else {
         printf("Unable to Return Change. Your inserted note of Rs. %d has been returned.\n", cash_inserted);
        return 0 ;
    }
}
