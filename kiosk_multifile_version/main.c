#include<stdio.h>

void menu();
int process();
int handle_payment();
void trans_display();
void daily_report();

int successful_trans=0;
int books=0;
int b_slots=10;
int renewals=5;
int c_slots=5;
int change_inv[5]={5,10,20,20,50};
int change_give[5] = {0, 0, 0, 0, 0};
int remaining_change=0;
float fine=0,card_fee=0,renew_fee=0,book_fee=0;
int s;
float temp_fine = 0, temp_card_fee = 0, temp_renew_fee = 0, temp_book_fee = 0;


int main(){

    printf("--- Welcome to University of Kelaniya Library Kiosk ---\n");

    while(1){
        menu();
        
        if(s==5){
            break;
        }

    int p_status=process();

        if(p_status==0){
            // Display the updated inventory status
        trans_display();
            continue;
        }

        if (handle_payment() == 1) {
        
        // TRANSACTION SUCCESSFUL.
        if (s == 1) {
        temp_fine += fine; 
    }
         if(s==3){
            renewals=renewals-1;
           temp_renew_fee+= renew_fee;
        }
        else if (s==2){
            b_slots = b_slots - books;
           temp_book_fee+= book_fee;
        }
        else if (s == 4) {
            c_slots = c_slots - 1; 
           temp_card_fee += card_fee;
        }
         successful_trans++;
    }

    else {
        // TRANSACTION FAILED
        printf("Transaction Failed.\n");
    }
    // Display the updated inventory status
        trans_display();
}
daily_report();
   
}
