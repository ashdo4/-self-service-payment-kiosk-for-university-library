#include<stdio.h>

#define UG 1
#define PG 2
#define NORMAL 3

#define M_500 0
#define M_200 1
#define M_100 2
#define M_50  3
#define M_20  4

int discounts(float *fee);
void menu(int *s);
int process(int s, float *fine, int *b_slots,int *renewals, int *c_slots, float *card_fee,float *book_fee, float *renew_fee,int *books);
int changes(int remaining_change,int change_inv[], int change_give[]);
int handle_payment(int s,float fine,float card_fee,float book_fee,float renew_fee,int change_inv[],int change_give[]);
void trans_display(int *b_slots,int *c_slots, int *renewals,int change_inv[]);
void daily_report(float fine,float card_fee, float renew_fee, float book_fee);

static int successful_trans=0;


int main(){
    int b_slots=10;
    int renewals=5;
    int c_slots=5;
    int change_inv[5]={5,10,20,20,50};
    int change_give[5] = {0, 0, 0, 0, 0};
    int remaining_change=0;
    float fine=0,card_fee=0,renew_fee=0,book_fee=0;
    int s;
    int books=0;
    

    printf("--- Welcome to University of Kelaniya Library Kiosk ---\n");

    while(1){
        menu(&s);
        
        if(s==5){
            break;
        }

    // 1. Create TEMPORARY variables for this specific transaction attempt
    float temp_fine = 0, temp_card_fee = 0, temp_renew_fee = 0, temp_book_fee = 0;
    int temp_b_slots = b_slots;
    int temp_renewals = renewals;
    int temp_c_slots = c_slots;

    int p_status=process(s, &temp_fine, &temp_b_slots, &temp_renewals, &temp_c_slots, &temp_card_fee, &temp_book_fee, &temp_renew_fee, &books);

        if(p_status==0){

            // Display the updated inventory status
        trans_display(&b_slots, &c_slots, &renewals, change_inv);
            continue;
        }
       if(s==3){
            temp_renewals=renewals-1;
        }
        else if (s==2){
            temp_b_slots = b_slots - books;
        }
        else if (s == 4) {
            temp_c_slots = c_slots - 1; 
        }

        if (handle_payment(s, temp_fine, temp_card_fee, temp_book_fee, temp_renew_fee, change_inv, change_give) == 1) {
        
        // TRANSACTION SUCCESSFUL. Now permanently commit the records
        fine += temp_fine;
        card_fee += temp_card_fee;
        renew_fee += temp_renew_fee;
        book_fee += temp_book_fee;

        b_slots = temp_b_slots;
        renewals = temp_renewals;
        c_slots = temp_c_slots;

       
    }

    else {
        // TRANSACTION FAILED
        printf("Transaction Failed.\n");
    }
    // Display the updated inventory status
        trans_display(&b_slots, &c_slots, &renewals, change_inv);
}
daily_report(fine, card_fee,  renew_fee,  book_fee);
   
}



void menu(int *s){
    printf("\n\nenter the service you want\n");
    printf("1 for Fine Payment\n");
    printf("2 for Book Reservation\n");
    printf("3 for Membership Renewal\n");
    printf("4 for Lost Library Card Replace\n");
    printf("5 for Exit\n");
    printf("\nenter your choice:");
    scanf("%d",s);
}

int process(int s, float *fine, int *b_slots,int *renewals, int *c_slots, float *card_fee, float *book_fee, float *renew_fee,int *books){
    int days=0;
   
    if(s==1){
        printf("enter the num of overdue days\n");
        scanf("%d",&days);
        if(days<0){
            printf("Invalid date\n");
            return 0;
        }
        else{
        *fine=days*20;
        }
    }

    else if(s==2){
        printf("how many books do you want?(max 3)\n");
        scanf("%d",books);
        if(*books<1 || *books>3){
            printf("Transaction canceled.Invalid book number\n");
            return 0 ;
        }
        else if(*books> *b_slots){
            printf("Service unavailable.No reservation slots available!\n");
            return 0;
        }
        else{
        (*book_fee)=(*books)*100;
        if (discounts(book_fee)==0){
            return 0;
        }
        
        }
      
        }
    


    else if(s==3){
        if(*renewals<=0){
            printf("Service unavailable.Membership renewal limit reached.\n");
            return 0 ;
        }
        else{
        *renew_fee=500;
        if (discounts(renew_fee)==0){
            return 0;
        }
        }
    }


    else if(s==4){
        if(*c_slots<=0){
            printf("Service Unavailable. No card replacement slots available!\n");
            return 0;
        }
        else {
       * card_fee=250;
       
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

int discounts(float *fee){
    //d1 is the discount type
    int d1;
   printf("enter 1 if you are an undergraduate\nenter 2 if you are a postgraduate\nenter 3  for other\n");
   scanf("%d",&d1);
   if(d1==1){
    *fee=(*fee)*0.85;
    printf("Undergraduate discount applied.\n");
   }
   else if(d1==2){
    *fee=(*fee)*0.90;
    printf("Postgraduate discount applied.\n");
   }
   else if(d1==3){
    printf("No discount applied.\n");
   }
   else{
    printf("Invalid input.\n");
    return 0;
   }
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



int handle_payment(int s,float fine,float card_fee,float book_fee,float renew_fee,int change_inv[],int change_give[]){

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
        successful_trans++;

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


void trans_display(int *b_slots,int *c_slots, int *renewals,int change_inv[]){
    printf("Remaining reservation slots   : %d\n",*b_slots);
    printf("Remaining card replacements   : %d\n",*c_slots);
    printf("Remaining renewals            : %d\n\n",*renewals);
    printf("  Rs. 500: %d | Rs. 200: %d | Rs. 100: %d | Rs. 50: %d | Rs. 20: %d\n",
           change_inv[M_500], change_inv[M_200], change_inv[M_100], change_inv[M_50], change_inv[M_20]);
           printf("=========================================\n");

}

void daily_report(float fine,float card_fee, float renew_fee, float book_fee){
    float total_fee=0;
    total_fee= fine + book_fee+ renew_fee+ card_fee;
    printf("\n\nDAILY REPORT\n"); 
    printf("\nNumber of successful transactions : %d\n\n",successful_trans);
    
    printf("Revenue  by service type\n");
    printf("Fine payments         : %.2f\n",fine);
    printf("Book Reservations     : %.2f\n",book_fee);
    printf("Membership Renewals   : %.2f\n",renew_fee);
    printf("Card Replacements     : %.2f\n",card_fee);
    printf("Total Revenue         : %.2f\n",total_fee);
    printf("=========================================\n");
    printf("=========================================\n");
    
}